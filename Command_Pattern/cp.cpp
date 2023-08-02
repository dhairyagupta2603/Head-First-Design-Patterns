#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <vector>

class Command {
   public:
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class Light {
   public:
    explicit Light(){};
    void on() { std::cout << "Light is ON\n"; }
    void off() { std::cout << "Light is OFF\n"; }
};

class LightOnCommand : public Command {
    std::shared_ptr<Light> light;

   public:
    explicit LightOnCommand(std::shared_ptr<Light> _light)
        : light(std::move(_light)) {}

    void execute() override { this->light->on(); }
    void undo() override { this->light->off(); }
};

class LightOffCommand : public Command {
    std::shared_ptr<Light> light;

   public:
    explicit LightOffCommand(std::shared_ptr<Light> _light)
        : light(std::move(_light)) {}

    void execute() override { this->light->off(); }
    void undo() override { this->light->on(); }
};

class SimpleRemoteControl {
    std::unique_ptr<Command> slot;

   public:
    explicit SimpleRemoteControl(){};

    void setCommand(std::unique_ptr<Command> Command) { this->slot = std::move(Command); }
    void buttonPressed() { this->slot->execute(); }
};

class NoCommand : public Command {
   public:
    void execute() override { std::cout << "Nothing Happens\n"; }
    void undo() override { std::cout << "Nothing Happens\n"; }
};

enum class FanSpeed : int {
    HIGH,
    MEDIUM,
    LOW,
    OFF
};

class Fan {
    FanSpeed fanSpeed;

   public:
    explicit Fan() { this->fanSpeed = FanSpeed::OFF; }

    void high() { this->fanSpeed = FanSpeed::HIGH; }
    void medium() { this->fanSpeed = FanSpeed::MEDIUM; }
    void low() { this->fanSpeed = FanSpeed::LOW; }
    void off() { this->fanSpeed = FanSpeed::OFF; }

    FanSpeed getSpeed() { return this->fanSpeed; }
};

class FanHighCommand : public Command {
    std::shared_ptr<Fan> fan;
    FanSpeed prevSpeed;

   public:
    explicit FanHighCommand(std::shared_ptr<Fan> _fan)
        : fan(_fan) {}

    void execute() override {
        this->prevSpeed = this->fan->getSpeed();
        this->fan->high();
    }

    void undo() override {
        if (this->prevSpeed == FanSpeed::HIGH)
            this->fan->high();
        else if (this->prevSpeed == FanSpeed::MEDIUM)
            this->fan->medium();
        else if (this->prevSpeed == FanSpeed::LOW)
            this->fan->low();
        else
            this->fan->off();
    }
};

class FanMedCommand : public Command {
    std::shared_ptr<Fan> fan;
    FanSpeed prevSpeed;

   public:
    explicit FanMedCommand(std::shared_ptr<Fan> _fan)
        : fan(_fan) {}

    void execute() override {
        this->prevSpeed = this->fan->getSpeed();
        this->fan->medium();
    }

    void undo() override {
        if (this->prevSpeed == FanSpeed::HIGH)
            this->fan->high();
        else if (this->prevSpeed == FanSpeed::MEDIUM)
            this->fan->medium();
        else if (this->prevSpeed == FanSpeed::LOW)
            this->fan->low();
        else
            this->fan->off();
    }
};

class FanOffCommand : public Command {
    std::shared_ptr<Fan> fan;
    FanSpeed prevSpeed;

   public:
    explicit FanOffCommand(std::shared_ptr<Fan> _fan)
        : fan(_fan) {}

    void execute() override {
        this->prevSpeed = this->fan->getSpeed();
        this->fan->off();
    }

    void undo() override {
        if (this->prevSpeed == FanSpeed::HIGH)
            this->fan->high();
        else if (this->prevSpeed == FanSpeed::MEDIUM)
            this->fan->medium();
        else if (this->prevSpeed == FanSpeed::LOW)
            this->fan->low();
        else
            this->fan->off();
    }
};

class MacroCommand : public Command {
    std::vector<std::unique_ptr<Command>> commands;

   public:
    explicit MacroCommand(std::vector<std::unique_ptr<Command>> _commands)
        : commands(std::move(_commands)) {}

    void execute() override {
        for (auto& command : this->commands)
            command->execute();
    }

    void undo() override {
        for (auto& command : this->commands)
            command->undo();
    };
};

class RemoteControl {
    std::array<std::shared_ptr<Command>, 7> onCommands;
    std::array<std::shared_ptr<Command>, 7> offCommands;
    std::shared_ptr<Command> undoCommand;

   public:
    explicit RemoteControl() {
        std::shared_ptr<Command> noCommand = std::make_shared<NoCommand>();
        for (size_t i = 0; i < 7; i < i++) {
            this->onCommands.at(i) = noCommand;
            this->offCommands.at(i) = noCommand;
        }
        this->undoCommand = noCommand;
    }

    void setCommand(int slot, std::weak_ptr<Command> onCommand, std::weak_ptr<Command> offCommand) {
        this->onCommands.at(slot) = onCommand.lock();
        this->offCommands.at(slot) = offCommand.lock();
    }

    void onButtonWasPushed(int slot) {
        this->onCommands.at(slot)->execute();
        this->undoCommand = onCommands.at(slot);
    }

    void offButtonWasPushed(int slot) {
        this->offCommands.at(slot)->execute();
        this->undoCommand = offCommands.at(slot);
    }

    void undoButtonWasPushed() { this->undoCommand->undo(); }
};

int main() {
    
    // auto remote = std::make_unique<SimpleRemoteControl>();
    // auto light = std::make_shared<Light>();

    // std::unique_ptr<Command> lightOn = std::make_unique<LightOnCommand>(light);
    // remote->setCommand(std::move(lightOn));
    // remote->buttonPressed();

    // std::unique_ptr<Command> lightOff = std::make_unique<LightOffCommand>(light);
    // remote->setCommand(std::move(lightOff));
    // remote->buttonPressed();

    // auto remoteController = std::make_unique<RemoteControl>();
    // auto light = std::make_shared<Light>();

    // std::shared_ptr<Command> lightIsOn = std::make_shared<LightOnCommand>(light);
    // std::shared_ptr<Command> lightIsOff = std::make_shared<LightOffCommand>(light);

    // remoteController->setCommand(0, lightIsOn, lightIsOff);
    // remoteController->onButtonWasPushed(0);
    // remoteController->offButtonWasPushed(0);
    // remoteController->undoButtonWasPushed();



    // auto rc = std::make_unique<RemoteControl>();
    // auto fan = std::make_shared<Fan>();
    // std::shared_ptr<Command> fanMed = std::make_shared<FanMedCommand>(fan);
    // std::shared_ptr<Command> fanHigh = std::make_shared<FanHighCommand>(fan);
    // std::shared_ptr<Command> fanOff = std::make_shared<FanOffCommand>(fan);

    // rc->setCommand(0, fanMed, fanOff);
    // rc->setCommand(1, fanHigh, fanOff);

    // rc->onButtonWasPushed(0);
    // rc->offButtonWasPushed(0);
    // rc->undoButtonWasPushed();

    // rc->onButtonWasPushed(1);
    // rc->undoButtonWasPushed();

    

    auto rc = std::make_unique<RemoteControl>();
    auto light = std::make_shared<Light>();
    auto fan = std::make_shared<Fan>();

    std::unique_ptr<Command> lightOn = std::make_unique<LightOnCommand>(light);
    std::unique_ptr<Command> lightOff = std::make_unique<LightOffCommand>(light);
    std::unique_ptr<Command> fanHigh = std::make_unique<FanHighCommand>(fan);
    std::unique_ptr<Command> fanOff = std::make_unique<FanOffCommand>(fan);

    std::vector<std::unique_ptr<Command>> partyOn;
    partyOn.push_back(std::move(lightOn));
    partyOn.push_back(std::move(fanHigh));

    std::vector<std::unique_ptr<Command>> partyOff;
    partyOff.push_back(std::move(lightOff));
    partyOff.push_back(std::move(fanOff));

    std::shared_ptr<Command> onMacro = std::make_shared<MacroCommand>(std::move(partyOn));
    std::shared_ptr<Command> offMacro = std::make_shared<MacroCommand>(std::move(partyOff));

    rc->setCommand(0, onMacro, offMacro);
    rc->onButtonWasPushed(0);
    rc->offButtonWasPushed(0);
    rc->undoButtonWasPushed();

}