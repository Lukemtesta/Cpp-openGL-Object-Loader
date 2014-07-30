//
//  Object Loader.cpp
//  Object Loader
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


#include "Object Loader.h"



// -------------- Constructors Overloading ------------------

objectLoader::objectLoader(){};

objectLoader::objectLoader(std::string filePath) : objectFile(filePath)
{
        //Create input file stream to read .obj file
        std::ifstream in(filePath, std::ios::in);

        std::cerr << "Loading Object: " << filePath << std::endl;
    
        // check if object file exists in current director
        if (!in)
        {
            std::cerr << "Cannot open " << filePath << std::endl;
//            std::cerr << "Current directory: " << getcwd(NULL,0) << std::endl;
            exit(1);
        }
    
        std::cerr << "Successfully Loaded Object: " << filePath << std::endl;
};



// ----------- Destructors ----------------

objectLoader::~objectLoader() {};



// -*******************---------- Members ----------******************--------

// ----------- loadOBJ() Overloading ----------


// Loads .obj file assuming openGL co-ordinate XYZ and no pre-computed mesh normals
//
// Inputs filename, and reference to variable outputs: vertor list, normal list, and buffer element list in
//                                                      ascending render order.
//



void objectLoader::loadOBJ()
{
    objectLoader::loadOBJ(objectFile,vertices,normals,elements);
}



void objectLoader::loadOBJ(std::string filename)
{
    objectLoader::loadOBJ(filename,vertices,normals,elements);
}



void objectLoader::loadOBJ(std::string filename, std::vector<glm::vec4> &vertices, std::vector<glm::vec3> &normals, std::vector<GLushort> &elements)
{
    
    std::cerr << "Loading Object: " << filename << std::endl;
    
    //Create input file stream to read .obj file
    std::ifstream in(filename, std::ios::in);
    
    // check if object file exists in current director
    if (!in)
    {
        std::cerr << "Cannot open " << filename << std::endl;
//        std::cerr << "Current directory: " << getcwd(NULL,0) << std::endl;
        
        exit(1);
    }
    
    std::cerr << "Successfully Loaded Object: " << filename << std::endl;
    
    std::string line;
    
    // read each object file line
    //
    //
    // object files are in the format:
    /*
     
        structured in lines
        lines starting with # are comments
        o introduces a new object
        v introduces a vertex
        vn introduces a normal
        f introduces a face, using vertex indices referring to order of vector storage, starting at 1
     
    */
    
    std::cout << "Begin Storing Mesh" << std::endl;
    
    while (getline(in, line))
    {
        
        std::cout << " . " << std::endl;
        
        // Case: 4D vector
        if (line.substr(0,2) == "v ")
        {
            // Append "v " marking
            std::istringstream s(line.substr(2));
            
            // store next three floats as X,Y,Z, Angle co-ordinates accordingly (Axis-angle format)
            glm::vec4 v;
            s >> v.x; s >> v.y; s >> v.z; v.w = 1.0f;
            
            // Dynamically add new item onto end of existing vector list
            vertices.push_back(v);
        }
        
        // Case: Faces
        else if (line.substr(0,2) == "f ")
        {
            // Append "v " marking
            std::istringstream s(line.substr(2));
            
            // Store Faces as 16-integers in order of rendering.
            GLushort a,b,c;
            
            // decrement face as blender counts from 1 and C++ from 0.
            s >> a; s >> b; s >> c;
            a--; b--; c--;
            
            // Each face corresponds to three vectors. Store vector numbers in a list of
            // openGL elements. Elements are rendered in order.
            
            elements.push_back(a);
            elements.push_back(b);
            elements.push_back(c);
        }
    }
    
    std::cout << "Done Loading Mesh" << std::endl;
    
    
    // Case: Mesh Computation
    
    // Generate normals for material and light rendering
    
    // Scale normal list size to vector and to contain 3D vectors representing each vertex normal.
    normals.resize(vertices.size(), glm::vec3(0.0, 0.0, 0.0));
    
    
    // For each /\ face, compute normal of face based on the element vertices for later shading models.
    /*for (int i = 0; i < elements.size(); i+=3)
    {
        GLushort ia = elements[i];
        GLushort ib = elements[i+1];
        GLushort ic = elements[i+2];
        
        glm::vec3 normal = glm::normalize(glm::cross(
                                                     glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
                                                     glm::vec3(vertices[ic]) - glm::vec3(vertices[ia])));
        
        normals[ia] = normals[ib] = normals[ic] = normal;
    }*/

}

