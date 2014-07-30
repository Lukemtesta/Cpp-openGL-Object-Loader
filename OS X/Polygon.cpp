//
//  Polygon.cpp
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


// ----------------------- Constructors --------------------


// Default constructor
Shape::Polygon::Polygon() : BaseShape(), Vertices(NULL) {};


// Copy Constructor : Deep Copy
Shape::Polygon::Polygon( const Polygon& Shape ) : BaseShape( (BaseShape&) Shape )
{
    Vertices = Shape.Vertices;
};


// Store Vertices using iterators. Stores front -> back
Shape::Polygon::Polygon( std::vector<Vector3>& newVertices) : BaseShape()
{
    Vertices = &newVertices;
	averageCenter();
};


// Store Vertices using iterators. Stores front -> back
Shape::Polygon::Polygon( const Vector3& pt, std::vector<Vector3>& newVertices) : BaseShape(pt)
{
    Vertices = &newVertices;
};


// ------------------------ Destructor ----------------------


Shape::Polygon::~Polygon() { delete Vertices; std::cout << "Deleting [Polygon]" << std::endl; };


// ------------------------ Override Operators --------------


// Deep Copy
Shape::Polygon& Shape::Polygon::operator =( const Polygon& Shape )
{
    Vertices = Shape.Vertices;
    (BaseShape&) *this = (BaseShape&) Shape;

    return *this;
};


// Appends Deep Copy for Exception Safety : Manual Vertices Copy
Shape::Polygon& Shape::Polygon::operator +=( const std::vector<Vector3>& newVertices )
{
    // Create Temp Copy of Dynamic Vector List
    std::vector<Vector3> temp(newVertices);
    
    // set this vector size to minimize insert time
    Vertices->reserve( (temp.size() + Vertices->size())  );
    
    // store temp to this
    for ( std::vector<Vector3>::const_iterator it = temp.begin() ; it != temp.end() ; it++ )
        Vertices->push_back(*it);
    
    // Update Center
    averageCenter();
    
    return *this;
};


// Deep Copy for Exception Safety : Manual Vertices Copy
Shape::Polygon& Shape::Polygon::operator =( const std::vector<Vector3>& newVertices )
{
    if( Vertices != NULL )
        Vertices->clear();
    else
        Vertices = new std::vector<Vector3>;
    
    // set this vector size to minimize insert time
    Vertices->reserve( newVertices.size() );
    
    // store temp to this
    for ( std::vector<Vector3>::const_iterator it = newVertices.begin() ; it != newVertices.end() ; it++ )
        Vertices->push_back(*it);
    
    // Update Center
    averageCenter();
    
    return *this;
};



// Scale All Vertices
Shape::Polygon& Shape::Polygon::operator *=( double scale )
{
    for (std::vector<Vector3>::iterator it(Vertices->begin()); it != Vertices->end(); it++)
    {
        it->first *= scale;
        it->second.first *= scale;
		it->second.second *= scale;
    }
    
    return *this;
};


// Scale All Vertices
Shape::Polygon& Shape::Polygon::operator /=( double scale )
{
    for (std::vector<Vector3>::iterator it(Vertices->begin()); it != Vertices->end(); it++)
    {
        it->first /= scale;
        it->second.first /= scale;
		it->second.second /= scale;
    }
    
    return *this;
};



// ------------------------------ Member Functions -------------------------


// Return clone copy
Shape::BaseShape* Shape::Polygon::clone()
{
    BaseShape* ptr = new Polygon(*this);
    
    return ptr;
};

// Calculate Center of Mass of Polygon assuming equal weighted vertices
Shape::Vector3 Shape::Polygon::averageCenter()
{
    Vector3 Size( 0, Vector(0,0) );
    std::vector<Vector3>::const_iterator it;
    
    for( it = Vertices->begin() ; it != Vertices->end(); it++)
    {
        Size.first += it->first;
        Size.second.first += it->second.first;
		Size.second.second += it->second.second;
    }
    
    Size.first /= Vertices->size();
    Size.second.first /= Vertices->size();
	Size.second.second /= Vertices->size();
    
    BaseShape::operator=(Size);
    
    std::cout << "Average Center [POLYGON]: " << Size.first << "," << Size.second.first << "," << Size.second.second << std::endl;
    
    return Size;
};


