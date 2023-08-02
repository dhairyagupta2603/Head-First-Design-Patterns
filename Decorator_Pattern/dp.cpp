#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

class Bverage {
   protected:
    std::string desc = "Unknown Beverage";

   public:
    std::string getDesc() {
        return this->desc;
    }
    virtual double cost() const = 0;
};

class CondimentDecorator : public Bverage {
   public:
    virtual std::string getDesc() = 0;
};

class Expresso : public Bverage {
   public:
    explicit Expresso() {
        this->desc = "Expresso Coffee";
    }

    double cost() const override {
        return 1.99;
    }
};

class HouseBlend : public Bverage {
   public:
    explicit HouseBlend() {
        this->desc = "House Blend Coffee";
    }

    double cost() const override {
        return 0.89;
    }
};

class Mocha : public CondimentDecorator {
    std::unique_ptr<Bverage> beverage;

   public:
    explicit Mocha(std::unique_ptr<Bverage> _beverage)
        : beverage(std::move(_beverage)) {}

    std::string getDesc() {
        return beverage->getDesc() + "Mocha";
    }

    double cost() const override {
        return 0.20 + beverage->cost();
    }
};

class Soy : public CondimentDecorator {
    std::unique_ptr<Bverage> beverage;

   public:
    explicit Soy(std::unique_ptr<Bverage> _beverage)
        : beverage(std::move(_beverage)) {}

    std::string getDesc() {
        return beverage->getDesc() + "Soy";
    }

    double cost() const override {
        return 0.15 + beverage->cost();
    }
};

class Whip : public CondimentDecorator {
    std::unique_ptr<Bverage> beverage;

   public:
    explicit Whip(std::unique_ptr<Bverage> _beverage)
        : beverage(std::move(_beverage)) {}

    std::string getDesc() {
        return beverage->getDesc() + "Whip";
    }

    double cost() const override {
        return 0.10 + beverage->cost();
    }
};

int main() {
	std::unique_ptr<Bverage> beverage = std::make_unique<Expresso>();
	std::cout<<"Beverage: "<<beverage->getDesc()<<" $"<<beverage->cost()<<"\n";

	std::unique_ptr<Bverage> beverage2 = std::make_unique<HouseBlend>();
	beverage2 = std::make_unique<Mocha>(std::move(beverage2));
	beverage2 = std::make_unique<Mocha>(std::move(beverage2));
	beverage2 = std::make_unique<Whip>(std::move(beverage2));
	std::cout<<"Beverage2: "<<beverage2->getDesc()<<" $"<<beverage2->cost()<<"\n";


}