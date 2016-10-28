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

        float mat_ambient[] ={ 0.329412f, 0.223529f, 0.027451f,1.0f };
        float mat_diffuse[] ={ 0.780392f, 0.568627f, 0.113725f, 1.0f };
        float mat_specular[] ={ 0.992157f, 0.941176f, 0.807843f, 1.0f };
        float shine = 27.8974f;

        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialf(GL_FRONT, GL_SHININESS, shine);

        if ( type == 'S' )
            glutSolidTeapot(3.0);
        else if ( type == 'W' )
            glutWireTeapot(3.0);

        glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

//---------------------------------------------------------------------------
