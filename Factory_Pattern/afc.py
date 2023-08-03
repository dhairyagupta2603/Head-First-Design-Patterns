from abc import ABC, abstractmethod

class Dough(ABC): pass
class Sauce(ABC): pass
class Cheese(ABC): pass
class Pepperoni(ABC): pass
class Clam(ABC): pass


class PizzaIngredientFactory(ABC):
    @abstractmethod 
    def create_dough(self) -> Dough: pass

    @abstractmethod
    def create_sauce(self) -> Sauce: pass

    @abstractmethod
    def create_cheese(Self) -> Cheese: pass

    @abstractmethod
    def create_pepperoni(self) -> Pepperoni: pass

    @abstractmethod
    def create_clam(self) -> Clam: pass


class Thin_crust_dough(Dough): pass
class Marinara_sauce(Sauce): pass
class Reggiano_cheese(Cheese): pass
class Sliced_pepperoni(Pepperoni): pass
class Fresh_clam(Clam): pass


class NYPizzaIngredientFactory(PizzaIngredientFactory):
    def create_dough(self) -> Dough: return Thin_crust_dough()
    def create_sauce(self) -> Sauce: return Marinara_sauce()
    def create_cheese(Self) -> Cheese: return Reggiano_cheese()
    def create_pepperoni(self) -> Pepperoni: return Sliced_pepperoni()
    def create_clam(self) -> Clam: return Fresh_clam()


class Pizza(ABC):
    @abstractmethod
    def prepare(self) -> None: pass

    def bake(self) -> None: print("Bake for 25 min at 350")
    def cut(self) -> None: print("Cutting the pizza into diagonal slices")
    def box(self) -> None: print("Place pizza in official PizzaStore box")


class Cheese_pizza(Pizza):
    def __init__(self, IF: PizzaIngredientFactory) -> None:
        self.IF: PizzaIngredientFactory = IF

    def prepare(self) -> None:
        print(f"Prepare {self.pygame.mixer.set_num_channels()}")

        self.dough: Dough = self.IF.create_dough()
        self.sauce: Sauce = self.IF.create_sauce()
        self.cheese: Cheese = self.IF.create_cheese()

class PizzaStore(ABC):
    @abstractmethod
    def create_pizza(self, pizza_type: str) -> Pizza: pass
    
    def order_pizza(self, pizza_type: str) -> Pizza:
        self.pizza: Pizza = self.create_pizza(pizza_type)
        self.pizza.prepare()
        self.pizza.bake()
        self.pizza.cut()
        self.pizza.box()
        return Pizza

class NY_pizza_store(PizzaStore):
    def create_pizza(self, pizza_type: str) -> Pizza:
        if pizza_type == "Cheese":
            return Cheese_pizza()
        else: 
            None

def main() -> None:
    ny_pizza_store = NY_pizza_store()
    ny_pizza_store.order_pizza("Cheese")
    print("Ethan ordered a pizza")


if __name__ == '__main__':
    main()
    