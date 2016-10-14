/***************************************************************************
*  FILE: flag.cpp
*  AUTHOR: Connor Beardsmore - 15504319
*  UNIT: CG200 Assignment S2 - 2016
*  PURPOSE: Draws the axis lines centered at the origin
*  LAST MOD: 10/10/16
*  REQUIRES: flag.hpp
***************************************************************************/

#include "flag.hpp"

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
            glColor3f( 1.0f, 0.0f, 0.0f );
            glScalef( 0.5f, 40.0f, 0.5f );
            glRotatef( 90.0f, 1.0f, 0.0f, 0.0f );
            gluCylinder( gluNewQuadric(), 1.5f, 1.5f, 50.0f, detail, detail );
        glPopMatrix();

        //TOP SPHERE
        glPushMatrix();
            glColor3f( BROWN );
            glScalef( 3.0f, 3.0f, 3.0f );
            glTranslatef( -10.0f, -3.0f, -10.0f );
            gluSphere( gluNewQuadric(), 10, detail, detail );
        glPopMatrix();

        //FLAG BOX


    glPopMatrix();
}

//---------------------------------------------------------------------------
