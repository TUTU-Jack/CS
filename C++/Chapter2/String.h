#pragma once

#include <iostream>
#include <cstring>

class String {
public:
	//带参构造函数
	String(const char* str = 0);
	//拷贝构造函数
	String(const String& str);
	~String();
public:
	//赋值操作符重载
	String& operator = (const String& str);
	char* get_c_str() const { return pdata; };
private:
	char* pdata;
};

std::ostream& operator << (std::ostream& os, const String& str)
{
	return os << str.get_c_str();
}

inline String::String(const char* str)
{
	if (str)
	{
		pdata = new char[strlen(str) + 1];
		strcpy(pdata, str);
	}
	else
	{
		pdata = new char[1];
		*pdata = '\0';
	}
}

inline String::String(const String& str)
{
	pdata = new char[strlen(str.pdata) + 1];
	strcpy(pdata, str.pdata);

}

inline String::~String()
{
	delete[] pdata;
	std::cout << "Destructor created" << std::endl;
}

inline String& String::operator = (const String& str)
{
	//检测自我赋值
	if (&str == this)
		return *this;

	delete[] this->pdata;
	this->pdata = new char[strlen(str.pdata) + 1];
	strcpy(this->pdata, str.pdata);

	return *this;
}
