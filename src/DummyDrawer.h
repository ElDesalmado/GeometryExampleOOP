#pragma once

#include "IPublic.h"

// dummy class to print drawing operations to the console
class DummyDrawer : public gm::IDrawer
{
    size_t lineThickness_ = 1;
    gm::ColorRGB color_{ 0.0f, 0.0f, 0.0f }; // black by default

public:

    // Inherited via IDrawer
    virtual size_t LineThickness() const override;
    virtual const gm::ColorRGB & Color() const override;
    virtual void SetLineThickness(size_t dots) override;
    virtual void SetColor(gm::ColorRGB color) override;
    virtual void DrawLine(float x1, float y1, float x2, float y2) override;
    virtual void DrawCircle(float xc, float yc, float radius) override;
};
