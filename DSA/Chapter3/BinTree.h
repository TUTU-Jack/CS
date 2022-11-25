#pragma once 

#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>

/*树节点*/
template <typename Elem>
struct BTNode {
    Elem data;          //节点数据
    BTNode *left;       //左孩子
    BTNode *right;      //右孩子

    int height;         //节点高度

    BTNode(const Elem &data):data(data),height(0),left(nullptr),right(nullptr) { };
};

namespace BT {

/*
 * 链表实现二叉树（树形数据结构），顺序表不好实现一般二叉树结构，因为左右孩子节点不好确认，除非增加信息（如父亲节点与孩子节点指针）
 * 重要思想递归：每个二叉树的子节点都可作为另一个二叉树的根节点，特点符合递归的特点（每一个大问题都是由具有相似结构（解法）的小问题组成）
 * 两种递归查找特点：（1）返回到根节点 （2）返回递归子节点
 * 普通二叉树插入时间复杂度 O(n)
 * 普通二叉树删除时间复杂度 O(n)
 * 普通二叉树查找时间复杂度 O(n)
 */
template <typename Elem>
class BinTree {
public:
    BinTree():root(nullptr) { };
    BinTree(const Elem &data):root(new BTNode<Elem>(data)) { };
    ~BinTree() { delete[] root; };
public:
    //前序（中 左 右）递归
    virtual void preOrderRecTrav() const { ppreOrderRecTrav(this->root); };
    //中序（左 中 右）递归
    virtual void midOrderRecTrav() const { pmidOrderRecTrav(this->root); };
    //后序（左 右 中）递归
    virtual void postOrderRecTrav() const { ppostOrderRecTrav(this->root); };

    //前序迭代
    virtual void preOrderIterTrav() const;
    //中序迭代
    virtual void midOrderIterTrav() const;
    //后序迭代
    virtual void postOrderIterTrav() const;

    //层序
    virtual void layOrderTrav() const;

    //查找节点
    const BTNode<Elem> *findNode(const Elem &x) const { return pfindNode(this->root,x); };
    //插入节点
    BinTree &insert(const Elem &x,int position,const Elem &data);
protected:
    void ppreOrderRecTrav(const BTNode<Elem> *root) const;
    void pmidOrderRecTrav(const BTNode<Elem> *root) const;
    void ppostOrderRecTrav(const BTNode<Elem> *root) const;

    std::vector<Elem> preOrderIterTrav(BTNode<Elem> *root) const;
    std::vector<Elem> midOrderIterTrav(BTNode<Elem> *root) const;
    std::vector<Elem> postOrderIterTrav(BTNode<Elem> *root) const;

    std::vector<Elem> layOrderTrav(BTNode<Elem> *root) const;


    BTNode<Elem> *pfindNode(BTNode<Elem> *root,const Elem &x) const;
private:
    BTNode<Elem> *root;

};

template <typename Elem>
void BinTree<Elem>::ppreOrderRecTrav(const BTNode<Elem> *root) const
{
    //递归退出条件（节点为空）
    if(root == nullptr)
        return;
    std::cout << root->data << " ";
    ppreOrderRecTrav(root->left);
    ppreOrderRecTrav(root->right);
}

template <typename Elem>
void BinTree<Elem>::pmidOrderRecTrav(const BTNode<Elem> *root) const
{
    if(root == nullptr)
        return;
    pmidOrderRecTrav(root->left);
    std::cout << root->data << " ";
    pmidOrderRecTrav(root->right);
}

template <typename Elem>
void BinTree<Elem>::ppostOrderRecTrav(const BTNode<Elem> *root) const
{
    if(root == nullptr)
        return;
    ppostOrderRecTrav(root->left);
    ppostOrderRecTrav(root->right);
    std::cout << root->data << " ";

}

//用栈数据结构模拟递归（在计算机中递归的物理性质用的就是栈空间（函数调用））
template <typename Elem>
std::vector<Elem> BinTree<Elem>::preOrderIterTrav(BTNode<Elem> *root) const
{
    //向量，用于存放节点数据
    std::vector<Elem> v;
    //栈，模拟递归
    std::stack<BTNode<Elem>*> s;

    //持续迭代直到栈空
    while(root != nullptr || !s.empty())
    {
        //迭代到左树最左边节点
        while(root != nullptr)
        {
            //左子树节点入栈
            s.push(root);
            //入栈节点数据存入向量（前序）
            v.push_back(root->data);
            root = root->left;
        }
        //出栈，向右查找
        if(!s.empty())
        {
            //返回栈顶元素
            root = s.top();
            //左节点出栈（递归到最后一个左节点）
            s.pop();
            //转向子树根节点的右子树
            root = root->right;
        }
    }

    return v;

}

template <typename Elem>
std::vector<Elem> BinTree<Elem>::midOrderIterTrav(BTNode<Elem> *root) const
{
    std::vector<Elem> v;
    std::stack<BTNode<Elem>*> s;

    while(root != nullptr || !s.empty())
    {
        while(root != nullptr)
        {
            s.push(root);
            root = root->left;
        }

        if(!s.empty())
        {
            root = s.top();
            s.pop();
            //出栈节点存入向量，中序（左子树递归完成后输出）
            v.push_back(root->data);
            root = root->right;
        }
    }

    return v;
}

template <typename Elem>
std::vector<Elem> BinTree<Elem>::postOrderIterTrav(BTNode<Elem> *root) const
{
    std::vector<Elem> v;
    std::stack<BTNode<Elem>*> s;

    //后序（左 右 中 -> 右 左 中 -> 中 左 右）
    while(root != nullptr || !s.empty())
    {
        while(root != nullptr)
        {
            s.push(root);
            v.push_back(root->data);
            root = root->right;
        }

        if(!s.empty())
        {
            root = s.top();
            s.pop();
            root = root->left;
        }
    }

    return v;

}

template <typename Elem>
void BinTree<Elem>::preOrderIterTrav() const
{
    std::vector<Elem> v = preOrderIterTrav(this->root);
    for(int i = 0;i < v.size();i++)
        std::cout << v.at(i) << " ";

}

template <typename Elem>
void BinTree<Elem>::midOrderIterTrav() const
{
    std::vector<Elem> v = midOrderIterTrav(this->root);
    for(int i = 0;i < v.size();i++)
        std::cout << v.at(i) << " ";

}

template <typename Elem>
void BinTree<Elem>::postOrderIterTrav() const
{
    std::vector<Elem> v = postOrderIterTrav(this->root);
    //输出结果翻转实现后序遍历
    std::reverse(v.begin(),v.end());
    for(int i = 0;i < v.size();i++)
        std::cout << v.at(i) << " ";

}

//利用队列数据结构实现层序遍历（先入先出，因此父子节点入队列后，父亲节点先出队列，因为是层序，所以不需要保存根节点）
template <typename Elem>
std::vector<Elem> BinTree<Elem>::layOrderTrav(BTNode<Elem> *root) const
{
    std::queue<BTNode<Elem>*> q;
    std::vector<Elem> v;

    q.push(root);
    while(root != nullptr && !q.empty())
    {
        //元素输出
        v.push_back(root->data);
        //出队列
        q.pop();

        //左孩子入队列
        if(root->left)
            q.push(root->left);
        //右孩子入队列
        if(root->right)
            q.push(root->right);

        //队首,向下迭代
        root = q.front();
    }

    return v;

}

template <typename Elem>
void BinTree<Elem>::layOrderTrav() const
{
    std::vector<Elem> v = layOrderTrav(this->root);
    for(int i = 0;i < v.size();i++)
        std::cout << v.at(i) << " ";
}

template <typename Elem>
BTNode<Elem> *BinTree<Elem>::pfindNode(BTNode<Elem> *root,const Elem &x) const
{
    //中间节点，保存返回节点（因为不保存的话，查找节点递归是返回到根节点的）
    BTNode<Elem> *temp;
    if(root == nullptr || root->data == x)
        return root;

    //左子树递归
    temp = pfindNode(root->left,x);
    //左子树递归返回节点不为空找到，返回为空，右子树递归
    return temp ? temp : pfindNode(root->right,x);
}

template <typename Elem>
BinTree<Elem> &BinTree<Elem>::insert(const Elem &x,int position,const Elem &data)
{
    BTNode<Elem> *temp = pfindNode(this->root,x);

    if(temp)
    {
        BTNode<Elem> *node = new BTNode<Elem>(data);
        if(position == 0)
        {
            if(temp->left == nullptr)
                temp->left = node;
        }
        else
        {
            if(temp->right == nullptr)
                temp->right = node;
        }

    }

    return *this;

}


}