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

    class XMLNode
    {
    private:
        std::list<std::shared_ptr<XMLNode>> m_children;
    public:
        std::string id;
        std::string text;

        XMLNode(std::string a_id)
               :m_children(),
                id(a_id),
                text(){};
        XMLNode(std::string a_id,
                std::list<std::shared_ptr<XMLNode>> a_children,
                std::string a_text)
               :m_children(a_children),
                id(a_id),
                text(a_text){};

        void print(std::string indent="")
        {
            if(text=="" && m_children.empty())
            {
                std::cout<<indent<<"<"<<id<<"/>"<<std::endl;
            }
            else
            {
                std::cout<<indent<<"<"<<id<<">"<<std::endl;
                if(text!="") std::cout<<indent<<text<<":"<<std::endl;
                for(std::shared_ptr<XMLNode>& child : m_children)
                {
                    child->print(indent+" ");
                }
                std::cout<<indent<<"</"<<id<<">"<<std::endl;
            }
        }

        void addChild(std::shared_ptr<XMLNode> node)
        {
            m_children.push_back(node);
        }


    };

    std::shared_ptr<XMLNode> parseXML(std::streambuf& buffer);

} // namespace mXML

#endif // _XML_HEADER_
