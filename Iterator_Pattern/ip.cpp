#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <vector>

class MenuItem {
   public:
    std::string name, desc;
    bool isVeg;
    float price;

    explicit MenuItem(const std::string& name, const std::string& desc, const bool& isVeg, const float& price)
        : name(name), desc(desc), isVeg(isVeg), price(price) {}
};

class Iterator {
   public:
    virtual bool hasNext() = 0;
    virtual std::shared_ptr<MenuItem> next() = 0;
};

class DinerMenuIterator : public Iterator {
    std::array<std::shared_ptr<MenuItem>, 6> items;
    size_t pos;

   public:
    explicit DinerMenuIterator(std::array<std::shared_ptr<MenuItem>, 6> items)
        : items(items), pos(0) {}

    bool hasNext() override {
        if (pos >= this->items.size() or this->items.at(pos) == nullptr)
            return false;
        else
            return true;
    }

    std::shared_ptr<MenuItem> next() override {
        std::weak_ptr<MenuItem> item = this->items.at(pos);
        pos++;
        return item.lock();
    }
};

class PancakeHouseIterator : public Iterator {
    std::vector<std::shared_ptr<MenuItem>> items;
    size_t pos;

   public:
    explicit PancakeHouseIterator(std::vector<std::shared_ptr<MenuItem>> items)
        : items(std::move(items)), pos(0) {}

    bool hasNext() override {
        if (pos >= this->items.size())
            return false;
        else
            return true;
    }

    std::shared_ptr<MenuItem> next() override {
        std::weak_ptr<MenuItem> item = this->items.at(pos);
        pos++;
        return item.lock();
    }
};

class PancakeHouseMenu {
    std::vector<std::shared_ptr<MenuItem>> items;

   public:
    explicit PancakeHouseMenu() {
        this->addItem(
            "Vegetarian BLT",
            "(Fakin') Bacon with lettuce & tomato on whole wheat",
            true, 2.99f);

        this->addItem(
            "BLT",
            "Bacon with lettuce & tomato on whole wheat",
            false, 2.99);

        this->addItem(
            "Soup of the day",
            "Soup of the day, with a side of potato salad",
            false, 3.29);

        this->addItem(
            "HotDog",
            "A hot dog, with saurkraut, relish, onions, topped with cheese",
            false, 3.05);
    }

    void addItem(const std::string& name, const std::string& desc, const bool& isVeg, const float& price) {
        this->items.push_back(std::make_shared<MenuItem>(name, desc, isVeg, price));
    }

    std::unique_ptr<Iterator> createIterator() {
        return std::make_unique<PancakeHouseIterator>(this->items);
    }
};

class DinerMenu {
    const size_t MAX_ITEMS = 6;
    int numItems = 0;
    std::array<std::shared_ptr<MenuItem>, 6> items;

   public:
    explicit DinerMenu() {
        this->addItem(
            "Vegetarian BLT",
            "(Fakin') Bacon with lettuce & tomato on whole wheat",
            true, 2.99f);

        this->addItem(
            "BLT",
            "Bacon with lettuce & tomato on whole wheat",
            false, 2.99);

        this->addItem(
            "Soup of the day",
            "Soup of the day, with a side of potato salad",
            false, 3.29);

        this->addItem(
            "HotDog",
            "A hot dog, with saurkraut, relish, onions, topped with cheese",
            false, 3.05);
    }

    void addItem(const std::string& name, const std::string& desc, const bool& isVeg, const float& price) {
        std::shared_ptr<MenuItem> item = std::make_shared<MenuItem>(name, desc, isVeg, price);

        if (this->numItems >= this->MAX_ITEMS)
            std::cout << "Sorry, menu is full! Can't add item to menu\n";
        else {
            this->items.at(numItems) = item;
            numItems++;
        }
    }

    std::unique_ptr<Iterator> createIterator() {
        return std::make_unique<DinerMenuIterator>(this->items);
    }
};

class Waitress {
    std::unique_ptr<PancakeHouseMenu> phm;
    std::unique_ptr<DinerMenu> dm;

   public:
    explicit Waitress(std::unique_ptr<PancakeHouseMenu> phm, std::unique_ptr<DinerMenu> dm)
        : phm(std::move(phm)), dm(std::move(dm)) {}

    void printMenu() {
        std::unique_ptr<Iterator> pi = this->phm->createIterator();
        std::unique_ptr<Iterator> di = this->dm->createIterator();

        printMenu1(std::move(pi));
        printMenu1(std::move(di));
    }

    void printMenu1(std::unique_ptr<Iterator> it) {
        while (it->hasNext()) {
            auto item = it->next();
            std::cout << "Name: " << item->name
                      << ", desc: " << item->desc
                      << ", isVeg: " << (item->isVeg ? "True" : "False")
                      << ", price: " << item->price << "\n";
        }
    }
};

int main() {
    auto phm = std::make_unique<PancakeHouseMenu>();
    auto dm = std::make_unique<DinerMenu>();

    auto waitress = std::make_unique<Waitress>(std::move(phm), std::move(dm));

    waitress->printMenu();
}