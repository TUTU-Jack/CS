#pragma once
#include <iostream>
#include <set>
#include <map>

template <typename T>
class DisJoinSet;

/*并查集*/
template <typename T>
std::ostream & operator << (std::ostream &os,const DisJoinSet<T> &djset);

template <typename T>
class DisJoinSet {
public:
    DisJoinSet(int capacity = 10):capacity(capacity),size(0),parent(new T[capacity+1]),data(new T[capacity+1]),S(new std::set<T>[capacity+1]) { };
    ~DisJoinSet() { delete[] parent;delete[] data;};
public:
    //查找集合根元素
    int findElem(const T &x);
    //插入集合元素
    DisJoinSet &insertSet(const T &data);
    //并集
    DisJoinSet &unionSet(const T &rx,const T &ry);

    friend std::ostream & operator << <T> (std::ostream &os,const DisJoinSet<T> &djset);
private:
    T *parent;          //集合元素下标
    T *data;            //节点数据
    int capacity;       //集合容量
    int size;           //集合元素个数
    std::map<T,int> m;  //映射，键值对，用于快速查询元素下标
    std::set<T> *S;     //集合
};

template <typename T>
int DisJoinSet<T>::findElem(const T &x)
{
    int temp;
    //迭代器查找集合元素
    auto it = m.find(x);
    //无该元素，返回 0
    if(it == m.end())
        return 0;
    //返回元素下标
    int rt = it->second;
    //不是集合根元素，迭代查找
    while(parent[rt] > 0)
        rt = parent[rt];
    
    //路径压缩算法（减小深度），提高集合元素查找速度，下次查找时无需迭代，O(1)
    for(int i = it->second;i != rt;i = temp)
    {
        temp = parent[i];
        //把集合中的每一个子集的下标变为集合根元素下标
        parent[i] = rt;
    }
    

    return rt;
}


template <typename T>
DisJoinSet<T> &DisJoinSet<T>::insertSet(const T &data)
{
    //集合容量满 或者 集合元素重复，退出
    if(size == capacity || findElem(data) != 0)
        return *this;
    //插入集合元素
    this->data[++size] = data;
    //插入元素默认为集合根元素 -1 （负数表示集合根元素，该值的绝对值表示该集合下的元素个数）
    this->parent[size] = -1;
    //插入键值对（快速索引）
    m[data] = size;
    S[size].insert(data);
    return *this;
}

template <typename T>
DisJoinSet<T> &DisJoinSet<T>::unionSet(const T &rx,const T &ry)
{
    //并入集合元素相等，退出
    if(rx == ry)
        return *this;
    //查找并入集合元素根元素，并集
    int rx_index = findElem(rx);
    int ry_index = findElem(ry);
    //属于同一集合，退出
    if(rx_index == ry_index)
        return *this;
    //低深度集合并入高深度集合，不增加集合深度
    if(parent[rx_index] > parent[ry_index])
    {
        //父集元素数量增加
        parent[ry_index] += parent[rx_index];
        //将子集并入父集（子集根元素父根元素下标为父集根元素下标）
        parent[rx_index] = ry_index;
        //集合元素插入
        S[ry_index].insert(S[rx_index].begin(),S[rx_index].end());
    }
    else
    {
        parent[rx_index] += parent[ry_index];
        parent[ry_index] = rx_index; 
        S[rx_index].insert(S[ry_index].begin(),S[ry_index].end());
    }

    return *this;

}

template <typename T>
std::ostream & operator << (std::ostream &os,const DisJoinSet<T> &djset)
{
    for(int i = 1;i <= djset.size;i++)
    {
        os << i << "\t" << djset.parent[i] << "\t" << djset.data[i] << std::endl;
        for(auto x : djset.S[i])
            os << x << " ";
        os << std::endl;
    }

    return os;
}