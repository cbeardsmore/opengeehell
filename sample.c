/***************************************************************************
*  FILE: sample.c
*  AUTHOR: Connor Beardsmore - 15504319
*  UNIT: CG200 Assignment S2 - 2016
*  PURPOSE: Matrix multiplication using multiprocessing and shared memory
*  LAST MOD: 19/09/16
*  REQUIRES: stdio.h, math.h, stdlib.h, OpenGL, GLUT
***************************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include "sample.h"

//---------------------------------------------------------------------------

// GLOBAL VARIABLES
// scale:	a factor to scale the viewed cube by
// alpha:	number of degrees by which the cube is rotated
// beta:	number of degrees by which the cube is tilted
// inc:	amount to increase alpha for every frame of animation

float scale, alpha, beta;
int inc;

//---------------------------------------------------------------------------
// FUNCTION: main()
// IMPORT: argc (int), argv (char**)
// EXPORT: error (int)
// PURPOSE: Does cool things

int main(int argc, char **argv)
{
	// Initialise GLUT and window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);

	// Create window and initialise window
	glutCreateWindow("CG200 Assignment 2");
	init();

	// Set callback functions
	glutDisplayFunc (display);
	glutReshapeFunc (reshape);
	glutKeyboardFunc(input);
	glutIdleFunc    (idle);

	glutMainLoop();
	return 0;
}

//---------------------------------------------------------------------------
// FUNCTION: init()
// PURPOSE: Initialisation of variables

void init()
{
    // Background color and enable depth testing
	glClearColor((float) 0.3, (float) 0.0, (float) 0.5, (float) 0.0);
	glEnable(GL_DEPTH_TEST);

	// Initial rotation and scale factors
	alpha = -20.0;
	beta  = 20.0;
	scale = 1.0;
	inc = 1;
}

//---------------------------------------------------------------------------
// FUNCTION: draw()
// PURPOSE: Defines objects to draw

void draw()
{
	/* set the colour to red and draw the coordinate
	 * axes. GL_LINES defines segments of straight
	 * lines connecting vertices v1 with v2, v3 with
	 * v4, v5 with v6, etc.  */
    glColor3f((float) 1.0, (float) 0.0, (float) 0.0);
	glBegin(GL_LINES);
		glVertex3f(-(float)(2.0*CUBE_SIZE), (float) 0, (float) 0);
		glVertex3f( (float)(2.0*CUBE_SIZE), (float) 0, (float) 0);
		glVertex3f( (float) 0,-(float)(2.0*CUBE_SIZE), (float) 0);
		glVertex3f( (float) 0, (float)(2.0*CUBE_SIZE), (float) 0);
		glVertex3f( (float) 0, (float) 0,-(float)(2.0*CUBE_SIZE));
		glVertex3f( (float) 0, (float) 0, (float)(2.0*CUBE_SIZE));
	glEnd();

	/* set the colour to green and draw a cube - one
	 * polyline and three segments. GL_LINE_STRIP
	 * defines a polyline connecting vertices v1, v2,
	 * v3,...,vn. It can be done in for {...} as
	 * well.  */
    glColor3f((float) 0.0, (float) 1.0, (float) 0.0);
	glBegin(GL_LINE_STRIP);
		glVertex3f(-(float)CUBE_SIZE, -(float)CUBE_SIZE, -(float)CUBE_SIZE);
		glVertex3f( (float)CUBE_SIZE, -(float)CUBE_SIZE, -(float)CUBE_SIZE);
		glVertex3f( (float)CUBE_SIZE, -(float)CUBE_SIZE,  (float)CUBE_SIZE);
		glVertex3f(-(float)CUBE_SIZE, -(float)CUBE_SIZE,  (float)CUBE_SIZE);
		glVertex3f(-(float)CUBE_SIZE, -(float)CUBE_SIZE, -(float)CUBE_SIZE);
		glVertex3f(-(float)CUBE_SIZE,  (float)CUBE_SIZE, -(float)CUBE_SIZE);
		glVertex3f( (float)CUBE_SIZE,  (float)CUBE_SIZE, -(float)CUBE_SIZE);
		glVertex3f( (float)CUBE_SIZE,  (float)CUBE_SIZE,  (float)CUBE_SIZE);
		glVertex3f(-(float)CUBE_SIZE,  (float)CUBE_SIZE,  (float)CUBE_SIZE);
		glVertex3f(-(float)CUBE_SIZE,  (float)CUBE_SIZE, -(float)CUBE_SIZE);
    glEnd();

	/* GL_LINES defines segments of straight lines
	 * connecting vertices v1 with v2, v3 with v4,
	 * v5 with v6, etc.  */
	glBegin(GL_LINES);
		glVertex3f( (float)CUBE_SIZE, -(float)CUBE_SIZE, -(float)CUBE_SIZE);
		glVertex3f( (float)CUBE_SIZE,  (float)CUBE_SIZE, -(float)CUBE_SIZE);
		glVertex3f( (float)CUBE_SIZE, -(float)CUBE_SIZE,  (float)CUBE_SIZE);
		glVertex3f( (float)CUBE_SIZE,  (float)CUBE_SIZE,  (float)CUBE_SIZE);
		glVertex3f(-(float)CUBE_SIZE, -(float)CUBE_SIZE,  (float)CUBE_SIZE);
		glVertex3f(-(float)CUBE_SIZE,  (float)CUBE_SIZE,  (float)CUBE_SIZE);
	glEnd();
}

//---------------------------------------------------------------------------
// FUNCTION: display()
// PURPOSE: Called by ssytem to draw every next buffer

void display(void)
{
	// Clear buffer of all data
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		// Increase rotation for visualisation effect
		alpha = alpha + (float) inc;

		// Reset rotation value when it reaches 360
		if( alpha  > 360.0 )
        {
			alpha -= 360.0;
        }

        // Translation and rotation transformations
        // Changing scale introduces scaling transformation
		glTranslatef((float) 0.0, (float) 0.0, -(float) (5.0 * CUBE_SIZE));
		glRotatef(beta , (float) 1.0, (float) 0.0, (float) 0.0);
		glRotatef(alpha, (float) 0.0, (float) 1.0, (float) 0.0);
		glScalef(scale, scale, scale);

		draw();

	glPopMatrix();

    // Force scene to draw and swap buffers, smoothes animation
	glFlush();
	glutSwapBuffers();
}

//---------------------------------------------------------------------------
// FUNCTION: reshape()
// IMPORT: width (int), height (int)
// PURPOSE: Projection transformation defined
//          Perspective -> use glFrustum()
//          Orthographic -> use glOrtho()

void reshape(int width, int height)
{
	glViewport(0, 0, (GLsizei) width, (GLsizei) height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/*glOrtho(-(float) 2.0*CUBE_SIZE, (float) 2.0*CUBE_SIZE, -(float) 2.0*CUBE_SIZE,
	           (float) 2.0*CUBE_SIZE, (float) 0.0*CUBE_SIZE,  (float)10.0*CUBE_SIZE);*/
	glFrustum(-(float) 2.0*CUBE_SIZE, (float) 2.0*CUBE_SIZE, -(float) 2.0*CUBE_SIZE,
			   (float) 2.0*CUBE_SIZE, (float) 3.0*CUBE_SIZE,  (float)40.0*CUBE_SIZE);

	glMatrixMode(GL_MODELVIEW);
}

//---------------------------------------------------------------------------
// FUNCTION: input()
// IMPORT: key (char), x (int), y (int)
// PURPOSE: Callback when key pressed

void input(char key, int x, int y)
{
	if ( key == 's' )
    {
        // If rotation has stopped then restart, otherwise stop
		if ( inc == 1 )
			inc = 0;
		else
			inc = 1;
    }
}

//---------------------------------------------------------------------------
// FUNCTION: idle()
// PURPOSE: Callback function run when system has spare resources

void idle(void)
{
	glutPostRedisplay();
}

//---------------------------------------------------------------------------
