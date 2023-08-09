#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

class WeatherObserver {
   public:
    virtual ~WeatherObserver() = default;
    virtual void update(float temp, float humidity, float pressure) = 0;
};

template <typename Observer_T>
class Subject {
   public:
    ~Subject() = default;

    virtual void registerObserver(std::shared_ptr<Observer_T> observer) = 0;
    virtual void removeObserver(std::shared_ptr<Observer_T> observer) = 0;
    virtual void notifyObservers() const = 0;
};

class WeatherStation : public Subject<WeatherObserver> {
   private:
    std::vector<std::shared_ptr<WeatherObserver>> observers;
    float temp, humidity, pressure;

   public:
    explicit WeatherStation() = default;
    ~WeatherStation() = default;

    float getTemp() const { return 69.0; }
    float getHum() const { return 72.0; }
    float getPressure() const { return 1.0; }

    void setMeasurements(float temperature, float humidity, float pressure) {
        this->temp = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        measurementsChanged();
    }

    void registerObserver(std::shared_ptr<WeatherObserver> observer) override {
        observers.push_back(std::move(observer));
    }

    void removeObserver(std::shared_ptr<WeatherObserver> observer) override {
        auto it = std::find_if(observers.begin(), observers.end(), [&observer](const auto& o) {
            return o.get() == observer.get();
        });

        if (it != observers.end()) {
            observers.erase(it);
        }
    }

    void notifyObservers() const override {
        for (const auto& o : observers) {
            o->update(temp, humidity, pressure);
        }
    }

    void measurementsChanged() const { notifyObservers(); }
};

class CurrentConditionDisplayElement : public WeatherObserver {
   private:
    float temp, humidity, pressure;
    std::shared_ptr<Subject<WeatherObserver>> weatherStation;

   public:
    explicit CurrentConditionDisplayElement(std::weak_ptr<Subject<WeatherObserver>> weatherStation)
        : weatherStation(weatherStation.lock()) {
        this->weatherStation->registerObserver(std::make_shared<CurrentConditionDisplayElement>(this));
    }

    void update(float temperature, float humidity, float pressure) {
        this->temp = temperature;
        this->humidity = humidity;
        display();
    }

    void display() const { std::cout << "Curr conditions: " << temp << " C, " << humidity << " mm and " << pressure << " atm.\n"; }
};

int main() {
    auto weatherStation = std::shared_ptr<WeatherStation>();
    auto currentConditionDE = std::make_shared<CurrentConditionDisplayElement>(weatherStation);
    weatherStation->notifyObservers();
}