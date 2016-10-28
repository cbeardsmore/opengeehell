/***************************************************************************
*  FILE: anchor.cpp
*  AUTHOR: Connor Beardsmore - 15504319
*  UNIT: CG200 Assignment S2 - 2016
*  PURPOSE: Draws the axis lines centered at the origin
*  LAST MOD: 10/10/16
*  REQUIRES: anchor.hpp
***************************************************************************/

#include "teapot.hpp"

//---------------------------------------------------------------------------
// NAME: drawTeapot();
// PURPOSE: Draw chain of anchor + anchor head

void drawTeapot( char type, double xStart, double yStart, double zStart, GLuint textureID, GLfloat rotation)
{
    // Utah Teapots
    glPushMatrix();

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glColor3f( GOLD );
        glTranslatef( xStart, yStart, zStart );
        glRotatef( rotation, 0.0f, 1.0f, 0.0f );
        glRotatef( -90.0f, 0.0f, 0.0f, 1.0f );
        glScalef( 2.0f, 2.0f, 2.0f );

        GLfloat materialSpecular[] = {0.5f, 0.5f, 0.5f, 1.0f};
        GLfloat materialEmission[] = {0.1f, 0.1f, 0.1f, 1.0f};
        glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
        glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
        glMaterialf(GL_FRONT, GL_SHININESS, 40);

        if ( type == 'S' )
            glutSolidTeapot(3.0);
        else if ( type == 'W' )
            glutWireTeapot(3.0);

        glDisable(GL_TEXTURE_2D);

    glPopMatrix();

}

//---------------------------------------------------------------------------
