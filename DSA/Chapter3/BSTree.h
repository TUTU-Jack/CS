#pragma once

#include <iostream>
#include "BinTree.h"

namespace BST {

//二叉搜索树
template <typename Elem>
class BSTree:public BT::BinTree<Elem> {
public:
    BSTree():root(nullptr) { };
    BSTree(const Elem &data):root(new BTNode<Elem>(data)) { };
    ~BSTree() { delete[] root; };
public:
    virtual void preOrderRecTrav() const override { BT::BinTree<Elem>::ppreOrderRecTrav(this->root); };
    virtual void midOrderRecTrav() const override { BT::BinTree<Elem>::pmidOrderRecTrav(this->root); };
    virtual void postOrderRecTrav() const override { BT::BinTree<Elem>::ppostOrderRecTrav(this->root); };

    virtual void preOrderIterTrav() const;
    virtual void midOrderIterTrav() const;
    virtual void postOrderIterTrav() const;

    virtual void layOrderTrav() const;

    //查找最大节点
    const BTNode<Elem> *findMax() const;
    //查找最小节点
    const BTNode<Elem> *findMin() const;
    //查找节点
    const BTNode<Elem> *findNode(const Elem &x) const;
    BSTree &insert(const Elem &data);
    BSTree &remove(const Elem &x);
protected:
    BTNode<Elem> *rfindMax(BTNode<Elem> *root) const;
    BTNode<Elem> *rfindMin(BTNode<Elem> *root) const;
    BTNode<Elem> *rfindNode(BTNode<Elem> *root,const Elem &x) const;
    BTNode<Elem> *rinsert(BTNode<Elem> *root,const Elem &data);
    BTNode<Elem> *rremove(BTNode<Elem> *root,const Elem &x);
private:
    BTNode<Elem> *root;
};

template <typename Elem>
inline void BSTree<Elem>::preOrderIterTrav() const
{
    std::vector<Elem> v = BT::BinTree<Elem>::preOrderIterTrav(this->root);
    for(int i = 0;i < v.size();i++)
        std::cout << v.at(i) << " ";

}

template <typename Elem>
inline void BSTree<Elem>::midOrderIterTrav() const
{
    std::vector<Elem> v = BT::BinTree<Elem>::midOrderIterTrav(this->root);
    for(int i = 0;i < v.size();i++)
        std::cout << v.at(i) << " ";

}

template <typename Elem>
inline void BSTree<Elem>::postOrderIterTrav() const
{
    std::vector<Elem> v = BT::BinTree<Elem>::postOrderIterTrav(this->root);
    std::reverse(v.begin(),v.end());
    for(int i = 0;i < v.size();i++)
        std::cout << v.at(i) << " ";

}

template <typename Elem>
inline void BSTree<Elem>::layOrderTrav() const
{
    std::vector<Elem> v = BT::BinTree<Elem>::layOrderTrav(this->root);
    for(int i = 0;i < v.size();i++)
        std::cout << v.at(i) << " ";
}

template <typename Elem>
inline BTNode<Elem> *BSTree<Elem>::rfindMax(BTNode<Elem> *root) const
{
    if(root->right == nullptr)
        return root;
    return rfindMax(root->right);
}

template <typename Elem>
inline const BTNode<Elem> *BSTree<Elem>::findMax() const
{
    return rfindMax(this->root);
}

template <typename Elem>
inline BTNode<Elem> *BSTree<Elem>::rfindMin(BTNode<Elem> *root) const
{
    if(root->left == nullptr)
        return root;
    return rfindMin(root->left);
}

template <typename Elem>
inline const BTNode<Elem> *BSTree<Elem>::findMin() const
{
    return rfindMin(this->root);
}

template <typename Elem>
inline BTNode<Elem> *BSTree<Elem>::rfindNode(BTNode<Elem> *root,const Elem &x) const
{
    if(root == nullptr)
        return root;

    //左子树递归
    if(x < root->data)
        root = rfindNode(root->left,x);
    //右子树递归
    else if(x > root->data)
        root = rfindNode(root->right,x);

    return root;
    
}

template <typename Elem>
inline const BTNode<Elem> *BSTree<Elem>::findNode(const Elem &x) const
{
    return rfindNode(this->root,x);
}

template <typename Elem>
BTNode<Elem> *BSTree<Elem>::rinsert(BTNode<Elem> *root,const Elem &data)
{
    if(root == nullptr)
        root = new BTNode<Elem>(data);
    else if(data < root->data)
        root->left = rinsert(root->left,data);
    else if(data > root->data)
        root->right = rinsert(root->right,data);

    return root;
}

template <typename Elem>
inline BSTree<Elem> &BSTree<Elem>::insert(const Elem &data)
{
    this->root = rinsert(this->root,data);

    return *this;
}

template <typename Elem>
BTNode<Elem> *BSTree<Elem>::rremove(BTNode<Elem> *root,const Elem &x)
{
    if(root == nullptr)
        return root;
    
    if(x < root->data)
        root->left = rremove(root->left,x);
    else if(x > root->data)
        root->right = rremove(root->right,x);
    else
    {
        BTNode<Elem> *temp;
        BTNode<Elem> *temp1;
        //被删除节点左右皆不为空，找到左子树的最大值（右子树的最小值）
        if(root->left && root->right)
        {
            temp = rfindMax(root->left);
            root->data = temp->data;

            //递归删除（查找被替换的节点，因为它最多只有一个左孩子，因此会进入另一个判断被删除）
            root->left = rremove(root->left,root->data);
            /* 迭代查找，然后删除（麻烦）
            //找到被替换节点的父节点
            temp1 = root->left;
            while(temp1->right != temp && temp1->right != nullptr)
            {
                temp1 = temp1->right;
            }

            //被替换节点无右子树，它本身就是最大值，因此把它的左子树挂在被删除节点的左节点
            if(temp1->right == nullptr)
                root->left = temp->left;
            else
                //将被删除（替换）的节点的左节点挂在被替换节点的父节点的右节点（防止被删除节点的左节点被遗失）
                //因为被删除节点为左子树的最大值，所以它只能是最后一个右节点，它最多只有一个左儿子
                temp1->right = temp->left;
            */
        }
        else
        {
            temp = root;
            std::cout << temp->data << std::endl;
            root = root->left ? root->left : root->right;
            delete[] temp;
        }

    }

    return root;
}

template <typename Elem>
inline BSTree<Elem> &BSTree<Elem>::remove(const Elem &x)
{
    this->root = rremove(this->root,x);

    return *this;
}

}