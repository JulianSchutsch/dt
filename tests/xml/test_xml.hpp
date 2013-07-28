#ifndef _TEST_XML_HEADER_
#define _TEST_XML_HEADER_

#include "testframework.hpp"

namespace Tests
{
    class Test_XML:public Test
    {
    private:

        void test_Construction();
        void test_Parser();

    public:
        Test_XML(TestFramework& testFramework):Test(testFramework){};
        std::string testName() override{return "XML";}
        void run() override;
    };
} // namespace Tests

#endif // _TEST_XML_HEADER_
