#pragma once
#include <iostream>

namespace Sq_Stack {

template <typename Elem>
class Stack;

template <typename Elem>
std::ostream & operator << (std::ostream &os,const Stack<Elem> &st);

template <typename Elem>
class Stack {
public:
    Stack(int capacity):capacity(capacity),top(-1),pdata(new Elem[capacity]){ };
    ~Stack() { delete[] pdata;};
private:
    Elem *pdata;
    int capacity;
    int top;
public:
    Stack &push(const Elem &data);
    Stack &pop();
    int Length() const { return top + 1;};
    Elem &getTop() const { return pdata[top];};
    bool isEmpty() { if(top == -1) return true; return false;};
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
    if(isFull())
        return *this;
    
    pdata[++top] = data;

    return *this;
}

template <typename Elem>
inline Stack<Elem>& Stack<Elem>::pop()
{
    if(isEmpty())
        return *this;
    top--;
    
    return *this;
}

}


