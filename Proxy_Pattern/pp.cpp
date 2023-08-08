#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>

class Subject {
public:
    virtual void request() const  = 0;
};

class RealSubject : public Subject {
public:
    void request() const override {std::cout<<"The actual subject  request ...\n";}
};


class Proxy : public Subject {
    std::shared_ptr<Subject> subject;

    bool checkAccess() const {
        std::cout<<"Proxy: Checking access prior to firing a real request\n";
        return true;
    }

public:
    explicit Proxy(std::weak_ptr<Subject> s)
        : subject(s.lock()) {}

    void request() const override {
        if (this->checkAccess()){
            this->subject->request();
        }
    }
};

class Client {
public:
    explicit Client(std::weak_ptr<Subject> subject) {
        subject.lock()->request();
    }
};

int main() {
    std::shared_ptr<Subject> subject = std::make_shared<RealSubject>();
    std::shared_ptr<Subject> proxy = std::make_shared<Proxy>(std::move(subject));

    std::make_unique<Client>(proxy);
    
}