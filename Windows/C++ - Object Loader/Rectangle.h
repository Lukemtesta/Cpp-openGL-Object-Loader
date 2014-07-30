//
//  Rectangle.h
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

#include "Polygon.h"

// For computation, will not use exception safe copy. Will reference for fast copy.

namespace Shape
{
	class Rectangle : public Polygon
	{
    
		public:
    
					// Constructors and Destructors
					Rectangle();
					Rectangle( const Vector3 pt, const double w, const double h);
					Rectangle( const Rectangle& Shape );
					Rectangle( const Vector3& pt, std::vector<Vector3>& Vertices );
    
					virtual ~Rectangle();
    
					// Overload Operators
					Rectangle& operator =( const Rectangle& Shape );
					inline Rectangle& operator =( const Vector3& pt );
					// Offset Centre
					inline Rectangle& operator +=( const Vector3& pt );
    
					inline Vector3 getDimensions();
    
		private:
					inline bool isEqual( Rectangle& Shape1, Rectangle& Shape2 );
    
					double width;
					double height;
	};
}





// ----------------------------------------- Inline Private Member Functions -------------------------------


Shape::Rectangle& Shape::Rectangle::operator =( const Vector3& pt )
{
    (BaseShape&) *this = pt;
    
    return *this;
};

Shape::Rectangle& Shape::Rectangle::operator +=( const Vector3& pt )
{
    (BaseShape&) *this += pt;
    
    return *this;
};

// Return width and height respectively
Shape::Vector3 Shape::Rectangle::getDimensions()
{
    return *new Vector3( width, Vector(height,0) );
};


// is Equal Operation
bool Shape::Rectangle::isEqual ( Rectangle& Shape1, Rectangle& Shape2 )
{
    double sumShape1 = Shape1.width + Shape1.height + Shape1.getCentre().first + Shape1.getCentre().second.first;
    double sumShape2 = Shape2.width + Shape2.height + Shape2.getCentre().first + Shape2.getCentre().second.first;
    
    if (sumShape1 == sumShape2)
        return true;
    else
        return false;
};



// -------------------------------------- Test Code ---------------------------


/*
Rectangle* rect1;
Rectangle* rect2;

//Test default constructor
cout << "Default Constructor" << endl;
rect1 = new Rectangle();
cout << "H: " << rect1->getDimensions().first <<  " , W: " << rect1->getDimensions().second << endl;
//cout << "centre: " << rect1->getCentre().first << ", " << rect1->getCentre().second << endl;
Polygon& plygn = (Polygon&) *rect1;
plygn.print();

//Test Build constructor
cout << "Build Constructor" << endl;
rect1 = new Rectangle( *new Vector( -1, 1), 10, 5 );
cout << "H: " << rect1->getDimensions().first <<  " , W: " << rect1->getDimensions().second << endl;
cout << "centre: " << rect1->getCentre().first << ", " << rect1->getCentre().second << endl;
plygn = (Polygon&) *rect1;
plygn.print();

//Test Copy Assignment
cout << "Copy Constructor" << endl;
rect2 = new Rectangle(*rect1);
cout << "H: " << rect2->getDimensions().first <<  " , W: " << rect2->getDimensions().second << endl;
cout << "centre: " << rect2->getCentre().first << ", " << rect2->getCentre().second << endl;
plygn = (Polygon&) *rect2;
plygn.print();

//Test Copy Assignment
cout << "Copy Assignment" << endl;
rect1 = new Rectangle( *new Vector( 25, 25), 0.5, 0.8 );
rect2 = rect1;
cout << "H: " << rect2->getDimensions().first <<  " , W: " << rect2->getDimensions().second << endl;
cout << "centre: " << rect2->getCentre().first << ", " << rect2->getCentre().second << endl;
plygn = (Polygon&) *rect2;
plygn.print();

// Test Assignment Offset Centre
*rect2 += *new Vector(-25, 25);
cout << "H: " << rect2->getDimensions().first <<  " , W: " << rect2->getDimensions().second << endl;
cout << "centre: " << rect2->getCentre().first << ", " << rect2->getCentre().second << endl;
plygn = (Polygon&) *rect2;
plygn.print();

// Test Change Centre
*rect2 = *new Vector(0.25, 0.25);
cout << "H: " << rect2->getDimensions().first <<  " , W: " << rect2->getDimensions().second << endl;
cout << "centre: " << rect2->getCentre().first << ", " << rect2->getCentre().second << endl;
plygn = (Polygon&) *rect2;
plygn.print();

*/