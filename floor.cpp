/***************************************************************************
*  FILE: floor.cpp
*  AUTHOR: Connor Beardsmore - 15504319
*  UNIT: CG200 Assignment S2 - 2016
*  PURPOSE: Draws the floor of the scene, a simple quad
*  LAST MOD: 07/10/16
*  REQUIRES: floor.hpp
***************************************************************************/

#include "floor.hpp"

//---------------------------------------------------------------------------
// NAME: drawFloor();
// IMPORT: textureID (GLuint)
// PURPOSE: Draw the floor as a simple quad

void drawFloor( GLuint textureID )
{
    glPushMatrix();

        //glEnable(GL_TEXTURE_2D);
        //glBindTexture(GL_TEXTURE_2D, textureID);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glDisable(GL_LIGHTING);

        // Translate down below the origin + camera
        glTranslatef(0.0, -40.0, 0.0);
        glScalef(2.0f, 0.05f, 2.0f);
        glColor3f( 0.1f, 0.1f, 0.0f );
        GLUquadric* quaddy = gluNewQuadric();
        //gluQuadricTexture( quaddy, GL_TRUE );
        gluSphere( quaddy, 400.5, 400, 400 );

        glEnable(GL_LIGHTING);
        //glDisable(GL_TEXTURE_2D);

    glPopMatrix();

}

//---------------------------------------------------------------------------
