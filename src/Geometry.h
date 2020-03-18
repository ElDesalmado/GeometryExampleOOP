#pragma once

// this is a private header for the library implementation. 
// It was made so for the sake of example - to show the Factory implementation
#include "IGeometry.h"

using namespace gm;

class Visual : public IVisual
{
    size_t lineThickness_{ 1 };
    ColorRGB color_{ 0.0f, 0.0f, 0.0f }; // black by default

public:
    
    size_t LineThickness() const override;
    const ColorRGB& Color() const override;
    void SetLineThickness(size_t dots) override;
    void SetColor(ColorRGB color) override;

};

// way to deal with the diamond problem
class GeomPosition : public virtual IPosition
{
    Point pos_;

public:
    GeomPosition(Point pos)
        : pos_(pos)
    {}

    const Point& Position() const override
    {
        return pos_;
    }

    void SetPosition(Point pos) override
    {
        pos_ = pos;
    }

    void Transpose(float dX, float dY) override
    {
        pos_.x += dX;
        pos_.y += dY;
    }

};

class GeomFormVisual : public IGeomForm,
    public GeomPosition
{
    // composition over inheritance 
    // another way to tackle the diamond problem
    Visual visuals_;

public:

    GeomFormVisual(const Point& pos)
        : GeomPosition(pos)
    {}

    // inherited from IVisual
    size_t LineThickness() const override;
    const ColorRGB& Color() const override;

    void SetLineThickness(size_t dots) override;
    void SetColor(ColorRGB color) override;

    // inherited from IPosition
    const Point& Position() const override;

    void SetPosition(Point pos) override;
    void Transpose(float dX, float dY) override;


};

class Rectangle : public GeomFormVisual
{
    PropertyGeometric<IPropertyGeometric::height> height_{ 10.0f };
    PropertyGeometric<IPropertyGeometric::width> width_{ 20.0f };

public:
    Rectangle(const Point& pos);

    // inherited from IGeomForm
    Type GeomType() const override;
    Rect BoundingRect() const override;
    bool PropertySupported(IPropertyGeometric::Type) const override;
    std::set<IPropertyGeometric::Type> SupportedProps() const override;
    void Scale(float times) override;

    // inherited from IPropertyHolder
    size_t CountProps(IProperty::Type type) const override;
    std::optional<RefIProperty> GetProperty(IProperty::Type type,
        size_t indx) override;
    std::optional<CRefIProperty> GetProperty(IProperty::Type type, 
        size_t indx) const override;

    // the caller is responsible to check whether the type is valid
    void SetProperty(const IProperty& prop) override;

    // inherited from IDrawable
    virtual void Draw(IDrawer &drawer) const override;

};

class Square : public GeomFormVisual
{
    PropertyGeometric<IPropertyGeometric::length> sizeLength_{ 10 };

public:
    Square(const Point& pos);

    // inherited from IGeomForm
    Type GeomType() const override;
    Rect BoundingRect() const override;
    bool PropertySupported(IPropertyGeometric::Type) const override;
    std::set<IPropertyGeometric::Type> SupportedProps() const override;
    void Scale(float times) override;

    // inherited from IPropertyHolder
    size_t CountProps(IProperty::Type type) const override;
    std::optional<RefIProperty> GetProperty(IProperty::Type type,
        size_t indx) override;
    std::optional<CRefIProperty> GetProperty(IProperty::Type type,
        size_t indx) const override;

    // the caller is responsible to check whether the type is valid
    void SetProperty(const IProperty& prop) override;

    // inherited from IDrawable
    virtual void Draw(IDrawer &drawer) const override;
};

class Circle : public GeomFormVisual
{
    PropertyGeometric<IPropertyGeometric::radius> radius_{ 15 };

public:
    Circle(const Point& pos);

    // inherited from IGeomForm
    Type GeomType() const override;
    Rect BoundingRect() const override;
    bool PropertySupported(IPropertyGeometric::Type) const override;
    std::set<IPropertyGeometric::Type> SupportedProps() const override;
    void Scale(float times) override;

    // inherited from IPropertyHolder
    size_t CountProps(IProperty::Type type) const override;
    std::optional<RefIProperty> GetProperty(IProperty::Type type,
        size_t indx) override;
    std::optional<CRefIProperty> GetProperty(IProperty::Type type,
        size_t indx) const override;

    // the caller is responsible to check whether the type is valid
    void SetProperty(const IProperty& prop) override;

    // inherited from IDrawable
    virtual void Draw(IDrawer &drawer) const override;
};