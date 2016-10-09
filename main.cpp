/***************************************************************************
*  FILE: main.cpp
*  AUTHOR: Connor Beardsmore - 15504319
*  UNIT: CG200 Assignment S2 - 2016
*  PURPOSE: OpenGL
*  LAST MOD: 19/09/16
*  REQUIRES: main.hpp
***************************************************************************/

#include "main.hpp"
using namespace std;

//---------------------------------------------------------------------------

// Global variables
GLuint textureID1;
GLuint textureID2;
GLfloat zoom;           // Zoom level
GLfloat xAngle;         // X rotation angle
GLfloat yAngle;         // Y rotation angle
GLfloat speed;          // Speed of animation

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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height,
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
    			zoom += ZOOM_INCREMENT;
            break;
        //Zoom out 0.1
        case 'z':
            if (zoom > 0.2f)
                zoom -= ZOOM_INCREMENT;
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
            paused = false;
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
            paused = true;
            break;
        // Resume
        case 'C':
        case 'c':
            paused = false;
            break;
        // Flat shaded polygonization
        case 'p':
            glShadeModel( GL_FLAT );
            break;
        // Smooth shaded polygonization
        case 'P':
            glShadeModel( GL_SMOOTH );
            break;
        // Reset all scene
        case 'r':
        case 'R':
            reset();
            break;
	}
}

//---------------------------------------------------------------------------
// FUNCTION: init()
// PURPOSE: Initialisation of rendering

void init()
{
    // Variable initialisation
    zoom = ZOOM_INCREMENT * 5.0;
    speed = 0.1f;
    angle = 30.0f;
    cameraAngle = 0.0f;
    BOX_SIZE = 7.0f;
    paused = true;
    xRot = false;
    yRot = false;

    // Background color and enable depth testing
    glClearColor( BACKGROUND_COLOR );
	glEnable( GL_DEPTH_TEST );
    glEnable( GL_COLOR_MATERIAL );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable( GL_LIGHT1 );
    glEnable( GL_NORMALIZE );

    // Shading model, smooth by default
    glShadeModel( GL_SMOOTH );

    // Load bitmaps into images
    Image* image = loadBMP( "./textures/vtr.bmp" );
    Image* image2 = loadBMP( "./textures/water.bmp" );

    // Load images into textures
    textureID1 = loadTexture( image );
    textureID2 = loadTexture( image2 );

    // Delete image objects
    delete image;
    delete image2;
}

//---------------------------------------------------------------------------
// NAME: GLprint()
// IMPORT: text (char*), inX (float), inY (float)
// PURPOE: Draw line of text at given coordinates

void GLprint(const char* text, float inX, float inY)
{
	int i;
	int length = strlen(text);

    // Set colour to white and set raster position to print to
	glColor3f( WHITE );
	glRasterPos3f(inX,inY,0.0f);

    // Print one char at a time over the entire string
	glPushMatrix();
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

        // Formatting and location of text fields
        float xCo = -13.3;
        float yCo = 7.6;
        float ySep = 0.5;
        int numControls = 11;

        const char* controls[numControls];
        controls[0] = "Key Functions";
        controls[1] = "-------------";
        controls[2] = "<Z>: Zoom In";
        controls[3] = "<z>: Zoom Out";
        controls[4] = "<x><X>: X Rotation";
        controls[5] = "<y><Y>: Y Rotation";
        controls[6] = "<p>: Flat Shaded Polygonization";
        controls[7] = "<P>: Smooth Shaded Polygonization";
        controls[8] = "<a><A>: Start Animation";
        controls[8] = "<a><A>: Pause Animation";
        controls[8] = "<a><A>: Resume Animation";
        controls[9] = "<r><R>: Reset All";
        controls[10] = "<Esc>: Quit Program";

        // Actual text printed to the screen
        for ( int ii = 0; ii < numControls; ii++ )
            GLprint( controls[ii], xCo, yCo - ( (float)ii * ySep ) );

	glPopMatrix();
	glEnable(GL_LIGHTING);
}

//---------------------------------------------------------------------------
// NAME: reset()
// PURPOSE: Reset scene to original settings

void reset()
{
    // Reset all global variables
    zoom = ZOOM_INCREMENT * 5.0;
    speed = 0.1f;
    paused = true;
    xRot = false;
    yRot = false;

    // Inverse X and Y rotations and reset angle back to 0
    glRotatef( -xAngle, 0.0f, 1.0f, 0.0f );
    glRotatef( -yAngle, 1.0f, 0.0f, 0.0f );
    xAngle = 0;
    yAngle = 0;
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

    // Pulls "camera out" to see the scene
	glTranslatef(0.0f, 0.0f, -20.0f);

    // Print text to screen, outside of pushed matrix
    printControls();

    // Lighting
	GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat lightPos[] = {-2 * BOX_SIZE, BOX_SIZE, 4 * BOX_SIZE, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    // Call draw to draw the objects into the scene
    // Scale all objects by the "zoom" factor
    glPushMatrix();
        glScalef( zoom, zoom, zoom );
        draw();
    glPopMatrix();

    // Forces task completion and swaps the double buffers over
    glFlush();
    glutSwapBuffers();
}

//---------------------------------------------------------------------------
// NAME: draw()
// PURPOSE: Draw objects into the 3D scene

void draw()
{
    // If rotations are true, rotate by additional angle increment
    if ( xRot )
        xAngle += ANGLE_INCREMENT;
    if ( yRot )
        yAngle += ANGLE_INCREMENT;

    // X and Y rotations based on angles
    glRotatef( xAngle, 0.0f, 1.0f, 0.0f );
    glRotatef( yAngle, 1.0f, 0.0f, 0.0f );

    // Disable bitmaps and textures for all following items
    glDisable(GL_TEXTURE_2D);

    // Draw objects in the scene
    drawFloor( textureID2 );
    drawAxis();

    // Utah Teapots for the lols
    glPushMatrix();
        glColor3f( RED );
        glTranslatef( 20.0f, -15.0f, -40.0f );
        glutSolidTeapot(3.0);
    glPopMatrix();
    glPushMatrix();
        glColor3f( GREEN );
        glTranslatef( 30.0f, -15.0f, -30.0f );
        glutWireTeapot(3.0);
    glPopMatrix();

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
	glutInitWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
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
