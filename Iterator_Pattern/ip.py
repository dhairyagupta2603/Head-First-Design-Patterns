from abc import ABC, abstractmethod
import numpy as np

class MenuItem:
    def __init__(self, name: str, desc: str, isVeg: bool, price: float) -> None:
        self.name: str = name
        self.desc: str = desc
        self.isVeg: bool = isVeg
        self.price: float = price


class Iterator(ABC):
    @abstractmethod
    def hasNext(self) -> bool: pass

    @abstractmethod
    def next(self) -> MenuItem: pass

class DinerMenuIterator(Iterator):
    def __init__(self, items: np.ndarray[6, MenuItem]) -> None:
        self.items: np.ndarray[6, MenuItem] = items
        self.pos = 0

    def hasNext(self) -> bool:
         if self.pos >= self.items.shape[0] or self.items[self.pos] == None: return False
         return True

    def next(self) -> MenuItem:
        item: MenuItem = self.items[self.pos]
        self.pos +=1
        return item

class PancakeHouseIterator(Iterator):
    def __init__(self, items: list[MenuItem]) -> None:
        self.items: list[MenuItem] = items
        self.pos = 0

    def hasNext(self) -> bool:
         if self.pos >= len(self.items): return False
         return True

    def next(self) -> MenuItem:
        item: MenuItem = self.items[self.pos]
        self.pos +=1
        return item

class PancakeHouseMenu:
    def __init__(self) -> None:
        self.items: list[MenuItem] = []
        self.addItem("Vegetarian BLT",
            "(Fakin') Bacon with lettuce & tomato on whole wheat",
            True, 2.99
        )

        self.addItem("BLT",
            "Bacon with lettuce & tomato on whole wheat",
            False, 2.99
        )

        self.addItem("Soup of the day",
            "Soup of the day, with a side of potato salad",
            False, 3.29
        )

        self.addItem("HotDog",
            "A hot dog, with saurkraut, relish, onions, topped with cheese",
            False, 3.05
        )

    def addItem(self, name: str, desc: str, isVeg: bool, price: float) -> None:
        self.items.append(MenuItem(name, desc, isVeg, price))

    def createIterator(self) -> Iterator: return PancakeHouseIterator(self.items)

class DinerMenu:
    def __init__(self) -> None:
        self.items: np.ndarray[6, MenuItem] = np.ndarray(6, dtype=MenuItem)
        self.pos = 0
        self.MAX_ITEMS = 6
        
        self.addItem("Vegetarian BLT",
            "(Fakin') Bacon with lettuce & tomato on whole wheat",
            True, 2.99
        )

        self.addItem("BLT",
            "Bacon with lettuce & tomato on whole wheat",
            False, 2.99
        )

        self.addItem("Soup of the day",
            "Soup of the day, with a side of potato salad",
            False, 3.29
        )

        self.addItem("HotDog",
            "A hot dog, with saurkraut, relish, onions, topped with cheese",
            False, 3.05
        )

    def addItem(self, name: str, desc: str, isVeg: bool, price: float) -> None:
        if self.pos >= self.MAX_ITEMS:
            print("Menu full")
        else:
            self.items[self.pos] = MenuItem(name, desc, isVeg, price)
            self.pos +=1

    def createIterator(self) -> np.ndarray[6, MenuItem]: return DinerMenuIterator(self.items)

class Waitress:
    def __init__(self, phm: PancakeHouseMenu, dm: DinerMenu) -> None:
        self.phm: PancakeHouseMenu = phm
        self.dm: DinerMenu = dm

    def printMenus(self) -> None:
        pi: Iterator = self.phm.createIterator()
        di: Iterator = self.dm.createIterator()

        self.printMenu(pi)
        self.printMenu(di)

    def printMenu(Self, it: Iterator) -> None:
        while it.hasNext():
            item: MenuItem = it.next()
            print(f"Name: {item.name}, desc: {item.desc}, isVeg: {item.isVeg}, price: {item.price}")

def main() -> None:
    waitress = Waitress(PancakeHouseMenu(), DinerMenu())
    waitress.printMenus()

if __name__ == '__main__':
    main()