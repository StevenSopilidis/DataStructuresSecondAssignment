#include <iostream>
#include <cstdlib>
#include "DataStructures/AATree.hpp"
#include "DataStructures/AATreeNode.h"

using namespace DataStructures;

int main()
{  
    auto* aa = new AATree<int>();
    aa->Insert(10);
    aa->Insert(7);
    aa->Insert(5);
    aa->Insert(3);
    aa->Insert(1);

    aa->Insert(34);
    aa->Insert(543);
    aa->Insert(32);
    aa->Insert(0);
    aa->Insert(-1);
    aa->Insert(-2);

    aa->Delete(7);
    aa->Delete(5);
    aa->Delete(543);
    aa->Delete(3);
    aa->Delete(-1);
    aa->Delete(-2);
    aa->Delete(10);

    aa->preOrderPrint(aa->getRoot());
    
    /*std::cout << aa->getRoot()->left->data << std::endl;
    std::cout << aa->getRoot()->data << std::endl;
    std::cout << aa->getRoot()->right->data << std::endl;*/
    //aa->preOrderPrint(aa->getRoot());

}

