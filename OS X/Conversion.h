//
//  Conversion.h
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

#include <iostream>
#include <sstream>

// glm is openGL Mathematics library
#include "../Debug/libs/glm.hpp"


#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif


/*
    Contains:
 
    Generic TypeCast Conversions for openGL
*/

namespace Conversion
{
    template <class DataC> std::string convertTostring(DataC number);
    
    // Valid for only arrays with access operator
    template <class DataC> GLfloat* VectorArrayToGLfloat(const std::vector<DataC>& input, int size );

	// Find end of Dynamic array out of class. I.e. Ends with 122 due to 0 = null in C++
	template<class DataC> int sizeDynamicArray(DataC* arr);

	// Convert Array to static GLubyte*
	template<class DataC> static GLubyte* convertToGLubyte(DataC* arr);

	// Convert glm or glfloats to an array of points
	template<class DataC> std::vector<Shape::Vector3> ConvertGLfloatsToVectorArray( std::vector<DataC> data );
};



// -------------------------- Template Declarations -------------------------


// Convert glm or glfloats to an array of points
template<class DataC> std::vector<Shape::Vector3> Conversion::ConvertGLfloatsToVectorArray( std::vector<DataC> data )
{
	std::vector<Shape::Vector3> pts;

	if ( sizeof(DataC) >= sizeof(float)*3 )
	{
		for(int i = 0; i < data.size(); i++)
			pts.push_back( Shape::Vector3( data[i][0], Shape::Vector(data[i][1], data[i][2]) ) );
	}

	return pts;
}


// Converts value to string
template<class DataC> std::string Conversion::convertTostring(DataC number)
{
    std::stringstream ss;//create a stringstream
    ss << number;//add number to the stream
    return ss.str();//return a string with the contents of the stream
};



template <class DataC> GLfloat* Conversion::VectorArrayToGLfloat(const std::vector<DataC>& input, int size )
{
    GLfloat* output = new GLfloat[size*3];
    
    int j = 0;
    for (int i = 0; i < size; i ++ )
    {
        output[j++] = input[i].first;
        output[j++] = input[i].second.first;
        output[j++] = input[i].second.second;
    }
    
    return output;
};


// Find end of Dynamic array out of class. I.e. Ends with 122 due to 0 = null in C++
template<class DataC> int Conversion::sizeDynamicArray(DataC* arr)
{
    int count = 0;
    while( arr[count] != NULL )
    {
        count++;
    };
    
    return --count;
};


// Convert Array to static GLubyte*
template<class DataC> static GLubyte* Conversion::convertToGLubyte(DataC* arr)
{
    int size = sizeDynamicArray(arr);
    
    static GLubyte* temp = new GLubyte[size];
    
    for( int i = 0; i < size; i++ )
        temp[i] = static_cast<GLubyte>( arr[i] );
    
    return temp;
};
