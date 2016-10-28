/***************************************************************************
*  FILE: rocks.hpp
*  AUTHOR: Connor Beardsmore - 15504319
*  UNIT: CG200 Assignment S2 - 2016
*  PURPOSE: Header file for rocks.cpp
*  LAST MOD: 12/10/16
*  REQUIRES: OpenGL.h, glut.h
***************************************************************************/

// OpenGL HEADER FILES, DEPENDING ON OS

#ifdef __APPLE__
    #include <OpenGL/OpenGL.h>
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

//---------------------------------------------------------------------------
//FUNCTION PROTOTYPES

void drawFlag(double,double,double,int,GLuint);

//---------------------------------------------------------------------------
