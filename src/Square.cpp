#include <cassert>

#include "Geometry.h"

Square::Square(const Point & pos)
    : GeomFormVisual(pos)
{}

IGeomForm::Type Square::GeomType() const
{
    return IGeomForm::square;
}

Rect Square::BoundingRect() const
{
    return Rect(Position(), sizeLength_.Value(), sizeLength_.Value());
}

bool Square::PropertySupported(IPropertyGeometric::Type type) const
{
    switch (type)
    {
    case IPropertyGeometric::length:
        return true;
    default:
        return false;
    }
}

std::set<IPropertyGeometric::Type> Square::SupportedProps() const
{
    return std::set<IPropertyGeometric::Type>{IPropertyGeometric::length};
}

void Square::Scale(float times)
{
    sizeLength_ *= times;
}

size_t Square::CountProps(IProperty::Type type) const
{
    if (type != IProperty::geometric)
        return 0;

    // length
    return 1;
}

std::optional<IPropertyHolder::RefIProperty> Square::GetProperty(IProperty::Type type, 
    size_t indx)
{
    // call default implementation if type is not supported or invalid indx
    if (type != IProperty::geometric ||
        indx >= CountProps(IProperty::geometric))
        return IPropertyHolder::GetProperty(type, indx);

    assert(!indx && "Unexpected value");
    return std::optional<RefIProperty>(sizeLength_);
}

std::optional<IPropertyHolder::CRefIProperty> Square::GetProperty(IProperty::Type type, size_t indx) const
{
    // call default implementation if type is not supported or invalid indx
    if (type != IProperty::geometric ||
        indx >= CountProps(IProperty::geometric))
        return IPropertyHolder::GetProperty(type, indx);

    assert(!indx && "Unexpected value");
    return std::optional<CRefIProperty>(sizeLength_);
}

void Square::SetProperty(const IProperty & prop)
{
    if (prop.PropType() != IProperty::geometric)
        throw std::invalid_argument("Property type is not supported!");

    // use static_cast is safe since the library's implementation enforces type safety
    const IPropertyGeometric &gprop = static_cast<const IPropertyGeometric&>(prop);

    switch (gprop.PropTypeGeom())
    {
    case IPropertyGeometric::length:
        sizeLength_ = static_cast<const decltype(sizeLength_)&>(gprop);
        return;
    default:
        throw std::invalid_argument("Property type is not supported!");
    }
}

void Square::Draw(IDrawer & drawer) const
{
    // remember visual props
    size_t prevThick = drawer.LineThickness();
    ColorRGB prevColor = drawer.Color();

    drawer.SetColor(GeomFormVisual::Color());
    drawer.SetLineThickness(GeomFormVisual::LineThickness());

    const Point& pos = GeomFormVisual::Position();

    // lower
    drawer.DrawLine(pos.x, pos.y,
        pos.x + sizeLength_.Value(), pos.y);

    // upper
    drawer.DrawLine(pos.x, pos.y + sizeLength_.Value(),
        pos.x + sizeLength_.Value(), pos.y + sizeLength_.Value());

    // left
    drawer.DrawLine(pos.x, pos.y,
        pos.x, pos.y + sizeLength_.Value());

    // rigth
    drawer.DrawLine(pos.x + sizeLength_.Value(), pos.y,
        pos.x + sizeLength_.Value(), pos.y + sizeLength_.Value());

    // recover previous state
    drawer.SetColor(prevColor);
    drawer.SetLineThickness(prevThick);
}