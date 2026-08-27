#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// ANSI Color Codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

// ====================== STRUCTS ======================
struct Item {
    string name;
    char symbol;
    int value;
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
    int getX() const { return x; }
    int getY() const { return y; }
    char getSymbol() const { return symbol; }
};

class Player : public Entity {
public:
    int health = 100;
    int money = 0;
    vector<Item> inventory;

    Player(int px, int py) : Entity(px, py, '@') {}

    void move(int dx, int dy, const vector<string>& grid) {
        int nx = x + dx, ny = y + dy;
        if (ny >= 0 && ny < (int)grid.size() && nx >= 0 && nx < (int)grid[0].size()) {
            if (grid[ny][nx] != '#') {
                x = nx; y = ny;
            }
        }
    }
};

class Enemy : public Entity {
public:
    int health = 45;
    Enemy(int px, int py) : Entity(px, py, 'E') {}
};

// ====================== GAME CLASS ======================
class Game {
private:
    vector<string> grid;
    Player player;
    vector<Enemy> enemies;
    vector<Item> worldItems;   // items available to pick
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
        enemies = { Enemy(5,3), Enemy(12,5), Enemy(8,10), Enemy(15,8) };
        worldItems = {
            {"Gold Coin", '$', 25, "Money +25"},
            {"Health Pack", 'H', 30, "Heal +30"},
            {"Gold Coin", '$', 40, "Money +40"},
            {"Health Pack", 'H', 25, "Heal +25"}
        };
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

        // Place items at fixed nice positions
        if (!worldItems.empty())      display[4][8]  = '$';
        if (worldItems.size() > 1)    display[7][12] = 'H';
        if (worldItems.size() > 2)    display[10][5] = '$';
        if (worldItems.size() > 3)    display[12][15]= 'H';

        // Print colored map
        for (int i = 0; i < (int)display.size(); ++i) {
            for (char c : display[i]) {
                if (c == '@')      cout << CYAN << BOLD << '@' << RESET;
                else if (c == 'E') cout << RED << BOLD << 'E' << RESET;
                else if (c == '$') cout << YELLOW << '$' << RESET;
                else if (c == 'H') cout << GREEN << 'H' << RESET;
                else if (c == '#') cout << "\033[90m#\033[0m";   // dark gray walls
                else if (c == '.') cout << GREEN << "." << RESET;
                else cout << c;
            }
            cout << '\n';
        }

        // HUD
        cout << "\n" << BOLD << "=== ASCII OPEN WORLD ADVENTURE ===" << RESET << "\n";
        cout << "Health: " << GREEN << player.health << RESET 
             << "   Money: " << YELLOW << "$" << player.money << RESET << "\n";
        cout << "Inventory: " << player.inventory.size() << " items\n";
        cout << "Enemies killed: " << enemiesKilled << "/3\n";
        cout << "Items collected: " << itemsCollected << "/3\n\n";

        cout << "Missions:\n";
        for (const auto& m : missions) {
            cout << " • " << m.title << ": " << m.progress << "/" << m.target 
                 << (m.completed ? " " GREEN "(COMPLETED)" RESET : "") << "\n";
        }

        cout << "\n" << BOLD << "Controls:" << RESET 
             << " WASD = Move | I = Inventory | Q = Quit\n";
    }

    void checkPickup() {
        int px = player.getX(), py = player.getY();

        if (py == 4 && px == 8 && !worldItems.empty()) {
            player.addItem(worldItems[0]);   // we'll define addItem below
            worldItems.erase(worldItems.begin());
            itemsCollected++;
            missions[1].progress = itemsCollected;
            if (missions[1].progress >= 3) missions[1].completed = true;
        }
        else if (py == 7 && px == 12 && worldItems.size() >= 2) {
            player.addItem(worldItems[1]);
            worldItems.erase(worldItems.begin() + 1);
            itemsCollected++;
            missions[1].progress = itemsCollected;
            if (missions[1].progress >= 3) missions[1].completed = true;
        }
        else if (py == 10 && px == 5 && worldItems.size() >= 3) {
            player.addItem(worldItems[2]);
            worldItems.erase(worldItems.begin() + 2);
            itemsCollected++;
            missions[1].progress = itemsCollected;
            if (missions[1].progress >= 3) missions[1].completed = true;
        }
        else if (py == 12 && px == 15 && !worldItems.empty()) {
            player.addItem(worldItems.back());
            worldItems.pop_back();
            itemsCollected++;
            missions[1].progress = itemsCollected;
            if (missions[1].progress >= 3) missions[1].completed = true;
        }
    }

    void handleCombat() {
        int px = player.getX(), py = player.getY();
        for (auto& e : enemies) {
            if (e.health > 0 && e.getX() == px && e.getY() == py) {
                cout << "\n" << RED << "=== COMBAT! ===" << RESET << "\n";
                cout << "1. Attack   2. Run away\nChoice: ";
                char ch = _getch();
                cout << ch << "\n";

                if (ch == '1' || ch == '1') {
                    e.health -= 30;
                    cout << GREEN << "You hit for 30 damage!" << RESET << "\n";
                    if (e.health <= 0) {
                        cout << GREEN << "Enemy defeated!" << RESET << "\n";
                        enemiesKilled++;
                        missions[0].progress = enemiesKilled;
                        if (missions[0].progress >= 3) missions[0].completed = true;
                        player.money += 35;
                    } else {
                        player.health -= 18;
                        cout << RED << "Enemy hits you for 18 damage!" << RESET << "\n";
                    }
                } else {
                    cout << "You escaped!\n";
                    player.move(-1, 0, grid);  // push back
                }
                return;
            }
        }
    }

    void showInventory() {
        system("cls");
        cout << BOLD << "=== INVENTORY ===" << RESET << "\n";
        if (player.inventory.empty()) {
            cout << "Your inventory is empty.\n";
        } else {
            for (size_t i = 0; i < player.inventory.size(); ++i) {
                cout << i+1 << ". " << player.inventory[i].name 
                     << " (" << player.inventory[i].desc << ")\n";
            }
        }
        cout << "\nPress any key to return...";
        _getch();
    }

    bool run() {
        while (true) {
            render();

            if (player.health <= 0) {
                cout << "\n" << RED << "=== GAME OVER === You have died!" << RESET << "\n";
                _getch();
                return false;
            }

            if (missions[0].completed && missions[1].completed) {
                cout << "\n" << GREEN << BOLD << "=== YOU WIN! ===\nAll missions completed!" << RESET << "\n";
                cout << "Final Money: $" << player.money << "\n";
                _getch();
                return true;
            }

            char key = _getch();   // wait for key press (no busy loop)

            int dx = 0, dy = 0;
            switch (key) {
                case 'w': case 'W': dy = -1; break;
                case 's': case 'S': dy =  1; break;
                case 'a': case 'A': dx = -1; break;
                case 'd': case 'D': dx =  1; break;
                case 'i': case 'I': showInventory(); continue;
                case 'q': case 'Q':
                    cout << "\nThanks for playing!\n";
                    return true;
            }

            if (dx || dy) {
                player.move(dx, dy, grid);
                checkPickup();
                handleCombat();
            }
        }
    }
};

// Add this inside Player class (or add it manually)
void Player::addItem(const Item& it) {
    inventory.push_back(it);
    cout << GREEN << "\nPicked up: " << it.name << " (" << it.desc << ")" << RESET << "\n";
}

// ====================== MAIN ======================
int main() {
    cout << "Starting ASCII Open World Adventure...\nPress any key to begin... ";
    _getch();

    Game game;
    game.run();

    return 0;
}