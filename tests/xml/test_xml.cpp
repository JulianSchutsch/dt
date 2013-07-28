#include "test_xml.hpp"

#include <memory>
#include "xml.hpp"

namespace Tests
{
    static XML::XMLNode_SPtr createXMLTree1()
    {
        using XML::XMLNode;
        using XML::XMLNode_SPtr;
        XMLNode_SPtr root(new XMLNode("ROOT"));
        root->children.push_back(XMLNode_SPtr(new XMLNode("CHILD1")));
        root->children.push_back(XMLNode_SPtr(new XMLNode("CHILD2")));
        return root;
    }

    void Test_XML::test_Construction()
    {
        AddSection("XML Construction");

        using XML::XMLNode;
        using XML::XMLNode_SPtr;

        XMLNode_SPtr root=createXMLTree1();
        ASSERTERROR(root->id=="ROOT","Root node id property invalid");
        ASSERTERROR(root->text=="","Root node text property invalid");

        {
            std::list<XMLNode_SPtr>::const_iterator i=root->children.cbegin();
            ASSERTERROR(i!=root->children.cend(),"Expected child node CHILD1, got null");
            ASSERTERROR((*i)->id=="CHILD1","Expected child node CHILD1");
            i++;
            ASSERTERROR(i!=root->children.cend(),"Expected child node CHILD2, got null");
            ASSERTERROR((*i)->id=="CHILD2","Expected child node CHILD2");
            i++;
            ASSERTERROR(i==root->children.cend(),"Expected no more children");
        }
    }

    void Test_XML::test_Parser()
    {
        AddSection("XML Parser");

        using XML::XMLNode_SPtr;
        using XML::parseXML;

        XMLNode_SPtr root=createXMLTree1();
        {
            std::stringbuf b("<ROOT><CHILD1></CHILD1><CHILD2></CHILD2></ROOT>");
            XMLNode_SPtr root2 = parseXML(b);
            ASSERTERROR(root->equals(root2),"Parser Tree (1) should be identical");
        }
    }

    void Test_XML::run()
    {
        test_Construction();
    }

} // namespace Tests
