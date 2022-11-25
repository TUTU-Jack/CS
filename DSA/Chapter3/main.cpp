#include "AVLTree.h"
#include "cstring"

void test1()
{
    BT::BinTree<int> bt(10);

    bt.insert(10,0,6);
    bt.insert(10,1,15);
    bt.insert(6,0,4);
    bt.insert(6,1,8);
    bt.insert(15,0,13);
    bt.insert(15,1,18);
    bt.insert(13,0,12);
    bt.insert(13,1,14);
    bt.insert(18,0,16);
    bt.insert(18,1,19);
    bt.insert(12,0,11);
 
    std::cout << "递归遍历:" << std::endl << "前序:";
    bt.preOrderRecTrav();
    std::cout << std::endl << "中序:";
    bt.midOrderRecTrav();
    std::cout << std::endl << "后序:";
    bt.postOrderRecTrav();
    std::cout << std::endl << std::endl;

    std::cout << "迭代遍历:" << std::endl << "前序:";
    bt.preOrderIterTrav();
   std::cout << std::endl << "中序:";
    bt.midOrderIterTrav();
    std::cout << std::endl << "后序:";
    bt.postOrderIterTrav();
    std::cout << std::endl << std::endl;

    std::cout << "层序遍历:" << std::endl;
    bt.layOrderTrav();
    std::cout << std::endl;
    

}

void test2()
{
    BST::BSTree<int> bst(10);
    bst.insert(6);
    bst.insert(15);
    bst.insert(4);
    bst.insert(8);
    bst.insert(13);
    bst.insert(18);
    bst.insert(12);
    bst.insert(14);
    bst.insert(16);
    bst.insert(19);
    bst.insert(11);
 
    bst.remove(10);
    std::cout << "递归遍历:" << std::endl << "前序:";
    bst.preOrderRecTrav();
    std::cout << std::endl << "中序:";
    bst.midOrderRecTrav();
    std::cout << std::endl << "后序:";
    bst.postOrderRecTrav();
    std::cout << std::endl << std::endl;

    std::cout << "迭代遍历:" << std::endl << "前序:";
    bst.preOrderIterTrav();
   std::cout << std::endl << "中序:";
    bst.midOrderIterTrav();
    std::cout << std::endl << "后序:";
    bst.postOrderIterTrav();
    std::cout << std::endl << std::endl;

    std::cout << "层序遍历:" << std::endl;
    bst.layOrderTrav();
    std::cout << std::endl;

}

void test3()
{   
    AVL::AVLTree<int> avl(10);
    avl.insert(6);
    avl.insert(15);
    avl.insert(4);
    avl.insert(8);
    avl.insert(13);
    avl.insert(18);
    avl.insert(12);
    avl.insert(14);
    avl.insert(16);
    avl.insert(19);
    avl.insert(11);

    /*
    AVL::AVLTree<int> avl(20);
    avl.insert(10);
    avl.insert(25);
    avl.insert(30);
    avl.insert(15);
    avl.insert(8);
    avl.insert(9);
    //LL
    avl.remove(20);
    //LR
    avl.remove(10);
    */

    avl.remove(10);
    std::cout << "递归遍历:" << std::endl << "前序:";
    avl.preOrderRecTrav();
    std::cout << std::endl << "中序:";
    avl.midOrderRecTrav();
    std::cout << std::endl << "后序:";
    avl.postOrderRecTrav();
    std::cout << std::endl << std::endl;

    std::cout << "迭代遍历:" << std::endl << "前序:";
    avl.preOrderIterTrav();
    std::cout << std::endl << "中序:";
    avl.midOrderIterTrav();
    std::cout << std::endl << "后序:";
    avl.postOrderIterTrav();
    std::cout << std::endl << std::endl;

    std::cout << "层序遍历:" << std::endl;
    avl.layOrderTrav();
    std::cout << std::endl;

}

int main(int argc,char *argv[])
{
    if(argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <test>" << std::endl;
        return 1;
    }

    if(strcmp(argv[1],"test1") == 0)
        test1();
    else if(strcmp(argv[1],"test2") == 0)
        test2();
    else if(strcmp(argv[1],"test3") == 0)
        test3();
    
    return 0;
}