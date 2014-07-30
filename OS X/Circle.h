//
//  Circle.h
//  Cpp_Revision
//
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

namespace Shape
{
	class Circle : public BaseShape
	{
		public:
				// Constructors
				Circle();
				Circle( const Vector3& pt, double radius );
				Circle( const Circle& circle);
    
				// Destructors
				virtual ~Circle();
    
				// Overload Copy Operators
				Circle& operator =( Circle& circle );
				inline Circle& operator =( const Vector3& pt );
				inline Circle& operator =( const double radius );
    
				// Overload Unary Operator
				inline Circle& operator +=( const double radius );
				inline Circle& operator -=( const double radius );
    
				// Member Functions
				inline double getRadius();
				void printRadius();
    
		private:
    
				double radius;
	};
}

// ------------------------ Inline Members ----------------------


double Shape::Circle::getRadius() { return radius; };


// ----------------------- Inline Overrides ---------------------


// Change Circle Centre
Shape::Circle& Shape::Circle::operator =( const Vector3& pt )
{
    BaseShape* tempBaseShape = this;
    
    *tempBaseShape = pt;
    
    return *this;
};


// Change Circle Radius
Shape::Circle& Shape::Circle::operator =( const double radius )
{
    this->radius = radius;
    return *this;
};


// Offset Circle Radius
Shape::Circle& Shape::Circle::operator +=( const double radius )
{
    this->radius += radius;
    return *this;
};


// Offset Circle Radius
Shape::Circle& Shape::Circle::operator -=( const double radius )
{
    this->radius -= radius;
    return *this;
};





// -------------------------------------------- Test Code ----------------------------------------------


/*
 Circle* c1;
 BaseShape* bs;
 Circle* c2;
 
 // default constructor
 std::cout << "c1: ";
 c1 = new Circle();
 c1->printRadius();
 
 // set constructor
 std::cout << "c1: ";
 c1 = new Circle( *new Vector(4,2), 2.34);
 bs = new BaseShape( (BaseShape&) *c1 );
 c1->printRadius();
 bs->print();
 
 // copy constructor
 std::cout << "c2: ";
 c2 = new Circle( *c1 );
 bs = new BaseShape( (BaseShape&) *c2 );
 c2->printRadius();
 bs->print();
 
 // copy operator
 std::cout << "copy operator c2: ";
 c2 = new Circle();
 *c2 = *c1;
 bs = new BaseShape( (BaseShape&) *c2 );
 c2->printRadius();
 bs->print();
 
 // set centre
 std::cout << "c2: ";
 *c2 = *new Vector(-3,4.153);
 bs = new BaseShape( (BaseShape&) *c2 );
 c2->printRadius();
 bs->print();
 
 // set radius
 std::cout << "c2: ";
 *c2 = 0.01;
 bs = new BaseShape( (BaseShape&) *c2 );
 c2->printRadius();
 bs->print();
 
 // increment radius
 std::cout << "c2: ";
 *c2 += 4.65/2;
 bs = new BaseShape( (BaseShape&) *c2 );
 c2->printRadius();
 bs->print();
 
 // decrement radius
 std::cout << "c2: ";
 *c2 -= 4.65/2;
 bs = new BaseShape( (BaseShape&) *c2 );
 c2->printRadius();
 bs->print();
 */