#pragma once
#include <iostream>

/*
 * 1.当不需要改变函数返回值时，将该函数定义为 const
 * 2.当不需要修改某个变量的值时，将该变量设置为 const
 * 3.传递参数时，尽量传引用，速度更快
 * 4.函数返回值是否为引用，看是否返回局部变量，返回局部变量不能返回引用，因为局部变量在作用域范围结束后会自动销毁，返回的是一个错误的变量空间
 * 5.引用是变量的别名，引用就是变量本身；指针是指向变量的变量
 * const 引用（引用传递，返回引用） 运算符重载 函数重载 this指针
 */
template <typename Elem>
class complex;

template <typename Elem>
complex<Elem> &_doapl(complex<Elem> &c1,const complex<Elem> &c2);

template <typename Elem>
class complex {
public:
	//带参构造函数
	complex(Elem r = 0, Elem i = 0) :rm(r), im(i) {};
public:
	//常成员函数
	Elem getReal() const { return rm; };
	Elem getImag() const { return im; };

	//操作符重载
	complex& operator += (const complex& c);
	complex& conj();

	bool operator == (const complex& c);
private:
	Elem rm, im;

	//友元函数
	friend complex<Elem> &_doapl <Elem>(complex<Elem> &c1,const complex<Elem> &c2);

};

template <typename Elem>
complex<Elem>& _doapl(complex<Elem>& c1, const complex<Elem>& c2)
{
	c1.rm += c2.rm;
	c1.im += c2.im;

	return c1;
}

template <typename Elem>
inline complex<Elem>& complex<Elem>::operator += (const complex<Elem>& c)
{
	return _doapl(*this, c);
}

template <typename Elem>
inline complex<Elem>& complex<Elem>::conj()
{
	this->im = -this->im;
	return *this;
}

template <typename Elem>
std::ostream& operator << (std::ostream & o, const complex<Elem>&c)
{
	return o << "(" << c.getReal() << "," << c.getImag() << ")";
}

template <typename Elem>
inline bool complex<Elem>::operator == (const complex<Elem>& c)
{
	return (this->rm == c.rm) && (this->im == c.im);
}

template <typename Elem>
complex<Elem> operator + (complex<Elem>& c1, complex<Elem>& c2)
{
	//使用类构造函数创建一个临时对象
	return complex<Elem>(c1.getReal() + c2.getReal(), c1.getImag() + c2.getImag());
}

template <typename Elem>
complex<Elem> operator + (complex<Elem>& c1,Elem rm)
{
	return complex<Elem>(c1.getReal() + rm, c1.getImag());
}