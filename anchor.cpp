/***************************************************************************
*  FILE: anchor.cpp
*  AUTHOR: Connor Beardsmore - 15504319
*  UNIT: CG200 Assignment S2 - 2016
*  PURPOSE: Draws the axis lines centered at the origin
*  LAST MOD: 10/10/16
*  REQUIRES: anchor.hpp
***************************************************************************/

#include "anchor.hpp"

//---------------------------------------------------------------------------
// NAME: drawAnchor();
// PURPOSE: Draw chain of anchor + anchor head

void drawAnchor( int pairs, double xStart, double yStart, double zStart, GLuint textureID, int detail )
{
        // RED TEAPOT CHAIN
        for ( int jj = 0; jj < pairs; jj++ )
        {
            glPushMatrix();

                glColor3f( GREY );
                glTranslatef( xStart, ( yStart + 5.0f * (double)jj ), zStart );
                glScalef( 0.35f, 1.0f, 0.35f );
                if ( jj % 2 == 0 )
                    glRotatef( 80.0f, 0.0f, 1.0f, 0.0f );
                glutSolidTorus( 1.2f, 3.0f, detail, detail);

            glPopMatrix();
        }
}

//---------------------------------------------------------------------------
