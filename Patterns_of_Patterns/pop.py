from abc import ABC, abstractmethod

class Quackable(ABC):
    @abstractmethod
    def quack(self) -> None: pass

class AbstractDuckFactory(ABC):
    @abstractmethod
    def createMallardDuck(self)-> Quackable: pass

    @abstractmethod
    def createRedheadDuck(self)-> Quackable: pass
    
    @abstractmethod
    def createDuckCall(self)-> Quackable: pass
    
    @abstractmethod
    def createRubberDuck(self)-> Quackable: pass

class MallardDuck(Quackable):
    def quack(self) -> None: print("QUACK!!")
    
class RedheadDuck(Quackable):
    def quack(self) -> None: print("QUACK!!")
    
class DuckCall(Quackable):
    def quack(self) -> None: print("KWAWK!!")
    
class RubberDuck(Quackable):
    def quack(self) -> None: print("Squeek!!")

class Goose:
    def honk(self)-> None: print("HONK!!")


class GooseAdapter(Quackable):
    def __init__(self, goose: Goose) -> None:
        self.goose: Goose = goose

    def quack(self) -> None: self.goose.honk()


class DuckFactory(AbstractDuckFactory):
    def createMallardDuck(self) -> Quackable: return MallardDuck()
    def createRedheadDuck(self) -> Quackable: return RedheadDuck()
    def createDuckCall(self) -> Quackable: return DuckCall()
    def createRubberDuck(self) -> Quackable: return RubberDuck()


class QuackCounter(Quackable):
    _numQuacks = 0
    
    @property
    def numQuacks(self) -> int: return type(self)._numQuacks

    @numQuacks.setter
    def numQuacks(self, val: int): type(self)._numQuacks = val
    
    def __init__(self, duck: Quackable) -> None:
        self.duck: Quackable = duck
    
    def resetNumQuacks(self) -> None:  self.numQuacks(0)

    def quack(self) -> None:
        self.duck.quack()
        self.numQuacks = self.numQuacks + 1

class CountingDuckFactory(AbstractDuckFactory):
    def createMallardDuck(self) -> Quackable: return QuackCounter(MallardDuck())
    def createRedheadDuck(self) -> Quackable: return QuackCounter(RedheadDuck())
    def createDuckCall(self) -> Quackable: return QuackCounter(DuckCall())
    def createRubberDuck(self) -> Quackable: return QuackCounter(RubberDuck())


class Flock(Quackable):
    def __init__(self) -> None:
        self.quackers: list[Quackable] = []

    def add(self, quacker: Quackable) -> None: self.quackers.append(quacker)

    def quack(self) -> None:
        for quacker in self.quackers: quacker.quack()
            
        
class DuckSimulator:
    def simulate(self, duckFactory: AbstractDuckFactory):
        mallardDuck: Quackable = duckFactory.createMallardDuck()
        redheadDuck: Quackable = duckFactory.createRedheadDuck()
        duckCall: Quackable = duckFactory.createDuckCall()
        rubberDuck: Quackable = duckFactory.createRubberDuck()
        gooseDuck: Quackable = GooseAdapter(Goose())

        floackOfDucks = Flock()
        floackOfDucks.add(redheadDuck)
        floackOfDucks.add(duckCall)
        floackOfDucks.add(rubberDuck)
        floackOfDucks.add(gooseDuck)

        floackOfMallards = Flock()
        floackOfMallards.add(mallardDuck)
        floackOfMallards.add(mallardDuck)
        floackOfMallards.add(mallardDuck)

        floackOfDucks.add(floackOfMallards)

        print("Duck Simulator: Whole Flock Simulation")
        self.simulateQuack(floackOfDucks)
        
        print("Duck Simulator: Mallard Flock Simulation")
        self.simulateQuack(floackOfMallards)

        print(f"Toatal Quacks performed: {QuackCounter(None).numQuacks}")

    def simulateQuack(self, quaker: Quackable)-> None: quaker.quack()


def main():
    duckSimulator = DuckSimulator()
    duckSimulator.simulate(CountingDuckFactory())


if __name__ == '__main__':
    main()

        
        
    
