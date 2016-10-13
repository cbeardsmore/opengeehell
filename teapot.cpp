/***************************************************************************
*  FILE: anchor.cpp
*  AUTHOR: Connor Beardsmore - 15504319
*  UNIT: CG200 Assignment S2 - 2016
*  PURPOSE: Draws the axis lines centered at the origin
*  LAST MOD: 10/10/16
*  REQUIRES: anchor.hpp
***************************************************************************/

#include "teapot.hpp"

//---------------------------------------------------------------------------
// NAME: drawTeapot();
// PURPOSE: Draw chain of anchor + anchor head

void drawTeapot( char type, double xStart, double yStart, double zStart )
{
    // Utah Teapots for the lols
    glPushMatrix();
        glColor3f( RED );
        glTranslatef( xStart, yStart, zStart );
        glRotatef( -60.0f, 0.0f, 0.0f, 1.0f );
        glScalef( 2.0f, 2.0f, 2.0f );
        if ( type == 'S' )
            glutSolidTeapot(3.0);
        else if ( type == 'W' )
            glutWireTeapot(3.0);
    glPopMatrix();

}

//---------------------------------------------------------------------------
