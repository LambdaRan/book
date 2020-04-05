#include <iostream>
#include <string>


// 策略模式


// 定义 飞行 接口
class FlyBehavior {
public:
    FlyBehavior() = default;
    virtual ~FlyBehavior() {}
    virtual void fly() const = 0;
};

class FlyWithWings : public FlyBehavior {
public:
    FlyWithWings() = default;
    ~FlyWithWings() {}

    void fly() const override {
        std::cout << "I'm flying" << std::endl;
    }
};

class FlyNoWay : public FlyBehavior {
public:
    FlyNoWay() = default;
    ~FlyNoWay() {}

    void fly() const override {
        std::cout << "I Can't fly" << std::endl;
    }
};


// 定义 嘎嘎 接口
class QuackBehavior {
public:
    QuackBehavior() = default;
    virtual ~QuackBehavior() {}
    virtual void quack() const = 0;
};


class Quack : public QuackBehavior {
public:
    Quack() = default;
    ~Quack() {}

    void quack() const override {
        std::cout << "Quack" << std::endl;
    }
};

class MuteQuack : public QuackBehavior {
public:
    MuteQuack() = default;
    ~MuteQuack() {}

    void quack() const override {
        std::cout << "MuteQuack" << std::endl;
    }
};

class Squeak : public QuackBehavior {
public:
    Squeak() = default;
    ~Squeak() {}

    void quack() const override {
        std::cout << "Squeak" << std::endl;
    }
};

// 定义Duck基类
class Duck {
public:
    Duck() : Duck("unknown", nullptr, nullptr) {}
    explicit Duck(const std::string& name) : Duck(name, nullptr, nullptr) {}
    Duck(const std::string& name, FlyBehavior* fly_behavior, QuackBehavior* quck_behavior) :
            _name(name), _fly_behavior(fly_behavior), _quck_behavior(quck_behavior) {}
    virtual ~Duck();

    void performFly() const {
        std::cout << _name << " ";
        if (_fly_behavior) {
            _fly_behavior->fly();
        } else {
            std::cout << "say : wuwu I Can't fly" << std::endl;
        }
    }
    void performQuck() const {
        std::cout << _name << " ";
        if (_quck_behavior) {
            _quck_behavior->quack();
        } else {
            std::cout << "say : wuwu I Can't quck" << std::endl;
        }
    }

    void swim() const {
        std::cout << "All duck float, event decoys!" << std::endl;
    }

    virtual void display() {}

private:
    std::string _name = "unknown";
    FlyBehavior *_fly_behavior;
    QuackBehavior *_quck_behavior;
};

Duck::~Duck() {
    if (_fly_behavior) {
        delete _fly_behavior;
    }
    _fly_behavior = nullptr;

    if (_quck_behavior) {
        delete _quck_behavior;
    }
    _quck_behavior = nullptr;
}

class MallardDuck : public Duck {
public:
    MallardDuck() : Duck() {}
    explicit MallardDuck(const std::string& name) : Duck(name, new FlyWithWings(), new Quack()) {}
    ~MallardDuck() {}

    virtual void display() override final {
        std::cout << "I'm a real Mallard duck" << std::endl;
    }
};


int main(void)
{
    std::cout << "Hello GDB " << std::endl;
    // demo duck
    MallardDuck mallar_duck;
    mallar_duck.performFly();
    mallar_duck.performQuck();

    MallardDuck md2("lambda");
    md2.performFly();
    md2.performQuck();
}
