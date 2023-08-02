from abc import ABC, abstractmethod

class Duck(ABC):
    @abstractmethod
    def quack(self)-> None: pass
    
    @abstractmethod
    def fly(self) -> None: pass

class MillardDuck(Duck):
    def quack(self) -> None: print("Quack")
    def fly(self) -> None: print("I believe I can fly")

class Turkey(ABC):
    @abstractmethod
    def gobble(self)-> None: pass

    @abstractmethod
    def fly(self)-> None: pass


class WildTurkey(Turkey):
    def gobble(self) -> None: print("Gobble Gobble")
    def fly(self) -> None: print("I am flying a short distance")

class TurkeyAdapter(Duck):
    def __init__(self, turkey: Turkey) -> None:
        self.turkey: Turkey = turkey

    def quack(self) -> None: self.turkey.gobble()

    def fly(self) -> None:
        for _ in range(5): self.turkey.fly()


def testDuck(duck: Duck) -> None:
    duck.quack()
    duck.fly()


def main():
    duck = MillardDuck()
    turkey = WildTurkey()

    turkeyAdapter = TurkeyAdapter(turkey)

    testDuck(duck)
    testDuck(turkeyAdapter)

main()
    