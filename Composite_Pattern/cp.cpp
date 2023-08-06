#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>

class MenuComponent {
   public:
    virtual void add(std::weak_ptr<MenuComponent> menuComponent) { throw "Unsupported Operation Exception"; }
    virtual void remove(std::weak_ptr<MenuComponent> menuComponent) { throw "Unsupported Operation Exception"; }
    virtual std::shared_ptr<MenuComponent> getChild(int i) { throw "Unsupported Operation Exception"; }
    virtual std::string getName() const { throw "Unsupported Operation Exception"; }
    virtual std::string getDesc() const { throw "Unsupported Operation Exception"; }
    virtual float getPrice() const { throw "Unsupported Operation Exception"; }
    virtual bool getIsVeg() const { throw "Unsupported Operation Exception"; }
    virtual void print() const { throw "Unsupported Operation Exception"; }
};

class MenuItem : public MenuComponent {
    std::string name, desc;
    bool isVeg;
    float price;

   public:
    explicit MenuItem(const std::string& name, const std::string desc, const bool& isVeg, const double& price)
        : name(name), desc(desc), isVeg(isVeg), price(price) {}

    std::string getName() const override { return this->name; }
    std::string getDesc() const override { return this->desc; }
    float getPrice() const override { return this->price; }
    bool getIsVeg() const override { return this->isVeg; }

    void print() const override {
        std::cout << " " << this->getName();
        if (!this->getIsVeg())
            std::cout << "(V)";

        std::cout << ", " << getPrice() << "\n";
        std::cout << "\t-- " << this->getDesc() << "\n";
    }
};

class Menu : public MenuComponent {
    std::vector<std::shared_ptr<MenuComponent>> menuComponents;
    std::string name, desc;

   public:
    explicit Menu(const std::string& name, const std::string& desc) : name(name), desc(desc) {}

    void add(std::weak_ptr<MenuComponent> menuComponent) override { this->menuComponents.push_back(menuComponent.lock()); }

    void remove(std::weak_ptr<MenuComponent> menuComponent) override {
        auto it = std::remove(this->menuComponents.begin(), this->menuComponents.end(), menuComponent.lock());
        this->menuComponents.erase(it, this->menuComponents.end());
    }

    std::shared_ptr<MenuComponent> getChild(int i) override { return this->menuComponents.at(i); }

    std::string getName() const override { return this->name; }
    std::string getDesc() const override { return this->desc; }

    void print() const override {
        std::cout << "\n"
                  << this->getName() << ", " << this->getDesc() << "\n";

        for (const auto& item : this->menuComponents) {
            item->print();
        }
    }
};

class Waitress {
    std::shared_ptr<MenuComponent> menu;

   public:
    explicit Waitress(std::weak_ptr<MenuComponent> menu)
        : menu(menu) {}
    void printMenu() { this->menu->print(); }
};

int main() {
    std::shared_ptr<MenuComponent> menus = std::make_shared<Menu>("ALL MENUS", "All menus combined");
    std::shared_ptr<MenuComponent> phm = std::make_shared<Menu>("PANCAKE HOUSE MENU", "Breakfast");
    std::shared_ptr<MenuComponent> dm = std::make_shared<Menu>("DINER MENU", "Lunch");
    std::shared_ptr<MenuComponent> cm = std::make_shared<Menu>("CAFE MENU", "Dinner");
    std::shared_ptr<MenuComponent> dessert = std::make_shared<Menu>("DESSERT MENU", "Dessert of course!");

    menus->add(phm);
    menus->add(dm);
    menus->add(cm);

    dm->add(std::make_shared<MenuItem>("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on whole wheat", true, 2.99f));
    dm->add(std::make_shared<MenuItem>("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99));
    dm->add(std::make_shared<MenuItem>("Soup of the day", "Soup of the day, with a side of potato salad", false, 3.29));
    dm->add(dessert);
    dessert->add(std::make_shared<MenuItem>("Apple Pie", "Apple pie with a flakey crust, topped with vanilla icecream", true, 1.59));

    auto waitress = std::make_unique<Waitress>(menus);
    waitress->printMenu();
}