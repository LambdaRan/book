#include <iostream>
#include <string>

class Beverage {
public:
    Beverage() = default;
    virtual ~Beverage() = default;

    virtual const std::string getDescription() const = 0;
    virtual double cost() = 0;
};

// 具体咖啡
class Espresso : public Beverage {
public:
    Espresso() : _description("Espresso") {}
    virtual ~Espresso() = default;

    const std::string getDescription() const override {
        return _description;
    }

    double cost() override {
        return 1.99;
    }

private:
    std::string _description;
};

class HouseBlend : public Beverage {
public:
    HouseBlend() : _description("HouseBlend") {}
    virtual ~HouseBlend() = default;

    const std::string getDescription() const override {
        return _description;
    }

    double cost() override {
        return 0.89;
    }

private:
    std::string _description;
};


// 装饰者类
class CondimentDecorator : public Beverage {
public:
    CondimentDecorator() = default;
    virtual ~CondimentDecorator() = default;

};
// 装饰者1
class Mocha : public CondimentDecorator {
public:
    Mocha(Beverage* beverage) : _beverage(beverage) {}
    ~Mocha() {
        if (_beverage) {
            delete _beverage;
        }
        _beverage = nullptr;
    }

    const std::string getDescription() const override {
        return _beverage->getDescription() + ",Mocha";
    }

    double cost() override {
        return _beverage->cost() + 0.2;
    }

private:
    Beverage* _beverage;
};

class Whip : public CondimentDecorator {
public:
    Whip(Beverage* beverage) : _beverage(beverage) {}
    ~Whip() {
        if (_beverage) {
            delete _beverage;
        }
        _beverage = nullptr;
    }

    const std::string getDescription() const override {
        return _beverage->getDescription() + ",Whip";
    }

    double cost() override {
        return _beverage->cost() + 1.1;
    }
private:
    Beverage* _beverage;
};


int main() {

    Beverage* beverage = new Espresso();
    std::cout << beverage->getDescription() << " " << beverage->cost() << std::endl;
    delete beverage;

    Beverage* beverage2 = new HouseBlend();
    beverage2 = new Mocha(beverage2);
    beverage2 = new Whip(beverage2);
    std::cout << beverage2->getDescription() << " " << beverage2->cost() << std::endl;
    delete beverage2;

    return 0;
}
