#pragma once
#include <iostream>


template <typename Elem>
class Linklist;

template <typename Elem>
std::ostream & operator << (std::ostream &os,const Linklist<Elem> &ll);

//链表节点元素（单向链表）
template <typename Elem>
struct Node {

    Elem data;          //节点元素
    Node* next;         //下一节点指针

    Node(const Elem &data):data(data),next(nullptr) { };
};

/*
 * 指针链接实现链式表结构
 * 插入平均时间复杂度 O(n/2)    最好 O(1) 插入在表头，最差 O(n) 插入在表尾
 * 删除平均时间复杂度 O(n/2)    最好 O(1) 删除表头，最差 O(n) 删除表尾
 * 查找时间复杂度 O(n)
 * 空间浪费在节点多一个指针
 */
template <typename Elem>
class Linklist {
public:
    Linklist():head(nullptr){ };
    ~Linklist() { delete[] head; };
private:
    Node<Elem>* head;
private:
    Node<Elem> *rfindNode(Node<Elem> *head,int index) const;
public:
    //查找某一位置节点
    Node<Elem> *findNode(int index) const;
    //插入节点
    Linklist &insert(int index,const Elem &data);
    //删除节点
    Linklist &remove(int index);
    //返回链表长度
    int Length() const;

    friend std::ostream & operator << <Elem>(std::ostream &os,const Linklist<Elem> &ll);
};

template <typename Elem>
Node<Elem>* Linklist<Elem>::rfindNode(Node<Elem> *head,int index) const
{
    int i = 1;
    //迭代查找，直到找到或者超出链表长度
    while(i < index && head != nullptr)
    {
        head = head->next;
        i++;
    }

    return head;
}

template <typename Elem>
Node<Elem>* Linklist<Elem>::findNode(int index) const 
{
    return rfindNode(this->head,index);
}

template <typename Elem>
Linklist<Elem>& Linklist<Elem>::insert(int index,const Elem &data)
{
    if(index <= 0)
        return *this;
    
    //头节点插入
    if(index == 1)
    {
        //创建新节点
        Node<Elem> *node = new Node<Elem>(data);
        //新节点指针链接头节点
        node->next = this->head;
        //头指针链接新节点
        this->head = node;

        return *this;
    }

    //找到被插入节点的前一个节点
    Node<Elem>* temp = findNode(index-1);

    //当前节点存在
    if(temp != nullptr)
    {
        //创建新节点
        Node<Elem> *node = new Node<Elem>(data);
        //新节点指针链接被插入位置原节点
        node->next = temp->next;
        //被插入位置的前一节点指针链接新节点
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
        //保存头节点
        Node<Elem> *temp = this->head;
        //头指针链接头节点一下节点
        this->head = temp->next;
        //删除节点
        delete[] temp;

        return *this;
    }

    //找到被删除节点的前一个节点
    Node<Elem> *temp = findNode(index-1);

    //被删除节点的前一个节点存在且被删除节点存在
    if(temp != nullptr && temp->next != nullptr)
    {
        //保存被删除节点
        Node<Elem> *temp1 = temp->next;
        //被删除节点前一节点指针链接被删除节点后一节点
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
