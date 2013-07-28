#include "test_variant.hpp"

namespace Tests
{

    void Test_Variant::test_int()
    {
        AddSection("Test int");
        Core::Variant variant(10);

        ASSERTERROR(variant==10,"Comparison to int failed");
        ASSERTERROR(!(variant==11),"Comparison to int failed");
        ASSERTERROR(!(variant==float(10.0)),"Comparison to float failed");
        ASSERTERROR(!(variant==double(10.0)),"Comparison to double failed");
        ASSERTERROR(!(variant=="" || variant=="10"),"Comparsion to string failed");
        ASSERTERROR(variant.toString()=="[Variant:Int]10","toString failed");
        ASSERTERROR(variant.isType(10),"isType failed");
    }

    void Test_Variant::test_float()
    {
        AddSection("Test float");
        Core::Variant variant(10.0f);

        ASSERTERROR(!(variant==10),"Comparison to int failed");
        ASSERTERROR(variant==float(10),"Comparison to float failed");
        ASSERTERROR(!(variant==float(10.1)),"Comparison to float failed");
        ASSERTERROR(!(variant==double(10)),"Comparison to double failed");
        ASSERTERROR(!(variant=="" || variant=="10"),"Comparison to string failed");
        ASSERTERROR(variant.toString()=="[Variant:Float]10","toString failed");
    }

    void Test_Variant::test_double()
    {
        AddSection("Test double");
        Core::Variant variant(double(10.0));

        ASSERTERROR(!(variant==10),"Comparison to int failed");
        ASSERTERROR(!(variant==float(10.1)),"Comparison to float failed");
        ASSERTERROR(!(variant==float(10.0)),"Comparison to float failed");
        ASSERTERROR(variant==double(10.0),"Comparison to double failed");
        ASSERTERROR(!(variant=="" || variant=="10"),"Comparison to string failed");
        ASSERTERROR(variant.toString()=="[Variant:Double]10","toString failed");

    }

    void Test_Variant::test_string()
    {
        AddSection("Test string");
        Core::Variant variant("TestString");

        ASSERTERROR(!(variant==10),"Comparison to int failed");
        ASSERTERROR(!(variant==float(10.0)),"Comparison to float failed");
        ASSERTERROR(!(variant==double(10.0)),"Comparison to double failed");
        ASSERTERROR(variant=="TestString","Comparison to string failed");
        ASSERTERROR(!(variant=="TestString_"),"Comparison to string failed");
        ASSERTERROR(variant.toString()=="[Variant:String]TestString","toString failed");
    }

    void Test_Variant::run()
    {
        test_int();
        test_float();
        test_double();
        test_string();
    }

}
