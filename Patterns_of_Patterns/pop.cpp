#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>


class Quackable {
   public:
    virtual void quack() = 0;
};

class AbstractDuckFactory {
   public:
    virtual std::unique_ptr<Quackable> createMallardDuck() = 0;
    virtual std::unique_ptr<Quackable> createRedheadDuck() = 0;
    virtual std::unique_ptr<Quackable> createDuckCall() = 0;
    virtual std::unique_ptr<Quackable> createRubberDuck() = 0;
};

class MallardDuck : public Quackable {
   public:
    void quack() override { std::cout << "QUACKKKKKK!!!\n"; }
};

class RedheadDuck : public Quackable {
   public:
    void quack() override { std::cout << "QUACKKKKKK!!!\n"; }
};

class DuckCall : public Quackable {
   public:
    void quack() override { std::cout << "KUAWWKKKKKK!!!\n"; }
};

class RubberDuck : public Quackable {
   public:
    void quack() override { std::cout << "Squack\n"; }
};

class Goose {
   public:
    void honk() { std::cout << "HONK!!!\n"; }
};

class GooseAdapter : public Quackable {
    std::unique_ptr<Goose> goose;

   public:
    explicit GooseAdapter(std::unique_ptr<Goose> goose)
        : goose(std::move(goose)) {}

    void quack() override { this->goose->honk(); }
};

class DuckFactory : public AbstractDuckFactory {
   public:
    std::unique_ptr<Quackable> createMallardDuck() override { return std::make_unique<MallardDuck>(); }

    std::unique_ptr<Quackable> createRedheadDuck() override { return std::make_unique<RedheadDuck>(); }

    std::unique_ptr<Quackable> createDuckCall() override { return std::make_unique<DuckCall>(); }

    std::unique_ptr<Quackable> createRubberDuck() override { return std::make_unique<RubberDuck>(); }
};

class QuackCounter : public Quackable {
    std::unique_ptr<Quackable> duck;
    static int numQuacks;

   public:
    explicit QuackCounter(std::unique_ptr<Quackable> duck)
        : duck(std::move(duck)) {}

    static int getNumQuacks() { return numQuacks; }
    static void resetNumQuacks() { numQuacks = 0; }

    void quack() override {
        this->duck->quack();
        QuackCounter::numQuacks++;
    }
};

int QuackCounter::numQuacks = 0;

class CountingDuckFactory : public AbstractDuckFactory {
   public:
    std::unique_ptr<Quackable> createMallardDuck() override { return std::make_unique<QuackCounter>(std::make_unique<MallardDuck>()); }

    std::unique_ptr<Quackable> createRedheadDuck() override { return std::make_unique<QuackCounter>(std::make_unique<RedheadDuck>()); }

    std::unique_ptr<Quackable> createDuckCall() override { return std::make_unique<QuackCounter>(std::make_unique<DuckCall>()); }

    std::unique_ptr<Quackable> createRubberDuck() override { return std::make_unique<QuackCounter>(std::make_unique<RubberDuck>()); }
};

class Flock : public Quackable {
    std::vector<std::unique_ptr<Quackable>> quackers;

   public:
    void add(std::unique_ptr<Quackable> quacker) {
        this->quackers.push_back(std::move(quacker));
    }

    void quack() override {
        for (const auto& quacker : this->quackers) {
            quacker->quack();
        }
    }
};

class DuckSimulator {
   public:
    void simulate(std::unique_ptr<AbstractDuckFactory> duckFactory) {
        std::unique_ptr<Quackable> mallardDuck = duckFactory->createMallardDuck();
        std::unique_ptr<Quackable> redheadDuck = duckFactory->createRedheadDuck();
        std::unique_ptr<Quackable> duckCall = duckFactory->createDuckCall();
        std::unique_ptr<Quackable> rubberDuck = duckFactory->createRubberDuck();
        std::unique_ptr<Quackable> gooseDuck = std::make_unique<QuackCounter>(std::make_unique<GooseAdapter>(std::make_unique<Goose>()));

        auto floackOfDucks = std::make_unique<Flock>();
        floackOfDucks->add(std::move(redheadDuck));
        floackOfDucks->add(std::move(duckCall));
        floackOfDucks->add(std::move(rubberDuck));
        floackOfDucks->add(std::move(gooseDuck));

        auto flockOfMallards = std::make_unique<Flock>();
        flockOfMallards->add(std::move(duckFactory->createMallardDuck()));
        flockOfMallards->add(std::move(duckFactory->createMallardDuck()));
        flockOfMallards->add(std::move(duckFactory->createMallardDuck()));

        floackOfDucks->add(std::move(flockOfMallards));

        std::cout << "Duck Simulator: Whole Flock Simulation\n";

        this->simulate(std::move(floackOfDucks));

        std::cout << "Toatal quacks performed: " << QuackCounter::getNumQuacks() << "\n";
    }

    void simulate(std::unique_ptr<Quackable> duck) {
        duck->quack();
    }
};

int main() {
    auto duckSimulator = std::make_unique<DuckSimulator>();
    std::unique_ptr<AbstractDuckFactory> duckfactory = std::make_unique<CountingDuckFactory>();
    duckSimulator->simulate(std::move(duckfactory));
}