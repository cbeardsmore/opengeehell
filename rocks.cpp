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

void drawRocks()
{
    glPushMatrix();

        glColor3f( BROWN );
        glTranslatef( -30.0f, -23.0f, -70.0f );
        glScalef( 2.0f, 1.0f, 1.3f );
        gluSphere( gluNewQuadric(), 10, 10, 10 );

    glPopMatrix();
}

//---------------------------------------------------------------------------
