#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>


using namespace std;

class Animal {
private:
    string species;
    string breed;
    double price;
    int quantity;
public:
    Animal(string species, string breed, double price, int quantity)
        : species(species), breed(breed), price(price), quantity(quantity) {}

    string getSpecies() const { return species; }
    string getBreed() const { return breed; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }
    void setPrice(double newPrice) { price = newPrice; }
};


class Feed {
private:
    string name;
    string suitableFor;
    double price;
    int quantity;
public:
    Feed(string name, string suitableFor, double price, int quantity)
        : name(name), suitableFor(suitableFor), price(price), quantity(quantity) {}

    string getName() const { return name; }
    string getSuitableFor() const { return suitableFor; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }
    void setPrice(double newPrice) { price = newPrice; }
};


class PetShop {
private:
    vector<Animal> animals;
    vector<Feed> feeds;
    vector<string> salesHistory;

public:
    void addProduct(const Animal& animal) { animals.push_back(animal); }
    void addProduct(const Feed& feed) { feeds.push_back(feed); }
    void removeProduct(string productName);
    void showProducts() const;
    void sellProduct(string productName, int quantity);
    void showSalesHistory() const;
    void updateProduct(string productName, double newPrice, int newQuantity);
    void showInventoryReport() const;
    void findProductByName(string productName) const;
    void findMostExpensiveProduct() const;
};


void PetShop::removeProduct(string productName) {
    for (auto it = animals.begin(); it != animals.end(); ++it) {
        if (it->getSpecies() == productName) {
            animals.erase(it);
            return;
        }
    }
    for (auto it = feeds.begin(); it != feeds.end(); ++it) {
        if (it->getName() == productName) {
            feeds.erase(it);
            return;
        }
    }
    cout << "Товар не найден!" << endl;
}

void PetShop::findProductByName(string productName) const {
    bool found = false;
    for (const auto& animal : animals) {
        if (animal.getSpecies() == productName || animal.getBreed() == productName) {
            cout << "Животное найдено:\n";
            cout << animal.getSpecies() << ": " << animal.getBreed() << "\nЦена: " << animal.getPrice()
                << "\nВ наличии: " << animal.getQuantity() << endl;
            found = true;
        }
    }
    for (const auto& feed : feeds) {
        if (feed.getName() == productName) {
            cout << "Корм найден:\n";
            cout << feed.getName() << " - Подходит для: " << feed.getSuitableFor() << "\nЦена: " << feed.getPrice()
                << " \nВ наличии: " << feed.getQuantity() << endl;
            found = true;
        }
    }
    if (!found)
        cout << "Продукт не найден!" << endl;
}

void PetShop::showProducts() const {

    cout << "Животные в наличии:" << endl;
    for (const auto& animal : animals) {
        cout << animal.getSpecies() << ": " << animal.getBreed() << "\nЦена: " << animal.getPrice()
            << "\nВ наличии: " << animal.getQuantity() << endl;
    }
    cout << endl;
    cout << "Корм в наличии:" << endl;
    for (const auto& feed : feeds) {
        cout << feed.getName() << " - Подходит для: " << feed.getSuitableFor() << "\nЦена: " << feed.getPrice()
            << " \nВ наличии: " << feed.getQuantity() << endl;
    }
    cout << endl;

}

void PetShop::sellProduct(string productName, int quantity) {
    for (auto& animal : animals) {
        if (animal.getSpecies() == productName) {
            if (animal.getQuantity() >= quantity) {
                animal.setQuantity(animal.getQuantity() - quantity);
                salesHistory.push_back(productName + " (животное) - " + to_string(quantity) + " шт.");
                cout << "Продажа успешно выполнена!" << endl;
                return;
            }
            else {
                cout << "Недостаточно товара в наличии!" << endl;
                return;
            }
        }
    }
    for (auto& feed : feeds) {
        if (feed.getName() == productName) {
            if (feed.getQuantity() >= quantity) {
                feed.setQuantity(feed.getQuantity() - quantity);
                salesHistory.push_back(productName + " (корм): " + to_string(quantity) + " шт.");
                cout << "Продажа успешно выполнена!" << endl;
                return;
            }
            else {
                cout << "Недостаточно товара в наличии!" << endl;
                return;
            }
        }
    }
    cout << "Товар не найден!" << endl;
}

void PetShop::showSalesHistory() const {
    cout << "История продаж:" << endl;
    for (const auto& sale : salesHistory) {
        cout << sale << endl;
    }
    cout << endl;
}

void PetShop::updateProduct(string productName, double newPrice, int newQuantity) {
    for (auto& animal : animals) {
        if (animal.getSpecies() == productName) {
            animal.setPrice(newPrice);
            animal.setQuantity(newQuantity);
            cout << "Информация о товаре успешно обновлена!" << endl;
            return;
        }
    }
    for (auto& feed : feeds) {
        if (feed.getName() == productName) {
            feed.setPrice(newPrice);
            feed.setQuantity(newQuantity);
            cout << "Информация о товаре успешно обновлена!" << endl;
            return;
        }
    }
    cout << "Товар не найден!" << endl;
}

void PetShop::findMostExpensiveProduct() const {
    if (!animals.empty() || !feeds.empty()) {
        auto mostExpensiveAnimal = max_element(animals.begin(), animals.end(), [](const Animal& a, const Animal& b) {
            return a.getPrice() < b.getPrice();
            });

        auto mostExpensiveFeed = max_element(feeds.begin(), feeds.end(), [](const Feed& a, const Feed& b) {
            return a.getPrice() < b.getPrice();
            });

        cout << "Самое дорогое животное: " << mostExpensiveAnimal->getSpecies() << " (" << mostExpensiveAnimal->getBreed()
            << ") Цена: " << mostExpensiveAnimal->getPrice() << endl;

        cout << "Самый дорогой корм: " << mostExpensiveFeed->getName() << " Цена: " << mostExpensiveFeed->getPrice() << endl;
    }
    else {
        cout << "Магазин пуст!" << endl;
    }
}


int main() {
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");
    PetShop petShop;

    int choice;
    do {
        cout << "\nМеню:" << endl;
        cout << "1. Добавить товар" << endl;
        cout << "2. Удалить товар" << endl;
        cout << "3. Изменить товар" << endl;
        cout << "4. Показать все товары" << endl;
        cout << "5. Продать товар" << endl;
        cout << "6. Показать историю продаж" << endl;
        cout << "7. Найти самый дорогой товар" << endl;
        cout << "8. Найти товар по названию" << endl;
        cout << "9. Выйти из программы" << endl;
        cout << "Выберите действие: ";

        cin >> choice;
        switch (choice) {
        case 1: {
            cout << "\nВыберите тип товара (1 - животное, 2 - корм): ";
            int typeChoice;
            cin >> typeChoice;
            if (typeChoice == 1) {
                string species, breed;
                double price;
                int quantity;
                cout << "Введите вид животного: ";
                cin >> species;
                cout << "Введите породу животного: ";
                cin >> breed;
                cout << "Введите цену: ";
                cin >> price;
                cout << "Введите количество: ";
                cin >> quantity;

                if (price <= 0 || quantity <= 0) {
                    cout << "\nЦена и количество должны быть положительными числами!" << endl;
                    break;
                }

                petShop.addProduct(Animal(species, breed, price, quantity));
            }
        case 2: {
            string productName;
            cout << "\nВведите название товара, который хотите удалить: ";
            cin >> productName;


            if (productName.empty()) {
                cout << "\nНазвание товара не должно быть пустым!" << endl;
                break;
            }

            petShop.removeProduct(productName);
            break;
        }

        case 3: {
            string productName;
            double newPrice;
            int newQuantity;
            cout << "\nВведите название товара, который хотите изменить: ";
            cin >> productName;
            cout << "Введите новую цену: ";
            cin >> newPrice;
            cout << "Введите новое количество: ";
            cin >> newQuantity;

            if (productName.empty() || newPrice <= 0 || newQuantity <= 0) {
                cout << "\nНеверные данные! Проверьте введенные значения." << endl;
                break;
            }

            petShop.updateProduct(productName, newPrice, newQuantity);
            break;
        }
        case 4: {
            petShop.showProducts();
            break;
        }
        case 5: {
            string productName;
            int quantity;
            cout << "\nВведите название товара, который хотите продать: ";
            cin >> productName;
            cout << "Введите количество: ";
            cin >> quantity;


            if (productName.empty() || quantity <= 0) {
                cout << "\nНеверные данные! Проверьте введенные значения." << endl;
                break;
            }

            petShop.sellProduct(productName, quantity);
            break;
        }
        case 6: {
            petShop.showSalesHistory();
            break;
        }
        case 7: {
            petShop.findMostExpensiveProduct();
            break;
        }
        case 8: {
            string productName;
            cout << "\nВведите название товара для поиска: ";
            cin >> productName;


            if (productName.empty()) {
                cout << "\nНазвание товара не должно быть пустым!" << endl;
                break;
            }

            petShop.findProductByName(productName);
            break;
        }
        case 9: {
            return 0;
        }
        default: {
            cout << "\nНеверный выбор действия!" << endl;
            break;
        }


        }
              return 0;
        }
    } while (true);
}
