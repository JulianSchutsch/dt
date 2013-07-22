#ifndef _TEST_VARIANT_HEADER_
#define _TEST_VARIANT_HEADER_

#include <iostream>

#include "testframework.hpp"
#include "variant.hpp"

namespace Tests
{

    class Test_Variant:Test
    {
    private:

        void test_int();
        void test_float();
        void test_double();
        void test_string();


    public:
        Test_Variant(TestFramework& testFramework):Test(testFramework){};
        std::string testName() override {return "Variant";}
        void run() override;
    };

} // namespace Tests

#endif // _TEST_VARIANT_HEADER_
