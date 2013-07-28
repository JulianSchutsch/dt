#ifndef _GUI_HEADER_
#define _GUI_HEADER_

#include <list>
#include <memory>
#include "guibounds.hpp"

namespace GUI
{
    class GUIObject;

    typedef std::shared_ptr<GUIObject> GUIObject_SPtr;
    typedef std::weak_ptr<GUIObject> GUIObject_WPtr;

    class GUIObject
    {
    private:
        bool focus;
        GUIObject_WPtr parent;
        std::list<GUIObject_SPtr> children;
    public:

    };
}

#endif // _GUI_HEADER_
