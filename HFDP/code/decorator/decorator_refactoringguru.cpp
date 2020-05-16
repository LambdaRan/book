
#include <iostream>
#include <string>

// 原始的类 可能是接口或者基类
class Component {
public:
    Component() =default;
    virtual ~Component() = default;

    virtual std::string Operation() const = 0;
};

// 基础组件，实现组件的基本功能
class ConcreteComponent : public Component {
public:
    ConcreteComponent() =default;
    ~ConcreteComponent() = default;

    virtual std::string Operation() const override {
        return "ConcreteComponent";
    }
};


// 装饰者类基类/接口，定义所有装饰者遵循的接口，包含一个组件成员变量
class Decorator : public Component {
public:
    explicit Decorator(Component* component) : _component(component) {}
    virtual ~Decorator() {}

    virtual std::string Operation() const override {
        return _component->Operation();
    }

protected:
    Component* _component;
};

// 具体装饰者A
class ConcreteDecoratorA : public Decorator {
public:
    ConcreteDecoratorA(Component* component) : Decorator(component) {}
    ~ConcreteDecoratorA() {}

    std::string Operation() const override {
        return "ConcreteDecoratorA(" + Decorator::Operation() + ")";
    }
};

// 具体装饰者B
class ConcreteDecoratorB : public Decorator {
public:
    ConcreteDecoratorB(Component* component) : Decorator(component) {}
    ~ConcreteDecoratorB() {}

    std::string Operation() const override {
        return "ConcreteDecoratorB(" + Decorator::Operation() + ")";
    }
};

void ClientCode(Component* component) {
    std::cout << "RESULT:" << component->Operation();
}

int main() {

    Component* simple = new ConcreteComponent;
    std::cout << "Client: I've got a simple component:\n";
    ClientCode(simple);
    std::cout << "\n\n";

    Component* decorator1 = new ConcreteDecoratorA(simple);
    Component* decorator2 = new ConcreteDecoratorB(decorator1);
    std::cout << "Client: Now I've got a decorated component:\n";
    ClientCode(decorator2);
    std::cout << "\n";

    delete simple;
    delete decorator1;
    delete decorator2;
    
    return 0;
}