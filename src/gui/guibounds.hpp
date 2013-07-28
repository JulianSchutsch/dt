#ifndef _GUIBOUNDS_HEADER_
#define _GUIBOUNDS_HEADER_

namespace GUI
{
    typedef long coord_t;
    enum class constraintType_t
    {
        None,
        Constant,
        UsingSize,
        UsingParentSize
    };

    class Bounds
    {
    public:
        coord_t top;
        coord_t left;
        coord_t height;
        coord_t width;
        bool    visible;
        bool isInside(coord_t x, coord_t y)
        {
            return visible && (x>=left) && (x<left+width) && (y>=top) && (y<top+height);
        }
    };

    class AbsBounds
    {
    public:
        coord_t top;
        coord_t left;
        coord_t height;
        coord_t width;
        coord_t subtop;
        coord_t subleft;
        coord_t visible;
    };

    class Anchors
    {
        bool top    = true;
        bool left   = true;
        bool right  = false;
        bool bottom = false;
        coord_t topBorder    = 0;
        coord_t leftBorder   = 0;
        coord_t rightBorder;
        coord_t bottomBorder;
    };

    class Constraint
    {
        constraintType_t minValueConstraint;
        coord_t          minValueConstant;
        constraintType_t maxValueConstraint;
        coord_t          maxValueConstant;
        constraintType_t minSizeConstraint;
        coord_t          minSizeConstant;
        constraintType_t maxSizeConstraint;
        coord_t          maxSizeConstant;
    };
}

#endif // _GUIBOUNDS_HEADER_
