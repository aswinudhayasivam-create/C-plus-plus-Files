#include <iostream>
#include <string>
using namespace std;

// ---------------- PLAYER CLASS ----------------
class Player {
private:
    int x, y;
    int health;
    string inventory[10];
    int itemCount;

public:
    Player() {
        x = 1;
        y = 1;
        health = 100;
        itemCount = 0;
    }

    int getX() { return x; }
    int getY() { return y; }
    int getHealth() { return health; }

    void setPosition(int nx, int ny) {
        x = nx;
        y = ny;
    }

    void move(char input) {
        if (input == 'w') x--;
        else if (input == 's') x++;
        else if (input == 'a') y--;
        else if (input == 'd') y++;
    }

    void takeDamage(int dmg) {
        health -= dmg;
    }

    void heal(int val) {
        health += val;
        if (health > 100) health = 100;
    }

    void addItem(string item) {
        if (itemCount < 10) {
            inventory[itemCount++] = item;
        }
    }

    void showInventory() {
        cout << "\nInventory:\n";
        if (itemCount == 0) {
            cout << "Empty\n";
            return;
        }
        for (int i = 0; i < itemCount; i++) {
            cout << "- " << inventory[i] << endl;
        }
    }
};

// ---------------- ENEMY CLASS ----------------
class Enemy {
private:
    int x, y;
    int health;
    bool alive;

public:
    Enemy() {
        x = 3;
        y = 5;
        health = 50;
        alive = true;
    }

    int getX() { return x; }
    int getY() { return y; }
    bool isAlive() { return alive; }

    void takeDamage(int dmg) {
        health -= dmg;
        if (health <= 0) {
            alive = false;
            cout << "Enemy defeated!\n";
        }
    }

    void attack(Player &p) {
        cout << "Enemy attacks you! (-10 HP)\n";
        p.takeDamage(10);
    }
};

// ---------------- MAP CLASS ----------------
class Map {
private:
    char grid[10][10];

public:
    Map() {
        // Initialize map
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (i == 0 || j == 0 || i == 9 || j == 9)
                    grid[i][j] = '#';
                else
                    grid[i][j] = ' ';
            }
        }

        grid[2][3] = 'I'; // item
        grid[5][7] = 'M'; // mission
    }

    void display(Player &p, Enemy &e) {
        system("cls"); // use "clear" for Linux/Mac

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (i == p.getX() && j == p.getY())
                    cout << 'P';
                else if (e.isAlive() && i == e.getX() && j == e.getY())
                    cout << 'E';
                else
                    cout << grid[i][j];
            }
            cout << endl;
        }

        cout << "\nHealth: " << p.getHealth() << endl;
    }

    char getCell(int x, int y) {
        return grid[x][y];
    }

    void clearCell(int x, int y) {
        grid[x][y] = ' ';
    }
};

// ---------------- GAME CLASS ----------------
class Game {
private:
    Player player;
    Enemy enemy;
    Map map;
    bool running;

public:
    Game() {
        running = true;
    }

    void handleInput(char input) {
        int oldX = player.getX();
        int oldY = player.getY();

        player.move(input);

        int newX = player.getX();
        int newY = player.getY();

        char cell = map.getCell(newX, newY);

        // Collision with wall
        if (cell == '#') {
            player.setPosition(oldX, oldY);
        }

        // Item pickup
        else if (cell == 'I') {
            cout << "You found a potion! (+20 HP)\n";
            player.heal(20);
            player.addItem("Potion");
            map.clearCell(newX, newY);
        }

        // Mission
        else if (cell == 'M') {
            cout << "Mission Completed!\n";
            running = false;
        }

        // Enemy encounter
        if (enemy.isAlive() &&
            newX == enemy.getX() && newY == enemy.getY()) {

            cout << "Fight Started!\n";

            while (enemy.isAlive() && player.getHealth() > 0) {
                enemy.takeDamage(15);
                if (enemy.isAlive())
                    enemy.attack(player);
            }
        }
    }

    void run() {
        char input;

        while (running && player.getHealth() > 0) {
            map.display(player, enemy);

            cout << "\nMove (W/A/S/D), I = Inventory, Q = Quit: ";
            cin >> input;

            if (input == 'q') break;

            if (input == 'i') {
                player.showInventory();
                system("pause");
                continue;
            }

            handleInput(tolower(input));
        }

        if (player.getHealth() <= 0)
            cout << "\nGame Over!\n";
        else
            cout << "\nThanks for playing!\n";
    }
};

// ---------------- MAIN ----------------
int main() {
    Game game;
    game.run();
    return 0;
}