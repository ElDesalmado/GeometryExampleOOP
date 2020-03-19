#include <cassert>

#include "Geometry.h"

Triangle::Triangle(const Point & pos)
	: GeomFormVisual(pos)
{

}

IGeomForm::Type Triangle::GeomType() const
{
	return IGeomForm::triangle;
}

Rect Triangle::BoundingRect() const
{
	// TODO: implement
	return Rect(Position(), 0, 0);// Position(), sizeLength_.Value(), sizeLength_.Value());
}

bool Triangle::PropertySupported(IPropertyGeometric::Type type) const
{
	switch (type)
	{
	case IPropertyGeometric::length:
		return true;
	default:
		return false;
	}
}

std::set<IPropertyGeometric::Type> Triangle::SupportedProps() const
{
	return std::set<IPropertyGeometric::Type>{IPropertyGeometric::length};
}

void Triangle::Scale(float times)
{
	length_ *= times;
}

size_t Triangle::CountProps(IProperty::Type type) const
{
	if (type != IProperty::geometric)
		return 0;

	// side length
	return 1;
}

std::optional<IPropertyHolder::RefIProperty> Triangle::GetProperty(IProperty::Type type,
	size_t indx)
{
	// call default implementation if type is not supported or invalid indx
	if (type != IProperty::geometric ||
		indx >= CountProps(IProperty::geometric))
		return IPropertyHolder::GetProperty(type, indx);

	assert(!indx && "Unexpected value");
	return std::optional<RefIProperty>(length_);
}

std::optional<IPropertyHolder::CRefIProperty> Triangle::GetProperty(IProperty::Type type, size_t indx) const
{
	// call default implementation if type is not supported or invalid indx
	if (type != IProperty::geometric ||
		indx >= CountProps(IProperty::geometric))
		return IPropertyHolder::GetProperty(type, indx);

	assert(!indx && "Unexpected value");
	return std::optional<CRefIProperty>(length_);
}

void Triangle::SetProperty(const IProperty & prop)
{
	if (prop.PropType() != IProperty::geometric)
		throw std::invalid_argument("Property type is not supported!");

	// use static_cast is safe since the library's implementation enforces type safety
	const IPropertyGeometric &gprop = static_cast<const IPropertyGeometric&>(prop);

	switch (gprop.PropTypeGeom())
	{
	case IPropertyGeometric::length:
		length_ = static_cast<const decltype(length_)&>(gprop);
		return;
	default:
		throw std::invalid_argument("Property type is not supported!");
	}
}

void Triangle::Draw(IDrawer & drawer) const
{
	// remember visual props
	size_t prevThick = drawer.LineThickness();
	ColorRGB prevColor = drawer.Color();

	drawer.SetColor(GeomFormVisual::Color());
	drawer.SetLineThickness(GeomFormVisual::LineThickness());

	constexpr float sin45 = 0.70710678f;

	const Point& base = GeomFormVisual::Position();
	Point upper{ base.x + 0.5f * length_.Value(), base.y + sin45 * length_.Value() };

	drawer.DrawLine(base.x, base.y, 
		upper.x, upper.y);
	drawer.DrawLine(base.x + length_.Value(), 
		base.y, upper.x, upper.y);
	drawer.DrawLine(base.x, base.y,
		base.x + length_.Value(), base.y);

	// recover previous state
	drawer.SetColor(prevColor);
	drawer.SetLineThickness(prevThick);
}
