#pragma once
#include <iostream>

namespace Link_Stack {

template <typename Elem>
struct Node {
    Elem data;
    Node *next;

    Node(const Elem &data):data(data),next(nullptr) { };
};

template <typename Elem>
class Stack;

template <typename Elem>
std::ostream & operator << (std::ostream &os,const Stack<Elem> &st);


/*
 *  链表实现栈数据结构（先入后出）
 *  插入时间复杂度 O(1)      
 *  删除时间复杂度 O(1) 
 *  查找时间复杂度 O(1) 只能返回栈顶元素
 *  空间占用节点多一个指针空间
 *  不用事先规定元素个数
 */
template <typename Elem>
class Stack {
public:
    Stack():top(nullptr) { };
    ~Stack() { delete[] top; };
public:
    Stack &push(const Elem &data);
    Stack &pop();
    bool isEmpty() const { if(top == nullptr) return true; return false; };
    int Length() const;
    Elem &getTop() const { if(isEmpty()) throw("Stack is empty!");return top->data;};

    friend std::ostream & operator << <Elem>(std::ostream &os,const Stack<Elem> &st);
private:
    Node<Elem> *top;

};

template <typename Elem>
std::ostream & operator << (std::ostream &os,const Stack<Elem> &st)
{
    Node<Elem> *temp = st.top;
    while(temp != nullptr)
    {
        os << temp->data << " ";
        temp = temp->next;
    }
    
    return os;
}

template <typename Elem>
Stack<Elem>& Stack<Elem>::push(const Elem &data)
{
    Node<Elem> *node = new Node<Elem>(data);

    //新节点指针指向头节点，之前插入的节点被压到下一个位置上（先入后出）
    node->next = top;
    //入栈，头指针指向新节点
    top = node;

    return *this;
}

template <typename Elem>
Stack<Elem>& Stack<Elem>::pop()
{
    Node<Elem> *temp = top;

    if(isEmpty())
        return *this;
    //出栈（最新入栈元素出栈，先入后出），头指针指向头节点下一节点
    top = temp->next;
    delete[] temp;

    return *this;
}

template <typename Elem>
int Stack<Elem>::Length() const
{
    int count = 0;
    Node<Elem> *temp = top;
    while(temp != nullptr)
    {
        count++;
        temp = temp->next;
    }

    return count;
}

}
