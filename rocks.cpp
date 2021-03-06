/***************************************************************************
*  FILE: rocks.cpp
*  AUTHOR: Connor Beardsmore - 15504319
*  UNIT: CG200 Assignment S2 - 2016
*  PURPOSE: Draws the axis lines centered at the origin
*  LAST MOD: 10/10/16
*  REQUIRES: rocks.hpp
***************************************************************************/

#include "rocks.hpp"

//---------------------------------------------------------------------------
// NAME: drawAnchor();
// PURPOSE: Draw chain of anchor + anchor head

void drawRocks(int detail, GLuint textureID)
{
    glPushMatrix();

        GLUquadric* quaddy = gluNewQuadric();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glColor3f( BROWN );

        glTranslatef( -45.0f, -23.0f, -100.0f );

        glPushMatrix();
            gluQuadricTexture(quaddy,GL_TRUE);
            glScalef( 3.0f, 3.0f, 3.0f );
            glTranslatef( -10.0f, -3.0f, -10.0f );
            gluSphere( quaddy, 10, detail, detail );
        glPopMatrix();

        glPushMatrix();
            gluQuadricTexture(quaddy,GL_TRUE);
            glScalef( 2.0f, 1.0f, 1.3f );
            gluSphere( quaddy, 10, detail, detail );
        glPopMatrix();

        glPushMatrix();
            gluQuadricTexture(quaddy,GL_TRUE);
            glTranslatef( -17.0f, -5.0f, 12.0f );
            glScalef( 1.2f, 1.3f, 1.7f );
            gluSphere( quaddy, 10, detail-3, detail-3 );
        glPopMatrix();

        gluDeleteQuadric(quaddy);
        glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

//---------------------------------------------------------------------------
