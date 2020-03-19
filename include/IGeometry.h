#pragma once

#include <memory>
#include <set>

#include "IPublic.h"

namespace gm
{
    struct Point
    {
        float x, y;

        Point(float x, float y)
            : x(x), y(y)
        {}
    };

    struct Rect
    {
        Point posXY;
        float width,
            height;

        Rect(const Point& pos, float width, float height)
            : posXY(pos),
            width(width),
            height(height)
        {}
    };

    struct PUBAPI IPosition
    {
        virtual const Point& Position() const = 0;
        
        virtual void SetPosition(Point pos) = 0;
        virtual void Transpose(float dX, float dY) = 0;

    };

    struct PUBAPI IPropertyGeometric : public IProperty
    {
        IProperty::Type PropType() const override
        {
            return IProperty::geometric;
        }

        // supported types for current library implementation
        // help to validate type and assumingly safe static upcast
        enum Type
        {
            length,
            radius,
            height,
            width
        };

        virtual Type PropTypeGeom() const = 0;
    };

   

    class PUBAPI IGeomForm : public IDrawable,
        public IPosition,
        public IVisual,
        public IPropertyHolder
    {

    public:
        enum Type
        {
            rectangle,
            square,
            circle,
            triangle
        };

        virtual Type GeomType() const = 0;
        virtual Rect BoundingRect() const = 0;

        // Supported Geometric properties. 
        // Defined not in IPublic since Geometric properties are defined here
        // default implementation
        virtual bool PropertySupported(IPropertyGeometric::Type) const
        {
            return false;
        }
        virtual std::set<IPropertyGeometric::Type> SupportedProps() const
        {
            return std::set<IPropertyGeometric::Type>();
        }


        virtual void Scale(float times) = 0;

        virtual ~IGeomForm() = default;

        // factory method, transfers ownership. Nullptr if type is not supported
        static std::unique_ptr<IGeomForm> Create(IGeomForm::Type type, 
            const Point& pos = Point(0.0f, 0.0f));
    };

    // for now all the available geometric properties are single-valued
   // so one class template will generate all the necessary ones
   // potentially the implementation may be more complicated
    template <IPropertyGeometric::Type type>
    class /*PUBAPI*/ PropertyGeometric : public IPropertyGeometric
    {
        float value_;
    public:

        PropertyGeometric(float value)
            : value_(value)
        {}

        IPropertyGeometric::Type PropTypeGeom() const override
        {
            return type;
        }

        float Value() const
        {
            return value_;
        }

        void operator*=(float multiply)
        {
            value_ *= multiply;
        }
    };

}
