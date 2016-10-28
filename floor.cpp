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

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glDisable(GL_LIGHTING);

        glColor3f(0.3, 0.2, 0.1);
        // Translate down below the origin + camera
        glTranslatef(0.0, -20.0, 0.0);

        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0);
            glVertex3fv(floorVertices[0]);
            glTexCoord2f(0.0, 1600.0);
            glVertex3fv(floorVertices[1]);
            glTexCoord2f(1600.0, 1600.0);
            glVertex3fv(floorVertices[2]);
            glTexCoord2f(1600.0, 0.0);
            glVertex3fv(floorVertices[3]);
        glEnd();

        glEnable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);

    glPopMatrix();

}

//---------------------------------------------------------------------------
