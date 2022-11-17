#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstring>
#include "Function.h"


extern int globalVarible;

#define PI 3.1415926

//函数指针
using PF = int(*)(int);


void Print(void *arg)
{
    const std::string message = *(const std::string*)arg;
    std::cout << message << std::endl;
}

//变量与函数相关测试
void test1()
{
    int a = 0;
    //函数传形参，为值传递，不改变变量本身
    Function(a);
    std::cout << "a:" << a << std::endl << std::endl;

    int b = 0;
    //函数传实参，引用传递,函数返回值为常引用，不可更改引用变量值
    const int &reference = Function(a,b);
    std::cout << "varible b value:" << b << std::endl;
    std::cout << "varible b address:" << &b << std::endl;
    std::cout << "reference value:" << reference << std::endl;
    std::cout << "reference address:" << &reference << std::endl << std::endl;
    //reference = 3; error

    //函数内部有静态局部变量，再次调用，静态局部变量跳过初始化（只初始化一次），值继续更改
    Function(a,b);
    std::cout << "reference value:" << reference << std::endl << std::endl;

    //函数参数为指针变量，传入变量地址会改变变量值
    int *pointer = Function(&globalVarible);
    std::cout << "global varible value:" << globalVarible << std::endl;
    std::cout << "global varible address:" << &globalVarible << std::endl;
    std::cout << "pointer varible value:" << *pointer << std::endl;
    std::cout << "pointer varible address:" << pointer << std::endl << std::endl;


    //函数返回类型为函数指针
    PF ff = Function("Hello World");
    printf("Function address:%p\n",&ff);

    ff = Function;
    printf("Function address:%p\n",&ff);

    //回调函数
    const std::string message = "Hello World!";
    Function(Print,(void*)&message);
}

//分支判断、循环语句测试
void test2()
{
    int i = 0;
    int steps = 0;
    
    double angle;
    float sinVal = 0.0f;
    
    int num = 0,lastnum = 0,curnum = 0;
    double maxAngle = PI * 2;
    do
    {
        std::cout << "Input the number of steps: ";
        std::cin >> steps;
    }while(steps <= 0);
    
    

    for(i = 0;i <= steps;i++)
    {
        angle = (double)i / (double)steps * maxAngle;
        sinVal = sin(angle);
        lastnum = curnum;
        num = sinVal * 30 + 30;
        curnum = num;
        printf("%3d: %5.2f",i,angle);
    
        while(num--)
            std::cout << " ";
        
        if(fabs(sinVal) == 1)
            std::cout << "*" << std::endl;
        else
        {
            if(curnum > lastnum)
                printf("\\ \n");
            else
                printf("/\n");
        }
            
    }

}

//文件流测试
void test3(const char* inFileName,const char *outFileName)
{
    //输入流 （读文件）
    std::ifstream outputFile;
    //输出流 （写文件）
    std::ofstream inputFile;

    outputFile.open(outFileName,std::ios::in);
    inputFile.open(inFileName,std::ios::out);

    if(!outputFile.is_open())
    {
        std::cout << "读文件未打开"  << std::endl;
        return;
    }

    if(!inputFile.is_open())
    {
        std::cout << "写文件未打开"  << std::endl;
        return;
    }

    //获取文件大小
    outputFile.seekg(0,std::ios::end);
    std::streamsize size = outputFile.tellg();
    outputFile.seekg(0,std::ios::beg);

    char *str = new char[size];
    outputFile.read(str,size);
    
    inputFile.write(str,size);

    outputFile.close();
    inputFile.close();

    delete[] str;
}

//设备流测试
void test4()
{
    char sentence[1024];
    std::cout << "输入字符串：";
    //从键盘读取字符串到缓存中
    std::cin.getline(sentence,sizeof(sentence));
    //将缓存数据输出到屏幕上
    std::cout << sentence << std::endl;
}


int main(int argc,char *argv[])
{
    if(argc < 2)
    {
        std::cout << "Usage:" << argv[0] << " <test>" << std::endl;
        return 1;
    }

    int index = 0;

    if(strcmp(argv[1],"test1") == 0)
        index = 1;
    else if(strcmp(argv[1],"test2") == 0)
        index = 2;
    else if(strcmp(argv[1],"test3") == 0)
        index = 3;
    else if(strcmp(argv[1],"test4") == 0)
        index = 4;

    switch(index)
    {
        case 1:
            test1();
            break;
        case 2:
            test2();
            break;
        case 3:
            test3("file.txt","main.cpp");
            break;
        case 4:
            test4();
            break;
        default:
            break;
    }


    return 0;
}