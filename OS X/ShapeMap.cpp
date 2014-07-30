//
//  Indexing.cpp
//  Money Object Loader
//
//  Created by Luke Testa on 06/02/2014.
//  Copyright (c) 2014 Luke Testa. All rights reserved.
//

#include "ShapeMap.h"

// ---------------------- Destructors --------------------------


ShapeMap::Indexing::~Indexing() { std::cout << "DELETING [INDEXING]" << std::endl; }


// --------------------- Indexing Functions --------------------



// Return list of Index for DrawElements using GL_LINES
int* ShapeMap::Indexing::getLineIndex(Shape::BaseShape& shape)
{
    std::map<std::string, int>::const_iterator itXYZ;
    
    GLfloat* temp = Conversion::VectorArrayToGLfloat(shape.getVertices(), shape.size() );
    int* indexList = new int[ (shape.size()*2) + 1];
    
    int index = 0;
    for( int i = 0; i < shape.size(); i++ )
    {
        std::string key = Conversion::convertTostring( temp[i*3]) + Conversion::convertTostring( temp[i*3+1] ) +Conversion::convertTostring( temp[i*3+2]);
        
        itXYZ = XYZ.find(key);
        
        // Is point in map? Get index
        if ( itXYZ != XYZ.end() )
        {
            // Store current point twice
            if( i > 0 )
            {
                indexList[index++] = XYZ[key];
                indexList[index++] = XYZ[key];
            }
            else
                indexList[index++] = XYZ[key];
            
        }
        
        // Point Already Exists. Do Not Store Point
        else
        {
            std::cerr << "Point is not in map" << std::endl;
            std::cout << "key: " << key << std::endl;
            return NULL;
        }
    }
    
    indexList[index++] = indexList[0];
    
    // As \0 is null and 0 in C++, using value 122 as end of dynamic array
    indexList[index] = NULL;
        
    return indexList;
};


int* ShapeMap::Indexing::getLineIndex( std::vector<Shape::Vector3>& points, std::vector<GLushort>& Indices )
{
	std::vector<Shape::Vector3> VertexList;

	for( int i = 0; i < Indices.size(); i++)
		VertexList.push_back( points[ Indices[i] ] );

	Shape::BaseShape* MonkeyMesh = new Shape::Polygon( VertexList );
	return getLineIndex( *MonkeyMesh );
}


// Return list of Index for DrawElements using GL_POLYGONS
int* ShapeMap::Indexing::getPolygonIndex(Shape::BaseShape& shape)
{
    std::map<std::string, int>::const_iterator itXYZ;
    
    GLfloat* temp = Conversion::VectorArrayToGLfloat(shape.getVertices(), shape.size() );
    int* indexList = new int[ shape.size() + 2];
	//int* indexList = new int[ shape.size() + 1 ];
    
    int index = 0;
    for(int i = 0; i < shape.size(); i++ )
    {
        std::string key = Conversion::convertTostring( temp[(i*3)]) + Conversion::convertTostring( temp[(i*3)+1] ) +Conversion::convertTostring( temp[(i*3)+2]);
        
        itXYZ = XYZ.find(key);
        
        // Is point in map? Get index
        if ( itXYZ != XYZ.end() )
                indexList[index++] = XYZ[key];

        // Point Already Exists. Do Not Store Point
        else
        {
            std::cerr << "Point is not in map" << std::endl;
            std::cout << "key: " << key << std::endl;
            return NULL;
        }
    }

	std::cout << "number of vertices: " << index << std::endl;
    
    // As \0 is null and 0 in C++, using value 122 as end of dynamic array
    indexList[index++] = indexList[0];
    indexList[index] = NULL;
    
    return indexList;
};




// Retrieve vertex order for rendering
int* ShapeMap::Indexing::getPolygonIndex( std::vector<Shape::Vector3>& points, std::vector<GLushort>& Indices )
{
	std::vector<Shape::Vector3> VertexList;

	for( int i = 0; i < Indices.size(); i++)
		VertexList.push_back( points[ Indices[i] ] );

	Shape::BaseShape* MonkeyMesh = new Shape::Polygon( VertexList );
	return getPolygonIndex( *MonkeyMesh );
}





// append input Shape's points to map if already dont exist in map
ShapeMap::Indexing& ShapeMap::Indexing::operator += (Shape::BaseShape& shape)
{
    GLfloat* temp = Conversion::VectorArrayToGLfloat(shape.getVertices(), shape.size() );
    std::string key;

	// Start counting from 1
	Data.push_back(NULL); Data.push_back(NULL); Data.push_back(NULL);
    
    for ( int i = 0; i < shape.size() ; i++ )
    {
        std::map<std::string, int>::const_iterator itXYZ;
        
        // Combined String X,Y,Z
        key = Conversion::convertTostring(temp[(i*3)]) + Conversion::convertTostring(temp[(i*3)+1]) + Conversion::convertTostring(temp[(i*3)+2]);
        itXYZ = XYZ.find( key );
        
        // Is point in map? If not store point
        if ( itXYZ == XYZ.end() )
        {
            int size = (int) ( (Data.size() + 1)/3 );
            
            XYZ.insert ( std::pair<std::string, GLfloat>( Conversion::convertTostring(temp[(i*3)]), size) );
            XYZ[key] = size;
            
            for( int z = 0; z < 3; z++ )
                Data.push_back(temp[(i*3)+z]);
        }
        // Point Already Exists. Do Not Store Point
    }
    
    return *this;
};







// ------------------------- Standalone Methods ----------------------



// Generates Normalized Equilateral primitive and returns Polygon to point
Shape::Polygon* ShapeMap::NormalizedPrimitive(int Sides)
{
    std::vector<Shape::Vector3>* points = new std::vector<Shape::Vector3>();
    
    // Change around unit circle
    double separation = PI / Sides, interval = 2*PI / Sides;
    
    // Ensure even number of vertices
    if ( (Sides%2) != 0 )
    {
        std::cerr << "Cannot Generate Non Even Vertice Shape" << std::endl;
        return NULL;
    }
    
    // Generate Shapes
    for (int i = 1; i <= Sides; i++ )
    {
        double index = separation + ( interval*(i-1) );
        
        // on unit circle, all x values must be /2
        points->push_back( *new Shape::Vector3( cos(index), Shape::Vector( sin(index), 0 ) ) );
    }
    
    // Store points in shape object. Then query the number of shapes in list
    Shape::Polygon* temp = new Shape::Polygon( *new Shape::Vector3( 0, Shape::Vector(0,0) ), *points );
    
    return temp;
};


int* NormalizedAxis( ShapeMap::Indexing& database )
{
	std::vector<Shape::Vector3> Axis;

	Axis.push_back( Shape::Vector3( 0, Shape::Vector(0,0) ) );
	Axis.push_back( Shape::Vector3( 1, Shape::Vector(0,0) ) );
	Axis.push_back( Shape::Vector3( 0, Shape::Vector(1,0) ) );
	Axis.push_back( Shape::Vector3( 0, Shape::Vector(0,1) ) );

	Shape::BaseShape* axis = new Shape::Polygon( Shape::Vector3( 0, Shape::Vector(0,0) ), Axis );
	database += *axis;

	int indexes[6] = { 1, 2, 1, 3, 1, 4 };

	return indexes;
}
