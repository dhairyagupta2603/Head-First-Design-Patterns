#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
#include <climits>
#include <cstdlib>

class GumballMachine;

class State {
   public:
    virtual void insertQuater() = 0;
    virtual void ejectQuater() = 0;
    virtual void turnCrank() = 0;
    virtual void dispense() = 0;
};

class SoldoutState : public State {
    std::shared_ptr<GumballMachine> machine;

public:
    explicit SoldoutState(std::weak_ptr<GumballMachine> machine)
        : machine(machine.lock()) {}

    void insertQuater() override { std::cout << "You can't insert a quarter, the machine is sold out\n"; }

    void ejectQuater() override { std::cout << "You can't eject, you haven't inserted a quarter yet\n"; }
    void turnCrank() override { std::cout << "You turned, but there are no gumballs\n"; }
    void dispense() override { std::cout << "No gumball dispensed\n"; }
};

class NoQuaterState : public State {
    std::shared_ptr<GumballMachine> machine;

   public:
    explicit NoQuaterState(std::weak_ptr<GumballMachine> machine)
        : machine(machine.lock()) {}

    void insertQuater() override {
        std::cout << "You inserted a quater!\n";
        this->machine->setState(this->machine->hasQuarterState);
    }

    void ejectQuater() override { std::cout << "You haven't inserted a quarter\n"; }
    void turnCrank() override { std::cout << "You turned, but there's no quarter\n"; }
    void dispense() override { std::cout << "You need to pay first\n"; }
};

class HasQuaterState : public State {

    std::shared_ptr<GumballMachine> machine;

   public:
    explicit HasQuaterState(std::weak_ptr<GumballMachine> machine)
        : machine(machine.lock()) {}

    void ejectQuater() override {
        std::cout << "Quarter returned\n";
        this->machine->setState(this->machine->noQuarterState);
    }

    void turnCrank() override {
        auto randomNum = []() {return (std::rand()/RAND_MAX)*10;};
        std::cout << "You turned...\n";
        if (randomNum() and this->machine->count > 1)
            this->machine->setState(this->machine->winnerState);
        else 
            this->machine->setState(this->machine->soldState);
    }

    void insertQuater() override { std::cout << "You can't insert another quarter!\n"; }
    void dispense() override { std::cout << "No gumball dispensed\n"; }
};

class SoldState : public State {
    std::shared_ptr<GumballMachine> machine;

   public:
    explicit SoldState(std::weak_ptr<GumballMachine> machine)
        : machine(machine.lock()) {}

    void insertQuater() override { std::cout << "Please wait, we're already giving you a gumball\n"; }
    void ejectQuater() override { std::cout << "Sorry, you already turned the crank\n"; }
    void turnCrank() override { std::cout << "Turning twice doesn't get you another gumball\n"; }

    void dispense() override {
        this->machine->releaseBall();
        if (this->machine->count > 0) {
            this->machine->setState(this->machine->noQuarterState);
        } else {
            std::cout << "Oops, out of gumballs!\n";
            this->machine->setState(this->machine->soldOutState);
        }
    }
};

class WinnerState : public State {
    std::shared_ptr<GumballMachine> machine;

   public:
    explicit WinnerState(std::weak_ptr<GumballMachine> machine)
        : machine(machine.lock()) {}

    void insertQuater() override { std::cout << "Please wait, we're already giving you a gumball\n"; }
    void ejectQuater() override { std::cout << "Sorry, you already turned the crank\n"; }
    void turnCrank() override { std::cout << "Turning twice doesn't get you another gumball\n"; }

    void dispense() override {
        std::cout << "YOU'RE A WINNER! You get two gumballs for your quarter\n";
        this->machine->releaseBall();
        if (this->machine->count == 0) {
            this->machine->setState(this->machine->soldOutState);
        } else {
            this->machine->releaseBall();
            if (this->machine->count > 0) {
                this->machine->setState(this->machine->noQuarterState);
            } else {
                std::cout << "Oops, out of gumballs!\n";
                this->machine->setState(this->machine->soldOutState);
            }
        }
    }
};

class GumballMachine {
   public:
    std::shared_ptr<State> soldOutState;
    std::shared_ptr<State> noQuarterState;
    std::shared_ptr<State> hasQuarterState;
    std::shared_ptr<State> soldState;
    std::shared_ptr<State> winnerState;

    std::shared_ptr<State> currState;

    int count = 0;

    explicit GumballMachine(const int count) {
        this->soldOutState = std::make_shared<SoldoutState>(*this);
        this->noQuarterState = std::make_shared<NoQuaterState>(*this);
        this->hasQuarterState = std::make_shared<HasQuaterState>(*this);
        this->soldState = std::make_shared<SoldState>(*this);

        this->count = count;
        if (count > 0)
            this->currState = this->hasQuarterState;
    }

    void insertQuater() { this->currState->insertQuater(); }
    void ejectQuater() { this->currState->ejectQuater(); }

    void turnCrank() {
        this->currState->turnCrank();
        this->currState->dispense();
    }

    void setState(std::weak_ptr<State> state) { this->currState = state.lock(); }

    void releaseBall() {
        std::cout << "A gumball comes rolling out the slot...\n";
        if (this->count != 0)
            this->count--;
    }
};

int main() {
    /*
            The code will work when gumballmachine class is declred on top and its functions are defined before main
    */
    auto machine = std::make_shared<GumballMachine>(5);

    machine->insertQuater();
    machine->turnCrank();

    machine->insertQuater();
    machine->ejectQuater();
    machine->turnCrank();

    machine->insertQuater();
    machine->turnCrank();
    machine->insertQuater();
    machine->turnCrank();
    machine->ejectQuater();

    machine->insertQuater();
    machine->insertQuater();
    machine->turnCrank();
    machine->insertQuater();
    machine->turnCrank();
    machine->insertQuater();
    machine->turnCrank();
}