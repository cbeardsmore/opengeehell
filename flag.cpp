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

void drawFlag( double xStart, double yStart, double zStart, int detail )
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
            glRotatef( 70.0f, 0.0f, 0.0f, 1.0f );
            glColor3f( 1.0f, 0.0f, 0.0f );
            glScalef( 12.0f, 18.0f, 1.0f );
            glTranslatef( -1.0f, -1.0f, 0.0f );
            glBegin(GL_QUADS);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(0.0f, 1.0f, 0.0f);
                glVertex3f(1.0f, 0.0f, 0.0f);
                glVertex3f(1.0f, 1.0f, 0.0f);
            glEnd();
        glPopMatrix();

    glPopMatrix();
}

//---------------------------------------------------------------------------
