/***************************************************************************
*  FILE: flag.cpp
*  AUTHOR: Connor Beardsmore - 15504319
*  UNIT: CG200 Assignment S2 - 2016
*  PURPOSE: Draws the axis lines centered at the origin
*  LAST MOD: 10/10/16
*  REQUIRES: flag.hpp
***************************************************************************/

#include "flag.hpp"
#include "colors.hpp"

//---------------------------------------------------------------------------
// NAME: drawAnchor();
// PURPOSE: Draw chain of anchor + anchor head

void drawFlag( double xStart, double yStart, double zStart, int detail, GLuint textureID )
{
    glPushMatrix();

        glTranslatef( xStart, yStart, zStart );

        //MAIN CYLINDER
        glPushMatrix();
            glRotatef( -20.0f, 0.0f, 0.0f, 1.0f );
            glColor3f( GREY );
            glScalef( 0.5f, 40.0f, 0.5f );
            glRotatef( 90.0f, 1.0f, 0.0f, 0.0f );
            gluCylinder( gluNewQuadric(), 1.5f, 1.5f, 50.0f, detail, detail );
        glPopMatrix();

        //TOP SPHERE
        glPushMatrix();
            glColor3f( BLACK );
            glScalef( 1.0f, 1.0f, 1.0f );
            glTranslatef( 0.0f, 0.0f, 0.0f );
            gluSphere( gluNewQuadric(), 2, detail, detail );
        glPopMatrix();

        //FLAG BOX
        glPushMatrix();

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glDisable(GL_LIGHTING);

            glRotatef( 70.0f, 0.0f, 0.0f, 1.0f );
            glColor3f( 1.0f, 1.0f, 1.0f );
            glScalef( 12.0f, 18.0f, 1.0f );
            glTranslatef( -1.0f, -1.0f, 0.0f );
            glBegin(GL_QUADS);
                glTexCoord2f(0.0, 0.0);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glTexCoord2f(0.0, 1.0);
                glVertex3f(0.0f, 1.0f, 0.0f);
                glTexCoord2f(1.0, 1.0);
                glVertex3f(1.0f, 1.0f, 0.0f);
                glTexCoord2f(1.0, 0.0);
                glVertex3f(1.0f, 0.0f, 0.0f);
            glEnd();

            glEnable(GL_LIGHTING);
            glDisable(GL_TEXTURE_2D);

        glPopMatrix();

    glPopMatrix();
}

//---------------------------------------------------------------------------
