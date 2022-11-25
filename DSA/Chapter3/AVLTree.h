#pragma once
#include "BSTree.h"

namespace AVL {

/*
 * 自平衡二叉搜索树（左右子树的高度差不超过1），因此可以使用二分查找，不会退化成链表
 * 重点：平衡操作
 * 插入时间复杂度 O(lgN)
 * 删除时间复杂度 O(lgN)
 * 查找时间复杂度 O(lgN)
 */
template <typename Elem>
class AVLTree:public BST::BSTree<Elem> {
public:
    AVLTree(const Elem &data):root(new BTNode<Elem>(data)) { };
    ~AVLTree() { delete[] root; };
public:
    virtual void preOrderRecTrav() const override { BT::BinTree<Elem>::ppreOrderRecTrav(this->root); };
    virtual void midOrderRecTrav() const override { BT::BinTree<Elem>::pmidOrderRecTrav(this->root); };
    virtual void postOrderRecTrav() const override { BT::BinTree<Elem>::ppostOrderRecTrav(this->root); };

    virtual void preOrderIterTrav() const;
    virtual void midOrderIterTrav() const;
    virtual void postOrderIterTrav() const;

    virtual void layOrderTrav() const;
    AVLTree &insert(const Elem &data);
    AVLTree &remove(const Elem &x);
private:
    int height(BTNode<Elem> *root) const { if(root == nullptr) return -1; return root->height; };
    int max(int x,int y) { return (x > y) ? x : y; };

    //左左单旋（新插入节点在根节点的左子树的左子树）
    BTNode<Elem> *LLRotate(BTNode<Elem> *root);
    //右右单旋（新插入节点在根节点的右子树的右子树）
    BTNode<Elem> *RRRotate(BTNode<Elem> *root);
    //左右双旋（新插入节点在根节点的左子树的右子树）
    BTNode<Elem> *LRRotate(BTNode<Elem> *root);
    //右左单旋（新插入节点在根节点的右子树的左子树）
    BTNode<Elem> *RLRotate(BTNode<Elem> *root);

    BTNode<Elem> *rinsert(BTNode<Elem> *root,const Elem &data);
    BTNode<Elem> *rremove(BTNode<Elem> *root,const Elem &x);
private:
    BTNode<Elem> *root;
};

template <typename Elem>
BTNode<Elem> *AVLTree<Elem>::LLRotate(BTNode<Elem> *root)
{
    BTNode<Elem> *child = root;
    //根节点指向根节点的左子树（将左子树拉上来）
    root = root->left;
    //将原先左子树的右子树插入到原先根节点的左子树
    child->left = root->right;
    //将原先的根节点拉下来变为原先左子树的右子树（满足搜索二叉树右边节点比左边节点大的特点）
    root->right = child;

    //原先左子树根节点变为根节点，高度在原先的基础上加1
    child->height = max(height(child->left),height(child->right)) + 1;

    //返回旋转后的树根节点
    return root;
}

template <typename Elem>
BTNode<Elem> *AVLTree<Elem>::RRRotate(BTNode<Elem> *root)
{
    BTNode<Elem> *child = root;
    //根节点指向根节点的右子树（将右子树拉上来）
    root = root->right;
     //将原先右子树的左子树插入到原先根节点的右子树
    child->right = root->left;
    //将原先的根节点拉下来变为原先右子树的左子树（满足搜索二叉树右边节点比左边节点大的特点）
    root->left = child;

    //原先右子树根节点变为根节点，高度在原先的基础上加1
    child->height = max(height(child->left),height(child->right)) + 1;

    //返回旋转后的树根节点
    return root;
}

template <typename Elem>
BTNode<Elem> *AVLTree<Elem>::LRRotate(BTNode<Elem> *root)
{
    //先将左子树右单旋（将被插入节点的树根节点拉上来）
    root->left = RRRotate(root->left);
    //再将根节点左单旋（将原先的左子树拉上来，以此平衡高度）
    root = LLRotate(root);
    return root;
}

template <typename Elem>
inline BTNode<Elem> *AVLTree<Elem>::RLRotate(BTNode<Elem> *root)
{
    root->right = LLRotate(root->right);
    root = RRRotate(root);

    return root;
}

template <typename Elem>
BTNode<Elem> *AVLTree<Elem>::rinsert(BTNode<Elem> *root,const Elem &data)
{
    //左/右节点为空，插入
    if(root == nullptr)
        root = new BTNode<Elem>(data);
    //左子树插入递归
    else if(data < root->data)
    {
        root->left = rinsert(root->left,data);
        //插入完成后返回到父节点，发现左右子树失衡，开始自平衡
        if((height(root->left) - height(root->right)) == 2)
        {
            //插入在左子树的左子树节点导致失衡，左左单旋
            if(data < root->left->data)
                root = LLRotate(root);
            //插入在左子树的右子树节点导致失衡，左右双旋
            else
                root = LRRotate(root);
        }

    }
    //右子树插入递归
    else if(data > root->data)
    {
        root->right = rinsert(root->right,data);
        //插入完成后返回到父节点，发现左右子树失衡，开始自平衡
        if((height(root->right) - height(root->left)) == 2)
        {
            //插入在右子树的右子树节点导致失衡，右右单旋
            if(data > root->right->data)
                root = RRRotate(root);
            //插入在右子树的左子树节点导致失衡，右左双旋
            else
                root = RLRotate(root);
        }


    }

    //插入完成后节点高度加1（递归时层层递增）
    root->height = max(height(root->left),height(root->right)) + 1;

    return root;

}

template <typename Elem>
inline AVLTree<Elem> &AVLTree<Elem>::insert(const Elem &data)
{
    this->root = rinsert(this->root,data);
    return *this;
}

template <typename Elem>
BTNode<Elem> *AVLTree<Elem>::rremove(BTNode<Elem> *root,const Elem &x)
{   
    //没找到被删除元素，返回
    if(root == nullptr)
        return root;
    //左子树递归删除
    if(x < root->data)
    {
        root->left = rremove(root->left,x);
        //递归返回到上一层时，也要检测树是否失衡，检测方法相同
        if(height(root->left) - height(root->right) == 2)
        {
            if(height(root->left->left) - height(root->left->right) == 1)
                root = LLRotate(root);
            else
                root = LRRotate(root);
        }
    }
    //右子树递归删除
    else if(x > root->data)
    {
        root->right = rremove(root->right,x);
        if(height(root->right) - height(root->left) == 2)
        {
            if(height(root->right->left) - height(root->right->right) == 1)
                root = RRRotate(root);
            else
                root = RLRotate(root);
        }
    }
    else
    {
        BTNode<Elem> *temp,*temp1;
        if(root->left && root->right)
        {
            //左子树的最大值或右子树的最小值都可以，这里选择右子树的最小值
            temp = BST::BSTree<Elem>::rfindMin(root->right);
            //替换数据
            root->data = temp->data;
            //递归删除被替换节点（找到的左子树的最大值或右子树的最小值）
            root->right = rremove(root->right,root->data);
            //被删除节点在右子树，可能造成左右子树失衡
            if(height(root->left) - height(root->right) == 2)
            {
                //如果是左子树的左子树比左子树的右子树高，相当于插入在左子树的左子树节点，因此左单旋
                if(height(root->left->left) - height(root->left->right) == 1)
                    root = LLRotate(root);
                //左右双旋（相当于插入在左子树的右子树节点）
                else
                    root = LRRotate(root);
                    
            }
        }
        else
        {
            temp = root;
            root = root->left ? root->left : root->right;
            delete[] temp;
        }

    }
    
    //节点高度改变
    if(root != nullptr)
        root->height = max(height(root->left),height(root->right)) + 1;

    return root;
}

template <typename Elem>
inline AVLTree<Elem> &AVLTree<Elem>::remove(const Elem &x)
{
    this->root = rremove(this->root,x);
    return *this;
}

template <typename Elem>
inline void AVLTree<Elem>::preOrderIterTrav() const
{
    std::vector<Elem> v = BT::BinTree<Elem>::preOrderIterTrav(this->root);
    for(int i = 0;i < v.size();i++)
        std::cout << v.at(i) << " ";

}

template <typename Elem>
inline void AVLTree<Elem>::midOrderIterTrav() const
{
    std::vector<Elem> v = BT::BinTree<Elem>::midOrderIterTrav(this->root);
    for(int i = 0;i < v.size();i++)
        std::cout << v.at(i) << " ";

}

template <typename Elem>
inline void AVLTree<Elem>::postOrderIterTrav() const
{
    std::vector<Elem> v = BT::BinTree<Elem>::postOrderIterTrav(this->root);
    std::reverse(v.begin(),v.end());
    for(int i = 0;i < v.size();i++)
        std::cout << v.at(i) << " ";

}

template <typename Elem>
inline void AVLTree<Elem>::layOrderTrav() const
{
    std::vector<Elem> v = BT::BinTree<Elem>::layOrderTrav(this->root);
    for(int i = 0;i < v.size();i++)
        std::cout << v.at(i) << " ";
}

}