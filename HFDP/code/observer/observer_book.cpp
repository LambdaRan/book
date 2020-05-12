
#include <iostream>
#include <string>
// #include <vector>
#include <unordered_map>


// 定义观察者接口
class Observer {
public:
    Observer() = default;
    virtual ~Observer() = default;;

    virtual void update(float temp, float _humidity, float _pressure) = 0;
    virtual const std::string& get_identifier() const = 0;
};

// 定义主题接口
class Subject {
public:
    Subject() = default;
    virtual ~Subject() = default;

    virtual void registerObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers() = 0;
};

// 定义显示接口
class DisplayElement {
public:
    DisplayElement() = default;
    virtual ~DisplayElement() = default;

    virtual void display() = 0;
};

// 气象站
class WeatherData : public Subject {
public:
    WeatherData() : _observers(), _temperature(0.0), _humidity(0.0), _pressure(0.0) {}
    ~WeatherData() {}

    virtual void registerObserver(Observer* observer) override final {
        const auto iter_find = _observers.find(observer->get_identifier());
        if (iter_find != _observers.end()) {
            std::cout << "Observer " << observer->get_identifier() << "has existed" << std::endl;
            return;
        }
        _observers[observer->get_identifier()] = observer;
    }

    virtual void removeObserver(Observer* observer) override final {
        const auto iter_find = _observers.find(observer->get_identifier());
        if (iter_find != _observers.end()) {
            _observers.erase(iter_find);
        }
    }

    virtual void notifyObservers() override final {
        for (const auto& observer : _observers) {
            observer.second->update(_temperature, _humidity, _pressure);
        }
    }

    void measurementsChanged() {
        notifyObservers();
    }

    void setMeasurements(float temperature, float humidity, float pressure) {
        _temperature = temperature;
        _humidity = humidity;
        _pressure = pressure;
        measurementsChanged();
    }

private:
    std::unordered_map<std::string, Observer*> _observers;
    float _temperature;
    float _humidity;
    float _pressure;
};

class CurrentConditionDisplay : public Observer, DisplayElement {
public:
    CurrentConditionDisplay(const std::string& identifier, Subject* subject)
            : _identifier(identifier),
              _subject(subject),
              _temperature(0.0),
              _humidity(0.0),
              _pressure(0.0)
    {
        if (!_subject) {
            std::cout << "Subject is null" << std::endl;
            return;
        }
        _subject->registerObserver(this);
    }

    ~CurrentConditionDisplay() {}

    // observer
    virtual void update(float temp, float humidity, float pressure) override final {
        _temperature = temp;
        _humidity = humidity;
        _pressure = pressure;
        display();
    }

    virtual const std::string& get_identifier() const override final {
        return _identifier;
    }

    // DisplayElement
    virtual void display() override final {
        std::cout << "identifier : " << _identifier << std::endl;
        std::cout << "Current conditions :\n" << _temperature << "\n" << _humidity << "\n" << _pressure << std::endl;
    }

private:
    std::string _identifier;
    Subject* _subject;
    float _temperature;
    float _humidity;
    float _pressure;
};

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    
    WeatherData wd;
    CurrentConditionDisplay ccd("conditions", &wd);
    wd.setMeasurements(1.1f, 1.2f, 1.3f);

    return 0;
}