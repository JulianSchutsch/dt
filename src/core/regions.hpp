#ifndef _REGIONS_HEADER_
#define _REGIONS_HEADER_

#include <list>
#include <iostream>

typedef int nodeType_t;

class Node
{
public:
    static int id;
};

class Node2
{
public:
    static int id;
};

class Region
{
    // Somehow region has to support query operations for every possible node
    // This screams for template hacks.
    // Just that one may not want to specify all possible nodes all the time,
    // typedef could certainly help a little, but may break modularisation.
    // Better would be to have a global enumeration of types, which can be used to
    // create an enumerated structure.
    // Template expansion could also be useful, if we could calculate the offset
    // in such a structure using only the template method
public:
    template <class NodeProxy>
    void getNodes(int x, int y)
    {
        std::cout<<"Try"<<std::endl;
        std::cout<<NodeProxy::id<<":"<<x<<":"<<y<<std::endl;
        std::cout<<"Done"<<std::endl;
    }
};

#endif // _REGIONS_HEADER_
