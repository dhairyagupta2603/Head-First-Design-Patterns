#include <iostream>
#include <memory>

class QuackBehaviour {
   public:
    virtual ~QuackBehaviour() = default;
    virtual void quacks() const = 0;
};

class SwimBehaviour {
   public:
    virtual ~SwimBehaviour() = default;
    virtual void swims() const = 0;
};

class Quack : public QuackBehaviour {
   public:
    void quacks() const override {
        std::cout << "Quack\n";
    }
};

class MuteQuack : public QuackBehaviour {
   public:
    void quacks() const override {
        std::cout << "<< Silence >>\n";
    }
};

class Squeak : public QuackBehaviour {
   public:
    void quacks() const override {
        std::cout << "Squeak\n";
    }
};

class Swim : public SwimBehaviour {
   public:
    void swims() const override {
        std::cout << "Swims\n";
    }
};

class NoSwim : public SwimBehaviour {
   public:
    void swims() const override {
        std::cout << "Doesn't Swim\n";
    }
};

class Duck {
   public:
    std::unique_ptr<QuackBehaviour> quackBehaviour;
    std::unique_ptr<SwimBehaviour> swimBehaviour;

    // virtual void display() const = 0;
    void performQuackBehaviour() const;
    void performSwimBehaviour() const;

    void setQuackBehaviour(std::unique_ptr<QuackBehaviour> quackBehaviour);
	void setSwimBehaviour(std::unique_ptr<SwimBehaviour> swimBehaviour);
};

void Duck::performQuackBehaviour() const {
    this->quackBehaviour->quacks();
}

void Duck::performSwimBehaviour() const{
    this->swimBehaviour->swims();
}

void Duck::setQuackBehaviour(std::unique_ptr<QuackBehaviour> quackBehaviour) {
	this->quackBehaviour = std::move(quackBehaviour);
}

void Duck::setSwimBehaviour(std::unique_ptr<SwimBehaviour> swimBehaviour) {
	this->swimBehaviour = std::move(swimBehaviour);
}


int main() {
	std::unique_ptr<Duck> mallardDuck = std::make_unique<Duck>();

	mallardDuck->setQuackBehaviour(std::make_unique<Quack>());
	mallardDuck->setSwimBehaviour(std::make_unique<Swim>());

	mallardDuck->performQuackBehaviour();
	mallardDuck->performSwimBehaviour(); 

    return EXIT_SUCCESS;
}