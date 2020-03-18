#pragma once

#ifndef BUILD_DLL
#define PUBAPI __declspec(dllimport)
#else
#define PUBAPI __declspec(dllexport)
#endif

#include <optional>

namespace gm
{

    struct ColorRGB
    {
        float r,
            g,
            b;

        ColorRGB(float r, float g, float b)
            : r(r),
            g(g),
            b(b)
        {}
    };

    struct PUBAPI IVisual
    {
        virtual size_t LineThickness() const = 0;
        virtual const ColorRGB& Color() const = 0;

        virtual void SetLineThickness(size_t dots) = 0;
        virtual void SetColor(ColorRGB color) = 0;
    };

    // drawer is a state machine
    // active visual properties may be queried and set 
    struct PUBAPI IDrawer : public IVisual
    {
        virtual void DrawLine(float x1, float y1, float x2, float y2) = 0;
        virtual void DrawCircle(float xc, float yc, float radius) = 0;
    };

    struct PUBAPI IDrawable
    {
        virtual void Draw(IDrawer &drawer) const = 0;

        // ownership of this object may be transfered
        virtual ~IDrawable() = default;
    };

   

    // ownership can not be transfered, no virtual destructor needed
    struct PUBAPI IProperty
    {
        enum Type
        {
            geometric,
            physic
        };

        virtual Type PropType() const = 0;
    };

    // no ownership transfer
    struct PUBAPI IPropertyHolder
    {
        using RefIProperty = std::reference_wrapper<IProperty>;
        using CRefIProperty = std::reference_wrapper<const IProperty>;

        virtual size_t CountProps(IProperty::Type type) const = 0;

        // default implementation
        virtual std::optional<RefIProperty> GetProperty(IProperty::Type type, size_t indx)
        {
            return std::nullopt;
        }
        virtual std::optional<CRefIProperty> GetProperty(IProperty::Type type, size_t indx) const
        {
            return std::nullopt;
        }

        virtual void SetProperty(const IProperty& prop) = 0;
    };
}