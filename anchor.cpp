/***************************************************************************
*  FILE: chain.cpp
*  AUTHOR: Connor Beardsmore - 15504319
*  UNIT: CG200 Assignment S2 - 2016
*  PURPOSE: Draws the axis lines centered at the origin
*  LAST MOD: 10/10/16
*  REQUIRES: chain.hpp
***************************************************************************/

#include "anchor.hpp"

//---------------------------------------------------------------------------
// FUNCTION: drawAnchor()
// PURPOSE: Draws a sick anchor

void drawAnchor(int segments, GLuint textureID)
{
		GLUquadric* quaddy = gluNewQuadric();
        glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glPushMatrix();

			glEnable(GL_TEXTURE_2D);
			gluQuadricTexture(quaddy, true);

            // BASE RED COLOR
			glColor3f(1.0, 0.0, 0.0);
            glScalef( 1.5f, 1.5f, 1.5f );
            glTranslatef( 15.0f, -9.0f, -80.0f );
            glRotatef( 30.0f, 0.0f, 0.0f, 1.0f );
            glRotatef( -15.0f, 1.0f, 0.0f, 0.0f );

			// TOP TORUS
			glPushMatrix();
				glTranslatef(0.0f,22.0f, 0.0f);
				glScalef(1.0f, 1.0f, 1.5f);
				glutSolidTorus(1.25f, 3.0f, 16, 2*segments);
			glPopMatrix();

			// STRAIGHT POLE
			glPushMatrix();
				glRotatef(-90,1.0f,0.0f,0.0f);
				glTranslatef(0.0f,0.0f,-4.0f);
				gluCylinder(quaddy, 1.5f, 1.5f, 22.0, segments, segments);

				// SIDEWAYS POLE
				glPushMatrix();
					glTranslatef(10.0f,20.0f, 0.0f);
					glRotatef(-90.0, 0.0, 1.0, 0.0);
					glTranslatef(18.0f,-20.0f, 0.0f);
					gluCylinder(quaddy, 1.5f, 1.5f, 20.0, segments, segments);
				glPopMatrix();

				// LEFT BALL
				// (Left-Right, In-Out, Up-Down)
				glPushMatrix();

					glTranslatef(10.0f, 0.0f, 18.0f);
					gluSphere(quaddy,  2.5f,  30,  segments);
				glPopMatrix();

				// RIGHT BALL
				// (Left-Right, In-Out, Up-Down)
				glPushMatrix();

					glTranslatef(-10.0f, 0.0f, 18.0f);
					gluSphere(quaddy,  2.5f,  30, segments);
				glPopMatrix();

				// THE TIP
				glPushMatrix();
					glTranslatef(0.0f,0.0f, 0.25f);
					glRotatef(180.0, 0.0, 1.0, 0.0);
					gluCylinder(quaddy, 1.6f, 0.1f, 1.5f, segments, segments);
				glPopMatrix();

				// LEFT BASE
				glPushMatrix();

					glTranslatef(0.0f,0.0f, 1.0f);
					glRotatef(-70.0, 0.0, 1.0, 0.0);
					// glTranslatef(14.0f,-20.0f, 0.0f);
					gluCylinder(quaddy, 1.5f, 1.5f, 11.0, segments, segments);
				glPopMatrix();

				// RIGHT BASE
				glPushMatrix();

					glTranslatef(0.0f,0.0f, 1.0f);
					glRotatef(70.0, 0.0, 1.0, 0.0);
					// glTranslatef(14.0f,-20.0f, 0.0f);
					gluCylinder(quaddy, 1.5f, 1.5f, 11.0, segments, segments);
				glPopMatrix();

				// RIGHT TIP
				glPushMatrix();

					glTranslatef(15.0f,0.0f, 0.0f);
					glRotatef(70.0, 0.0, 1.0, 0.0);
					glTranslatef(-6.25f,0.0f, -3.0f);
					gluCylinder(quaddy, 2.0f, 0.1f, 4.0, segments, segments);
				glPopMatrix();

				// LEFT TIP
				glPushMatrix();

					glTranslatef(15.0f,0.0f, 10.0f);
					glRotatef(-70.0, 0.0, 1.0, 0.0);
					glTranslatef(-13.5f,0.0f, 22.0f);
					gluCylinder(quaddy, 2.0f, 0.1f, 4.0, segments, segments);
				glPopMatrix();

                gluDeleteQuadric(quaddy);

			glPopMatrix();

		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
}
