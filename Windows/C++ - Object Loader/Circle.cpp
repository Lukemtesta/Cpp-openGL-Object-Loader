//
//  Circle.cpp
//  Cpp_Revision
//
//


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