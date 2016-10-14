/***************************************************************************
*  FILE: main.hpp
*  AUTHOR: Connor Beardsmore - 15504319
*  UNIT: CG200 Assignment S2 - 2016
*  PURPOSE: Function prototypes for main.h
*  LAST MOD: 10/10/16
*  REQUIRES: iostream, stdlib.h, math.h, imageloader.hpp, stdbool.h,
*            floor.hpp, axis.hpp
***************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "imageloader.hpp"
#include "stdbool.h"
#include "floor.hpp"
#include "axis.hpp"
#include "anchor.hpp"
#include "rocks.hpp"
#include "teapot.hpp"
#include "flag.hpp"

//---------------------------------------------------------------------------
// OpenGL HEADER FILES, DEPENDING ON OS

#ifdef __APPLE__
    #include <OpenGL/OpenGL.h>
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

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

//ANIMATION + ROTATIONS
GLfloat zoom;           // Zoom level
GLfloat xAngle;         // X rotation angle
GLfloat yAngle;         // Y rotation angle
GLfloat speed;          // Speed of animation
GLfloat teapotRise;
GLfloat flagFall;
GLuint detail;

//TEXTURE IDS
GLuint floorTexture;
GLuint anchorTexture;

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
