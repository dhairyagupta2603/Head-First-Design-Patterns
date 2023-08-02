#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

class CaffeineBeverage {
   public:
    const void prepare() {
        this->boilWater();
        this->brew();
        this->pourInCup();
        this->addCondiments();
    }

	protected:
    virtual void brew() = 0;
    virtual void addCondiments() = 0;

    void boilWater() { std::cout << "Boiling water\n"; }
    void pourInCup() { std::cout << "Pouring into cup\n"; }
};

class Coffee : public CaffeineBeverage {
   protected:
    void brew() override { std::cout << "Dipping coffee through filter\n"; }
    void addCondiments() override { std::cout << "Adding suger and milk\n"; }
};

class Tea : public CaffeineBeverage {
   protected:
    void brew() override { std::cout << "Steeping the tea\n"; }
    void addCondiments() override { std::cout << "Adding lemon\n"; }
};

class CaffeineBeverageWithHook {
   public:
    const void prepare() {
        this->boilWater();
        this->brew();
        this->pourInCup();
        if (this->wantCondiments())
            this->addCondiments();
    }

   protected:
    virtual void brew() = 0;
    virtual void addCondiments() = 0;

    void boilWater() { std::cout << "Boiling water\n"; }
    void pourInCup() { std::cout << "Pouring into cup\n"; }

    virtual bool wantCondiments() { return true; }
};

class CoffeeWithHook : public CaffeineBeverageWithHook {
   protected:
    void brew() override { std::cout << "Dipping coffee through filter\n"; }
    void addCondiments() override { std::cout << "Adding suger and milk\n"; }

    bool wantCondiments() override {
        char ans;
        std::cout << "You want condiments? (y/n) ";
        std::cin >> ans;

        if (ans == 'y')
            return true;
        return false;
    }
};

int main() {
    std::unique_ptr<CaffeineBeverage> tea = std::make_unique<Tea>();
    std::unique_ptr<CaffeineBeverage> coffee = std::make_unique<Coffee>();

    tea->prepare();
    coffee->prepare();

    std::cout << "----------------------------------------------------\n";

    std::unique_ptr<CaffeineBeverageWithHook> coffeeWithHook = std::make_unique<CoffeeWithHook>();

    coffeeWithHook->prepare();
}