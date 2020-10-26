# 深度探索C++对象模型 （Inside the C++ Object Model）


## 第3章 Data语义学（The Semantics of Data）


### 3.3 Data Member的存取
#### Static Data Members
类静态数据成员不会存在每个类实例中，而是存在程序的data segment之中。类静态数据成员不会给类实例带来空间或执行时间上的额外负担。

若取一个静态数据成员的地址，会得到一个指向数据类型的指针，而不是一个指向其类成员的指针，因为静态成员变量并不内含在一个类对象之中。

#### Nonstatic Data Members
每一个非静态成员变量的偏移位置在编译时期即可获知，甚至如果成员属于一个基类子对象（派生自单一或多重继承串链）也是一样的。因此，存取一个非静态数据成员变量，其效率和存取一个C struct的成员或一个非派生类的成员是一样的。

通过指针访问类成员x的执行效率在是一个struct成员、一个类成员、单一继承、多继承的情况下是完全相同的。但是，如果类成员x是一个虚基类的成员，存取速度会稍微慢一点。

### 3.4 继承与Data Member
派生类的成员和基类成员的排列顺序，并未在C++ Standard中强制指定。
#### 只要继承不要多态（Inheritance without Polymorphism）
子类单一继承基类，并且基类中不包含虚函数。这种情况下并不会增加空间或存取时间上的额外负担。

C++语言保证出现在派生类中的基类子对象有其完整原样性。就是说，基类中如果有alignment增加的空间，在派生类中不会使用这些额外的空间存储成员变量，而是保证基类的空间的完整性。
如：基类成员变量1字节+padding3字节=4字节。派生成员变量1字节+基类4字节+padding 3字节=8字节。

#### 加上多态（Adding Polymorphism）
子类单一继承基类，并且基类中含有虚函数。这种情况会带来空间和存取时间上的额外负担。

* 导入一个和类有关的virtual table，用来存放类所声明的每一个virtual function的地址。这个virtual table元素个数一般而言是被声明的virtual function个数，再加上一个或两个slots（用于支持runtime type identification）。
* 在每一个类对象中增加一个vptr（虚函数表指针），提供执行期的连接，使每一个类对象能找到相应的virtual table。
* 加强constructor，使它能够为vptr设定初值，指向类所对应的virtual table。
* 加强destructor，使它能够取消"指向类相关virtual table"的vptr。

编译期把vptr放在类对象的哪里会更好？不同的编译期有不同的做法，有的放在类对象的前端，有的放在类对象的后端。
#### 多重继承（Multiple Inheritance）
多重继承的问题主要发生在派生类对象和其第二或后继的基类对象之间的转换。派生类对象的指针付给第二基类指针时存在转换，因为第二基类子对象的地址并不是派生类对象的起始位置。

存取第二或后继基类的成员变量，不需要付出额外的成本，因为这些成员变量的位置在编译期就已经固定。
#### 虚拟继承（Virtual Inheritance）
菱形继承问题。

第二个解决方法，是在virtual function table中存放virtual base class的offset。
### 3.5 对象成员的效率（Object Member Efficiency）
### 3.6 指向Data Members的指针（Pointer to Data Members）
成员在类对象中的偏移位置。
#### "指向Members的指针"的效率问题
使用指向数据成员的指针操作成员，在未优化的情况下会使用双倍的时间。但是优化后存取效率一样。


## 第四章 Function语意学（The Semantics of Function）
C++支持三种类型的成员函数：静态、非静态、虚拟成员函数。
### 4.1 Member的各种调用方式
三种类型的成员函数引入顺序：非静态成员函数 --> 虚拟成员函数 --> 静态成员函数
#### Nonstatic Member Function（非静态成员函数）
在编译的时候，成员函数会转化为非成员函数，对象this指针作为非成员函数的第一个形参。成员函数名经过mangling处理，成为程序中独一无二的行数名。
#### 名称的特殊处理（Name Mangling）
类的成员变量、成员函数在编译时都会经过name-mangling处理，转化为独一无二的名称。函数的重载其实是不同的函数。
#### Virutal Member Functions（虚拟成员函数）
虚拟成员函数名字也会参与name-mangling。
#### Static Member Functions （静态成员函数）
静态成员函数的特性：
* 它不能够直接存取其类中的非静态成员。（因为它没有对象this指针。）
* 它不能够声明为const、volatile后virtual。（因为它没有对象this指针。）
* 它不需要经由类对象才调用。（它可以通过类对象来调用静态成员函数）

如果取一个静态成员函数的地址，获得的将是其在内存中的位置，也就是其地址。由于静态成员函数没有this指针，所有其地址的类型并不是一个"指向类成员函数的指针"，而是一个"非成员函数指针"。
### 4.2 virtual Member Functions（虚拟成员函数）
虚函数的一般实现模型：每一个class有一个virtual table，内含该class之中有作用的virtual function的地址，然后每个object有一个vptr，指向virtual table的地址。

每一个虚函数都被指派一个固定的索引值，这个索引值在整个继承体系中保持与特定的虚函数的关系。

在单一继承情况下，多态时如何确定执行哪一个函数呢？
1. 每个虚函数在虚函数表中的索引值固定不变。
2. 原先虚函数表每个slot存放的是父类虚函数地址，子类覆写虚函数时，把自己实现的函数地址赋值到相应的虚函数slots中。
3. 每个虚函数在虚函数表中的索引在编译期是知道的，所以就可以知道该调用哪一个函数。` (*ptr->vptr[4])(ptr)`

#### 多重继承下的Virtual Functions
多重继承中支持virtual function，只要的问题是 在执行期间调整this指针。
比较有效率的解决办法时利用所谓的thunk方法。

在多重继承之下，一个派生类内含n个虚函数表，n为继承上层基类的个数。
#### 虚拟继承下的Virtual Functions
**建议：不要在虚基类中声明非静态成员。**
### 4.3 函数的效能
### 4.4 指向Mermber Function的指针
`double (Point::*pmf)() = &Point::z;` 指向类成员函数的指针，声明示例。
使用`classname::*`的形式声明一个指向成员函数的指针。`(C::*p)(parms)和(obj.*p)(args)`括号必不可少，原因是调用运算符的优先级要高于指针指向成员运算符的优先级。

使用一个成员函数指针，如果并不用于virtual function、多重继承、虚基类等情况的话，并不会比使用一个非成员函数指针的成本更高。
#### 支持"指向Virtual Member Functions"的指针
对一个虚成员函数取其地址，所能得到的只是其在虚函数表的索引值。
#### 在多重继承之下，指向Member Functions的指针
```c++
// 一般结构，用于支持在多重继承之下指向成员函数的指针
struct __mptr {
    int delta;
    int index;
    union {
        ptrtofunc faddr;
        int v_offset;
    };
};
```
#### "指向Member Functions之指针"的效率
### 4.5 Inline Functions
inline只是给编译器提的建议，编译器在某些情况下可能不会真正的inline代码。
#### 形式参数（Formal Arguments）
#### 局部变量（Local Variables）

## 第五章 构造、析构、拷贝语意学（Sematics of Construction,Destruction,and Copy）
#### 纯虚函数的存在（Presence of a Pure Virtual Function）
不要把析构函数定义为纯虚函数。
#### 虚拟规格的存在（Presence of a virtual specialization）
#### 虚拟规格中const的存在
最好不要在抽象基类中把虚函数定义为const。
#### 重新考虑class的声明
### 5.1 无继承情况下的对象构造
#### 抽象数据类型（Abstract Data type）
#### 为继承做准备
最好提供一个拷贝构造函数，在NRV优化下很有作用。
### 5.2 继承体系下的对象构造
拷贝赋值运算符一定要判断自赋值情况。
#### 虚拟继承（Virtual Inheritance）
#### vptr初始化语义学（The Semantics of the vptr Initialization）
在构造函数中调用虚函数，这个虚函数是此对象中的那个。
constructor的执行算法通常如下：
1. 在派生类的构造函数中，所有虚基类及上一层基类的构造函数会被调用。
2. 上述完成之后，**对象的vptr（s）被初始化，指向相关的virtual table（s）**
3. 如果有成员初始化列表的话，将在构造函数体内扩展开来。这必须在vptr被设定之后才做，以免有一个虚成员函数被调用。
4. 最后，执行程序员所提供的代码。
### 5.3 对象复制语意学（Object Copy Semantic）
不要在任何虚基类中声明数据。
### 5.4 对象的效能（Object Efficiency）
### 5.5 析构语意学（Semantic of Destruction）
destructor的函数执行流程：
1. destructor的函数体首先被执行。
2. 如果class拥有成员类对象，且其拥有析构函数，那么他们会以其声明顺序的相反顺序被调用。
3. 如果object内含一个vptr，现在被重新设定，指向适当基类的虚函数表。
4.
## 第六章 执行期语意学（Runtime Semantics）
### 6.1 对象的构造和析构（Object construction and destruction）
#### 全局对象
#### 局部静态对象（Local Static Object）
#### 对象数组（array of object）
### 6.2 new和delete运算符
#### 针对数据的new语意

