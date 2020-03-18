#include "DummyDrawer.h"

#include <iostream>

using namespace gm;

size_t DummyDrawer::LineThickness() const
{
    return lineThickness_;
}

const ColorRGB & DummyDrawer::Color() const
{
    return color_;
}

void DummyDrawer::SetLineThickness(size_t dots)
{
    lineThickness_ = dots;
}

void DummyDrawer::SetColor(ColorRGB color)
{
    color_ = color;
}

void DummyDrawer::DrawLine(float x1, float y1, float x2, float y2)
{
    std::cout << "Drawing line: (" << x1 << ":" << y1 << ")->(" << x2 <<
        ":" << y2 << "), thick = " << lineThickness_ << ", color [" <<
        color_.r << "," << color_.g << "," << color_.b << "]" << std::endl;
}

void DummyDrawer::DrawCircle(float xc, float yc, float radius)
{
    std::cout << "Drawing circle: (" << xc << ":" << yc << ")->(r:" << radius <<
        "), thick = " << lineThickness_ << ", color [" <<
        color_.r << "," << color_.g << "," << color_.b << "]" << std::endl;
}
