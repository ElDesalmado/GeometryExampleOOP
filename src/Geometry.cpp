#include "Geometry.h"

size_t Visual::LineThickness() const
{
    return lineThickness_;
}

const ColorRGB & Visual::Color() const
{
    return color_;
}

void Visual::SetLineThickness(size_t dots)
{
    lineThickness_ = dots;
}

void Visual::SetColor(ColorRGB color)
{
    color_ = color;
}


GeomFormVisual::GeomFormVisual(const Point & pos)
	: GeomPosition(pos)
{}

size_t GeomFormVisual::LineThickness() const
{
    return visuals_.LineThickness();
}

const ColorRGB & GeomFormVisual::Color() const
{
    return visuals_.Color();
}

void GeomFormVisual::SetLineThickness(size_t dots)
{
    visuals_.SetLineThickness(dots);
}

void GeomFormVisual::SetColor(ColorRGB color)
{
    visuals_.SetColor(color);
}

const Point & GeomFormVisual::Position() const
{
    return GeomPosition::Position();
}

void GeomFormVisual::SetPosition(Point pos)
{
    GeomPosition::SetPosition(pos);
}

void GeomFormVisual::Transpose(float dX, float dY)
{
    GeomPosition::Transpose(dX, dY);
}

std::unique_ptr<IGeomForm> IGeomForm::Create(IGeomForm::Type type,
    const Point& pos)
{
    switch (type)
    {
    case gm::IGeomForm::rectangle:
        return std::make_unique<Rectangle>(pos);
    case gm::IGeomForm::square:
        return std::make_unique<Square>(pos);
    case gm::IGeomForm::circle:
        return std::make_unique<Circle>(pos);
    case gm::IGeomForm::triangle:
		return std::make_unique<Triangle>(pos);
	default:
        break;
    }

    return nullptr;
}


