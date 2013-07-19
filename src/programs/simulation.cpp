#include <iostream>
#include "regions.hpp"

int main()
{
    std::cout<<"Hello World"<<std::endl;
    Region region;
    region.getNodes<Node>(10,10);
    region.getNodes<Node2>(10,10);
}
