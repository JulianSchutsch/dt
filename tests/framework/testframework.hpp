#ifndef _TESTFRAMEWORK_HEADER_
#define _TESTFRAMEWORK_HEADER_

#include <iostream>

namespace Tests
{
    class TestFramework
    {
    private:
        unsigned long m_sectionCount = 0;
        unsigned long m_messageCount = 0;
        unsigned long m_warningCount = 0;
        unsigned long m_errorCount   = 0;
    public:
        void AddSection(std::string a_test, std::string a_section)
        {
            m_sectionCount++;
            std::cout<<"[Section]:"<<a_test<<" -> "<<a_section<<std::endl;
        }
        void AddMessage(std::string a_test, std::string a_message)
        {
            m_messageCount++;
            std::cout<<"[Message]:"<<a_test<<" -> "<<a_message<<std::endl;
        }
        void AddError(std::string a_test, std::string a_error)
        {
            m_warningCount++;
            std::cout<<"[Error]  :"<<a_test<<" -> "<<a_error<<std::endl;
        }
        void AddWarning(std::string a_test, std::string a_warning)
        {
            m_errorCount++;
            std::cout<<"[Warning]:"<<a_test<<" -> "<<a_warning<<std::endl;
        }

        TestFramework(){};
        TestFramework(const TestFramework& source) = delete;
        TestFramework(const TestFramework&& source) = delete;
        TestFramework& operator = (const TestFramework& source) = delete;
        TestFramework& operator = (const TestFramework&& source) = delete;
    };

    class Test
    {
    private:
        TestFramework& m_testFramework;
    public:
        Test(TestFramework& testFramework):m_testFramework(testFramework){};
        virtual ~Test(){};
        virtual std::string testName() = 0;
        void AddSection(std::string a_section)
        {
            m_testFramework.AddSection(testName(), a_section);
        }
        void AddMessage(std::string a_message)
        {
            m_testFramework.AddMessage(testName(), a_message);
        }
        void AddError(std::string a_error)
        {
            m_testFramework.AddError(testName(), a_error);
        }
        void AddWarning(std::string a_warning)
        {
            m_testFramework.AddWarning(testName(), a_warning);
        }
        virtual void run()=0;
    };

}

#endif // _TESTFRAMEWORK_HEADER_
