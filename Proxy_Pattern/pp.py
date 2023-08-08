from abc import ABC, abstractmethod

class Subject(ABC):
    @abstractmethod
    def request(self) -> None: pass


class RealSubject(Subject):
    def request(self) -> None: 
        print("The actual subject request ...")


class Proxy(Subject):
    def __init__(self, subject: Subject) -> None:
        self.subject: Subject = subject

    def request(self) -> None:
        if self.__checkAccess(): self.subject.request()

    def __checkAccess(self) -> None:
        print("Proxy: Checking access prior to firing a real request")
        return True


class Client:
    def __init__(self, subject: Subject) -> None: 
        subject.request()
    
        
def main() -> None:
    subject = RealSubject()
    proxy = Proxy(subject)
    Client(proxy)


if __name__ == '__main__':
    main()    
        