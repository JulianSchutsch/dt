#include "test_refcount.hpp"

namespace Tests
{

    bool Test_RefCount::newFlag = false;
    bool Test_RefCount::deleteFlag = false;

    void Test_RefCount::test_dynamic()
    {
        AddSection("Dynamic");
        deleteFlag = false;
        newFlag    = false;
        {
            TestObj* testobj=new TestObj;
            Core::Ref<TestObj> ref(testobj);
            ASSERTERROR(newFlag,"No new Operator called.");
            ASSERTERROR(!deleteFlag,"Unexpected call for delete operator");
            ASSERTERROR(ref.count()==1,"Invalid Refcount");
            newFlag=false;
            Core::Ref<TestObj> ref2(ref);
            ASSERTERROR(!newFlag,"New Operator called.");
            ASSERTERROR(!deleteFlag,"Unexpected call for delete operator");
            ASSERTERROR(ref.count()==2,"Invalid Refcount");
            ASSERTERROR(ref2.count()==2,"Invalid Refcount");
            Core::Ref<TestObj> ref3=ref;
            ASSERTERROR(!newFlag,"New Operator called.");
            ASSERTERROR(!deleteFlag,"Unexpected call for delete operator");
            ASSERTERROR(ref.count()==3,"Invalid Refcount");
            ASSERTERROR(ref2.count()==3,"Invalid Refcount");
            ASSERTERROR(ref3.count()==3,"Invalid Refcount");
            ref3=ref3;
            ASSERTERROR(!newFlag,"New Operator called.");
            ASSERTERROR(!deleteFlag,"Unexpected call for delete operator");
            ASSERTERROR(ref.count()==3,"Invalid Refcount");
            ASSERTERROR(ref2.count()==3,"Invalid Refcount");
            ASSERTERROR(ref3.count()==3,"Invalid Refcount");
            ref2=ref3;
            ASSERTERROR(!newFlag,"New Operator called.");
            ASSERTERROR(!deleteFlag,"Unexpected call for delete operator");
            ASSERTERROR(ref.count()==3,"Invalid Refcount");
            ASSERTERROR(ref2.count()==3,"Invalid Refcount");
            ASSERTERROR(ref3.count()==3,"Invalid Refcount");
            ref3=nullptr;
            ASSERTERROR(ref.count()==2,"Invalid Refcount");
            ASSERTERROR(ref2.count()==2,"Invalid Refcount");
            try
            {
                ASSERTERROR(ref3.count() || !ref3.count(),"Missing exception for nullptr ref");
            }
            catch(Core::RefCountException& re){};
        }
        ASSERTERROR(!newFlag,"New Operator called for.");
        ASSERTERROR(deleteFlag,"Missing call for delete operator");
        deleteFlag=false;
    }

    void Test_RefCount::test_static()
    {
        AddSection("Static");
        deleteFlag = false;
        newFlag    = false;
        {
            // Verify initialization of reference object, check that count is +2
            TestObj testobj;
            Core::Ref<TestObj> ref(testobj);
            ASSERTERROR(!newFlag,"New Operator called for constant object.");
            ASSERTERROR(!deleteFlag,"Unexpected call for delete operator");
            ASSERTERROR(ref.count()==2,"Invalid Refcount");
            // Verify second initialization of reference object, check if count is only +1
            Core::Ref<TestObj> sec(testobj);
            ASSERTERROR(!newFlag,"New Operator called for constant object.");
            ASSERTERROR(!deleteFlag,"Unexpected call for delete operator");
            ASSERTERROR(ref.count()==3,"Invalid Refcount");
            sec=nullptr;
            ASSERTERROR(!newFlag,"New Operator called for constant object.");
            ASSERTERROR(!deleteFlag,"Unexpected call for delete operator");
            ASSERTERROR(ref.count()==2,"Invalid Refcount");
            // Verify copy constructor
            Core::Ref<TestObj> ref2(ref);
            ASSERTERROR(!newFlag,"New Operator called for constant object.");
            ASSERTERROR(!deleteFlag,"Unexpected call for delete operator");
            ASSERTERROR(ref.count()==3,"Invalid Refcount");
            ASSERTERROR(ref2.count()==3,"Invalid Refcount");
            // Verify assignment construction
            Core::Ref<TestObj> ref3=ref;
            ASSERTERROR(!newFlag,"New Operator called for constant object.");
            ASSERTERROR(!deleteFlag,"Unexpected call for delete operator");
            ASSERTERROR(ref.count()==4,"Invalid Refcount");
            ASSERTERROR(ref2.count()==4,"Invalid Refcount");
            ASSERTERROR(ref3.count()==4,"Invalid Refcount");
            // Verify self assignment
            ref3=ref3;
            ASSERTERROR(!newFlag,"New Operator called for constant object.");
            ASSERTERROR(!deleteFlag,"Unexpected call for delete operator");
            ASSERTERROR(ref.count()==4,"Invalid Refcount");
            ASSERTERROR(ref2.count()==4,"Invalid Refcount");
            ASSERTERROR(ref3.count()==4,"Invalid Refcount");
            // Verify assignment
            ref2=ref3;
            ASSERTERROR(!newFlag,"New Operator called for constant object.");
            ASSERTERROR(!deleteFlag,"Unexpected call for delete operator");
            ASSERTERROR(ref.count()==4,"Invalid Refcount");
            ASSERTERROR(ref2.count()==4,"Invalid Refcount");
            ASSERTERROR(ref3.count()==4,"Invalid Refcount");
            // Verify null
            ref3=nullptr;
            ASSERTERROR(ref.count()==3,"Invalid Refcount");
            ASSERTERROR(ref2.count()==3,"Invalid Refcount");
            try
            {
                ASSERTERROR(ref3.count() || !ref3.count(),"Missing exception for nullptr ref");
            }
            catch(Core::RefCountException& re){};
        }
        ASSERTERROR(!newFlag,"New Operator called for constant object.");
        ASSERTERROR(!deleteFlag,"Unexpected call for delete operator");
    }

    void Test_RefCount::run()
    {
        test_dynamic();
        test_static();
    }
}
