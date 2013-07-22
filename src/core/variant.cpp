#include "variant.hpp"

namespace Core
{
    std::string Variant::toString() const
    {
        std::stringstream ss;
        switch(m_variantType)
        {
        case variantType_t::None:
            return "[Variant:None]";
        case variantType_t::Int:
            ss<<"[Variant:Int]"<<m_variantUnion.u_int;
            return ss.str();
        case variantType_t::Float:
            ss<<"[Variant:Float]"<<m_variantUnion.u_float;
            return ss.str();
        case variantType_t::Double:
            ss<<"[Variant:Double]"<<m_variantUnion.u_double;
            return ss.str();
        case variantType_t::String:
            ss<<"[Variant:String]"<<m_string;
            return ss.str();
        }
        return "";
    }
}
