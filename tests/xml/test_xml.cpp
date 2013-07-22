#include "test_xml.hpp"

#include <memory>
#include "xml.hpp"

namespace Tests
{

    void Test_XML::test_Construction()
    {
        AddSection("XML Construction");
        std::shared_ptr<XML::XMLNode> root(new XML::XMLNode("ROOT"));
        if(root->id!="ROOT") AddError("Root node id property invalid");
        if(root->text!="") AddError("Root node text property invalid");
    }

    void Test_XML::run()
    {
        test_Construction();
    }

} // namespace Tests
