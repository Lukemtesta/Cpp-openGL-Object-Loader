//
//  Indexing.h
//  Money Object Loader
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

#include "Rectangle.h"
#include "Conversion.h"

#include <map>
#include <cmath>
#include <list>

#define PI 3.141592654


namespace ShapeMap
{
    class Indexing
    {
        public:
                    inline Indexing();
                    inline Indexing(Shape::BaseShape& points);
                    inline Indexing(std::vector<Shape::Vector3>& points);
        
                    virtual ~Indexing();
        
                    Indexing& operator +=(Shape::BaseShape& shape);
        
                    inline GLfloat* getArray();
                    int* getLineIndex(Shape::BaseShape& shape);
					int* getLineIndex( std::vector<Shape::Vector3>& points, std::vector<GLushort>& Indices );
                    int* getPolygonIndex(Shape::BaseShape& Shape);
					int* getPolygonIndex( std::vector<Shape::Vector3>& points, std::vector<GLushort>& Indices );
                    inline int getSize();

        private:
                    Indexing(const Indexing& copy);
        
                    std::map<std::string, int> XYZ;
                    std::vector<GLfloat> Data;
    };
    
    Shape::Polygon* NormalizedPrimitive(int Sides);
	int* NormalizedAxis( Indexing& database );
    
};




// ------------- Inline Declarations ---------------


ShapeMap::Indexing::Indexing() {};


// Return Number of Vertices Stored in VertexMap
int ShapeMap::Indexing::getSize()
{
    return (int)Data.size();
};


// Return Array for DrawElements or DrawArray
GLfloat* ShapeMap::Indexing::getArray()
{
    std::cout << "Number of Stored Vertices: " << Data.size()/3 << std::endl;
    
    GLfloat* temp = new GLfloat[Data.size()];
    
    for (int i = 0; i < Data.size(); i++ )
        temp[i] = Data[i];
    
    return temp;
};



// Copy points from generated shape class
ShapeMap::Indexing::Indexing(Shape::BaseShape& points)
{
    this->operator += (points);
};


// Copy list of points
ShapeMap::Indexing::Indexing(std::vector<Shape::Vector3>& points)
{
    Shape::BaseShape& ptr = *new Shape::Polygon( *new Shape::Vector3( 0, Shape::Vector(0,0) ), points );
    this->operator += (ptr);
}
