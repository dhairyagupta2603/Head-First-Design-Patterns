#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
#include <mutex>

// initial class
class ChocolateBoiler {
   private:
    bool isEmpty, isBoiled;

   public:
    explicit ChocolateBoiler() {
        this->isEmpty = true;
        this->isBoiled = false;
    }

    void fill() {
        if (this->isEmpty) {
            this->isEmpty = false;
            this->isBoiled = false;
        }
    }

    void drain() {
        if (!this->isEmpty and this->isBoiled) {
            this->isEmpty = true;
        }
    }

    void boil() {
        if (!this->isEmpty and !this->isBoiled) {
            this->isBoiled = true;
        }
    }
};

// Singleton class - thread safe (possibly)
class ThreadSafeChocolateBoilerSingleton {
   private:
   	struct PrivateTag {}; // to make constructor private 
	// done in https://stackoverflow.com/questions/69652744/c-singleton-private-constructor-not-accessible-from-static-function

    bool isEmpty, isBoiled;    

   public:
   	// pass private tage as an argument
	explicit ThreadSafeChocolateBoilerSingleton(PrivateTag) {
        this->isEmpty = true;
        this->isBoiled = false;
    }

    static std::weak_ptr<ThreadSafeChocolateBoilerSingleton> getInstance() {
		static std::weak_ptr<ThreadSafeChocolateBoilerSingleton> weak_cb;
		auto cb = weak_cb.lock();

		if (!cb){
			cb = std::make_shared<ThreadSafeChocolateBoilerSingleton>(PrivateTag {});
			weak_cb = cb;
		}
        return cb;
    }

    void fill() {
        if (this->isEmpty) {
            this->isEmpty = false;
            this->isBoiled = false;
        }
    }

    void drain() {
        if (!this->isEmpty and this->isBoiled) {
            this->isEmpty = true;
        }
    }

    void boil() {
        if (!this->isEmpty and !this->isBoiled) {
            this->isBoiled = true;
        }
    }
};

int main() {
	std::shared_ptr<ThreadSafeChocolateBoilerSingleton> cb = ThreadSafeChocolateBoilerSingleton::getInstance().lock();
    std::shared_ptr<ThreadSafeChocolateBoilerSingleton> cb2 = ThreadSafeChocolateBoilerSingleton::getInstance().lock();
    std::cout<<(cb == cb2)<<"\n";
}