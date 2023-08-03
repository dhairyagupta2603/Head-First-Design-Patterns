from abc import ABC, abstractmethod

class Beverage(ABC):
    def __init__(self) -> None:
        super().__init__()
        self.desc = "Unknown beverage"

    def get_desc(self) -> str: return self.desc

    @abstractmethod
    def cost(self) -> float: pass

class CondimentDecorator(Beverage, ABC):
    def __call__(self) -> None:
        self.beverage
    
    @abstractmethod
    def get_desc(self) -> str: pass

class Expresso(Beverage):
    def __init__(self) -> None:
        super().__init__()
        self.desc = 'Expresso'

    def cost(self) -> float:
        return 1.99

class HouseBlend(Beverage):
    def __init__(self) -> None:
        super().__init__()
        self.desc = 'HouseBlend'

    def cost(self) -> float:
        return 1.99

class Mocha(CondimentDecorator):
    def __init__(self, beverage: Beverage) -> None:
        super().__init__()
        self.beverage = beverage

    def get_desc(self) -> str:
        return self.beverage.get_desc() + 'Mocha'

    def cost(self) -> float:
        return 0.20 + self.beverage.cost()

class Soy(CondimentDecorator):
    def __init__(self, beverage: Beverage) -> None:
        super().__init__()
        self.beverage = beverage

    def get_desc(self) -> str:
        return self.beverage.get_desc() + 'Soy'

    def cost(self) -> float:
        return 0.15 + self.beverage.cost()

def main():
    beverage = Expresso()
    print(f'{beverage.get_desc()} ${beverage.cost()}')

    b2 = HouseBlend()
    b2 = Mocha(b2)
    b2 = Soy(b2)
    print(f'{b2.get_desc()} ${b2.cost()}')


if __name__ == '__main__':
    main()
    