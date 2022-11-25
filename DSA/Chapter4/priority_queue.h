#pragma once
#include <iostream>

template <typename Elem>
class PriorityQueue;

template <typename Elem>
std::ostream & operator << (std::ostream &os,const PriorityQueue<Elem> &pq)
{
    for(int i = 1;i <= pq.size;i++)
        os << pq.data[i] << " ";
    return os;
}

/*
 * 用堆数据结构实现优先级队列操作（最小堆/最大堆：孩子节点都比父节点大/小）
 * 堆：用数组实现的完全二叉树
 * 重要操作：上浮 、下浮
 * 插入时间复杂度 O(logN),上浮操作二分法
 * 删除时间复杂度 O(logN),下浮操作二分法
 * 查找时间复杂度 O(1) 高优先级的先出
 * 空间占用小
 */

template <typename Elem>
class PriorityQueue {
public:
    //容量加 1，数组第零个位置不用（方便计算父子节点位置 i/2 父节点，i * 2 左孩子， i * 2 + 1 右孩子）
    PriorityQueue(int capacity):capacity(capacity),data(new Elem[capacity+1]),size(0) { };
    ~PriorityQueue() { delete[] data;};
public:
    bool isEmpty() const;
    bool isFull() const;
    //向上浮动
    void percolateUp(int index);
    //向下浮动
    void percolateDown(int index);
    PriorityQueue &insertHeap(const Elem &data);
    PriorityQueue &removeHeap();
    Elem getTop();
private:
    Elem *data;
    int capacity;
    int size;

public:
    friend std::ostream & operator << <Elem> (std::ostream &os,const PriorityQueue<Elem> &pq);
};

template <typename Elem>
inline bool PriorityQueue<Elem>::isEmpty() const
{
    if(size == 0)
        return true;
    return false;
}

template <typename Elem>
inline bool PriorityQueue<Elem>::isFull() const
{
    if(size == capacity)
        return true;
    return false;
}

//向上浮动，在最后一个位置插入数据后可能造成最小堆/最大堆的性质消失，这时需要与父节点一一比较，然后替换
template <typename Elem>
void PriorityQueue<Elem>::percolateUp(int index)
{
    //保存比较值（插入值）
    Elem x = data[index];
    int i = 0;
    //与父节点比较，如果比父节点小，则上浮（孩子节点值为父节点值，大值往下），直到树根节点
    for(i = index;i > 1 && x < data[i/2];i /= 2)
        data[i] = data[i/2];
    
    //调整位置
    data[i] = x;
    
}

template <typename Elem>
void PriorityQueue<Elem>::percolateDown(int index)
{
    //保存比较值（删除值）
    Elem x = data[index];
    //child 用于区分左右孩子
    int i = 0,child = 0;
    //与左右孩子比较，直到最后一个节点
    for(i = index;i*2 <= this->size;i = child)
    {
        //先让孩子节点为左孩子
        child = i * 2;
        //左右孩子比较，取较小的一个与删除值比较，不能越界
        if(data[child] > data[child+1] && child != this->size)
            child++;
        //比较值大于最小孩子，向下浮动（父节点值为孩子节点值，小值往上），找到则退出循环
        if(x > data[child])
            data[i] = data[child];
        else
            break;
    }

    //调整位置
    data[i] = x;
}

template <typename Elem>
PriorityQueue<Elem> &PriorityQueue<Elem>::insertHeap(const Elem &data)
{
    if(isFull())
        return *this;
    
    //插入到最后一个位置，从数组第一个元素开始插入，依次往后
    this->data[++this->size] = data;
    //向上浮动
    percolateUp(this->size);
    
    return *this;
}

template <typename Elem>
PriorityQueue<Elem> &PriorityQueue<Elem>::removeHeap()
{
    if(isEmpty())
        return *this;

    //将最后一个节点的值放到第一个节点以此删除节点（防止破坏完全二叉树结构）
    this->data[1] = this->data[this->size--];
    //向下浮动
    percolateDown(1);

    return *this;
}

template <typename Elem>
Elem PriorityQueue<Elem>::getTop()
{
    if(isEmpty())
        throw -1;
    return this->data[this->size];
}


