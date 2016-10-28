/***************************************************************************
*  FILE: bubbles
*  AUTHOR: Connor Beardsmore - 15504319
*  UNIT: CG200 Assignment S2 - 2016
*  PURPOSE: Header file for bubbles.cpp
*  LAST MOD: 07/10/16
*  REQUIRES: OpenGL.h, glut.h
***************************************************************************/

// OpenGL HEADER FILES, DEPENDING ON OS

#ifdef __APPLE__
    #include <OpenGL/OpenGL.h>
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "colors.hpp"

//---------------------------------------------------------------------------
//FUNCTION PROTOTYPES

void drawBubbles(double,double,double,int);

//---------------------------------------------------------------------------
