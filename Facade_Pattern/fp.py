

class DVDPlayer:
    def on(self) -> None: print("Dvd player is on")
    def off(self) -> None: print("Dvd player is off")
    def stop(self) -> None: print("Dvd player is stopped")
    def eject(self) -> None: print("Dvd is ejected")
    def playMovie(self) -> None: print("movie is being played")


class Amplifier:
    def on(self) -> None: print("Amp is on")
    def off(self) -> None: print("Amp is off")
    def setDVD(self) -> None: print("Used the dvd")
    def setSurroundSound(self) -> None: print("have set the sound as surround")
    def setVolume(self, volume: int) -> None: print(f"The volume is {volume}")

class Projector:
    def on(self) -> None: print("The projector is on")
    def off(self) -> None: print("The projector is off")
    def wideScreenMode(self) -> None: print("Switched to wide screen mode")

class Lights:
    def dim(self, dimming: int): print(f"Lights dimmed to {dimming}")
    def on(self) -> None: print("The lights are on")


class Screen:
    def down(self) -> None: print("screen is down")
    def up(self) -> None: print("screen is up")


class PopcornPopper:
    def on(self) -> None: print("Switched on Popper")
    def off(self) -> None: print("Switched off Popper")   
    def pop(self) -> None: print("Popper stated poppig")


class HomeTheatreFacade:
    def __init__(self, amp: Amplifier, dvd: DVDPlayer, projector: Projector, lights: Lights, screen: Screen, popper: PopcornPopper) -> None:
        self.amp: Amplifier = amp
        self.dvd: DVDPlayer = dvd
        self.projector: Projector = projector
        self.lights: Lights = lights
        self.screen: Screen = screen
        self.popper: PopcornPopper = popper

    def watchMovie(self) -> None:
        self.popper.on()
        self.popper.pop()
        self.lights.dim(10)
        self.screen.down()
        self.projector.on()
        self.projector.wideScreenMode()
        self.amp.on()
        self.amp.setDVD()
        self.amp.setVolume(5)
        self.dvd.on()
        self.dvd.playMovie()

    def endMovie(self):
        self.popper.off()
        self.lights.on()
        self.screen.up()
        self.projector.off()
        self.amp.off()
        self.dvd.stop()
        self.dvd.eject()
        self.dvd.off()

def main() -> None:
        f = HomeTheatreFacade(
            Amplifier(), DVDPlayer(), Projector(), Lights(), Screen(), PopcornPopper()
        )
        f.watchMovie()
        print("-----------------------")
        f.endMovie()

if __name__ == '__main__':
    main()
