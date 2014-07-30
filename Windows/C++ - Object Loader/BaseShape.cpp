//
//  BaseShape.cpp
//  Cpp_Revision
//
//

#include "BaseShape.h"

//---------------------------- Constructors --------------------------------


// Default Constructor
Shape::BaseShape::BaseShape() : Centre(NULL), Colour(NULL), Angle(0) {};

// Copy Constructor : Deep Copy
Shape::BaseShape::BaseShape(const BaseShape& Shape) :  Colour(Shape.Colour), Angle(0) { Centre = Shape.Centre; };

Shape::BaseShape::BaseShape(const Vector3& pt) : Colour(NULL), Angle(0) { Centre = new Vector3(pt); }


// --------------------------- Destructors ---------------------------


Shape::BaseShape::~BaseShape()
{
    std::cout << "Deleting [BaseShape]: Centre" << std::endl;
    delete Centre;
    delete Colour;
};



// --------------------------- Member Functions -----------------------------

void Shape::BaseShape::print() const
{
    if (!Centre || !Orientation || !Colour )
    {
        std::cout << "No Centre || Orientation || Colour Stored" << std::endl;
        return;
    }
    
    std::cout << "Centre: (" << Centre->first << "," << Centre->second.first << "," << Centre->second.second << ") " << std::endl;
    std::cout << "Colour: " << Colour->first.first << ", " << Colour->first.second << ", " << Colour->second.first << std::endl;
    std::cout << "Transparency: " << Colour->second.second << std::endl;
    std::cout << "Angle: " << Angle << std::endl;
};






