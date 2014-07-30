//
//  BaseShape.cpp
//  Cpp_Revision
//
/*

Copyright (c) 2014 Luke Marcus Biagio Testa
All rights reserved.

Redistribution and use in source and binary forms are permitted
provided that the above copyright notice and this paragraph are
duplicated in all such forms and that any documentation,
advertising materials, and other materials related to such
distribution and use acknowledge that the software was developed
by the Luke Marcus Biagio Testa. The name of the
Luke Marcus Biagio Testa may not be used to endorse or promote products derived
from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * 
 */

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






