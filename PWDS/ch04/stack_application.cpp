

#include "SqStack.h"

#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#include <string>
#include <iostream>
// 中缀表达式转后缀表达式

// 规则： 从左到右遍历中缀表达式的每个数字和符号，若是数字就输出，即成为后缀表达式的一部分；
//      若是符号，则判断其与栈顶符号的优先级，是右括号或低优先级低于栈顶符号（乘除优先加减）
//      则栈顶元素依次出栈并输出，并将当前符号进栈，一直到最终输出后缀表达式为止。

std::string infixToSuffix(const char *expression)
{
    size_t len = strlen(expression);    
    char result[2*len];
    SqStack<char, 128> symbol;
    bool isSymbol = false;
    size_t numCount = 0;
    for (size_t i = 0; i < len; ++i)
    {
        if (isdigit(expression[i]))
        {
            //result[numCount++] = ' ';
            if (isSymbol)
                result[numCount++] = ' ';
            isSymbol = false;    
            result[numCount++] = expression[i];
        }
        else 
        {
            isSymbol = true; 
            if (!symbol.empty())
            {
                char ch;
                switch(expression[i])
                {
                    case '+':
                    case '-':
                    {
                        ch = symbol.top();
                        if (ch == '*' || ch == '/') // 优先级低于栈顶运算符
                        {
                            result[numCount++] = ' ';
                            result[numCount++] = ch;
                            symbol.pop();
                            while (!symbol.empty()) // 栈顶元素依次出栈并输出
                            {
                                ch = symbol.top();
                                if (ch == '(')
                                {
                                    symbol.push(expression[i]);
                                    break;
                                }
                                else  
                                {
                                    result[numCount++] = ' ';
                                    result[numCount++] = ch;
                                }
                                symbol.pop();
                            }
                            // 将当前元素进栈
                            symbol.push(expression[i]);    
                        }
                        else  
                        {
                            symbol.push(expression[i]);
                        }
                    }
                    break;
                    // case '-':
                    // break;
                    case '*':
                    case '/':
                    case '(':
                    {
                        symbol.push(expression[i]);
                    }
                    break;
                    // case '/':
                    // break;
                    // case '(':
                    // break;
                    case ')':
                    {
                        while (!symbol.empty()) // 栈顶元素依次出栈并输出
                        {
                            ch = symbol.top();
                            symbol.pop();
                            if (ch == '(')
                            {
                                while (!symbol.empty())
                                {
                                    ch = symbol.top();
                                    if (ch == '*' || ch == '/')
                                    {
                                        result[numCount++] = ' ';
                                        result[numCount++] = ch;
                                        symbol.pop();                
                                    }
                                    else  
                                    {
                                        break;
                                    }
                                }
                                break;
                            }
                            else  
                            {
                                result[numCount++] = ' ';
                                result[numCount++] = ch;
                            }
                        }      
                    }
                    break;
                    case ' ':
                    break;
                    default:
                        break;
                }
            }
            else  
            {
                symbol.push(expression[i]);
            }          
        }
    }

    while (!symbol.empty()) // 栈中符号全部出栈
    {
        char ch = symbol.top();
        symbol.pop();
        result[numCount++] = ' ';
        result[numCount++] = ch;
    }
    result[numCount++] = ' ';
    result[numCount] = '\0';
    return std::string(result);     
}

// 后缀表达式计算结果
// 规则： 从左到右遍历表达式的每个数字和符号，遇到是数字就进栈，
//       遇到是符号，就将处于栈顶的两个数字出栈，进行计算，运算结果进栈，一直到最终获得结果。
inline
int calculate(const char ch, int v1, int v2)
{
    int ret;
    switch(ch)
    {
        case '+':
            ret = v1 + v2;
        break;
        case '-':
            ret = v1 - v2;
        break;
        case '*':
            ret = v1 * v2;
        break;
        case '/':
            ret = v1 / v2;  
        break;
        default:
            break;         
    }
    return ret;
}
int calculateSuffixExpression(std::string &expression)
{

    SqStack<int, 128> number;
    char numstr[12] = {0};
    int numCount = 0;
    int numtmp = 0;
    for (size_t i = 0; i < expression.length(); ++i)
    {
        if (isdigit(expression[i]))
        {
            numstr[numCount++] = expression[i];
        }
        else  
        {
            if (expression[i] == ' ')
            {
                switch (numCount)
                {
                    case 0:
                        continue;
                    case 1:
                        numtmp = numstr[0] - '0';
                        break;
                    default:
                        numstr[numCount] = '\0';
                        numtmp = atoi(numstr);
                        break;
                }
                //std::cout << "push: " << numtmp << std::endl;
                number.push(numtmp); 
                numCount = 0;                               
            }
            else  
            {
                int top1 = number.top();
                number.pop();
                int top2 = number.top();
                number.pop();
                numtmp = calculate(expression[i], top2, top1);
                //std::cout << "top2:" << top2 << expression[i] << "top1:" << top1 << " numtmp: " << numtmp << std::endl;
                number.push(numtmp);                
            }
        }
    }
    return number.top();
}

int main(void)
{

    const char *expre = "9+(312-1)*3+10/2";// 9 312 1 - 3 * + 1 0 2 / +
    const char *expre1 = "6+3*(9-7)-8/2";//6397-*+82/- 
    const char *expre2 = "(8-2)/(3-1)*(9-6)"; // 82-31-/96-* 
    const char *expre3 = "((23*(3+(8-1)*3)+2)-(9/3))";
    //std::cout << infixToSuffix(expre1) << std::endl;

    std::string str = infixToSuffix(expre);
    int ret = calculateSuffixExpression(str);
    std::cout << str << "\n ret: " << ret << std::endl;

    str = infixToSuffix(expre1);
    ret = calculateSuffixExpression(str);
    std::cout << str << "\n ret: " << ret << std::endl; 

    str = infixToSuffix(expre2);
    ret = calculateSuffixExpression(str);
    std::cout << str << "\n ret: " << ret << std::endl; 

    str = infixToSuffix(expre3);
    ret = calculateSuffixExpression(str);
    std::cout << str << "\n ret: " << ret << std::endl;

    return 0;
}