from abc import ABC, abstractmethod

class QuackBehaviour(ABC):
    @abstractmethod
    def quacks(self) -> None: pass

class SwimBehaviour(ABC):
    @abstractmethod
    def swims(self) -> None: pass

class Quack(QuackBehaviour):
    def quacks(self) -> None: # override QuackBehaviour.quacks()
        print("Quack")

class Squeek(QuackBehaviour):
    def quacks(self) -> None: # override QuackBehaviour.quacks()
        print("Sqeek")

class Swim(SwimBehaviour):
    def swims(self) -> None: # override SwimBehaviour.swims()
        print("Swims")

class Floats(SwimBehaviour):
    def swims(self) -> None: # override SwimBehaviour.swims()
        print("Floats")

class Duck:
    def performQuackBehaviour(self) -> None:
        self.quackBehaviour.quacks()

    def performSwimBehaviour(self) -> None:
        self.swimBehaviour.swims()

    def setQuackBehaviour(self, quackBehaviour: QuackBehaviour) -> None:
        self.quackBehaviour: QuackBehaviour = quackBehaviour

    def setSwimBehaviour(self, swimBehaviour: SwimBehaviour) -> None:
        self.swimBehaviour: SwimBehaviour = swimBehaviour

def main() -> None:
    mallardDuck = Duck()
    mallardDuck.setQuackBehaviour(Quack())
    mallardDuck.setSwimBehaviour(Swim())

    mallardDuck.performQuackBehaviour()
    mallardDuck.performSwimBehaviour()


if __name__ == '__main__':
    main()