#include <iostream>
#include <string>

#include "Complex.h"
#include "String.h"
#include "Screen.h"

void test1()
{
    complex<double> c1(1, 2);
	complex<double> c2(1, 1);

	c1 += c2;

	c2 = c1 + c2;

	std::cout << "c1:" << c1 << " c2:" << c2 << std::endl;

	if (c1 == c2)
		std::cout << "complex is equal" << std::endl;

	c1 = c1 + 2.0;

	std::cout << "c1 Conjugate plural: " << c1.conj() << std::endl;
}

void test2()
{
    String s1(NULL);
	String s2("Hello World!");

	String s3(s1);

	std::cout << s3 << std::endl;

	s3 = s2;

	std::cout << s3 << std::endl;
}

void test3()
{
    Screen MyScreen('#',5,3);
    const Screen blank('r',5,3);
    MyScreen.set_char(2,2,'t').display(std::cout);
    std::cout << std::endl;
    blank.display(std::cout);

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

    switch(index)
    {
        case 1:
            test1();
            break;
        case 2:
            test2();
            break;
        case 3:
            test3();
            break;
        default:
            break;
    }

    return 0;
}