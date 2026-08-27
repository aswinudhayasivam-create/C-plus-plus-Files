#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

// ---------------- USER ----------------
class User {
public:
    string username, password;

    void signup() {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        ofstream file("users.txt", ios::app);
        file << username << " " << password << endl;
        file.close();

        cout << "Signup successful!\n";
    }

    bool login() {
        string u, p;
        cout << "Enter username: ";
        cin >> u;
        cout << "Enter password: ";
        cin >> p;

        ifstream file("users.txt");
        string fu, fp;

        while (file >> fu >> fp) {
            if (fu == u && fp == p) {
                username = u;
                cout << "Login successful!\n";
                return true;
            }
        }
        cout << "Invalid login!\n";
        return false;
    }
};

// ---------------- FOOD ----------------
class Food {
public:
    string name;
    int price;

    Food(string n, int p) {
        name = n;
        price = p;
    }
};

// ---------------- RESTAURANT ----------------
class Restaurant {
public:
    string name;
    vector<Food> menu;

    Restaurant(string n) {
        name = n;
    }

    void addFood(string n, int p) {
        menu.push_back(Food(n, p));
    }

    void showMenu() {
        cout << "\nMenu of " << name << ":\n";
        for (int i = 0; i < menu.size(); i++) {
            cout << i + 1 << ". " << menu[i].name 
                 << " - Rs." << menu[i].price << endl;
        }
    }
};

// ---------------- CART ----------------
class Cart {
public:
    vector<Food> items;

    void add(Food f) {
        items.push_back(f);
        cout << f.name << " added!\n";
    }

    int total() {
        int sum = 0;
        for (auto &i : items) sum += i.price;
        return sum;
    }

    void show() {
        cout << "\n--- CART ---\n";
        for (auto &i : items)
            cout << i.name << " - Rs." << i.price << endl;

        cout << "Total: Rs." << total() << endl;
    }

    string getTime() {
        time_t now = time(0);
        return ctime(&now);
    }

    void checkout(string username) {
        int payChoice;
        cout << "\nSelect Payment:\n1. Cash\n2. Card\nChoice: ";
        cin >> payChoice;

        string payment = (payChoice == 1) ? "Cash" : "Card";

        // Simulated delivery stages
        vector<string> status = {
            "Order Placed",
            "Preparing",
            "Out for Delivery",
            "Delivered"
        };

        ofstream file("orders.txt", ios::app);

        file << "User: " << username << endl;
        file << "Time: " << getTime();
        file << "Items:\n";

        for (auto &i : items)
            file << i.name << " - Rs." << i.price << endl;

        file << "Total: Rs." << total() << endl;
        file << "Payment: " << payment << endl;
        file << "Status: Delivered\n";
        file << "----------------------\n";

        file.close();

        // Simulate tracking
        cout << "\nTracking Order...\n";
        for (auto &s : status) {
            cout << s << endl;
        }

        cout << "\n✅ Order Delivered Successfully!\n";
        items.clear();
    }
};

// ---------------- MAIN ----------------
int main() {
    User user;
    int ch;

    cout << "1. Signup\n2. Login\nChoice: ";
    cin >> ch;

    if (ch == 1) user.signup();
    if (!user.login()) return 0;

    vector<Restaurant> restaurants;

    Restaurant r1("Pizza Hub");
    r1.addFood("Margherita", 200);
    r1.addFood("Farmhouse", 300);

    Restaurant r2("Burger Point");
    r2.addFood("Veg Burger", 100);
    r2.addFood("Cheese Burger", 150);

    restaurants.push_back(r1);
    restaurants.push_back(r2);

    Cart cart;
    int choice;

    while (true) {
        cout << "\n===== SWIGGY ULTIMATE =====\n";
        cout << "1. Restaurants\n2. Cart\n3. Checkout\n4. Order History\n5. Exit\n";
        cin >> choice;

        if (choice == 1) {
            for (int i = 0; i < restaurants.size(); i++)
                cout << i + 1 << ". " << restaurants[i].name << endl;

            int r;
            cin >> r;

            if (r > 0 && r <= restaurants.size()) {
                Restaurant &res = restaurants[r - 1];
                res.showMenu();

                int f;
                cin >> f;

                if (f > 0 && f <= res.menu.size())
                    cart.add(res.menu[f - 1]);
            }

        } else if (choice == 2) {
            cart.show();

        } else if (choice == 3) {
            cart.show();
            cart.checkout(user.username);

        } else if (choice == 4) {
            ifstream file("orders.txt");
            string line;
            cout << "\n--- HISTORY ---\n";
            while (getline(file, line))
                cout << line << endl;

        } else if (choice == 5) {
            break;
        }
    }

    return 0;
}