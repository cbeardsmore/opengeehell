/***************************************************************************
*  FILE: sample.h
*  AUTHOR: Connor Beardsmore - 15504319
*  UNIT: CG200 Assignment S2 - 2016
*  PURPOSE: Function prototypes for sample.c
*  LAST MOD: 19/09/16
*  REQUIRES: stdio.h, math.h, stdlib.h, OpenGL, GLUT
***************************************************************************/

// MACROS FOR COMMONLY USED NUMERICAL VALUES
// CUBE_SIZE:		Half the length of the cubes sides
// WINDOW_WIDTH:	The width of the window in pixels
// WINDOW_HEIGHT:	The height of the window in pixels

#define	CUBE_SIZE     1.0
#define WINDOW_WIDTH  400
#define WINDOW_HEIGHT 400

//---------------------------------------------------------------------------
// FUNCTION PROTOTYPES

void init();
void draw();
void display(void);
void reshape(int, int);
void input(char, int, int);
void idle(void);

//---------------------------------------------------------------------------
