class ChocolateBoiler:
    def __init__(self) -> None:
        self.isEmpty = True
        self.isBoiled = False

    def fill(self) -> None:
        if self.isEmpty:
            self.isEmpty = False
            self.isBoiled = False

    def drain(self) -> None:
        if not self.isEmpty and self.isBoiled:
            self.isEmpty = True

    def boil(self) -> None:
        if self.isEmpty and not self.isBoiled:
            self.isEmpty = True


class ChocolateBoilerSingleton(object):
    def __new__(cls):
        if not hasattr(cls, 'instance'):
            cls.instance = super(ChocolateBoilerSingleton, cls).__new__(cls)

            cls.instance.isEmpty = True
            cls.instance.isBoiled = False
        return cls.instance

    def fill(self) -> None:
        if self.isEmpty:
            self.isEmpty = False
            self.isBoiled = False

    def drain(self) -> None:
        if not self.isEmpty and self.isBoiled:
            self.isEmpty = True

    def boil(self) -> None:
        if self.isEmpty and not self.isBoiled:
            self.isEmpty = True


def main() -> None:
    cb = ChocolateBoilerSingleton()
    cb2 = ChocolateBoilerSingleton()
    print(cb2 is cb)


if __name__ == '__main__':
    main()
    


