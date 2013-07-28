#ifndef _TEST_REFCOUNT_HEADER_
#define _TEST_REFCOUNT_HEADER_

#include <string>

#include "testframework.hpp"
#include "refcount.hpp"

namespace Tests
{
    class Test_RefCount:public Test
    {
    public:
        static bool newFlag;
        static bool deleteFlag;
    private:
        class TestObj
        {
            REFCOUNTABLE
        private:
        public:
            void* operator new(size_t size)
            {
                Test_RefCount::newFlag = true;
                return malloc(size);
            }
            void operator delete(void* pnt)
            {
                deleteFlag = true;
                free(pnt);
            }
        };
        void test_dynamic();
        void test_static();
    public:
        Test_RefCount(TestFramework& testFramework):Test(testFramework){};
        std::string testName() override {return "RefCount";}
        void run() override;
    };
}

#endif // _TEST_BASICS_REFCOUNT_HEADER_
