#include "xml.hpp"

#include <sstream>

namespace XML
{

    static std::string parseXMLIdentifier(std::streambuf& buffer)
    {
        std::stringstream identifier;
        {
            char c=buffer.sgetc();
            std::cout<<"c:"<<c<<std::endl;
            if((c<'A' || c>'Z') && (c<'a' || c>'z'))
            {
                throw XMLParseException();
            }
            buffer.snextc();
            identifier<<c;
        }
        std::cout<<"IDLOOP"<<std::endl;
        for(;;)
        {
            char c=buffer.sgetc();
            std::cout<<"c_:"<<c<<":"<<std::endl;
            if((c<'0' || c>'9') && (c<'A' || c>'Z') && (c<'a' || c>'z'))
            {
                std::cout<<"Break"<<std::endl;
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
        std::list<std::shared_ptr<XMLNode>> children;
        std::string text;

        parseXMLSkipSpace(buffer);

        for(;;)
        {
            char c=buffer.sgetc();
            std::cout<<"Node:"<<c<<std::endl;
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
                std::cout<<"Textc:"<<c<<std::endl;
                if(c=='<')
                {
                    if(c2=='/')
                    {
                        buffer.snextc();
                        break;
                    }
                    // TODO: There may be other cases.
                    children.push_back(parseXMLNode(buffer));
                }
                textbuffer<<c;
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
        std::cout<<"Complete";
        // Complete...just build and return it.
        std::shared_ptr<XMLNode> node(new XMLNode(id, children, text));
        return node;
    }

    std::shared_ptr<XMLNode> parseXML(std::streambuf& buffer)
    {
        std::cout<<"Parse Start"<<std::endl;
        parseXMLSkipSpace(buffer);
        char c=buffer.sgetc();
        if(c=='<')
        {
            buffer.snextc();
            std::cout<<"Parse Node"<<std::endl;
            std::shared_ptr<XMLNode> current=parseXMLNode(buffer);
            std::cout<<"Something"<<std::endl;
            return current;
        }
        std::cout<<"Nothing"<<std::endl;
        return std::shared_ptr<XMLNode>();
    }
}
