#pragma once
#include <iostream>

template <typename Elem>
class Sqlist;

template <typename Elem>
std::ostream & operator << (std::ostream &os,const Sqlist<Elem> &sl);

template <typename Elem>
class Sqlist {
public:
    typedef int size_t;
    Sqlist(size_t capacity,const Elem &data):capacity(capacity),length(1) { this->data = new Elem[capacity];this->data[0] = data;};
    ~Sqlist() { delete[] data;};
public:
    Sqlist &insert(size_t index,const Elem &data);
    Sqlist &remove(size_t index);
    int FindX(const Elem &data) const;
    Elem &Find(size_t index) { return data[index - 1];};
    size_t Length() const { return length;};
    bool isFull() { if(length == capacity) return true; return false;};
    bool isEmpty() { if(length == 0) return true; return false;};

    friend std::ostream & operator << <Elem>(std::ostream &os,const Sqlist<Elem> &sl);
private:
    Elem *data;
    size_t capacity;
    size_t length;
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
    if(index <= 0 || index > capacity || index > length+1 || isFull())
        return *this;

    //最后一个位置数据往后移，其余数据依次往后，直到被插入位置
    for(i = this->length - 1;i >= index - 1;i--)
        this->data[i+1] = this->data[i];
    
    this->data[index - 1] =  data;
    this->length++;

    return *this;
}

template <typename Elem>
Sqlist<Elem>& Sqlist<Elem>::remove(size_t index)
{
    int i = 0;
    if(index <=0 || index > length || isEmpty())
        return *this;
    
    //被删除位置之后的数据顺序往前移
    for(i = index - 1;i < length;i++)
        this->data[i] = this->data[i+1];

    this->length--;

    return *this;
}

template <typename Elem>
int Sqlist<Elem>::FindX(const Elem &data) const
{
    size_t i = 0;
    while(this->data[i] != data && i < this->length)
        i++;
    
    if(this->data[i] != data)
        return -1;

    return i;
}


