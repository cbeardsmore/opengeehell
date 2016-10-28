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
            {
    			zoom += ZOOM_INCREMENT;
                detail++;
            }
            break;
        //Zoom out 0.1
        case 'z':
            if (zoom > 0.2f)
            {
                zoom -= ZOOM_INCREMENT;
                detail--;
            }
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
                speed += 0.05;
            break;
        // Slower
        case 'S':
        case 's':
            if ( speed >= 0.01 )
                speed -= 0.05;
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
    detail = 10;
    teapotRise = 0.0;
    flagFall = 0.0;

    // Background color and enable depth testing
    glClearColor( BACKGROUND_COLOR );
	glEnable( GL_DEPTH_TEST );
    glEnable( GL_COLOR_MATERIAL );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable( GL_LIGHT1 );
    glEnable( GL_NORMALIZE );

    // Transaprency + FOG
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_FOG);

    // Allows us to set ambient + diffuse default via GL_COLOR
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;

    // GLOBAL AMBEINT LIGHTING
    GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 0.5f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    // FIRST LIGHT GL_LIGHT0
    GLfloat lightPos[] = {10.0f, 10.0f, 0.0f, 1.0};
    GLfloat ambience[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat diffuse[] = {0.3f, 0.3f, 1.0f, 1.0f};
    GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambience);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);


    // SECOND LIGHT GL_LIGHT1
    GLfloat lightPos2[] = {-40.0f, 0.0f, -90.0f, 1.0};
    GLfloat ambience2[] = {0.0f, 0.0f, 0.2f, 1.0f};
    GLfloat diffuse2[] = {0.3f, 0.3f, 1.0f, 1.0f};
    GLfloat specular2[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambience2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse2);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular2);

    // SHADING MODEL
    glShadeModel( GL_SMOOTH );

    // Load bitmaps into images
    Image* image = loadBMP( "./textures/dirt.bmp" );
    Image* image2 = loadBMP( "./textures/g.bmp" );
    Image* image3 = loadBMP( "./textures/rock.bmp" );

    // Load images into textures
    floorTexture = loadTexture( image );
    anchorTexture = loadTexture( image2 );
    rockTexture = loadTexture( image3 );

    // Delete image objects
    delete image;
    delete image2;
    delete image3;
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
    detail = 10;

    // Inverse X and Y rotations and reset angle back to 0
    glRotatef( -xAngle, 0.0f, 1.0f, 0.0f );
    glRotatef( -yAngle, 1.0f, 0.0f, 0.0f );
    xAngle = 0;
    yAngle = 0;
    teapotRise = 0.0;
    flagFall = 0.0;
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

    if ( !paused )
    {
        teapotRise += speed * 0.1;
        flagFall += speed * 0.05;
    }

    // X and Y rotations based on angles
    glRotatef( xAngle, 0.0f, 1.0f, 0.0f );
    glRotatef( yAngle, 1.0f, 0.0f, 0.0f );

    // Disable bitmaps and textures for all following items
    glDisable(GL_TEXTURE_2D);


    // FOG
    GLfloat fogColor[] = {0.0f, 0.0f, 1.0f, 1};
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 0.0f);
    glFogf(GL_FOG_END, 200.0f);

    // Draw objects in the scene
    drawFloor( floorTexture );
    drawAxis();
    drawAnchor( 20, 30.0, 0.0 + teapotRise, -50.0, detail );
    drawAnchor( 20, 40.0, 0.0 + teapotRise, -40.0, detail );
    drawRocks( detail, rockTexture );
    drawTeapot( 'S', 33.0, -9.0 + teapotRise, -50.0, rockTexture );
    drawTeapot( 'W', 43.0, -9.0 + teapotRise, -40.0, rockTexture );
    drawFlag( -50.0f, 28.0f - flagFall, -105.0f, detail );


    glPushMatrix();
        glTranslatef( 0.0f, 0.0f, -100.0f );
        glColor4f( 0.0f, 1.0f, 0.0f, 0.6f );
        gluSphere( gluNewQuadric(), 10, 2*detail, 2*detail );
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
