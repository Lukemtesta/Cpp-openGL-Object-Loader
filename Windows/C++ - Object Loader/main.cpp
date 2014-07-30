//
//  main.cpp
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

/*
 * The program accepts one input argument. This is the full path to the object file (non-normalised vertices).
 *
 * Example: ./main cone.obj
 */

#include "Object Loader.h"
#include "ShapeMap.h"


#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif


#define SCREEN_H 1280
#define SCREEN_W 800
#define MOUSE_SENSITIVITY 2


struct FrenetFrame
{
	Shape::Vector3 CameraPosition;
	Shape::Vector MousePosition;
	Shape::Vector3 WorldRotation;
};


// Global objectModels

FrenetFrame MotionModel;
ShapeMap::Indexing PointDatabase;
std::map< std::string, int* > Dictionary;


/* predefine function names */
void initgl( std::string object );
void display(void);
void keyboard(unsigned char key, int x, int y);
void mouseClick( int button, int state, int x, int y);
void mouseMove( int x, int y );
int* VertexOrder( ShapeMap::Indexing& database, std::string objname, int TYPE );
void RenderText(float x, float y, std::string text);


/* main program - setup window using GLUT */
int main(int argc, char **argv)
{
	if (argc != 2 )
	{
		std::cout << "The correct command line format is: <Program Exe> <Object filepath> " << std::endl;
		return 0;
	}

    /* Initialise GLUT window manger */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    
    glutInitWindowSize(1000, 800);
    glutCreateWindow("Object Loader");
    glClearColor (1.0, 1.0, 1.0, 1.0); /* background colour */
    
    glutDisplayFunc(display);   /* Register a drawing function with GLUT */
    
    initgl( argv[1] );                   /* initialise the opengl */
    
	glutMotionFunc( mouseMove );
	glutMouseFunc( mouseClick );
    glutKeyboardFunc(keyboard);
    glutMainLoop();             /* loop forever & start displaying */
    return  0;
}


/* Initialisation of OpenGL */
void initgl( std::string objectName )
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f*SCREEN_W/SCREEN_H, 0.1f, 100.0f);
    gluLookAt( 0, 4, -12,     0, 0, 0,    0, 1, 0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Load and store objects
	Dictionary["AxisLines"] = VertexOrder( PointDatabase, "axis.obj", 0 );
	Dictionary["ObjectLines"] = VertexOrder( PointDatabase, objectName, 1 );
	Dictionary["ObjectFilled"] = VertexOrder( PointDatabase, objectName, 0 );
	Dictionary["FloorFilled"] = VertexOrder( PointDatabase, "floor.obj", 0 );

	// convert GLfloat to static GLfloat
    static GLfloat* vectorMap( PointDatabase.getArray() );
    
    //Initialize 3D Index VBO
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vectorMap);

    glEnable(GL_DEPTH_TEST);
	glEnable (GL_BLEND); 
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


int* VertexOrder( ShapeMap::Indexing& database, std::string objname, int TYPE )
{
	objectLoader Object(objname);
	Object.loadOBJ();

	// Create shape containing mesh vertex information
	std::vector<Shape::Vector3> pts = Conversion::ConvertGLfloatsToVectorArray( Object.vertices );
	Shape::BaseShape& ObjectMesh = *new Shape::Polygon( *new Shape::Vector3( 0, Shape::Vector(0,0) ), pts );

	// Add mesh vertex information into point database
	database += ObjectMesh;

	// Retrieve mesh vertex order from point database
	if( TYPE == 1 )
		return database.getLineIndex( ObjectMesh.getVertices() , Object.elements );
	else
		return database.getPolygonIndex( ObjectMesh.getVertices() , Object.elements );
}


void mouseMove( int x, int y )
{
	if( MotionModel.MousePosition != Shape::Vector(0,0) )
	{
		MotionModel.WorldRotation.second.first += (MotionModel.MousePosition.first - x)/MOUSE_SENSITIVITY;
		MotionModel.WorldRotation.first += (MotionModel.MousePosition.second - y)/MOUSE_SENSITIVITY;
	}

	MotionModel.MousePosition = Shape::Vector(x,y);
	display();
}

void mouseClick( int button, int state, int x, int y)
{
	if( !(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) )
		MotionModel.MousePosition = Shape::Vector(0,0);
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'q':
			MotionModel.CameraPosition.first += 0.05;
			break;
		case 'w':
			MotionModel.CameraPosition.first -= 0.05;
			break;
		case 'a':
			MotionModel.CameraPosition.second.first += 0.05;
			break;
        case 's':
			MotionModel.CameraPosition.second.first -= 0.05;
			break;
        case 'z':
			MotionModel.CameraPosition.second.second += 0.05;
			break;
        case 'x':
			MotionModel.CameraPosition.second.second -= 0.05;
			break;
        default:
			break;
	}
    
	glutPostRedisplay();
    
}


// Renders text on orthonormal display normalised to [-1 1 -1 1]
void RenderText(float x, float y, std::string text)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -10, 100);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glRasterPos2f(x, y);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)text.c_str() );

	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW); 
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();

	glColor3f(0.0,0.0,0.0);
	glLineWidth(1);

	// ----------------------------------------------------- Render Instruction Text -------------------------------------------------
	RenderText(-0.8,0.7, "Rotate: Left Click Drag. Translate: Q/W, A/S & Z/X.");

	// -------------------------------------------------------- Render Object ------------------------------------------------------
	glPushMatrix();
		glTranslatef( MotionModel.CameraPosition.first, MotionModel.CameraPosition.second.first, MotionModel.CameraPosition.second.second );
		glRotatef( MotionModel.WorldRotation.first, 1, 0, 0 );
		glRotatef( MotionModel.WorldRotation.second.first, 0, 1, 0 );

		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		glDrawElements(GL_LINES, Conversion::sizeDynamicArray( Dictionary["ObjectLines"] ), GL_UNSIGNED_BYTE, Conversion::convertToGLubyte( Dictionary["ObjectLines"] ) );
	glPopMatrix();

	// ------------------------------------------------------ Render Reflective Surface ---------------------------------------------
	glDisable(GL_DEPTH_TEST);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, 1, 0xffffffff);

	// Render Floor in Stencil Buffer with closer depth than reflection
	glDrawElements(GL_TRIANGLES, Conversion::sizeDynamicArray( Dictionary["FloorFilled"] ), GL_UNSIGNED_BYTE, Conversion::convertToGLubyte( Dictionary["FloorFilled"] ) );

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_DEPTH_TEST);

	glStencilFunc(GL_EQUAL, 1, 0xffffffff);  
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glPushMatrix();
		glTranslatef( MotionModel.CameraPosition.first, MotionModel.CameraPosition.second.first, MotionModel.CameraPosition.second.second );
		glTranslatef(0, -4, 0);
		glRotatef( MotionModel.WorldRotation.first, 1, 0, 0 );
		glRotatef( MotionModel.WorldRotation.second.first, 0, 1, 0 );
		glScalef(1, -1, 1);

		glDrawElements(GL_LINES, Conversion::sizeDynamicArray( Dictionary["ObjectLines"] ), GL_UNSIGNED_BYTE, Conversion::convertToGLubyte( Dictionary["ObjectLines"] ) );
	glPopMatrix();

	// ---------------------------------------------------------------- Render Floor -----------------------------------------------------------
	glColor4f(0.7, 0.7, 0.7, 0.25);
	glDrawElements(GL_TRIANGLES, Conversion::sizeDynamicArray( Dictionary["FloorFilled"] ), GL_UNSIGNED_BYTE, Conversion::convertToGLubyte( Dictionary["FloorFilled"] ) );

	glDisable(GL_STENCIL_TEST);

	// ---------------------------------------------------------------- Render Axis --------------------------------------------------------------

	glLineWidth(5);
	glPushMatrix();
		glTranslatef(0, -5.2, 0);
		glRotatef( MotionModel.WorldRotation.first, 1, 0, 0 );
		glRotatef( MotionModel.WorldRotation.second.first, 0, 1, 0 );
		glScalef(0.7,0.7,0.7);

		glColor3f(1,0,0);
		glDrawElements(GL_LINES, Conversion::sizeDynamicArray( Dictionary["AxisLines"] ), GL_UNSIGNED_BYTE, Conversion::convertToGLubyte( Dictionary["AxisLines"] ) );
		glColor3f(0,1,0);
		glRotatef(90,0,0,1);
		glDrawElements(GL_LINES, Conversion::sizeDynamicArray( Dictionary["AxisLines"] ), GL_UNSIGNED_BYTE, Conversion::convertToGLubyte( Dictionary["AxisLines"] ) );
		glColor3f(0,0,1);
		glRotatef(90,0,1,0);
		glDrawElements(GL_LINES, Conversion::sizeDynamicArray( Dictionary["AxisLines"] ), GL_UNSIGNED_BYTE, Conversion::convertToGLubyte( Dictionary["AxisLines"] ) );
	glPopMatrix();

    glFlush();
}






