#include <iostream>
#include "regions.hpp"

int main()
{
    std::cout<<"Hello World"<<std::endl;
    Region region;
   // auto node=region.getNode<Node>(10,10);
    auto node2=region.getNode<Node2>(10,10);
}
