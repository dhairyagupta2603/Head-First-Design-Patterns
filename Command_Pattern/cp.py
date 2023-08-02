from abc import ABC, abstractmethod
from enum import Enum

class Command(ABC):
    @abstractmethod
    def execute(self) -> None: pass

    @abstractmethod
    def undo(self) -> None: pass


class Light:
    def on(self) -> None: print("Light is ON")
    def off(self) -> None: print("Light is OFF")


class LightOnCommand(Command):
    def __init__(self, light: Light) -> None:
        super().__init__()
        self.light: Light = light

    def execute(self) -> None: self.light.on()
    def undo(self) -> None: self.light.off()


class LightOffCommand(Command):
    def __init__(self, light: Light) -> None:
        super().__init__()
        self.light: Light = light

    def execute(self) -> None: self.light.off()
    def undo(self) -> None: self.light.on()


class SimpleRemoteControl:
    def setCommand(self, command: Command) -> None: 
        self.slot: Command = command

    def buttonPressed(self): self.slot.execute()


class NoCommand(Command):
    def execute(self) -> None: print("Nothing happens")
    def undo(self) -> None: print("nothing happens")


class FanSpeed(Enum):
    HIGH = 3
    MEDIUM = 2
    LOW = 1
    OFF = 0


class Fan:
    def __init__(self) -> None: self.fanSpeed = FanSpeed.OFF

    def high(self) -> None: self.fanSpeed = FanSpeed.HIGH
    def medium(self) -> None: self.fanSpeed = FanSpeed.MEDIUM
    def low(self) -> None: self.fanSpeed = FanSpeed.LOW
    def off(self) -> None: self.fanSpeed = FanSpeed.OFF

    def getSpeed(self) -> FanSpeed: return self.fanSpeed


class FanHighCommand(Command):
    def __init__(self, fan: Fan) -> None:
        self.fan: Fan = fan

    def execute(self) -> None:
        self.prevSpeed: FanSpeed = self.fan.getSpeed()
        self.fan.high()

    def undo(self)-> None:        
        if self.prevSpeed == FanSpeed.HIGH: self.fan.high()
        elif self.prevSpeed == FanSpeed.MEDIUM: self.fan.medium()
        elif self.prevSpeed == FanSpeed.LOW: self.fan.low()
        else: self.fan.off()


class FanMedCommand(Command):
    def __init__(self, fan: Fan) -> None:
        self.fan: Fan = fan

    def execute(self) -> None:
        self.prevSpeed: FanSpeed = self.fan.getSpeed()
        self.fan.medium()

    def undo(self)-> None:        
        if self.prevSpeed == FanSpeed.HIGH: self.fan.high()
        elif self.prevSpeed == FanSpeed.MEDIUM: self.fan.medium()
        elif self.prevSpeed == FanSpeed.LOW: self.fan.low()
        else: self.fan.off()


class FanOffCommand(Command):
    def __init__(self, fan: Fan) -> None:
        super().__init__()
        self.fan: Fan = fan

    def execute(self) -> None:
        self.prevSpeed: FanSpeed = self.fan.getSpeed()
        self.fan.off()

    def undo(self)-> None:        
        if self.prevSpeed == FanSpeed.HIGH: self.fan.high()
        elif self.prevSpeed == FanSpeed.MEDIUM: self.fan.medium()
        elif self.prevSpeed == FanSpeed.LOW: self.fan.low()
        else: self.fan.off()


class MacroCommand(Command):
    def __init__(self, commands: list[Command]) -> None:
        self.commands: list[Command]  = commands

    def execute(self) -> None: 
        for command in self.commands: command.execute()
    def undo(self) -> None: 
        for command in self.commands: command.undo()


class RemoteControl:
    def __init__(self) -> None:
        self.onCommands: list[Command] = [NoCommand() for _ in range(7)]
        self.offCommands: list[Command] = [NoCommand() for _ in range(7)]
        self.undoCommand: Command = NoCommand()

    def setCommand(self, slot: int, onCommand: Command, offCommand: Command) -> None:
        self.onCommands[slot] = onCommand
        self.offCommands[slot] = offCommand

    def onButtonPushed(self, slot: int) -> None:
        self.onCommands[slot].execute()
        self.undoCommand = self.onCommands[slot]

    def offButtonPushed(self, slot: int) -> None:
        self.offCommands[slot].execute()
        self.undoCommand = self.offCommands[slot]

    def undoButtonPressed(self) -> None:
        self.undoCommand.undo()

    
def main() -> None:
    # remote = SimpleRemoteControl()
    # light = Light()
    
    # lightOn = LightOnCommand(light)
    # remote.setCommand(lightOn)
    # remote.buttonPressed()

    # lightoff = LightOffCommand(light)
    # remote.setCommand(lightoff)
    # remote.buttonPressed()

    # rc = RemoteControl()
    # light = Light()
    # lightOn: Command = LightOnCommand(light)
    # lightOff: Command = LightOffCommand(light)

    # rc.setCommand(0, lightOn, lightOff)
    # rc.onButtonPushed(0)
    # rc.offButtonPushed(0)
    # rc.undoButtonPressed()



    # rc = RemoteControl()
    # fan = Fan()
    # fanMed = FanMedCommand(fan)
    # fanHigh = FanHighCommand(fan)
    # fanOff = FanOffCommand(fan)

    # rc.setCommand(0, fanMed, fanOff)
    # rc.setCommand(1, fanHigh, fanOff)

    # rc.onButtonPushed(0)
    # rc.offButtonPushed(0)
    # rc.undoButtonPressed()

    # rc.onButtonPushed(1)
    # rc.undoButtonPressed()



    rc = RemoteControl()
    light = Light()
    fan = Fan()

    partyOn: list[Command] = [LightOnCommand(light), FanHighCommand(fan)]
    partyOff: list[Command] = [LightOffCommand(light), FanOffCommand(fan)]

    onMacro: Command = MacroCommand(partyOn)
    offMacro: Command = MacroCommand(partyOff)

    rc.setCommand(0, onMacro, offMacro)
    rc.onButtonPushed(0)
    rc.offButtonPushed(0)
    rc.undoButtonPressed()
    

main()