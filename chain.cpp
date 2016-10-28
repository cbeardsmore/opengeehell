/***************************************************************************
*  FILE: chain.cpp
*  AUTHOR: Connor Beardsmore - 15504319
*  UNIT: CG200 Assignment S2 - 2016
*  PURPOSE: Draws the axis lines centered at the origin
*  LAST MOD: 10/10/16
*  REQUIRES: chain.hpp
***************************************************************************/

#include "chain.hpp"

//---------------------------------------------------------------------------
// NAME: drawchain();
// PURPOSE: Draw chain of chain + chain head

void drawChain( int pairs, double xStart, double yStart, double zStart, int detail, GLfloat rotation )
{
    glPushMatrix();

        //CHAIN
        for ( int jj = 0; jj < pairs; jj++ )
        {
            glPushMatrix();
                glColor3f( GREY );
                glTranslatef( xStart, ( yStart + 5.0f * (double)jj ), zStart );
                glScalef( 0.35f, 1.0f, 0.35f );
                if ( jj % 2 == 0 )
                    glRotatef( 80.0f+rotation, 0.0f, 1.0f, 0.0f );
                else
                    glRotatef( rotation, 0.0f, 1.0f, 0.0f );
                glutSolidTorus( 1.2f, 3.0f, detail, detail);
            glPopMatrix();
        }

    glPopMatrix();
}

//---------------------------------------------------------------------------
