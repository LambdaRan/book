

http://en.cppreference.com/w/cpp/algorithm/stable_sort

std::stable_sort

定义于头文件 <algorithm>
(1)	
    template< class RandomIt >
    void stable_sort( RandomIt first, RandomIt last );
(2)	(C++17 起)
    template< class ExecutionPolicy, class RandomIt >
    void stable_sort( ExecutionPolicy&& policy, RandomIt first, RandomIt last );
(3)	
    template< class RandomIt, class Compare >
    void stable_sort( RandomIt first, RandomIt last, Compare comp );
(4)	(C++17 起)
    template< class ExecutionPolicy, class RandomIt, class Compare >
    void stable_sort( ExecutionPolicy&& policy, RandomIt first, RandomIt last, Compare comp );

以升序排序范围 [first, last) 中的元素。保证保持相等元素的顺序。

1) 用 operator< 比较元素。
3) 用给定的比较函数 comp 比较元素。
2,4) 同 (1,3) ，但按照 policy 执行。
    这些重载不参与重载决议，除非 std::is_execution_policy_v<std::decay_t<ExecutionPolicy>> 为 true 。

参数
    first, last	-	要排序的元素范围
    policy	-	所用的执行策略。细节见执行策略。
    comp	-	比较函数对象（即满足比较 (Compare) 概念的对象），若第一参数小于（即先序于）第二参数则返回 ​true 。
    比较函数的签名应等价于如下者：
    bool cmp(const Type1 &a, const Type2 &b);
    签名不必拥有 const & ，但函数对象必须不修改传递给它的对象。
    类型 Type1 与 Type2 必须使得 RandomIt 类型的对象能在解引用后隐式转换到这两个类型。 ​

类型要求
    -RandomIt 必须满足 ValueSwappable 和 RandomAccessIterator 的要求。
    -解引用 RandomIt 结果的类型必须满足 MoveAssignable 和 MoveConstructible 的要求。

返回值
（无）

复杂度
O(N·log(N)2) 次应用 cmp ，其中 N = std::distance(first, last) 。若额外内存可用，则复杂度为 O(N·log(N)) 。

异常
    拥有名为 ExecutionPolicy 的模板参数的重载按下列方式报告错误：

    若作为算法一部分调用的函数的执行抛出异常，且 ExecutionPolicy 是三个标准策略之一，则调用 std::terminate 。
        对于任何其他 ExecutionPolicy ，行为是实现定义的。
    若算法无法分配内存，则抛出 std::bad_alloc 。

注意
    此函数试图分配等于待排序序列长度的临时缓冲区。若分配失败，则选择较低效的算法。

示例

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
 
struct Employee {
    Employee(int age, std::string name) : age(age), name(name) { } 
    int age;
    std::string name;  // 不参与比较
};
 
bool operator<(const Employee &lhs, const Employee &rhs) {
    return lhs.age < rhs.age;
}
 
int main()
{
    std::vector<Employee> v = { 
        Employee(108, "Zaphod"),
        Employee(32, "Arthur"),
        Employee(108, "Ford"),
    };  
 
    std::stable_sort(v.begin(), v.end());
 
    for (const Employee &e : v) {
        std::cout << e.age << ", " << e.name << '\n';
    }   
}

输出：
32, Arthur
108, Zaphod
108, Ford
