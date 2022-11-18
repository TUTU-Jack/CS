#pragma once
#include <iostream>


template <typename Elem>
class Linklist;

template <typename Elem>
std::ostream & operator << (std::ostream &os,const Linklist<Elem> &ll);

template <typename Elem>
struct Node {

    Elem data;
    Node* next;

    Node(const Elem &data):data(data),next(nullptr) { };
};

template <typename Elem>
class Linklist {
public:
    Linklist(const Elem &data):head(new Node<Elem>(data)){ };
    ~Linklist() { delete[] head; };
private:
    Node<Elem>* head;
public:
    Node<Elem> *FindNode(int index) const;
    Linklist &insert(int index,const Elem &data);
    Linklist &remove(int index);
    int Length() const;

    friend std::ostream & operator << <Elem>(std::ostream &os,const Linklist<Elem> &ll);
};

template <typename Elem>
Node<Elem>* Linklist<Elem>::FindNode(int index) const 
{
    int i = 1;

    Node<Elem> *temp = this->head;
    
    //依次查找，直到最后一个节点
    while(i < index && temp != nullptr)
    {
        temp = temp->next;
        i++;
    }
    
    return temp;
}

template <typename Elem>
Linklist<Elem>& Linklist<Elem>::insert(int index,const Elem &data)
{
    if(index <= 0)
        return *this;
    
    //头节点插入
    if(index == 1)
    {
        Node<Elem> *node = new Node<Elem>(data);
        node->next = this->head;
        this->head = node;

        return *this;
    }

    //找到被插入节点的前一个节点
    Node<Elem>* temp = FindNode(index-1);

    //当前节点存在
    if(temp != nullptr)
    {
        //std::cout << "h" << std::endl;
        Node<Elem> *node = new Node<Elem>(data);
        node->next = temp->next;
        temp->next = node;
    }

    return *this;
}

template <typename Elem>
Linklist<Elem>& Linklist<Elem>::remove(int index)
{
    if(index <= 0)
        return *this;
    
    //头节点删除
    if(index == 1)
    {
        Node<Elem> *temp = this->head;
        this->head = temp->next;
        delete[] temp;

        return *this;
    }

    //找到被删除节点的前一个节点
    Node<Elem> *temp = FindNode(index-1);

    //被删除节点的前一个节点存在且被删除节点存在
    if(temp != nullptr && temp->next != nullptr)
    {
        Node<Elem> *temp1 = temp->next;
        temp->next = temp1->next;
        delete[] temp1;
    }

    return *this;
}

template <typename Elem>
int Linklist<Elem>::Length() const
{
    int count = 0;
    Node<Elem> *temp = this->head;
    while(temp != nullptr)
    {
        temp = temp->next;
        count++;
    }

    return count;
}

template <typename Elem>
std::ostream & operator << (std::ostream &os,const Linklist<Elem> &ll)
{
    Node<Elem> *temp = ll.head;
    while(temp != nullptr)
    {
        os << temp->data << " ";
        temp = temp->next;
    }
    
    return os;
}
