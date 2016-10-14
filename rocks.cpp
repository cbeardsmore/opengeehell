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

void drawRocks(int detail)
{
    glPushMatrix();

        glTranslatef( -45.0f, -23.0f, -100.0f );

        glPushMatrix();
            glColor3f( BROWN );
            glScalef( 3.0f, 3.0f, 3.0f );
            glTranslatef( -10.0f, -3.0f, -10.0f );
            gluSphere( gluNewQuadric(), 10, detail, detail );
        glPopMatrix();

        glPushMatrix();
            glColor3f( BROWN );
            glScalef( 2.0f, 1.0f, 1.3f );
            gluSphere( gluNewQuadric(), 10, detail, detail );
        glPopMatrix();

        glPushMatrix();
            glColor3f( BROWN );
            glTranslatef( -17.0f, -5.0f, 12.0f );
            glScalef( 1.2f, 1.3f, 1.7f );
            gluSphere( gluNewQuadric(), 10, detail-3, detail-3 );
        glPopMatrix();

    glPopMatrix();
}

//---------------------------------------------------------------------------
