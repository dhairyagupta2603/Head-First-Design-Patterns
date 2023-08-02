from abc import ABC, abstractmethod

class QuackBehaviour(ABC):
    @abstractmethod
    def quacks(self): pass

class SwimBehaviour(ABC):
    @abstractmethod
    def swims(self): pass

class Quack(QuackBehaviour):
    def quacks(self): # override QuackBehaviour.quacks()
        print("Quack")

class Squeek(QuackBehaviour):
    def quacks(self): # override QuackBehaviour.quacks()
        print("Sqeek")

class Swim(SwimBehaviour):
    def swims(self): # override SwimBehaviour.swims()
        print("Swims")

class Floats(SwimBehaviour):
    def swims(self): # override SwimBehaviour.swims()
        print("Floats")

class Duck:
    def performQuackBehaviour(self):
        self.quackBehaviour.quacks()

    def performSwimBehaviour(self):
        self.swimBehaviour.swims()

    def setQuackBehaviour(self, quackBehaviour: QuackBehaviour):
        self.quackBehaviour = quackBehaviour

    def setSwimBehaviour(self, swimBehaviour: SwimBehaviour):
        self.swimBehaviour = swimBehaviour

def main():
    mallardDuck = Duck()
    mallardDuck.setQuackBehaviour(Quack())
    mallardDuck.setSwimBehaviour(Swim())

    mallardDuck.performQuackBehaviour()
    mallardDuck.performSwimBehaviour()


if __name__ == '__main__':
    main()