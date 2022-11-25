#pragma once
#include <iostream>

template <typename Elem>
class Sqlist;

template <typename Elem>
std::ostream & operator << (std::ostream &os,const Sqlist<Elem> &sl);

/*
 *  数组实现顺序表结构
 *  插入平均时间复杂度 O(n/2)       最好 O(1) 插入在表尾，最差 O(n) 插入在表头
 *  删除平均时间复杂度 O(n/2)       最好 O(1) 删除表尾，最差 O(n) 删除表头
 *  索引查找时间复杂度 O(1)
 *  值查找平均时间复杂度 O(n/2)     最好 O(1) 表头，最差 O(n) 表尾
 *  空间占用不大
 */
template <typename Elem>
class Sqlist {
public:
    typedef int size_t;
    Sqlist(size_t capacity):capacity(capacity),length(0) { this->data = new Elem[capacity]; };
    ~Sqlist() { delete[] data;};
public:
    //插入元素
    Sqlist &insert(size_t index,const Elem &data);
    //删除元素
    Sqlist &remove(size_t index);
    //查找某一元素
    int FindX(const Elem &data) const;
    //根据顺序表下标获取元素
    Elem &Find(size_t index) { return data[index - 1];};
    //返回顺序表长度
    size_t Length() const { return length;};
    //顺序表是否满
    bool isFull() { if(length == capacity) return true; return false;};
    //顺序表是否为空
    bool isEmpty() { if(length == 0) return true; return false;};

    friend std::ostream & operator << <Elem>(std::ostream &os,const Sqlist<Elem> &sl);
private:
    Elem *data;         //顺序表元素
    size_t capacity;    //顺序表容量
    size_t length;      //顺序表长度
};

template <typename Elem>
std::ostream & operator << (std::ostream &os,const Sqlist<Elem> &sl)
{
    int i = 0;
    for(i = 0;i < sl.length;i++)
        os << sl.data[i] << " ";
    return os;
}

template <typename Elem>
Sqlist<Elem>& Sqlist<Elem>::insert(size_t index,const Elem &data)
{
    int i = 0;
    //插入位置要合法，表不满
    if(index <= 0 || index > capacity || index > length+1 || isFull())
        return *this;

    //最后一个位置数据往后移，其余数据依次往后，直到被插入位置被空出来
    for(i = length - 1;i >= index - 1;i--)
        this->data[i+1] = this->data[i];
    //在某一位置插入元素
    this->data[index - 1] =  data;
    //长度增加
    this->length++;

    return *this;
}

template <typename Elem>
Sqlist<Elem>& Sqlist<Elem>::remove(size_t index)
{
    int i = 0;
    //删除位置合法，表不为空
    if(index <=0 || index > length || isEmpty())
        return *this;
    
    //被删除位置之后的数据顺序往前移，以此达到删除的目的
    for(i = index - 1;i < length;i++)
        this->data[i] = this->data[i+1];
    //表长度减少
    this->length--;

    return *this;
}

template <typename Elem>
int Sqlist<Elem>::FindX(const Elem &data) const
{
    size_t i = 0;
    //迭代查找
    while(this->data[i] != data && i < this->length)
        i++;
    
    if(this->data[i] != data)
        return -1;

    return i;
}


