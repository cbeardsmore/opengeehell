/***************************************************************************
*  FILE: main.hpp
*  AUTHOR: Connor Beardsmore - 15504319
*  UNIT: CG200 Assignment S2 - 2016
*  PURPOSE: Function prototypes for main.h
*  LAST MOD: 07/10/16
*  REQUIRES: NONE
***************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "imageloader.hpp"

//---------------------------------------------------------------------------
// OpenGL HEADER FILES, DEPENDING ON OS

#ifdef __APPLE__
    #include <OpenGL/OpenGL.h>
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

//---------------------------------------------------------------------------
// FUNCTION PROTOTYPES

GLuint loadTexture(Image*);
void init();
void draw();
void handleResize(int, int);
void drawScene();
void reshape(int, int);
void input(unsigned char, int, int);
void idle(void);

//---------------------------------------------------------------------------
