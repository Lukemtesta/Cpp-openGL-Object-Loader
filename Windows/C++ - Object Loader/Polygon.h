//
//  Polygon.h
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
#include <iterator>

namespace Shape
{
		class Polygon : public BaseShape
		{
			public:
					// Constructors & Destructors
					Polygon();
					Polygon( const Polygon& Shape );
					Polygon( std::vector<Vector3>& newVertices );
					Polygon( const Vector3& pt, std::vector<Vector3>& newVertices );
    
					virtual ~Polygon();
    
					// Override Assignment Operator
					Polygon& operator =( const Polygon& Shape );
					Polygon& operator =( const std::vector<Vector3>& newVertices );
    
					Polygon& operator +=( const std::vector<Vector3>& newVertices );
					Polygon& operator *=( double scale );
					Polygon& operator /=( double scale );
    
					// Member Functions
					inline std::vector<Vector3> getVertices();
					inline void print();
    
					//void render();
					inline int size();
					BaseShape* clone();
    
		private:
					// Calculates center of polygon assuming each point has equal mass
					Vector3 averageCenter();
    
					std::vector<Vector3>* Vertices;

	};
}


// -------------------- Inline Members & Abstract Functions ------------------------



std::vector<Shape::Vector3> Shape::Polygon::getVertices()
{
    return *Vertices;
};


// Get size of Polygon
int Shape::Polygon::size()
{
    return (int)Vertices->size();
};



// Print Vertex Information
void Shape::Polygon::print()
{
    if( Vertices == NULL )
    {
        std::cout << "No Stored Vertices" << std::endl;
        return;
    }
    
    if( !Vertices->size() )
    {
        std::cout << "No Stored Vertices" << std::endl;
        return;
    }
    
    std::cout << "Vertices: ";
    
    for ( std::vector<Vector3>::const_iterator it( Vertices->begin() ); it != Vertices->end(); it++ )
        std::cout << "(" << it->first << "," << it->second.first << "," << it->second.second << ") , ";
    
    std::cout << std::endl;
};



// --------------------- Test Code ------------------------


/*
Polygon* plygn1 = new Polygon();
std::cout << "plygn1: ";
plygn1->print();

std::vector<Vector> temp = { *new Vector(0,0), *new Vector(0,1) };

std::cout << "plygn1: ";
plygn1 = new Polygon( *new Vector(3,3), temp );
BaseShape* shape1 = new BaseShape( (BaseShape&) *plygn1 );
plygn1->print();
shape1->print();

std::cout << "plygn2: ";
plygn1 = new Polygon( *new Vector(1,5), temp );
Polygon* plygn2 = new Polygon( *plygn1 );
shape1 = new BaseShape( (BaseShape&) *plygn2 );
plygn2->print();
shape1->print();

std::cout << "plygn2: ";
plygn1 = new Polygon( *new Vector(7,3), temp );
plygn2 = new Polygon();
plygn2 = plygn1;
shape1 = new BaseShape( (BaseShape&) *plygn2 );
plygn2->print();
shape1->print();

std::vector<Vector> temp1 = { *new Vector(25,15), *new Vector(-6,302), *new Vector(8,8) };

*plygn2 += temp1;
shape1 = new BaseShape( (BaseShape&) *plygn2 );
plygn2->print();
shape1->print();

*plygn2 = temp1;
shape1 = new BaseShape( (BaseShape&) *plygn2 );
plygn2->print();
shape1->print();

(BaseShape& ) *plygn2 = *new Vector(1424,142414);
shape1 = new BaseShape( (BaseShape&) *plygn2 );
plygn2->print();
shape1->print();
*/