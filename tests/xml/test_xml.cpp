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
        root->addChild(XMLNode_SPtr(new XMLNode("CHILD1")));
        root->addChild(XMLNode_SPtr(new XMLNode("CHILD2")));
        return root;
    }

    void Test_XML::test_Construction()
    {
        using XML::XMLNode;
        using XML::XMLNode_SPtr;
        using XML::parseXML;
        AddSection("XML Construction");
        XMLNode_SPtr root=createXMLTree1();
        if(root->id!="ROOT") AddError("Root node id property invalid");
        if(root->text!="") AddError("Root node text property invalid");

        {
            std::list<XMLNode_SPtr>::const_iterator i=root->children.cbegin();
            if(i==root->children.cend()) AddError("Expected Child node CHILD1, got null");
            if((*i)->id!="CHILD1") AddError("Expected Child node CHILD1");
            i++;
            if(i==root->children.cend()) AddError("Expected Child node CHILD2, got null");
            if((*i)->id!="CHILD2") AddError("Expected Child node CHILD2");
            i++;
            if(i!=root->children.cend()) AddError("Expected no more children");
        }
        {
            std::stringbuf b("<ROOT><CHILD1></CHILD1><CHILD2></CHILD2></ROOT>");
            XMLNode_SPtr root2 = parseXML(b);
            if(!root->equals(root2))
            {
                AddError("Parsed Tree (1) should be identical");
            }
        }
    }

    void Test_XML::run()
    {
        test_Construction();
    }

} // namespace Tests
