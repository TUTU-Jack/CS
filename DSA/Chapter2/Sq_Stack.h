#pragma once
#include <iostream>

namespace Sq_Stack {

template <typename Elem>
class Stack;

template <typename Elem>
std::ostream & operator << (std::ostream &os,const Stack<Elem> &st);

/*
 *  顺序表实现栈数据结构（先入后出）
 *  插入时间复杂度 O(1)      
 *  删除时间复杂度 O(1) 
 *  查找时间复杂度 O(1) 只能返回栈顶元素
 *  空间占用不大
 *  需要事先规定元素个数
 */
template <typename Elem>
class Stack {
public:
    Stack(int capacity):capacity(capacity),top(-1),pdata(new Elem[capacity]){ };
    ~Stack() { delete[] pdata;};
private:
    Elem *pdata;        //栈元素
    int capacity;       //栈容量
    int top;            //栈顶（栈长度）
public:
    //入栈
    Stack &push(const Elem &data);
    //出栈
    Stack &pop();
    //栈长度
    int Length() const { return top + 1;};
    //栈顶元素
    Elem &getTop() const { return pdata[top];};
    //栈是否为空
    bool isEmpty() { if(top == -1) return true; return false;};
    //栈是否满
    bool isFull() { if(top == capacity -1) return true; return false;};

    friend std::ostream & operator << <Elem>(std::ostream &os,const Stack<Elem> &st);
};

template <typename Elem>
std::ostream & operator << (std::ostream &os,const Stack<Elem> &st)
{
    int i = 0;
    for(i = 0;i <= st.top;i++)
        os << st.pdata[i] << " ";
    
    return os;
}

template <typename Elem>
inline Stack<Elem>& Stack<Elem>::push(const Elem &data)
{
    //栈满
    if(isFull())
        return *this;
    //入栈，栈顶后移（栈长度增加）
    pdata[++top] = data;

    return *this;
}

template <typename Elem>
inline Stack<Elem>& Stack<Elem>::pop()
{
    //栈空
    if(isEmpty())
        return *this;
    //出栈，栈顶后移（栈长度减少）
    top--;
    
    return *this;
}

}


