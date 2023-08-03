from abc import ABC, abstractmethod

class Pizza(ABC):
    def __init__(self) -> None:
        super().__init__()
        self.name: str = None
        self.dough: str = None
        self.sauce: str = None
        self.toppings: list[str] = []

    def prepare(self) -> None:
        print(f'Prepare {self.name}')
        print('Tossing dough...')
        print('Adding sauce...')
        print(f'Adding topping: {self.toppings}')

    def bake(self) -> None: print('Bake for 25 min at 350')
    def cut(self) -> None: print('Cutting the pizza into diagonal slices')
    def box(self) -> None: print('Place pizza in official pizzastore box')
    def getName(self) -> None: return self.name


class NYStyleCheesePizza(Pizza):
    def __init__(self) -> None:
        super().__init__()
        self.name: str = "NY Style Sauce and Cheese Pizza"
        self.dough: str = "Thin Crust Dough"
        self.sauce: str = "Marinara Sauce"
        self.toppings.append("Grated Reggiano Cheese")

class ChicagoStyleCheesePizza(Pizza):
    def __init__(self) -> None:
        super().__init__()
        self.name: str = "Chicago Style Deep Dish Cheese Pizza"
        self.dough: str = "Extra Thick Crust Dough"
        self.sauce: str = "Plum Tomato Sauce"
        self.toppings.append("Shredded Mozzarella Cheese")

    def cut(self) -> None:
        print("Cutting the pizza into square slices")

class PizzaStore(ABC):
    def orderPizza(self, pizzaType: str) -> Pizza:
        pizza: Pizza =  self.createPizza(pizzaType)
        pizza.prepare()
        pizza.bake()
        pizza.cut()
        pizza.box()
        return pizza

    @abstractmethod
    def createPizza(self, pizzaType: str) -> Pizza: pass


class NYPizzaStore(PizzaStore):
    def createPizza(self, pizzaType: str) -> Pizza:
        if pizzaType == "Cheese":
            return NYStyleCheesePizza()
        else:
            return None


def main() -> None:
    nyStore = NYPizzaStore()
    pizza = nyStore.orderPizza("Cheese")
    print(f"Ethan ordered a {pizza.getName()}")


if __name__ == '__main__':
    main()
    
        