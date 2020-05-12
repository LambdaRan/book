
#include <iostream>
#include <string>
#include <list>


class IObserver {
public:
    virtual ~IObserver() {}
    virtual void Update(const std::string& message_from_subject) = 0;
};

class ISubject {
public:
    virtual ~ISubject() {};
    virtual void Attach(IObserver *observer) = 0;
    virtual void Detach(IObserver *observer) = 0;
    virtual void Notify() = 0;
};

class Subject : public ISubject {
public:
    Subject() = default;
    virtual ~Subject() {
        std::cout << "Goodbye! I was the subject." << std::endl;
    }

    void Attach(IObserver *observer) override {
        _list_observers.emplace_back(observer);
    }

    void Detach(IObserver *observer) override {
        _list_observers.remove(observer);
    }

    void Notify() override {
        HowManyObserver();
        for (const auto observer : _list_observers) {
            observer->Update(_message);
        }
    }

    void CreateMessage(const std::string& message = "Empty") {
        this->_message = message;
        Notify();
    }

    void HowManyObserver() {
        std::cout << "There are " << _list_observers.size() << " observers in the list.\n";
    }

    void SomeBusinessLogic() {
        _message = "change message message";
        Notify();
        std::cout << "I'm about to do some thing important\n";
    }

private:
    std::list<IObserver*> _list_observers;
    std::string _message;
};

class Observer : public IObserver {
public:
    Observer(Subject& subject)
            : _subject(subject),
              _number(0)
    {
        _subject.Attach(this);
        std::cout << "Hi, I'm the Observer \"" << ++Observer::_static_number << "\".\n";
        _number = _static_number;
    }

    virtual ~Observer() {
        std::cout << "Goodbye, I was the Observer \"" << _number << "\".\n";
    }

    void Update(const std::string& message_from_subject) override {
        _message_from_subject = message_from_subject;
        PrintInfo();
    }

    void RemoveMeFromTheList() {
        _subject.Detach(this);
        std::cout << "Observer \"" << _number << "\" removed from the list.\n";
    }

    void PrintInfo() {
        std::cout << "Observer \"" << _number << "\": a new message is available --> " << _message_from_subject << "\n";
    }

private:
    std::string _message_from_subject;
    Subject& _subject;
    static int _static_number;
    int _number;
};

int Observer::_static_number = 0;



void ClientCode() {
    Subject *subject = new Subject;
    Observer *observer1 = new Observer(*subject);
    Observer *observer2 = new Observer(*subject);
    Observer *observer3 = new Observer(*subject);
    Observer *observer4;
    Observer *observer5;

    subject->CreateMessage("Hello World! :D");
    observer3->RemoveMeFromTheList();

    subject->CreateMessage("The weather is hot today! :p");
    observer4 = new Observer(*subject);

    observer2->RemoveMeFromTheList();
    observer5 = new Observer(*subject);

    subject->CreateMessage("My new car is great! ;)");
    observer5->RemoveMeFromTheList();

    observer4->RemoveMeFromTheList();
    observer1->RemoveMeFromTheList();

    delete observer5;
    delete observer4;
    delete observer3;
    delete observer2;
    delete observer1;
    delete subject;
}

int main()
{
    ClientCode();
    return 0;
}
