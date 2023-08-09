from abc import ABC, abstractmethod
from random import randint

class State:
    @abstractmethod
    def insertQuater(self) -> None: pass

    @abstractmethod
    def ejectQuater(self) -> None: pass

    @abstractmethod
    def turnCrank(self) -> None: pass

    @abstractmethod
    def dispense(self) -> None: pass


class soldoutState(State):
    def __init__(self, machine: 'GumballMachine') -> None:
        self.machine: GumballMachine = machine

    def insertQuater(self) -> None: print("You can't insert a quarter, the machine is sold out")
    def ejectQuater(self) -> None: print("You can't eject, you haven't inserted a quarter yet")
    def turnCrank(self) -> None: print("You turned, but there are no gumballs")
    def dispense(self) -> None: print("No gumball dispensed")

    
class NoQuaterState(State):
    def __init__(self, machine: 'GumballMachine') -> None:
        self.machine: GumballMachine = machine

    def insertQuater(self) -> None: 
        print("You inserted a quater!")
        self.machine.setState(self.machine.hasQuarterState)
        
    def ejectQuater(self) -> None: print("You haven't inserted a quarter")
    def turnCrank(self) -> None: print("You turned, but there's no quarter")
    def dispense(self) -> None: print("You need to pay first")


class WinnerState(State):
    def __init__(self, machine: 'GumballMachine') -> None:
        self.machine: GumballMachine = machine

    def insertQuater(self) -> None: print("Please wait, we're already giving you a gumball")
    def ejectQuater(self) -> None: print("Sorry, you already turned the crank")
    def turnCrank(self) -> None: print("Turning twice doesn't get you another gumball")
    def dispense(self) -> None: 
        print("YOU'RE A WINNER! You get two gumballs for your quarter")
        self.machine.releaseBall()
        if self.machine.count == 0:
            self.machine.setState(self.machine.soldOutState)
        else:
            self.machine.releaseBall()
            if self.machine.count > 0:
                self.machine.setState(self.machine.noQuarterState)
            else:
                print("Oops, out of gumballs!")
                self.machine.setState(self.machine.soldOutState)
    
    
class HasQuaterState(State):
    def __init__(self, machine: 'GumballMachine') -> None:
        self.machine: GumballMachine = machine

    def insertQuater(self) -> None: print("You can't insert another quarter!")
    
    def ejectQuater(self) -> None: 
        print("Quarter returned")
        self.machine.setState(self.machine.noQuarterState)
        
    def turnCrank(self) -> None: 
        if randint(1, 10) == 5 and self.machine.count > 1:
            self.machine.setState(self.machine.winnerState)
        else:
            self.machine.setState(self.machine.soldState)
        
    def dispense(self) -> None: print("No gumball dispensed")

    
class SoldState(State):
    def __init__(self, machine: 'GumballMachine') -> None:
        self.machine: GumballMachine = machine

    def insertQuater(self) -> None: print("Please wait, we're already giving you a gumball")
    def ejectQuater(self) -> None: print("Sorry, you already turned the crank")
    def turnCrank(self) -> None: print("Turning twice doesn't get you another gumball")
    
    def dispense(self) -> None: 
        self.machine.releaseBall()
        if self.machine.count > 0:
            self.machine.setState(self.machine.noQuarterState)
        else:
            print("Oops, out of gumballs!")
            self.machine.setState(self.machine.soldOutState)
    

class GumballMachine:
    def __init__(self, count: int) -> None:
        self.soldOutState: State = SoldState(self)
        self.noQuarterState: State = NoQuaterState(self)
        self.hasQuarterState: State = HasQuaterState(self)
        self.soldState: State = SoldState(self)
        self.winnerState: State = WinnerState(self)
        
        self.count: int = count
        if self.count > 0:
            self.currState: State = self.hasQuarterState

    def insertQuater(self) -> None: self.currState.insertQuater()
    def ejectQuater(self) -> None: self.currState.ejectQuater()

    def turnCrank(self) -> None:
        self.currState.turnCrank()
        self.currState.dispense()

    def setState(self, state: State) -> None: self.currState = state

    def releaseBall(self) -> None:
        print("A gumball comes rolling out the slot...")
        if self.count != 0: self.count -=1


def main():
    machine = GumballMachine(5)
    machine.insertQuater()
    machine.turnCrank()

    machine.insertQuater()
    machine.ejectQuater()
    machine.turnCrank()

    machine.insertQuater()
    machine.turnCrank()
    machine.insertQuater()
    machine.turnCrank()


if __name__ == '__main__':
    main()