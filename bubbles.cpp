/***************************************************************************
*  FILE: bubbles.cpp
*  AUTHOR: Connor Beardsmore - 15504319
*  UNIT: CG200 Assignment S2 - 2016
*  PURPOSE: Bubbs yo
*  LAST MOD: 10/10/16
*  REQUIRES: bubbles.hpp
***************************************************************************

MARKING GUIDE:
--------------
SIMPLE SHAPES: Spheres for bubbles, Floor plane (quad), GLUTTeapot
COMPOSITE SHAPES: Chain, Pirate Flag, Rocks, Chest

LIGHT SOURCES: One white at front. One green specular at back
SURFACE FINISHES: Pirate flag, Floor bitmap, Teapot texture map

LEVEL OF DETAIL: Detail variables decided on amount of polygons

FUNCTION DISPLAY: Displayed statically on screen in clear white text

KEYS:

ANIMATION: Chain moves up and rotates. Flag moves down. Bubbles move to back

EFFECTS: Bubbles are transparent, Blue fog moves in upon zooming

***************************************************************************/

#include "bubbles.hpp"

//---------------------------------------------------------------------------
// NAME: drawTeapot();
// PURPOSE: Draw chain of anchor + anchor head

void drawBubbles( double xStart, double yStart, double zStart, int detail )
{
    int radius = 5;
    float trans = 0.1f;

    // BIG BUBBLE
    glPushMatrix();
        glTranslatef( xStart, yStart, zStart );
        glColor4f( WHITE , trans );
        gluSphere( gluNewQuadric(), radius, 2*detail, 2*detail );
    glPopMatrix();

    // MID BUBBLE
    glPushMatrix();
        glTranslatef( xStart+10.0, yStart+4.0, zStart+5.0 );
        glColor4f( WHITE, trans );
        gluSphere( gluNewQuadric(), radius/2.0, 2*detail, 2*detail );
    glPopMatrix();

    // SMALL BUBBLE
    glPushMatrix();
        glTranslatef( xStart-5.0, yStart+10, zStart );
        glColor4f( WHITE , trans );
        gluSphere( gluNewQuadric(), radius/3.0, 2*detail, 2*detail );
    glPopMatrix();

}

//---------------------------------------------------------------------------
