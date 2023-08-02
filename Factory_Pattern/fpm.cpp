#include <iostream>
#include <memory>
#include <vector>

class Pizza{
public:
	std::string name, dough, sauce;
	std::vector<std::string> toppings;

	void prepare(){
		std::cout<<"Preparing "<<name<<"\n";
		std::cout<<"Tossing dough...\n";
		std::cout<<"Adding sauce...\n";
		std::cout<<"Adding toppings: ";
		for(const std::string& s: toppings){
			std::cout<<" "<<s;
		}
	}
	virtual void bake(){
		std::cout<<"Bake for 25 min at 350\n";
	}
	virtual void cut(){
		std::cout<<"Cuttong the pizza into diagonal slices\n";
	}
	virtual void box(){
		std::cout<<"Place Pizza in official pizzaStore box\n";
	}

	std::string getName() {
		return this->name;
	}
};

class NYStyleCheesePizza: public Pizza {
public:
	explicit NYStyleCheesePizza() {
		this->name = "NY stule Sauce and Cheese Pizza";
		this->dough = "Thisn Crust Dough";
		this->sauce = "Marinara Sauce";
		this->toppings.push_back("grated Reggino Cheese");
	}
};

class NYStyleVeggiePizza: public Pizza {
public:
	explicit NYStyleVeggiePizza() {
		this->name = "Chicago style deep dish cheese pizza";
		this->dough = "Extra Thick Crust Dough";
		this->sauce = "Plum Tomoto sauce";
		this->toppings.push_back("Shredded Mozzarella Cheese");
	}

	void cut() override {
		std::cout<<"Cutting the pizza into square slices\n";
	}
};

class PizzaStore {
public:
	std::unique_ptr<Pizza> orderPizza(std::string pizza_type){
		std::unique_ptr<Pizza> pizza = std::make_unique<Pizza>();
		pizza = this->createPizza(pizza_type);
		pizza->prepare();
		pizza->bake();
		pizza->cut();
		pizza->box();
		return pizza;
	}

	virtual std::unique_ptr<Pizza> createPizza(std::string pizzaType) = 0; 
};


class NYPizzaStore : public PizzaStore {
	std::unique_ptr<Pizza> createPizza(std::string pizzaType) override {
		if (pizzaType == "Cheese"){
			return std::make_unique<NYStyleCheesePizza>();
		} else if (pizzaType == "Veggie") {
			return std::make_unique<NYStyleVeggiePizza>();
		} return nullptr;
	}
};

int main() {
	std::unique_ptr<PizzaStore> nyStore = std::make_unique<NYPizzaStore>();
	std::unique_ptr<Pizza> nyPizza = nyStore->orderPizza("Cheese");
	std::cout<<"Ethan ordered a "<<nyPizza->getName()<<"\n";
}