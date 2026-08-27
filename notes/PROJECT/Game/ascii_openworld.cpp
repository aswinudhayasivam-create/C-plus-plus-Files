#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// ====================== STRUCTS ======================
struct Item {
    string name;
    char symbol;
    int value;  // money or heal amount
    string desc;
};

struct Mission {
    string title;
    string desc;
    int target;
    int progress;
    bool completed;
    int reward;
};

// ====================== CLASSES ======================
class Entity {
protected:
    int x, y;
    char symbol;
public:
    Entity(int px, int py, char s) : x(px), y(py), symbol(s) {}
    virtual ~Entity() = default;
    int getX() const { return x; }
    int getY() const { return y; }
    char getSymbol() const { return symbol; }
    void setPos(int px, int py) { x = px; y = py; }
};

class Player : public Entity {
public:
    int health = 100;
    int money = 0;
    vector<Item> inventory;

    Player(int px, int py) : Entity(px, py, '@') {}

    void move(int dx, int dy, const vector<string>& grid) {
        int nx = x + dx;
        int ny = y + dy;
        if (ny >= 0 && ny < (int)grid.size() && nx >= 0 && nx < (int)grid[0].size()) {
            if (grid[ny][nx] != '#') {
                x = nx;
                y = ny;
            }
        }
    }

    void addItem(const Item& it) {
        inventory.push_back(it);
        cout << "\nYou picked up: " << it.name << " (" << it.desc << ")\n";
    }
};

class Enemy : public Entity {
public:
    int health = 40;
    Enemy(int px, int py) : Entity(px, py, 'E') {}
};

// ====================== GAME CLASS ======================
class Game {
private:
    vector<string> grid;
    Player player;
    vector<Enemy> enemies;
    vector<Item> itemsOnMap;
    vector<Mission> missions;
    int enemiesKilled = 0;
    int itemsCollected = 0;

    void initMap() {
        grid = {
            "####################",
            "#..................#",
            "#..####............#",
            "#..#..#..####......#",
            "#..#..#..#..#......#",
            "#..####..#..#......#",
            "#........#..#......#",
            "#........####......#",
            "#..................#",
            "#..##########......#",
            "#..#........#......#",
            "#..#........#......#",
            "#..##########......#",
            "#..................#",
            "####################"
        };
    }

    void spawnEntities() {
        // Spawn enemies
        enemies.clear();
        enemies.emplace_back(5, 3);
        enemies.emplace_back(12, 5);
        enemies.emplace_back(8, 10);
        enemies.emplace_back(15, 8);

        // Spawn items
        itemsOnMap.clear();
        itemsOnMap.push_back({"Gold Coin", '$', 25, "Money +25"});
        itemsOnMap.push_back({"Health Pack", 'H', 30, "Heal +30"});
        itemsOnMap.push_back({"Gold Coin", '$', 40, "Money +40"});
        itemsOnMap.push_back({"Health Pack", 'H', 25, "Heal +25"});

        // Place them at random valid positions (simple fixed for demo)
        // In real code you could randomize, here fixed for reproducibility
    }

    void initMissions() {
        missions = {
            {"Gang Cleanup", "Kill 3 enemies", 3, 0, false, 150},
            {"Treasure Hunt", "Collect 3 items", 3, 0, false, 100}
        };
    }

public:
    Game() : player(3, 3) {
        srand(static_cast<unsigned>(time(nullptr)));
        initMap();
        spawnEntities();
        initMissions();
    }

    bool isValid(int nx, int ny) const {
        if (ny < 0 || ny >= (int)grid.size() || nx < 0 || nx >= (int)grid[0].size())
            return false;
        return grid[ny][nx] != '#';
    }

    void render() {
        system("cls");
        vector<string> display = grid;

        // Place player
        display[player.getY()][player.getX()] = player.getSymbol();

        // Place enemies
        for (const auto& e : enemies) {
            if (e.health > 0) {
                display[e.getY()][e.getX()] = e.getSymbol();
            }
        }

        // Place items
        for (const auto& it : itemsOnMap) {
            // For simplicity, we don't store positions here – in full version you'd store coords
            // Demo: fixed positions for visible items
        }
        // Manual item placement for demo
        if (!itemsOnMap.empty()) display[4][8] = '$';
        if (itemsOnMap.size() > 1) display[7][12] = 'H';
        if (itemsOnMap.size() > 2) display[10][5] = '$';
        if (itemsOnMap.size() > 3) display[12][15] = 'H';

        // Print map
        for (const auto& row : display) {
            cout << row << '\n';
        }

        // HUD
        cout << "\n=== ASCII OPEN WORLD ===\n";
        cout << "Health: " << player.health << "   Money: $" << player.money << "\n";
        cout << "Inventory: " << player.inventory.size() << " items\n";
        cout << "Enemies killed: " << enemiesKilled << " / 3\n";
        cout << "Items collected: " << itemsCollected << " / 3\n\n";

        cout << "Missions:\n";
        for (const auto& m : missions) {
            cout << " - " << m.title << ": " << m.progress << "/" << m.target 
                 << (m.completed ? " (DONE)" : "") << "\n";
        }

        cout << "\nControls: WASD = Move | I = Inventory | Q = Quit\n";
    }

    void checkPickup() {
        // Simple position-based pickup (demo positions)
        int px = player.getX(), py = player.getY();

        if (py == 4 && px == 8 && !itemsOnMap.empty()) {
            player.addItem(itemsOnMap[0]);
            itemsOnMap.erase(itemsOnMap.begin());
            itemsCollected++;
            missions[1].progress = itemsCollected;
            if (missions[1].progress >= missions[1].target) missions[1].completed = true;
        }
        else if (py == 7 && px == 12 && itemsOnMap.size() > 1) {
            player.addItem(itemsOnMap[1]);
            itemsOnMap.erase(itemsOnMap.begin() + 1);
            itemsCollected++;
            missions[1].progress = itemsCollected;
            if (missions[1].progress >= missions[1].target) missions[1].completed = true;
        }
        // Add more positions if needed
    }

    void handleCombat() {
        int px = player.getX(), py = player.getY();
        for (auto& e : enemies) {
            if (e.health > 0 && e.getX() == px && e.getY() == py) {
                cout << "\n=== COMBAT! ===\nYou encountered an enemy!\n";
                cout << "1. Attack   2. Flee\nChoice: ";
                char choice;
                cin >> choice;
                if (choice == '1') {
                    e.health -= 25;
                    cout << "You hit the enemy for 25 damage!\n";
                    if (e.health <= 0) {
                        cout << "Enemy defeated!\n";
                        enemiesKilled++;
                        missions[0].progress = enemiesKilled;
                        if (missions[0].progress >= missions[0].target) missions[0].completed = true;
                        player.money += 30;
                    } else {
                        player.health -= 15;
                        cout << "Enemy hits you back for 15 damage!\n";
                    }
                } else {
                    cout << "You fled!\n";
                    player.move(-1, 0, grid); // push back one step
                }
                return;
            }
        }
    }

    void showInventory() {
        system("cls");
        cout << "=== INVENTORY ===\n";
        if (player.inventory.empty()) {
            cout << "Empty!\n";
        } else {
            for (size_t i = 0; i < player.inventory.size(); ++i) {
                cout << i+1 << ". " << player.inventory[i].name 
                     << " (" << player.inventory[i].desc << ")\n";
            }
        }
        cout << "\nPress any key to return...";
        _getch();
    }

    void update() {
        checkPickup();
        handleCombat();

        // Check win condition (simple)
        if (missions[0].completed && missions[1].completed) {
            cout << "\n\n=== YOU WIN! All missions completed! ===\n";
            cout << "Final Money: $" << player.money << "\n";
            cout << "Press any key to exit...";
            _getch();
            exit(0);
        }
    }

    bool run() {
        while (true) {
            render();

            if (player.health <= 0) {
                cout << "\n=== GAME OVER === You died!\n";
                return false;
            }

            if (!_kbhit()) {
                // Small delay for smooth feel
                for (int i = 0; i < 8000000; ++i); // crude delay
                continue;
            }

            char key = _getch();
            int dx = 0, dy = 0;

            switch (key) {
                case 'w': case 'W': dy = -1; break;
                case 's': case 'S': dy = 1;  break;
                case 'a': case 'A': dx = -1; break;
                case 'd': case 'D': dx = 1;  break;
                case 'i': case 'I': showInventory(); continue;
                case 'q': case 'Q': 
                    cout << "\nThanks for playing!\n";
                    return true;
            }

            if (dx != 0 || dy != 0) {
                player.move(dx, dy, grid);
                update();
            }
        }
    }
};

// ====================== MAIN ======================
int main() {
    cout << "Starting ASCII Open World Adventure...\n";
    cout << "Press any key to begin...";
    _getch();

    Game game;
    game.run();

    return 0;
}