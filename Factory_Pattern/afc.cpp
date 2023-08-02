#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

class Dough {};
class Sauce {};
class Cheese {};
class Pepperoni {};
class Clam {};
class Veggie {};

// abstract factory class
class PizzaIngredientFactory {
   public:
    virtual std::unique_ptr<Dough> createDough() = 0;
    virtual std::unique_ptr<Sauce> createSauce() = 0;
    virtual std::unique_ptr<Cheese> createCheese() = 0;
    virtual std::unique_ptr<Pepperoni> createPepperoni() = 0;
    virtual std::unique_ptr<Clam> createClam() = 0;
    // virtual std::vector<std::unique_ptr<Veggie>> createVeggies() = 0;
};

class ThinCrustDough : public Dough {};
class MarinaraSauce : public Sauce {};
class ReggianoCheese : public Cheese {};
class SlicedPepperoni : public Pepperoni {};
class FreshClam : public Clam {};
class Garlic : public Veggie {};
class Onion : public Veggie {};
class Mushroom : public Veggie {};
class RedPepper : public Veggie {};

class NYPizzaIngredientFactory : public PizzaIngredientFactory {
   public:
    std::unique_ptr<Dough> createDough() override { return std::make_unique<ThinCrustDough>(); }
    std::unique_ptr<Sauce> createSauce() override { return std::make_unique<MarinaraSauce>(); }
    std::unique_ptr<Cheese> createCheese() override { return std::make_unique<ReggianoCheese>(); }
    std::unique_ptr<Pepperoni> createPepperoni() override { return std::make_unique<SlicedPepperoni>(); }
    std::unique_ptr<Clam> createClam() override { return std::make_unique<FreshClam>(); }

    // std::vector<std::unique_ptr<Veggie>> createVeggies() {
    //     return {
    //         std::make_unique<Garlic>(),
    //         std::make_unique<Onion>(),
    //         std::make_unique<Mushroom>(),
    //         std::make_unique<RedPepper>()};
    // }
};

class ThickCrustDough : public Dough {};
class PlumTomatoSauce : public Sauce {};
class Mozzarella : public Cheese {};
class FrozenClam : public Clam {};
class Eggplant : public Veggie {};
class Spinach : public Veggie {};
class BalckOlives : public Veggie {};

class ChicagoPizzaIngredientFactory : public PizzaIngredientFactory {
   public:
    std::unique_ptr<Dough> createDough() override { return std::make_unique<ThickCrustDough>(); }
    std::unique_ptr<Sauce> createSauce() override { return std::make_unique<PlumTomatoSauce>(); }
    std::unique_ptr<Cheese> createCheese() override { return std::make_unique<Mozzarella>(); }
    std::unique_ptr<Pepperoni> createPepperoni() override { return std::make_unique<SlicedPepperoni>(); }
    std::unique_ptr<Clam> createClam() override { return std::make_unique<FrozenClam>(); }

    // std::vector<std::unique_ptr<Veggie>> createVeggies() {
    //     return {
    //         std::make_unique<Eggplant>(),
    //         std::make_unique<Spinach>(),
    //         std::make_unique<BalckOlives>()};
    // }
};

class Pizza {
   protected:
    std::string name;
    std::unique_ptr<Dough> dough;
    std::unique_ptr<Sauce> sauce;
    std::unique_ptr<Cheese> cheese;
    std::unique_ptr<Pepperoni> pepperoni;
    std::unique_ptr<Clam> clam;
    // std::vector<std::unique_ptr<Veggie>> veggies;

   public:
    virtual void prepare() = 0;

    void bake() { std::cout << "Bake for 25 min at 350\n"; }
    void cut() { std::cout << "Cutting the pizza into diagonal slices\n"; }
    void box() { std::cout << "Place pizza in official PizzaStore box\n"; }

    void setName(const std::string& name) { this->name; }
    std::string getName() { return this->name; }
};

class CheezePizza : public Pizza {
    std::unique_ptr<PizzaIngredientFactory> ingredientFactory;

   public:
    explicit CheezePizza(std::unique_ptr<PizzaIngredientFactory> iF)
        : ingredientFactory(std::move(iF)) {}

    void prepare() override {
        std::cout << "Preparing " << this->getName() << "\n";
        this->dough = std::move(this->ingredientFactory->createDough());
        this->sauce = std::move(this->ingredientFactory->createSauce());
        this->cheese = std::move(this->ingredientFactory->createCheese());
    }
};

class ClamPizza : public Pizza {
    std::unique_ptr<PizzaIngredientFactory> ingredientFactory;

   public:
    explicit ClamPizza(std::unique_ptr<PizzaIngredientFactory> iF)
        : ingredientFactory(std::move(iF)) {}

    void prepare() override {
        std::cout << "Preparing " << this->getName() << "\n";
        this->dough = std::move(this->ingredientFactory->createDough());
        this->sauce = std::move(this->ingredientFactory->createSauce());
        this->cheese = std::move(this->ingredientFactory->createCheese());
    }
};

class PizzaStore {
   public:
    std::unique_ptr<Pizza> orderPizza(std::string pizza_type) {
        std::unique_ptr<Pizza> pizza = std::move(this->createPizza(pizza_type));
        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();
        return pizza;
    }

    virtual std::unique_ptr<Pizza> createPizza(const std::string& pizzaType) = 0;
};

class NYPizzaStore : public PizzaStore {
   protected:
    std::unique_ptr<Pizza> createPizza(const std::string& item) override {
        std::unique_ptr<Pizza> pizza = nullptr;
        std::unique_ptr<PizzaIngredientFactory> iF = nullptr;

        if (item == "Cheese")
            pizza = std::make_unique<CheezePizza>(std::move(iF));
        else if (item == "Clam")
            pizza = std::make_unique<ClamPizza>(std::move(iF));
        else
            pizza = nullptr;
        return pizza;
    }
};

int main() {
    std::unique_ptr<PizzaStore> nyPizzaStore = std::make_unique<NYPizzaStore>();
    std::unique_ptr<Pizza> nyPizza = nyPizzaStore->orderPizza("Cheese");
    nyPizza->setName("NY Cheese Cheese Pizza");
    std::cout << "Ethan ordered a " << nyPizza->getName() << "\n";
}