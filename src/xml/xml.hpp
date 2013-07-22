#ifndef _XML_HEADER_
#define _XML_HEADER_

#include <string>
#include <map>
#include <memory>
#include <list>

#include "variant.hpp"

namespace XML
{
    class XMLParseException
    {
        virtual const char* what()
        {
            return "XMLParseException";
        }
    };

    class XMLNode;
    typedef std::shared_ptr<XMLNode> XMLNode_SPtr;

    class XMLNode
    {
    public:
        std::list<XMLNode_SPtr> children;
        std::string id;
        std::string text;
        std::map<std::string, Core::Variant> attributes;

        XMLNode(std::string a_id)
               :children(),
                id(a_id),
                text(),
                attributes(){}
        XMLNode(std::string a_id,
                std::list<XMLNode_SPtr> a_children,
                std::string a_text)
               :children(a_children),
                id(a_id),
                text(a_text),
                attributes(){}
        bool equals(XMLNode_SPtr other);
        void print(std::string indent="");
        void addChild(XMLNode_SPtr node){children.push_back(node);}

    };

    XMLNode_SPtr parseXML(std::streambuf& buffer);

} // namespace mXML

#endif // _XML_HEADER_
