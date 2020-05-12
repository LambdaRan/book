
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Strategy {
public:
    Strategy() = default;
    virtual ~Strategy() = default;

    virtual std::string DoAlgorithm(const std::vector<std::string> &data) const = 0;
};

class Context {
public:
    Context(Strategy* strategy = nullptr) :_strategy(strategy) {}
    virtual ~Context() = default;

    void SetStrategy(Strategy* strategy) {
        _strategy = strategy;
    }

    void DoSomeBussinessLogic() const {
        std::cout << "Context: Sorting data using the strategy (not sure how it'll do it)\n";
        std::string result = _strategy->DoAlgorithm(std::vector<std::string>{"a", "e", "c", "b", "d"});
        std::cout << result << std::endl;
    }

private:
    Strategy* _strategy;
};

class ConcreteStrategyA : public Strategy {
public:
    ConcreteStrategyA() = default;
    ~ConcreteStrategyA() = default;

    std::string DoAlgorithm(const std::vector<std::string>& data) const override {
        std::string result;
        for (const auto& str : data) {
            result += str;
        }
        std::sort(result.begin(), result.end());
        return result;
    }
};

class ConcreteStrategyB : public Strategy {
public:
    ConcreteStrategyB() = default;
    ~ConcreteStrategyB() = default;

    std::string DoAlgorithm(const std::vector<std::string> & data) const override {
        std::string result;
        for (const auto& str : data) {
            result += str;
        }
        std::sort(result.begin(), result.end());
        for (size_t i = 0; i < result.size()/2; ++i) {
            std::swap(result[i], result[result.size() - i -1]);
        }
        return result;
    }
};

void ClientCode() {
    ConcreteStrategyA csa;
    Context ctx(&csa);
    std::cout << "Client: Strategy is set to normal sorting.\n";
    ctx.DoSomeBussinessLogic();
    std::cout << "\n";
    std::cout << "Client: Strategy is set to reverse sorting.\n";
    ConcreteStrategyB csb;
    ctx.SetStrategy(&csb);
    ctx.DoSomeBussinessLogic();
}
int main() {

    ClientCode();
    return 0;
}