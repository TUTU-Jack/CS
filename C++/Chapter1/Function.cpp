#include "Function.h"
#include <iostream>

//全局变量
int globalVarible = 0;

//函数参数或返回值类型为普通变量
int Function(int a)
{
    std::cout << "形参：" << ++a << std::endl;
    return 0;
}

//函数参数或返回值类型为指针变量
int* Function(int *c)
{
    (*c)++;

    std::cout << "指针值：" << *c << std::endl;
    std::cout << "指针地址：" << c << std::endl << std::endl;
    return c;
}

//函数参数或返回值类型为变量的引用
const int& Function(int a,int &b)
{
    //静态局部变量，作用域为函数内部，但生命周期为全局
    static int staticLocalVarible = 0;
    staticLocalVarible++;

    b++;
    std::cout << "静态局部变量：" << staticLocalVarible << std::endl;
    std::cout << "静态局部变量地址：" << &staticLocalVarible << std::endl;
    std::cout << "引用：" << b << std::endl;
    std::cout << "引用地址：" << &b << std::endl << std::endl;

    return b;
}

//（由内向外）函数本身为 Function 参数为 const std::string &str，函数返回值为函数指针，指向的函数的参数为 int ，返回类型为 int
int (*Function(const std::string &str))(int)
{
    std::cout << "全局变量地址：" << &globalVarible << std::endl;
    std::cout << str << std::endl;

    return Function;
}

//回调函数：函数指针作为函数参数
void Function(void(*callbackFunction)(void *),void *para)
{
    std::cout << "调用回调函数:"; 
    callbackFunction(para);
}