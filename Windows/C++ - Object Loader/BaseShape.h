//
//  BaseShape.h
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

#include <iostream>
#include <vector>


namespace Shape
{
	typedef std::pair< double, double > Vector;
	typedef std::pair< double, Vector > Vector3;
	typedef std::pair< Vector, Vector > Vector4;


	// Abstract Class dependent on Graphic Library (e.g. openCV or openGL) for rendering. Only contains 1 pt so no need to instantiate
	class BaseShape
	{
		public:
					// Constructors
					BaseShape();
					BaseShape(const BaseShape& Shape);
					BaseShape(const Vector3& pt );
    
					// Destructors
					virtual ~BaseShape();
    
    
					// Override Assignment Operator
					inline BaseShape& operator =(const BaseShape& Shape);

					// Center point manipulation
					inline BaseShape& operator =(const Vector3& pt);
					inline BaseShape& operator +=( const Vector3& offset );
					inline BaseShape& operator -=( const Vector3& offset );
    
					// Colour as Vec4f for openGL
					inline BaseShape& operator =(const Vector4& colour);
					inline BaseShape& operator +=(const Vector4& colour);
					inline BaseShape& operator -=(const Vector4& colour);
    
					// AxisAngle Magnitude for 1 1 1 ( degrees )
					inline BaseShape& operator =(const float& angleMag);
					inline BaseShape& operator +=(const float& angleMag);
					inline BaseShape& operator -=(const float& angleMag);
    
    
					// Member Functions
					inline Vector3 getCentre() const;
					inline Vector4 getColour() const;
					inline float getAngle() const;
    
					virtual void print() const;
    
    
					// Pure Virtual Member Pointers
					virtual BaseShape* clone() = 0;
					virtual int size() = 0;
					virtual std::vector<Vector3> getVertices() = 0;
					//virtual void render() = 0;
    
		private:
    
					Vector3* Orientation;
					Vector3* Centre;
					Vector4* Colour;
					float Angle;
	};
}


// ----------------------------- Inline Members ---------------------------


// Returns Magnitude of AxisAngle
float Shape::BaseShape::getAngle() const
{
    return Angle;
};


Shape::Vector4 Shape::BaseShape::getColour() const
{
    if( Colour == NULL )
    {
        std::cerr << " No Angle " << std::endl;
        exit(0);
    }
    else
        return *Colour;
};


Shape::Vector3 Shape::BaseShape::getCentre() const
{
    if( Centre == NULL )
    {
        std::cerr << " No Centre" << std::endl;
        exit(0);
    }
    else
        return *Centre;
};


// --------------------------- Inline Overrides -----------------------------


// Deep Copy : Exception Safe
Shape::BaseShape& Shape::BaseShape::operator=(const BaseShape& Shape)
{
    Centre = new Vector3( *Shape.Centre );
    
    return *this;
};

// Manual Deep Copy
Shape::BaseShape& Shape::BaseShape::operator =( const Vector3& pt )
{
    Centre = new Vector3(pt);
    
    return *this;
};


// Offset Centre
Shape::BaseShape& Shape::BaseShape::operator +=( const Vector3& offset )
{
    Centre->first += offset.first;
    Centre->second.first += offset.second.first;
	Centre->second.second += offset.second.second;
    
    return *this;
};


// Offset Centre
Shape::BaseShape& Shape::BaseShape::operator -=( const Vector3& offset )
{    
    Centre->first -= offset.first;
    Centre->second.first -= offset.second.first;
	Centre->second.second -= offset.second.second;
    
    return *this;
};


// Set Colour
Shape::BaseShape& Shape::BaseShape::operator= (const Vector4& colour)
{
    if( Colour == NULL )
        Colour = new Vector4( *new std::pair<double,double>(0,0), *new std::pair<double,double>(0,0) );
    
    Colour->first.first = colour.first.first;
    Colour->first.second = colour.first.second;
    Colour->second.first = colour.second.first;
    Colour->second.second = colour.second.second;
    
    return *this;
};


// Offset Colour
Shape::BaseShape& Shape::BaseShape::operator+= (const Vector4& colour)
{
    if( Colour == NULL )
        Colour = new Vector4( *new std::pair<double,double>(0,0), *new std::pair<double,double>(0,0) );
    
    Colour->first.first = colour.first.first;
    Colour->first.second = colour.first.second;
    Colour->second.first = colour.second.first;
    Colour->second.second = colour.second.second;
    
    return *this;
};


// Offset Colour
Shape::BaseShape& Shape::BaseShape::operator-= (const Vector4& colour)
{
    if( Colour == NULL )
        Colour = new Vector4( *new std::pair<double,double>(0,0), *new std::pair<double,double>(0,0) );
    
    Colour->first.first = colour.first.first;
    Colour->first.second = colour.first.second;
    Colour->second.first = colour.second.first;
    Colour->second.second = colour.second.second;
    
    return *this;
};



// Set Angle Magnitude
Shape::BaseShape& Shape::BaseShape::operator =(const float& angleMag)
{
    Angle = angleMag;
    
    return *this;
};


// Offset Angle Magnitude
Shape::BaseShape& Shape::BaseShape::operator +=(const float& angleMag)
{
    Angle += angleMag;
    
    return *this;
};


// Offset Angle Magnitude
Shape::BaseShape& Shape::BaseShape::operator -=(const float& angleMag)
{
    Angle -= angleMag;
    
    return *this;
};



// ----------------------------- Test Code --------------------------

/*
BaseShape* temp1 = new BaseShape();
std::cout << "temp1: ";
temp1->printCentre();

BaseShape* temp2 = new BaseShape( *new Vector(2,2) );
std::cout << "temp2: ";
temp2->printCentre();

temp1 = new BaseShape( *temp2 );
std::cout << "temp1: ";
temp1->printCentre();

temp1 = new BaseShape();
std::cout << "temp1: ";
temp1 = temp2;
temp1->printCentre();

temp2 = new BaseShape( *new Vector(3,3) );
std::cout << "temp1: ";
temp1 = temp2;
temp1->printCentre();
*/