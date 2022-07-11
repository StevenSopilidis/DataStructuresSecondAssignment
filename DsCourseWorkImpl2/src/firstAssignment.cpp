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
    aa->Insert(2);
    aa->Insert(1);

    ////std::cout << aa->Search(2) << std::endl;
    std::cout << "---------------------" << std::endl;
    aa->preOrderPrint(aa->getRoot());

    /*std::cout << aa->getRoot()->left->data << std::endl;
    std::cout << aa->getRoot()->data << std::endl;
    std::cout << aa->getRoot()->right->data << std::endl;*/
    //aa->preOrderPrint(aa->getRoot());

}

