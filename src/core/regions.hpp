#ifndef _REGIONS_HEADER_
#define _REGIONS_HEADER_

#include <list>
#include <map>
#include <array>
#include <iostream>

enum class nodeType_t:int
{
    Node = 0,
    Node2,
    Bottom,
};

class Region;

class Node
{
private:
    Region* region;
public:
    Region* getRegion(){return region;};
    //static const nodeType_t id=nodeType_t::Node;
};

class Node2:Node
{
public:
    static const nodeType_t id=nodeType_t::Node2;
};

class Region
{
private:
    std::map<unsigned long, Node*> nodes;
public:
    template <class NodeProxy>
    NodeProxy* getNode(int x, int y)
    {
        std::cout<<"Try"<<std::endl;
        std::cout<<int(NodeProxy::id)<<":"<<x<<":"<<y<<":"<<std::endl;
        std::cout<<"Done"<<std::endl;
        return nullptr;
    }
};

#endif // _REGIONS_HEADER_
