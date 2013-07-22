#include "variant.hpp"

#include "testframework.hpp"
#include "test_variant.hpp"
#include "test_xml.hpp"

int main()
{
    Tests::TestFramework testFramework;
    Tests::Test_Variant test_variant(testFramework);
    test_variant.run();
}
