#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

class Duck {
   public:
    virtual void quack() = 0;
    virtual void fly() = 0;
};

class MillardDuck : public Duck {
   public:
    void quack() override { std::cout << "Quack\n"; }
    void fly() override { std::cout<<"I believe I can fly\n";}
};


class Turkey {
public:
	virtual void gobble() = 0;
	virtual void fly() = 0;
};


class WildTurkey : public Turkey {
	void gobble() override { std::cout<<"Gobble Gobble\n";}
	void fly() override { std::cout<<"I am flying a short distance\n";}
};


// inherited Duck as Duck is expected: turkey -> turkeyadapter -> Duck
class TurkeyAdapter : public Duck {
	std::unique_ptr<Turkey> turkey;

public:
	explicit TurkeyAdapter(std::unique_ptr<Turkey> _turkey)
		: turkey(std::move(_turkey)) {}

	void quack() override { this->turkey->gobble();}
	
	void fly() override {
		for (uint8_t i = 0; i < 5; i++){
			this->turkey->fly();
		}
	}
};

void testDuck(std::unique_ptr<Duck> duck){
	duck->fly();
	duck->quack();
}

int main() {
	std::unique_ptr<Duck> duck = std::make_unique<MillardDuck>();
	std::unique_ptr<Turkey> turkey = std::make_unique<WildTurkey>();
	auto turkeyAdapter = std::make_unique<TurkeyAdapter>(std::move(turkey));

	testDuck(std::move(duck));
	testDuck(std::move(turkeyAdapter));
}