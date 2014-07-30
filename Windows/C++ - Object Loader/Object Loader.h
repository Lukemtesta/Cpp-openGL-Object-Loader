//
//  Object Loader.h
//  Money Object Loader
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

#ifndef Object_Loader__Object_Loader__
#define Object_Loader__Object_Loader__


#ifdef WIN32
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#else
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
//#include <unistd.h>

// glm is openGL Mathematics library
#include "../Debug/libs/glm.hpp"



#endif /* defined(__Object_Loader__Object_Loader__) */

class objectLoader
{
    private:
    
    protected:
    
        std::string objectFile;
    
    public:
    
        // ------------- Variables ------------------
    
        std::vector<glm::vec4> vertices;
        std::vector<glm::vec3> normals;
        std::vector<GLushort> elements;
    
        // ------------- Members -------------------
    
        objectLoader();
        objectLoader(std::string fileName);
    
        ~objectLoader();
    
    void loadOBJ();
    
    void loadOBJ(std::string filename);
    
    void loadOBJ(std::string filename, std::vector<glm::vec4> &vertices, std::vector<glm::vec3> &normals, std::vector<GLushort> &elements);
    
};