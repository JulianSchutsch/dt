#include "test_variant.hpp"

namespace Tests
{

    void Test_Variant::test_int()
    {
        AddSection("Test int");
        Core::Variant variant(10);

        if(!(variant==10))
        {
            AddError("Comparison to int failed (expected success)");
        }

        if(variant==11)
        {
            AddError("Comparison to int failed (expected failure)");
        }

        if(variant==float(10.0))
        {
            AddError("Comparison to float failed (expected failure)");
        }

        if(variant==double(10.0))
        {
            AddError("Comparison to double failed (expected failure)");
        }

        if(variant=="" || variant=="10")
        {
            AddError("Comparison to string failed (expected failure)");
        }

        if(variant.toString()!="[Variant:Int]10")
        {
            AddWarning("toString failed");
        }

        if(!variant.isType(10))
        {
            AddError("isType failed");
        }

    }

    void Test_Variant::test_float()
    {
        AddSection("Test float");
        Core::Variant variant(10.0f);

        if(variant==10)
        {
            AddError("Comparison to int failed (expected failure)");
        }

        if(!(variant==float(10.0)))
        {
            AddError("Comparison to float failed (expected success)");
        }

        if(variant==float(10.1))
        {
            AddError("Comparison to float failed (expected failure)");
        }

        if(variant==double(10.0))
        {
            AddError("Comparison to double failed (expected success)");
        }

        if(variant=="" || variant=="10")
        {
            AddError("Comparison to string failed (expected failure)");
        }

        if(variant.toString()!="[Variant:Float]10")
        {
            AddWarning("toString failed");
        }

    }

    void Test_Variant::test_double()
    {
        AddSection("Test double");
        Core::Variant variant(double(10.0));

        if(variant==10)
        {
            AddError("Comparison to int failed (expected failure)");
        }

        if(variant==float(10.1))
        {
            AddError("Comparison to float failed (expected failure)");
        }

        if(variant==float(10.0))
        {
            AddError("Comparison to float failed (expected success)");
        }

        if(!(variant==double(10.0)))
        {
            AddError("Comparison to double failed (expected succes)");
        }

        if(variant=="" || variant=="10")
        {
            AddError("Comparison to string failed (expected failure)");
        }

        if(variant.toString()!="[Variant:Double]10")
        {
            AddWarning("toString failed");
        }

    }

    void Test_Variant::test_string()
    {
        AddSection("Test string");
        Core::Variant variant("TestString");

        if(variant==10)
        {
            AddError("Comparison to int failed (expected failure)");
        }

        if(variant==float(10.0))
        {
            AddError("Comparison to float failed (expected failure)");
        }

        if(variant==double(10.0))
        {
            AddError("Comparsion to double failed (expected failure)");
        }

        if(!(variant=="TestString"))
        {
            AddError("Comparison to string failed (expected success)");
        }

        if(variant=="TestString_")
        {
            AddError("Comparison to string failed (expected failure)");
        }

        if(variant.toString()!="[Variant:String]TestString")
        {
            AddWarning("toString failed");
        }

    }

    void Test_Variant::run()
    {
        test_int();
        test_float();
        test_double();
        test_string();
    }

}
