#include "Geometry.h"

Rectangle::Rectangle(const Point & pos)
    : GeomFormVisual(pos)
{}

IGeomForm::Type Rectangle::GeomType() const
{
    return IGeomForm::rectangle;
}

Rect Rectangle::BoundingRect() const
{
    return Rect(Position(), width_.Value(), height_.Value());
}

bool Rectangle::PropertySupported(IPropertyGeometric::Type type) const
{
    switch (type)
    {
    case IPropertyGeometric::width:
    case IPropertyGeometric::height:
        return true;
    default:
        return false;
    }
}

std::set<IPropertyGeometric::Type> Rectangle::SupportedProps() const
{
    return std::set<IPropertyGeometric::Type>{IPropertyGeometric::width,
        IPropertyGeometric::height};
}

void Rectangle::Scale(float times)
{
    height_ *= times;
    width_ *= times;
}

size_t Rectangle::CountProps(IProperty::Type type) const
{
    if (type != IProperty::geometric)
        return 0;

    // height and width
    return 2;
}

std::optional<IPropertyHolder::RefIProperty>
Rectangle::GetProperty(IProperty::Type type, size_t indx)
{
    // call default implementation if type is not supported or invalid indx
    if (type != IProperty::geometric ||
        indx >= CountProps(IProperty::geometric))
        return IPropertyHolder::GetProperty(type, indx);

    if (indx = 0)
        return std::optional<RefIProperty>(height_);

    return std::optional<RefIProperty>(width_);
}

std::optional<IPropertyHolder::CRefIProperty>
Rectangle::GetProperty(IProperty::Type type, size_t indx) const
{
    // call default implementation if type is not supported or invalid indx
    if (type != IProperty::geometric ||
        indx >= CountProps(IProperty::geometric))
        return IPropertyHolder::GetProperty(type, indx);

    if (indx = 0)
        return std::optional<CRefIProperty>(height_);

    return std::optional<CRefIProperty>(width_);
}

void Rectangle::SetProperty(const IProperty & prop)
{
    if (prop.PropType() != IProperty::geometric)
        throw std::invalid_argument("Property type is not supported!");

    // use static_cast is safe since the library's implementation enforces type safety
    const IPropertyGeometric &gprop = static_cast<const IPropertyGeometric&>(prop);

    switch (gprop.PropTypeGeom())
    {
    case IPropertyGeometric::height:
        height_ = static_cast<const decltype(height_)&>(gprop);
        return;
    case IPropertyGeometric::width:
        width_ = static_cast<const decltype(width_)&>(gprop);
        return;
    default:
        throw std::invalid_argument("Property type is not supported!");
    }
}

void Rectangle::Draw(IDrawer & drawer) const
{
    // remember visual props
    size_t prevThick = drawer.LineThickness();
    ColorRGB prevColor = drawer.Color();

    drawer.SetColor(GeomFormVisual::Color());
    drawer.SetLineThickness(GeomFormVisual::LineThickness());

    const Point& pos = GeomFormVisual::Position();

    // lower
    drawer.DrawLine(pos.x, pos.y,
        pos.x + width_.Value(), pos.y);

    // upper
    drawer.DrawLine(pos.x, pos.y + height_.Value(),
        pos.x + width_.Value(), pos.y + height_.Value());

    // left
    drawer.DrawLine(pos.x, pos.y,
        pos.x, pos.y + height_.Value());

    // rigth
    drawer.DrawLine(pos.x + width_.Value(), pos.y,
        pos.x + width_.Value(), pos.y + height_.Value());

    // recover previous state
    drawer.SetColor(prevColor);
    drawer.SetLineThickness(prevThick);
}
