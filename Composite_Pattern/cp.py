from abc import ABC, abstractmethod
    
class MenuComponent(ABC):
    def add(self, menuComponent: 'MenuComponent') -> None: pass
    def remove(self, menuComponent: 'MenuComponent') -> None: pass
    def getChild(self, idx: int) -> None: pass
    def getName(self) -> str: pass
    def getDesc(self) -> str: pass
    def getPrice(self) -> float: pass
    def getIsVeg(self) -> bool: pass
    def print(self) -> None: pass


class MenuItem(MenuComponent):
    def __init__(self, name: str, desc: str, isVeg: bool, price: float) -> None:
        self.name: str = name
        self.desc: str = desc
        self.isVeg: bool = isVeg
        self.price: float = price

    def getName(self) -> str: return self.name
    def getDesc(self) -> str: return self.desc

    def print(self) -> None:
        print(f" {self.getName()}", end="")
        if self.getIsVeg(): print(" (V) ", end="")
        print(f", {self.getPrice()}\n\t-- {self.getDesc()}")


class Menu(MenuComponent):
    def __init__(self, name: str, desc: str) -> None:
        self.name: str = name
        self.desc: str = desc
        self.menuComponents: list[MenuComponent] = []

    def add(self, menuComponent: MenuComponent) -> None: self.menuComponents.append(menuComponent)

    def remove(self, menuComponent: MenuComponent) -> None: self.menuComponents.remove(menuComponent)

    def getName(self) -> str: return self.name
    def getDesc(self) -> str: return self.desc

    def print(self) -> None:
        print(f"\n{self.getName()}, {self.getDesc()}")

        for item in self.menuComponents: item.print()


class Waitress:
    def __init__(self, menu: MenuComponent) -> None:
        self.menu: MenuComponent = menu      

    def printMenu(self)-> None: self.menu.print()


def main() -> None:
    menus = Menu("ALL MENUS", "All menus combined")
    phm = Menu("PANCAKE HOUSE MENU", "Breakfast")
    dm = Menu("DINER MENU", "Lunch")
    cm = Menu("CAFE MENU", "Dinner")
    desssert = Menu("DESSERT MENU", "Dessert of course!")

    menus.add(phm)
    menus.add(dm)
    menus.add(cm)

    dm.add(MenuItem("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on whole wheat", True, 2.99))
    dm.add(MenuItem("BLT", "Bacon with lettuce & tomato on whole wheat", False, 2.99))
    dm.add(MenuItem("Soup of the day", "Soup of the day, with a side of potato salad", False, 3.29))
    dm.add(desssert)
    desssert.add(MenuItem("Apple Pie", "Apple pie with a flakey crust, topped with vanilla icecream", True, 1.59))

    waitress = Waitress(menus)
    waitress.printMenu()

if __name__ == '__main__':
    main()
        