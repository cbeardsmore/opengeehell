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
#include "stdbool.h"
#include "floor.hpp"
#include "axis.hpp"

//---------------------------------------------------------------------------
//CONSTANTS

#define ANGLE_INCREMENT 0.5
#define ZOOM_INCREMENT 0.1
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600

//---------------------------------------------------------------------------
//GLOBAL VARIABLES

float angle;
float cameraAngle;
float BOX_SIZE;
bool paused;
bool xRot;
bool yRot;

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
void input(unsigned char, int, int);
void init();
void GLprint(char*, float, float);
void printControls();
void reset();
void resize(int, int);
void display();
void draw();
void idle(void);

//---------------------------------------------------------------------------
