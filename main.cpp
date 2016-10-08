/***************************************************************************
*  FILE: main.cpp
*  AUTHOR: Connor Beardsmore - 15504319
*  UNIT: CG200 Assignment S2 - 2016
*  PURPOSE: OpenGL
*  LAST MOD: 19/09/16
*  REQUIRES: NONE
***************************************************************************/

#include "main.hpp"
using namespace std;

float angle = 30.0f;
float cameraAngle = 0.0f;

//---------------------------------------------------------------------------
// FUNCTION: input()
// IMPORT: key (char), mouseX (int), mouseY (int)
// PURPOSE: Callback when key pressed

//Called when a key is pressed
void input(unsigned char key, int mouseX, int mouseY)
{
	switch (key)
    {
        // Exit
		case 'U':
        case 'u':
			exit(0);
        // Zoom in 0.1
        case 'Z':   break;
        //Zoom out 0.1
        case 'z':   break;
        // X rotation
        case 'X':
        case 'x':   break;
        // Y rotation
        case 'Y':
        case 'y':   break;
        // Animation
        case 'A':
        case 'a':   break;
        // Faster
        case 'F':
        case 'f':   break;
        // Slower
        case 'S':
        case 's':   break;
        // Pause
        case 'T':
        case 't':   break;
        // Resume
        case 'C':
        case 'c':   break;
        // Flat shaded polygonization
        case 'p':   break;
        // Smooth shaded polygonization
        case 'P':   break;
	}
}

//---------------------------------------------------------------------------
// FUNCTION: init()
// PURPOSE: Initialisation of rendering

void init()
{
    // Background color and enable depth testing
    glClearColor(0.7f, 0.9f, 1.0f, 1.0f);
	glEnable( GL_DEPTH_TEST );
}

//---------------------------------------------------------------------------
// FUNCTION: resize()
// IMPORT: width (int), height (int)

void resize(int width, int height)
{
	// Tell OpenGL to convert from coordinates to pixel values
	glViewport(0, 0, width, height);
    // Switch to setting camera perspective
	glMatrixMode(GL_PROJECTION);

    // Reset camera
	glLoadIdentity(); //Reset the camera

    // Angle, w/h ratio, Near Z clipping, Far Z clipping
    double ratio = (double)width / (double)height;
	gluPerspective( 45.0, ratio , 1.0, 200.0 );
}

//---------------------------------------------------------------------------

//Draws the 3D scene
void display()
{
	// Clear last draw ingormation
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Switch to drawing perspective
	glMatrixMode(GL_MODELVIEW);
    // Reset drawing perspective
	glLoadIdentity();
    glRotatef(-cameraAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -5.0f);

	glPushMatrix();
	glTranslatef(0.0f, -1.0f, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);

	glBegin(GL_QUADS);

	//Trapezoid
	glColor3f(0.5f, 0.0f, 0.8f);
	glVertex3f(-0.7f, -0.5f, 0.0f);
	glColor3f(0.0f, 0.9f, 0.0f);
	glVertex3f(0.7f, -0.5f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.4f, 0.5f, 0.0f);
	glColor3f(0.0f, 0.65f, 0.65f);
	glVertex3f(-0.4f, 0.5f, 0.0f);

	glEnd();

	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.0f, 1.0f, 0.0f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glScalef(0.7f, 0.7f, 0.7f);

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.75f, 0.0f);

	//Pentagon
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);

	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);

	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);

	glEnd();

	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.0f, 1.0f, 0.0f);
	glRotatef(angle, 1.0f, 2.0f, 3.0f);

	glBegin(GL_TRIANGLES);

	//Triangle
	glColor3f(1.0f, 0.7f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);

	glEnd();

	glPopMatrix();
    // Send 3D scene to screen
	glutSwapBuffers();
}

//---------------------------------------------------------------------------
// FUNCTION: idle()
// PURPOSE: Callback function run when system has spare resources

void idle(void)
{
	glutPostRedisplay();
}

//---------------------------------------------------------------------------
// FUNCTION: main()
// IMPORT: argc (int), argv (char**)
// PURPOSE: Does cool things

int main(int argc, char** argv)
{
	//Initialize GLUT and Window
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);

	//Create the window
	glutCreateWindow( "Under The Sea - CG Assignment 2" );
    // Initialise rendering
	init();

	//Set callback functions
	glutDisplayFunc( display );
	glutKeyboardFunc( input );
	glutReshapeFunc( resize );
    glutIdleFunc( idle );

    // Start Main Loop (never returns)
	glutMainLoop();
	return 0;
}

//---------------------------------------------------------------------------
