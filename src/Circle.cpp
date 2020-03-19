#include <cassert>

#include "Geometry.h"

Circle::Circle(const Point & pos)
    : GeomFormVisual(pos)
{

}

IGeomForm::Type Circle::GeomType() const
{
    return IGeomForm::circle;
}

Rect Circle::BoundingRect() const
{
    // TODO: implement
    return Rect(Position(), 0, 0);// Position(), sizeLength_.Value(), sizeLength_.Value());
}

bool Circle::PropertySupported(IPropertyGeometric::Type type) const
{
    switch (type)
    {
    case IPropertyGeometric::radius:
        return true;
    default:
        return false;
    }
}

std::set<IPropertyGeometric::Type> Circle::SupportedProps() const
{
    return std::set<IPropertyGeometric::Type>{IPropertyGeometric::radius};
}

void Circle::Scale(float times)
{
    radius_ *= times;
}

size_t Circle::CountProps(IProperty::Type type) const
{
    if (type != IProperty::geometric)
        return 0;

    // radius
    return 1;
}

std::optional<IPropertyHolder::RefIProperty> Circle::GetProperty(IProperty::Type type,
    size_t indx)
{
    // call default implementation if type is not supported or invalid indx
    if (type != IProperty::geometric ||
        indx >= CountProps(IProperty::geometric))
        return IPropertyHolder::GetProperty(type, indx);

    assert(!indx && "Unexpected value");
    return std::optional<RefIProperty>(radius_);
}

std::optional<IPropertyHolder::CRefIProperty> Circle::GetProperty(IProperty::Type type, size_t indx) const
{
    // call default implementation if type is not supported or invalid indx
    if (type != IProperty::geometric ||
        indx >= CountProps(IProperty::geometric))
        return IPropertyHolder::GetProperty(type, indx);

    assert(!indx && "Unexpected value");
    return std::optional<CRefIProperty>(radius_);
}

void Circle::SetProperty(const IProperty & prop)
{
    if (prop.PropType() != IProperty::geometric)
        throw std::invalid_argument("Property type is not supported!");

    // use static_cast is safe since the library's implementation enforces type safety
    const IPropertyGeometric &gprop = static_cast<const IPropertyGeometric&>(prop);

    switch (gprop.PropTypeGeom())
    {
    case IPropertyGeometric::length:
        radius_ = static_cast<const decltype(radius_)&>(gprop);
        return;
    default:
        throw std::invalid_argument("Property type is not supported!");
    }
}

void Circle::Draw(IDrawer & drawer) const
{
    // remember visual props
    size_t prevThick = drawer.LineThickness();
    ColorRGB prevColor = drawer.Color();

    drawer.SetColor(GeomFormVisual::Color());
    drawer.SetLineThickness(GeomFormVisual::LineThickness());

    const Point& pos = GeomFormVisual::Position();

    drawer.DrawCircle(pos.x, pos.y, radius_.Value());

    // recover previous state
    drawer.SetColor(prevColor);
    drawer.SetLineThickness(prevThick);
}