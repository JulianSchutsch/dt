#include "xml.hpp"

#include <sstream>

namespace XML
{

    bool XMLNode::equals(XMLNode_SPtr other)
    {
        if(id!=other->id || text!=other->text || children.size()!=other->children.size()) return false;

        std::list<XMLNode_SPtr>::const_iterator a=children.cbegin();
        std::list<XMLNode_SPtr>::const_iterator b=children.cbegin();

        while(a!=children.cend())
        {
            if(!(*a)->equals(*b)) return false;
            a++;
            b++;
        }

        return true;
    }

    void XMLNode::print(std::string indent)
    {
        if(text=="" && children.empty())
        {
            std::cout<<indent<<"<"<<id<<"/>"<<std::endl;
        }
        else
        {
            std::cout<<indent<<"<"<<id<<">"<<std::endl;
            if(text!="") std::cout<<indent<<text<<":"<<std::endl;
            for(XMLNode_SPtr& child : children)
            {
                child->print(indent+" ");
            }
            std::cout<<indent<<"</"<<id<<">"<<std::endl;
        }
    }


    static std::string parseXMLIdentifier(std::streambuf& buffer)
    {
        std::stringstream identifier;
        {
            char c=buffer.sgetc();
            if((c<'A' || c>'Z') && (c<'a' || c>'z'))
            {
                throw XMLParseException();
            }
            buffer.snextc();
            identifier<<c;
        }
        for(;;)
        {
            char c=buffer.sgetc();
            if((c<'0' || c>'9') && (c<'A' || c>'Z') && (c<'a' || c>'z'))
            {
                break;
            }
            buffer.snextc();
            identifier<<c;
        }
        return identifier.str();

    }

    static void parseXMLSkipSpace(std::streambuf& buffer)
    {
        while(buffer.sgetc()==' ' || buffer.sgetc()=='\n' || buffer.sgetc()=='\r')
        {
            buffer.snextc();
        }
    }

    static std::shared_ptr<XMLNode> parseXMLNode(std::streambuf& buffer)
    {
        // 1. Read Symbol name
        parseXMLSkipSpace(buffer);
        std::string id=parseXMLIdentifier(buffer);
        std::cout<<"Parse Id:"<<id<<std::endl;
        std::list<XMLNode_SPtr> children;
        std::string text;

        parseXMLSkipSpace(buffer);

        for(;;)
        {
            char c=buffer.sgetc();
            char c2=buffer.snextc();
            if((c=='/') && (c2=='>'))
            {
                buffer.snextc();
                goto completeNode;
            }
            if(c=='>')
            {
                goto parseText;
            }
            // TODO: Parse attribute
        }
    parseText:
        std::cout<<"Parse Text"<<std::endl;
        {
            std::stringstream textbuffer;
            parseXMLSkipSpace(buffer);
            for(;;)
            {
                char c=buffer.sgetc();
                char c2=buffer.snextc();
                if(c!='<')
                {
                    textbuffer<<c;
                }
                else
                {
                    if(c2=='/')
                    {
                        buffer.snextc();
                        break;
                    }
                    // TODO: There may be other cases.
                    children.push_back(parseXMLNode(buffer));
                }
            }
            text=textbuffer.str();
        }
        {
            std::string::reverse_iterator trimpos=text.rbegin();
            while((trimpos!=text.rend()) && (*trimpos==' ' || *trimpos=='\n' || *trimpos=='\r'))
            {
                trimpos++;
            }
            text.erase(trimpos.base(),text.end());
        }
        std::cout<<"Parse end"<<std::endl;
        {
            std::string endidentifier=parseXMLIdentifier(buffer);
            if(endidentifier!=id)
            {
                throw XMLParseException();
            }
            parseXMLSkipSpace(buffer);
            char c=buffer.sgetc();
            if(c!='>')
            {
                throw XMLParseException();
            }
            buffer.snextc();
        }
    completeNode:
        std::cout<<"Complete"<<std::endl;
        // Complete...just build and return it.
        XMLNode_SPtr node(new XMLNode(id, children, text));
        return node;
    }

    XMLNode_SPtr parseXML(std::streambuf& buffer)
    {
        std::cout<<"Parse Start"<<std::endl;
        parseXMLSkipSpace(buffer);
        char c=buffer.sgetc();
        if(c=='<')
        {
            buffer.snextc();
            std::cout<<"Parse Node"<<std::endl;
            XMLNode_SPtr current=parseXMLNode(buffer);
            std::cout<<"Something"<<std::endl;
            return current;
        }
        std::cout<<"Nothing"<<std::endl;
        return XMLNode_SPtr();
    }
}
