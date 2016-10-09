/***************************************************************************
*  FILE: axis.cpp
*  AUTHOR: Connor Beardsmore - 15504319
*  UNIT: CG200 Assignment S2 - 2016
*  PURPOSE: Draws the axis lines centered at the origin
*  LAST MOD: 10/10/16
*  REQUIRES: axis.hpp
***************************************************************************/

#include "axis.hpp"

//---------------------------------------------------------------------------
// NAME: drawAxis();
// PURPOSE: Draw three colored lines to represent the 3 axis.

void drawAxis()
{
    // Lines to show the 3 axis on the screen for reference
    glPushMatrix();
        glBegin(GL_LINES);
            // X LINE IS RED
            glColor3f( RED );
            glVertex3f( -LINE_SPAN, 0, 0 );
            glVertex3f(  LINE_SPAN, 0, 0 );
            // Y LINE IS GREEEN
            glColor3f( GREEN );
            glVertex3f( 0, -LINE_SPAN, 0 );
            glVertex3f( 0,  LINE_SPAN, 0 );
            // Z LINE IS BLUE
            glColor3f( BLUE );
            glVertex3f( 0, 0, -LINE_SPAN );
            glVertex3f( 0, 0,  LINE_SPAN );
        glEnd();
    glPopMatrix();
}

//---------------------------------------------------------------------------
