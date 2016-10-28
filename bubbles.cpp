/***************************************************************************
*  FILE: bubbles.cpp
*  AUTHOR: Connor Beardsmore - 15504319
*  UNIT: CG200 Assignment S2 - 2016
*  PURPOSE: Bubbs yo
*  LAST MOD: 10/10/16
*  REQUIRES: bubbles.hpp
***************************************************************************/

#include "bubbles.hpp"

//---------------------------------------------------------------------------
// NAME: drawTeapot();
// PURPOSE: Draw chain of anchor + anchor head

void drawBubbles( double xStart, double yStart, double zStart, int detail )
{
    int radius = 5;

    glPushMatrix();
        glTranslatef( xStart, yStart, zStart );
        glColor4f( GREEN , 0.4f );
        gluSphere( gluNewQuadric(), radius, 2*detail, 2*detail );
    glPopMatrix();

}

//---------------------------------------------------------------------------
