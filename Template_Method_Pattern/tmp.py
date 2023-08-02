from abc import ABC, abstractmethod

class CaffeineBeverage:
    def prepare(self) -> None:
        self.boilWater()
        self.brew()
        self.pourInCup()
        self.addCondiments()

    @abstractmethod
    def brew(self) -> None: pass

    @abstractmethod
    def addCondiments(self) -> None: pass

    def boilWater(self) -> None: print("Boiling water")
    def pourInCup(self) -> None: print("Pouring into cup")


class Coffee(CaffeineBeverage):
    def brew(self) -> None: print("Dipping coffee through filter")
    def addCondiments(self) -> None: print("Adding suger and milk")

    
class Tea(CaffeineBeverage):
    def brew(self) -> None: print("Steeping the tea")
    def addCondiments(self) -> None: print("Adding lemon")


class CaffeineBeverageWithHook(ABC):
    def prepare(self) -> None:
        self.boilWater()
        self.brew()
        self.pourInCup()
        if self.wantCondiments():
            self.addCondiments()

    @abstractmethod
    def brew(self) -> None: pass

    @abstractmethod
    def addCondiments(self) -> None: pass

    @abstractmethod
    def wantCondiments(self) -> bool: return True

    def boilWater(self) -> None: print("Boiling water")
    def pourInCup(self) -> None: print("Pouring into cup")


class CoffeeWithHook(CaffeineBeverageWithHook):
    def brew(self) -> None: print("Dipping coffee through filter")
    def addCondiments(self) -> None: print("Adding suger and milk")

    def wantCondiments(self) -> bool:
        ans: str = input("You want Condoiments (y/n)? ")

        if ans == 'y': return True
        return False
    

def main()->None:
    tea = Tea()
    tea.prepare()

    coffee = Coffee()
    coffee.prepare()

    print("----------------------------------------------------")

    coffeeWithHook = CoffeeWithHook()
    coffeeWithHook.prepare()
    

if __name__ == '__main__':
    main()
