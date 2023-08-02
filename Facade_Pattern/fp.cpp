#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

class DvdPlayer {
   public:
    void on() { std::cout << "Dvd player is on\n"; }
    void off() { std::cout << "Dvd player is off\n"; }
    void stop() { std::cout << "Dvd player is stopped\n"; }
    void eject() { std::cout << "Dvd is ejected\n"; }
    void playMovie() { std::cout << "movie is being played\n"; }
};

class Amplifier {
   public:
    void on() { std::cout << "Amp is on\n"; }
    void off() { std::cout << "Amp is off\n"; }
    void setDvd(DvdPlayer dvd) { std::cout << "Used the dvd\n"; }
    void setSurroundSound() { std::cout << "have set the sound as surround\n"; }
    void setVolume(int volume) { std::cout << "the volume is " << volume << "\n"; }
};

class Projector {
   public:
    void on() { std::cout << "The projector is on\n"; }
    void off() { std::cout << "The projector is off\n"; }
    void wideScreenMode() { std::cout << "Switched to wide screen mode\n"; }
};

class Lights {
   public:
    void dim(int dimming) { std::cout << "Lights dimmed  to " << dimming << "%\n"; }
    void on() { std::cout << "The lights are on\n"; }
};

class Screen {
   public:
    void down() { std::cout << "screen is down\n"; }
    void up() { std::cout << "screen is up\n"; }
};

class PopcornPopper {
   public:
    void on() { std::cout << "Switched on Popper\n"; }
    void off() { std::cout << "Switched off Popper\n"; }
    void pop() { std::cout << "Popper stated poppig\n"; }
};

class HomeTheatreFacade {
    Amplifier amp;
    DvdPlayer dvd;
    Projector projector;
    Lights lights;
    Screen screen;
    PopcornPopper popper;

   public:
    explicit HomeTheatreFacade(Amplifier amp, DvdPlayer dvd, Projector projector, Lights lights, Screen screen, PopcornPopper popper)
        : amp(amp), dvd(dvd), projector(projector), lights(lights), screen(screen), popper(popper) {}

    void watchMovie() {
        popper.on();
        popper.pop();

        lights.dim(10);
        screen.down();
        projector.on();
        projector.wideScreenMode();
        amp.on();
        amp.setDvd(dvd);
        amp.setVolume(5);
        dvd.on();
        dvd.playMovie();
    }

    void endMovie() {
        popper.off();
        lights.on();
        screen.up();
        projector.off();
        amp.off();
        dvd.stop();
        dvd.eject();
        dvd.off();
    }
};

int main() {
	Amplifier amp;
    DvdPlayer dvd;
    Projector projector;
    Lights lights;
    Screen screen;
    PopcornPopper popper;
	HomeTheatreFacade f(amp, dvd, projector, lights, screen, popper);
	f.watchMovie();
	f.endMovie();
}