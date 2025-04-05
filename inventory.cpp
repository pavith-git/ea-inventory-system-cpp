#include <iostream>
#include <string>
#include <utility>
#include <climits> 

class Item {
private:
    std::string name;
    int quantity;
    float price;

public:
    Item(std::string name, int quantity, float price)
        : name{std::move(name)}, quantity{quantity}, price{price} {}

    std::string get_name() const {
        return name;
    }

    int get_quantity() const {
        return quantity;
    }

    void set_quantity(int new_quantity) {
        quantity = new_quantity;
    }

    float get_price() const {
        return price;
    }

    bool is_match(const std::string &other) {
        return name == other;
    }
};

class Inventory {
private:
    Item *items[20];
    float total_money;
    int item_count;

    static void display_data(Item &item) {
        std::cout << "\nItem name: " << item.get_name();
        std::cout << "\nQuantity: " << item.get_quantity();
        std::cout << "\nPrice: " << item.get_price();
    }

public:
    Inventory()
        : items{}, total_money{0}, item_count{0} {}

    void add_item() {
        std::string name;
        int quantity;
        float price;

        std::cin.ignore();
        std::cout << "\nEnter item name: ";
        std::cin >> name;
        std::cout << "Enter quantity: ";
        std::cin >> quantity;
        std::cout << "Enter price: ";
        std::cin >> price;

        items[item_count] = new Item(name, quantity, price);
        item_count++;
    }

    void remove_item() {
        std::string name;
        int input_quantity;

        std::cout << "Enter item name to sell: ";
        std::cin >> name;
        std::cout << "Enter quantity to sell: ";
        std::cin >> input_quantity;

        for (int i = 0; i < item_count; ++i) {
            if (items[i]->get_name() == name) {
                int current_quantity = items[i]->get_quantity();

                if (input_quantity > current_quantity) {
                    std::cout << "Not enough quantity available.\n";
                    return;
                }

                int new_quantity = current_quantity - input_quantity;
                items[i]->set_quantity(new_quantity);

                int money_earned = input_quantity * items[i]->get_price();
                total_money += money_earned;

                std::cout << "Items sold. Money received: " << money_earned << "\n";

                if (new_quantity == 0) {
                    delete items[i];
                    for (int j = i; j < item_count - 1; ++j) {
                        items[j] = items[j + 1];
                    }
                    item_count--;
                    std::cout << "Item removed from inventory (quantity is 0).\n";
                }

                return;
            }
        }

        std::cout << "Item not found in inventory.\n";
    }

    void list_items() {
        if (item_count == 0) {
            std::cout << "\nInventory is empty.";
            return;
        }

        std::cout << "\nCurrent Inventory:";
        for (int i = 0; i < item_count; i++) {
            display_data(*items[i]);
            std::cout << "\n";
        }

        std::cout << "Total Money Earned: " << total_money << "\n";
    }
};

int main() {
    int choice;
    Inventory inventory_system;
    std::cout << "Welcome to the inventory!";

    while (1) {
        std::cout << "\n\nMENU\n"
                  << "1. Add new item\n"
                  << "2. Sell item\n"
                  << "3. List items\n"
                  << "4. Exit\n\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                inventory_system.add_item();
                break;

            case 2:
                inventory_system.remove_item();
                break;

            case 3:
                inventory_system.list_items();
                break;

            case 4:
                exit(0);

            default:
                std::cout << "\nInvalid choice entered";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                break;
        }
    }
}
