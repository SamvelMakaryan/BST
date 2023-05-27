#include "BST.hpp"
#include <iostream>
int main() {
    BST<int> ob1 {10, 13, -5, 4, 99};
    BST<int> ob2(7); 
    ob2 = ob1; 
    std::cout << "Iterating on ob2\n";
    for (auto& i : ob2) {
        std::cout << i << " ";
    }
    ob1.insert(2);
    ob1.insert(3);
    ob1.insert(4);
    ob1.insert(5);
    ob1.insert(17);
    ob1.insert(-9);
    ob1.insert(18);
    auto ob3(ob1);
    std::cout << std::endl << "Inorder Traversal on ob3\n";
    ob3.erase(4);
    ob3.inorder();
    std::cout << std::endl << "Preorder Traversal on ob3\n";
    ob3.preorder();
    std::cout << std::endl << "Postorder Traversal on ob3\n";
    ob3.postorder();    
    std::cout << std::endl << "Levelorder Traversal on ob3\n";
    ob3.levelorder();
    std::cout << std::endl << "Number of ob1 nodes - ";
    std::cout << ob1.get_number_of_nodes() << std::endl;
    ob3.clear();
    std::cout << "Checking does ob3 is clear  -  " << std::boolalpha << ob3.empty() << std::endl;
    ob3 += ob1;
    std::cout << "ob3 after adding elements of ob1" << std::endl;
    for (auto& i : ob3) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "Checking does ob1 contains number (-5)  -  " << ob1.contains(-5) << std::endl;
    std::cout << "Finding in ob2 number (99)  -  ";
    if(ob2.find(99) != ob2.end()) {
        if (*ob2.find(99) == 99)
        std::cout << "found " << std::endl;
    }
    else {
        std::cout << "not found" << std::endl;
    }
    std::cout << "The height of ob3 is  -  " << ob3.get_height() << std::endl;
    std::cout << "Checking if ob1 equals to ob3  -  " << (ob1 == ob3) << std::endl; 
    std::cout << "Printing ob2 \n" << ob2;
}
