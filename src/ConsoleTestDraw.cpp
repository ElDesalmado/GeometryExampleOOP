
#include "IGeometry.h"

#include "DummyDrawer.h"

#include <iostream>
#include <vector>
#include <map>
#include <string>

std::map<gm::IGeomForm::Type, std::string> formNames{ 
    std::make_pair(gm::IGeomForm::rectangle, std::string("rectangle")),
    std::make_pair(gm::IGeomForm::square, std::string("square")),
    std::make_pair(gm::IGeomForm::circle, std::string("circle")),
    std::make_pair(gm::IGeomForm::triangle, std::string("triangle"))
};

int main(int argc, const char *argv)
{
    DummyDrawer drawer;

    std::unique_ptr<gm::IGeomForm> rectTest =
        gm::IGeomForm::Create(gm::IGeomForm::rectangle, gm::Point(10.0f, 15.0f));

    if (!rectTest)
    {
        std::cout << "Failed to create a rectangle" << std::endl;
        return -1;
    }

    std::cout << "Draw test rectangle:\n";
    rectTest->Draw(drawer);

    rectTest->Transpose(50, 50);
    rectTest->SetLineThickness(3);
    rectTest->SetColor(gm::ColorRGB(3.0f, 2.0f, 14.0f));

    try
    {
        rectTest->SetProperty(gm::PropertyGeometric<gm::IPropertyGeometric::height>(22));
        rectTest->SetProperty(gm::PropertyGeometric<gm::IPropertyGeometric::width>(34));
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    // this must throw
    try
    {
        rectTest->SetProperty(gm::PropertyGeometric<gm::IPropertyGeometric::length>(10));
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Expected error: " << e.what() << std::endl;
    }

    std::cout << "Draw modified test rectangle:\n";
    rectTest->Draw(drawer);

    std::vector<gm::IGeomForm::Type> fromTypes{ gm::IGeomForm::square,
        gm::IGeomForm::rectangle,
        gm::IGeomForm::circle,
        gm::IGeomForm::triangle
    };

    gm::Point base{ 0.0f, 0.0f };

    std::vector<std::unique_ptr<gm::IGeomForm>> forms;
    for (gm::IGeomForm::Type t : fromTypes)
    {
        forms.emplace_back(gm::IGeomForm::Create(t, base));
        base.x += 20;
        base.y += 30;
    }

    for (const std::unique_ptr<gm::IGeomForm>& pform : forms)
    {
        if (!pform)
        {
            std::cerr << "ERROR: Form was nullptr!" << std::endl;
            return -1;
        }

        std::cout << "Drawing " << formNames[pform->GeomType()] << std::endl;
        pform->Draw(drawer);
    }

    return 0;
}
