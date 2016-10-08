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
#define	CUBE_SIZE 20.0
#define zoomIncrement 0.1

float angle = 30.0f;
float cameraAngle = 0.0f;
GLuint textureID;
const float BOX_SIZE = 7.0f;
int paused = 1;

GLfloat zoom = zoomIncrement;
GLfloat xRot;
GLfloat yRot;
GLfloat xAngle;
GLfloat yAngle;
GLfloat speed;

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
		case 'Q':
        case 'q':
			exit(0);
        // Zoom in 0.1
        case 'Z':
            if (zoom < 3.0f)
    			zoom += zoomIncrement;
            break;
        //Zoom out 0.1
        case 'z':
            if (zoom > 0.2f)
                zoom -= zoomIncrement;
            break;
        // X rotation
        case 'X':
        case 'x':
            xRot = !xRot;
            break;
        // Y rotation
        case 'Y':
        case 'y':
            yRot = !yRot;
            break;
        // Animation
        case 'A':
        case 'a':
            paused = 0;
            if ( speed < 0.01 )
                speed += 0.01;
        // Faster
        case 'F':
        case 'f':
            if ( speed < 1 )
                speed += 0.01;
            break;
        // Slower
        case 'S':
        case 's':
            if ( speed >= 0.01 )
                speed -= 0.01;
            break;
        // Pause
        case 'T':
        case 't':
            paused = 1;
            break;
        // Resume
        case 'C':
        case 'c':
            paused = 0;
            break;
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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable( GL_DEPTH_TEST );
    glEnable( GL_COLOR_MATERIAL );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable( GL_LIGHT1 );
    glEnable( GL_NORMALIZE );

    // Shading model
    glShadeModel( GL_SMOOTH );

    // Load textures
    Image* image = loadBMP( "vtr.bmp" );
    textureID = loadTexture( image );
    delete image;
}

//---------------------------------------------------------------------------
// NAME: GLPrint()
// IMPORT: text (char*), inX (float), inY (float)
// PURPOE: Draw line of text at given coordinates

void GLPrint(const char* text, float inX, float inY)
{
	int i;
	int length = strlen(text);

	glColor3f(1.0,1.0,1.0);
	glRasterPos3f(inX,inY,-15.0f);
	glPushMatrix();

	// Print one char at a time over the entire string
	for(i=0; i < length; i++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);

	glPopMatrix();
}

//---------------------------------------------------------------------------
// NAME: printControls()
// PURPOSE: Calls to GLPrint() to output text to the display

void printControls()
{
    glDisable(GL_LIGHTING);
	glPushMatrix();
		glRotatef(-15.0f,1.0f,0.0f,0.0f);

		GLPrint("Input:",-15.0,12.0);
		GLPrint("<z>/<Z> : Zooms in/out",-15.0,11.0);
		GLPrint("<x>/<X> : X-axis rotation clock/anti-clockwise",-15.0,10.0);
		GLPrint("<y>/<Y> : Y-axis rotation clock/anti-clockwise",-15.0,9.0);
		GLPrint("<p>/<P> : Turn on Smooth/Flat Shading",-15.0,8.0);
		GLPrint("<a>/<A> : Start animation",-15.0,7.0);
		GLPrint("<t>/<T> : Pause animation",-15.0,6.0);
		GLPrint("<c>/<C> : Resume Animation",-15.0,5.0);
		GLPrint("<Esc> : Quit the program",-15.0,4.0);
	glPopMatrix();
	glEnable(GL_LIGHTING);
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
	glLoadIdentity();

    // Angle, w/h ratio, Near Z clipping, Far Z clipping
    double ratio = (double)width / (double)height;
	gluPerspective( 45.0, ratio , 1.0, 200.0 );
    glMatrixMode(GL_MODELVIEW);
}

//---------------------------------------------------------------------------

//Draws the 3D scene
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -20.0f);
    glScalef( zoom, zoom, zoom );


    if ( xRot )
        xAngle += 0.5;
    if ( yRot )
        yAngle += 0.5;

    glRotatef( xAngle, 0.0f, 1.0f, 0.0f );
    glRotatef( yAngle, 1.0f, 0.0f, 0.0f );


	GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat lightPos[] = {-2 * BOX_SIZE, BOX_SIZE, 4 * BOX_SIZE, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    // Lines to show the 3 axis on the screen for reference
	glBegin(GL_LINES);
        // X LINE IS RED
        glColor3f( 1.0, 0.0, 0.0 );
		glVertex3f( -(2.0*CUBE_SIZE), 0, 0);
		glVertex3f(  (2.0*CUBE_SIZE), 0, 0);
        // Y LINE IS GREEEN
        glColor3f( 0.0, 1.0, 0.0 );
		glVertex3f( 0, -(2.0*CUBE_SIZE), 0);
		glVertex3f( 0,  (2.0*CUBE_SIZE), 0);
        // Z LINE IS BLUE
        glColor3f( 0.0, 0.0, 1.0 );
		glVertex3f( 0, 0, -(2.0*CUBE_SIZE));
		glVertex3f( 0, 0,  (2.0*CUBE_SIZE));
	glEnd();

	glBegin(GL_QUADS);

    	//Top face
    	glColor3f(1.0f, 1.0f, 0.0f);
    	glNormal3f(0.0, 1.0f, 0.0f);
    	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    	glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    	glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);

    	//Bottom face
    	glColor3f(1.0f, 0.0f, 1.0f);
    	glNormal3f(0.0, -1.0f, 0.0f);
    	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);

    	//Left face
    	glNormal3f(-1.0, 0.0f, 0.0f);
    	glColor3f(0.0f, 1.0f, 1.0f);
    	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    	glColor3f(0.0f, 0.0f, 1.0f);
    	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);

    	//Right face
    	glNormal3f(1.0, 0.0f, 0.0f);
    	glColor3f(1.0f, 0.0f, 0.0f);
    	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    	glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    	glColor3f(0.0f, 1.0f, 0.0f);
    	glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);

	glEnd();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);

    	//Front face
    	glNormal3f(0.0, 0.0f, 1.0f);
    	glTexCoord2f(0.0f, 0.0f);
    	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    	glTexCoord2f(1.0f, 0.0f);
    	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    	glTexCoord2f(1.0f, 1.0f);
    	glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    	glTexCoord2f(0.0f, 1.0f);
    	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);

    	//Back face
    	glNormal3f(0.0, 0.0f, -1.0f);
    	glTexCoord2f(0.0f, 0.0f);
    	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    	glTexCoord2f(1.0f, 0.0f);
    	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    	glTexCoord2f(1.0f, 1.0f);
    	glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    	glTexCoord2f(0.0f, 1.0f);
    	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);

	glEnd();
	glDisable(GL_TEXTURE_2D);

    //printControls();

    glFlush();
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
