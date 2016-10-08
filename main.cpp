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
GLuint textureID;


//---------------------------------------------------------------------------
// NAME: loadTexture()
// IMPORT: image (Image*)
// EXPORT: textureID (GLuint)
// PURPOSE: Make image into texture and return the ID

GLuint loadTexture( Image* image )
{
	GLuint textureId;
    // Make room for texture
	glGenTextures(1, &textureId);
    // Bind given texture to edit it
	glBindTexture(GL_TEXTURE_2D, textureId);
	//Map image to texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,image->width, image->height,
				           0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

	return textureId;
}

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
        case 'p':   glShadeModel( GL_FLAT );
                    break;
        // Smooth shaded polygonization
        case 'P':   glShadeModel( GL_SMOOTH );
                    break;
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
    glEnable( GL_COLOR_MATERIAL );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable( GL_LIGHT1 );
    glEnable( GL_NORMALIZE );
    glShadeModel( GL_SMOOTH );

    Image* image = loadBMP( "vtr.bmp" );
    textureID = loadTexture( image );
    delete image;
}

//---------------------------------------------------------------------------
// FUNCTION: resize()
// IMPORT: width (int), height (int)

void resize(int width, int height)
{
	// Tell OpenGL to convert from coordinates to pixel values
	glViewport(0, 0, width, height);
    // Switch to setting camera perspective
	glMatrixMode( GL_PROJECTION );

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glTranslatef(0.0f, 1.0f, -6.0f);

	GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat directedLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat directedLightPos[] = {-10.0f, 15.0f, 20.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//Bottom
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0f, 0.2f, 0.2f);
	glBegin(GL_QUADS);

	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.5f, -2.5f, 2.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.5f, -2.5f, 2.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.5f, -2.5f, -2.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.5f, -2.5f, -2.5f);

	glEnd();

	//Back
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.5f, -2.5f, -2.5f);
	glTexCoord2f(5.0f, 5.0f);
	glVertex3f(0.0f, 2.5f, -2.5f);
	glTexCoord2f(10.0f, 0.0f);
	glVertex3f(2.5f, -2.5f, -2.5f);

	glEnd();

	//Left
	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0f, 0.7f, 0.3f);
	glBegin(GL_QUADS);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-2.5f, -2.5f, 2.5f);
	glVertex3f(-2.5f, -2.5f, -2.5f);
	glVertex3f(-2.5f, 2.5f, -2.5f);
	glVertex3f(-2.5f, 2.5f, 2.5f);

	glEnd();

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
