#ifndef _VARIANT_HEADER_
#define _VARIANT_HEADER_

#include <string>
#include <sstream>
#include <iostream>

namespace Core
{

    enum class variantType_t
    {
        None,
        Int,
        Float,
        Double,
        String
    };

    class Variant
    {
    private:

        union variantUnion_t
        {
            int    u_int;
            float  u_float;
            double u_double;
            variantUnion_t(){};
            variantUnion_t(int a_int):u_int(a_int){};
            variantUnion_t(float a_float):u_float(a_float){};
            variantUnion_t(double a_double):u_double(a_double){};
        };

        variantType_t  m_variantType;
        variantUnion_t m_variantUnion;
        std::string    m_string;

    public:

        explicit Variant():m_variantType(variantType_t::None),m_variantUnion(),m_string(){};

        explicit Variant(const int a_int):m_variantType(variantType_t::Int),m_variantUnion(a_int),m_string(){};

        explicit Variant(const float a_float):m_variantType(variantType_t::Float),m_variantUnion(a_float),m_string(){}

        explicit Variant(const double a_double):m_variantType(variantType_t::Double),m_variantUnion(a_double),m_string(){}

        explicit Variant(const std::string a_string):m_variantType(variantType_t::String),m_variantUnion(),m_string(a_string){};

        bool isType(const int& a_int) const
        {
            return m_variantType==variantType_t::Int;
        }

        bool isType(const float& a_float) const
        {
            return m_variantType==variantType_t::Float;
        }

        bool isType(const double& a_double) const
        {
            return m_variantType==variantType_t::Double;
        }

        bool isType(const std::string& a_string) const
        {
            return m_variantType==variantType_t::String;
        }

        bool operator == (const int a_int) const
        {
            return m_variantType==variantType_t::Int?m_variantUnion.u_int==a_int:false;
        }

        bool operator == (const float a_float) const
        {
            return m_variantType==variantType_t::Float?m_variantUnion.u_float==a_float:false;
        }

        bool operator == (const double a_double) const
        {
            return m_variantType==variantType_t::Double?m_variantUnion.u_double==a_double:false;
        }

        bool operator == (const std::string& a_string) const
        {
            return m_variantType==variantType_t::String?m_string==a_string:false;
        }

        bool operator == (const Variant& other) const
        {
            if(!(m_variantType==other.m_variantType)) return false;
            switch(m_variantType)
            {
            case variantType_t::None:
                return true;
            case variantType_t::Int:
                return m_variantUnion.u_int==other.m_variantUnion.u_int;
            case variantType_t::Float:
                return m_variantUnion.u_float==other.m_variantUnion.u_float;
            case variantType_t::Double:
                return m_variantUnion.u_double==other.m_variantUnion.u_double;
            case variantType_t::String:
                return m_string==other.m_string;
            }
            // TODO: Throw exception for incomplete implementation
            return false;
        }

        std::string toString() const;

    };

} // namespace Core

#endif // _VARIANT_HEADER_
