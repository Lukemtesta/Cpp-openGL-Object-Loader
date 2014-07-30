//
//  Circle.cpp
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


#include "Circle.h"



// ------------------------- Constructor --------------------------------


// Explicit Default Constructor
Shape::Circle::Circle() : BaseShape(), radius(0) {};


// Create Circle of Centre and Radius
Shape::Circle::Circle(const Vector3& pt, double radius ) : BaseShape(pt), radius(radius)
{
   // BaseShape* tempBaseShape = this;
    
   // *tempBaseShape = pt;
};


// Explicit Copy Constructor
Shape::Circle::Circle( const Circle& circle ) : BaseShape ( (BaseShape&) circle ), radius(circle.radius) {};



// ------------------------- Destructors --------------------------------


// Explicit Destructor
Shape::Circle::~Circle() { std::cout << "Deleteing [CIRCLE]" << std::endl; };



// ------------------------- Member Functions ----------------------------

void Shape::Circle::printRadius()
{
    if (!radius)
    {
        std::cout << "No Radius" << std::endl;
        return;
    }
    
    std::cout << "radius: " << radius << std::endl;
};



// ------------------------- Overload Operators -----------------------------


// Deep Copy
Shape::Circle& Shape::Circle::operator =( Circle& circle )
{
    BaseShape& tempBaseShape = *this;
    
    radius = circle.radius;
    tempBaseShape = circle.getCentre();
    
    return *this;
};