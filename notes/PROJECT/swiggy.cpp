#include <iostream>
#include <vector>
using namespace std;

// Food Item
class Food {
public:
    string name;
    int price;

    Food(string n, int p) {
        name = n;
        price = p;
    }
};

// Restaurant
class Restaurant {
public:
    string name;
    vector<Food> menu;

    Restaurant(string n) {
        name = n;
    }

    void addFood(string name, int price) {
        menu.push_back(Food(name, price));
    }

    void displayMenu() {
        cout << "\nMenu of " << name << ":\n";
        for (int i = 0; i < menu.size(); i++) {
            cout << i + 1 << ". " << menu[i].name 
                 << " - Rs." << menu[i].price << endl;
        }
    }
};

// Cart
class Cart {
public:
    vector<Food> items;

    void addToCart(Food f) {
        items.push_back(f);
        cout << f.name << " added to cart!\n";
    }

    int getTotal() {
        int total = 0;
        for (auto &i : items) {
            total += i.price;
        }
        return total;
    }

    void showCart() {
        cout << "\nYour Cart:\n";
        for (auto &i : items) {
            cout << i.name << " - Rs." << i.price << endl;
        }
        cout << "Total: Rs." << getTotal() << endl;
    }
};

// Main App
int main() {
    vector<Restaurant> restaurants;

    // Sample Data
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
        cout << "\n===== SWIGGY CLONE =====\n";
        cout << "1. View Restaurants\n";
        cout << "2. View Cart\n";
        cout << "3. Checkout\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\nRestaurants:\n";
            for (int i = 0; i < restaurants.size(); i++) {
                cout << i + 1 << ". " << restaurants[i].name << endl;
            }

            int rChoice;
            cout << "Select restaurant: ";
            cin >> rChoice;

            if (rChoice > 0 && rChoice <= restaurants.size()) {
                Restaurant &r = restaurants[rChoice - 1];
                r.displayMenu();

                int fChoice;
                cout << "Select item to add to cart: ";
                cin >> fChoice;

                if (fChoice > 0 && fChoice <= r.menu.size()) {
                    cart.addToCart(r.menu[fChoice - 1]);
                }
            }

        } else if (choice == 2) {
            cart.showCart();

        } else if (choice == 3) {
            cart.showCart();
            cout << "\nOrder placed successfully!\n";
            cart.items.clear();

        } else if (choice == 4) {
            break;
        }
    }

    return 0;
}