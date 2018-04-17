

#ifndef UNCOPYABLE_H
#define UNCOPYABLE_H

class Uncopyable
{
protected:
    Uncopyable() {}
    ~Uncopyable() {}
private:
    Uncopyable(const Uncopyable&);
    const Uncopyable& operator=(const Uncopyable&);
};

#endif // !NONCOPYABLE_H