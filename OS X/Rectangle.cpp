//
//  Rectangle.cpp
//  Cpp_Revision
//
//  Created by Luke Testa on 06/01/2014.
//  Copyright (c) 2014 Luke Testa. All rights reserved.
//

#include "Rectangle.h"


//------------------------------------------ Constructors -------------------------------------


// Explicit Default Constructor
Shape::Rectangle::Rectangle() : Polygon(), width(0), height(0) {};

// Copy Constructor
Shape::Rectangle::Rectangle( const Rectangle& Shape ) : Polygon ( (Polygon&) Shape ), width( Shape.width ), height ( Shape.height ) {};


Shape::Rectangle:: Rectangle( const Vector3& pt, std::vector<Vector3>& Vertices ) : Polygon ( pt, Vertices )
{
    width = Vertices[0].first - Vertices[1].first;
    height = Vertices[1].second.first - Vertices[3].second.first;
};


Shape::Rectangle::Rectangle( const Vector3 pt, const double w, const double h) : Polygon(), height(h), width(w)
{
    std::vector<Vector3> Vertices;
    
    Vertices.push_back( *new Vector3( pt.first - (width/2), Vector( pt.second.first - (height/2), 0 ) ) );
    Vertices.push_back( *new Vector3( pt.first + (width/2), Vector( pt.second.first - (height/2), 0 )  ) );
    Vertices.push_back( *new Vector3( pt.first - (width/2), Vector( pt.second.first + (height/2), 0 )  ) );
    Vertices.push_back( *new Vector3( pt.first + (width/2), Vector( pt.second.first + (height/2), 0 )  ) );
    
    (Polygon&) *this = Vertices;    
};



// ---------------------------------------- Destructors -----------------------------------------


// Explicit Destructor
Shape::Rectangle::~Rectangle() { std::cout << "Deleting [RECTANGLE]" << std::endl; };



// ---------------------------------------- Overload Operators ----------------------------------


// Non-Exception Safe Deep Copy
Shape::Rectangle& Shape::Rectangle::operator =( const Rectangle& Shape )
{
    if ( !isEqual( *this, (Rectangle&) Shape ) )
    {
        this->width = Shape.width;
        this->height = Shape.height;
    
        // Execute Polymorphic Assignment Operator Member with Sliced Members
        (Polygon&) *this = (Polygon&) Shape;
    }
    
    return *this;
};





