#include "variant.hpp"

#include "testframework.hpp"
#include "test_variant.hpp"
#include "test_xml.hpp"
#include "test_refcount.hpp"

#include "gui.hpp"

int main()
{
    Tests::TestFramework testFramework;
    {
        Tests::Test_Variant test_variant(testFramework);
        test_variant.run();
    }
    {
        Tests::Test_XML test_xml(testFramework);
        test_xml.run();
    }
    {
        Tests::Test_RefCount test_refcount(testFramework);
        test_refcount.run();

    }
}
