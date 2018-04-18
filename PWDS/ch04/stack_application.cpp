

#include "SqStack.h"

#include <string.h>
#include <ctype.h>

#include <string>
// 中缀表达式转后缀表达式

// 规则： 从左到右遍历中缀表达式的每个数字和符号，若是数字就输出，即成为后缀表达式的一部分；
//      若是符号，则判断其与栈顶符号的优先级，是右括号或低优先级低于栈顶符号（乘除优先加减）
//      则栈顶元素依次出栈并输出，并将当前符号进栈，一直到最终输出后缀表达式为止。



std::string infixToSuffix(const char *expression)
{
    size_t len = strlen(expression);    
    //char strint[12] = {0};
    char result[2*len] = {0};
    SqStack<char, len> symbol;

    size_t numCount = 0;
    for (size_t i = 0; i < len; ++i)
    {
        if (isdigit(expression[i]))
        {

            //strint[numCount++] = expression[i];
            result[numCount++] = expression[i];
        }
        else 
        {
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
                                    symbol.pop();
                                    symbol.push(expression[i]);
                                    break;
                                }
                                else  
                                {
                                    result[numCount++] = ' ';
                                    result[numCount++] = ch;
                                }
                            }    
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
                    break;
                    case '/':
                    break;
                    case '(':
                    break;
                    case ')':
                    break;
                    default:
                        break;
                }
            }
            else  
            {
                symbol.push(expression[i]);
            }
            //result[numCount++] = ' ';
            
        }
    }
}














int main(void)
{


    return 0;
}