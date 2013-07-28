#ifndef _BASICS_HEADER_
#define _BASICS_HEADER_

#include <exception>
//*****************************************************************************
// RefCount
//   Reference counter capable of handling dynamically and statically allocated
//   objects.
//*****************************************************************************

namespace Core
{

    typedef unsigned long refcount_t;
    struct refcountable_t
    {
        public:
            refcount_t count=0;
            bool refered=false;
    };

    #define REFCOUNTABLE                            \
        public:                                     \
            Core::refcountable_t __refcountdata={}; \

    class RefCountException:public std::exception
    {
        virtual const char* what() const noexcept override
        {
            return "RefCountException";
        }
    };

    template<class T>
    class Ref
    {
    private:
        T* pnt=nullptr;
        void incref() const noexcept {pnt->__refcountdata.count++;}
        void decref() const noexcept
        {
            if(pnt!=nullptr)
            {
                if((--pnt->__refcountdata.count)==0)
                {
                    delete pnt;
                }
            }
        }
    public:
        // Default constructor
        Ref() noexcept:pnt(nullptr){};
        // Constructor for dynamically allocated objects
        //  (Please never use it for statically allocated objects with &myobj)
        Ref(T* apnt):pnt(apnt)
        {
            if(apnt!=nullptr) incref();
        }
        // Constructor for statically allocated objects+
        //  (Please never use it for dynamically allocated objects with *myobj)
        Ref(T& apnt) noexcept:pnt(&apnt)
        {
            if(!apnt.__refcountdata.refered)
            {
                apnt.__refcountdata.refered=true;
                incref();
            }
            incref();
        }

        Ref(const Ref& other) noexcept
        {
            if(&other!=this)
            {
                pnt = other.pnt;
                incref();
            }
        }

        Ref& operator = (const Ref& other) noexcept
        {
            if(&other!=this)
            {
                decref();
                pnt = other.pnt;
                incref();
            }
            return *this;
        }

        Ref(Ref&& other) noexcept
        {
            pnt = other.pnt;
            other.pnt = nullptr;
        }

        Ref& operator = (Ref&& other) noexcept
        {
            if(&other!=this)
            {
                decref();
                pnt = other.pnt;
                other.pnt = nullptr;
            }
            return *this;
        }

        ~Ref() noexcept
        {
            if(pnt!=nullptr) decref();
        }

        T* operator ->() const noexcept
        {
            return pnt;
        }

        refcount_t count() const
        {
            if(pnt)
            {
                return pnt->__refcountdata.count;
            }
            else
            {
                throw RefCountException();
            }
        }

    };
}

#endif // _BASICS_HEADER_
