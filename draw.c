/*
*	Name: Stephen Clark
*	Date: 06/28/2016
*
*	CSCI 4229 - Summer 2016
*	Final Project
*
*	draw.c
*		This file contains all of the functions I used to draw the skatepark
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//  Macro for sin & cos in degrees
#define Cos(th) cos(3.1415927/180*(th))
#define Sin(th) sin(3.1415927/180*(th))

// Macros for grid size
#define GRID_SIZE 5.0
#define GRID_SPACING 0.1


extern float shinyvec[1];    	// Shininess (value)
extern unsigned int texture[7]; // Texture names


//A scaleable cube used to create any 3D box
void draw_cube(double x, double y, double z,
	double dx, double dy, double dz,
	double th, int tex, int color)
{
	//  Set specular color to white
	float white[] = {1,1,1,1};
	float black[] = {0,0,0,1};
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);


	glPushMatrix();
	//  Offset
	glTranslated(x,y,z);
	glRotated(th,0,1,0);
	glScaled(dx,dy,dz);

	//  Enable textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, texture[tex]);

    if (color == 1)			// Yellowish -- for surface platforms
    	glColor3f(1, 1, 0.6588);
    else if (color == 2)	// Black -- for non-surface platforms
    	glColor3f(0, 0, 0);
    else if (color == 3) 	// Wood -- for alternating stairs
    	glColor3f(0.4196, 0.2666, 0.1373);
    else if (color == 4)	// Dark Grey -- for ramp and platforms
    	glColor3f(0.35, 0.35, 0.35);
    else
    	glColor3f(1, 1, 1);


	// Top
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0); glVertex3f(-1, 1, 1);
	glTexCoord2f(0, 1); glVertex3f(-1, 1, -1);
	glTexCoord2f(1, 1); glVertex3f(1, 1, -1);
	glTexCoord2f(1, 0); glVertex3f(1, 1, 1);
	glEnd();


	// Bottom
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glTexCoord2f(0, 0); glVertex3f(-1, -1, 1);
	glTexCoord2f(0, 1); glVertex3f(-1, -1, -1);
	glTexCoord2f(1, 1); glVertex3f(1, -1, -1);
	glTexCoord2f(1, 0); glVertex3f(1, -1, 1);
	glEnd();


	// Side: +Z
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 0); glVertex3f(-1, -1, 1);
	glTexCoord2f(0, 1); glVertex3f(-1, 1, 1);
	glTexCoord2f(1, 1); glVertex3f(1, 1, 1);
	glTexCoord2f(1, 0); glVertex3f(1, -1, 1);
	glEnd();


	// Side: -Z
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 0); glVertex3f(-1, -1, -1);
	glTexCoord2f(0, 1); glVertex3f(-1, 1, -1);
	glTexCoord2f(1, 1); glVertex3f(1, 1, -1);
	glTexCoord2f(1, 0); glVertex3f(1, -1, -1);
	glEnd();


	// Side: +X
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glTexCoord2f(0, 0); glVertex3f(1, -1, 1);
	glTexCoord2f(0, 1); glVertex3f(1, 1, 1);
	glTexCoord2f(1, 1); glVertex3f(1, 1, -1);
	glTexCoord2f(1, 0); glVertex3f(1, -1, -1);
	glEnd();


	// Side: -X
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0, 0); glVertex3f(-1, -1, 1);
	glTexCoord2f(0, 1); glVertex3f(-1, 1, 1);
	glTexCoord2f(1, 1); glVertex3f(-1, 1, -1);
	glTexCoord2f(1, 0); glVertex3f(-1, -1, -1);
	glEnd();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}



// A scaleable ramp
void draw_ramp(double x, double y, double z,
	double dx, double dy, double dz,
	double th, int tex, int color)
{
	//  Set specular color to white
	float white[] = {1,1,1,1};
	float black[] = {0,0,0,1};
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);


	glPushMatrix();
	//  Offset
	glTranslated(x,y,z);
	glRotated(th,0,1,0);
	glScaled(dx,dy,dz);

	//  Enable textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D,texture[tex]);

	glColor3f(1, 1, 0.6588);
    if (color)
    	glColor3f(0.35, 0.35, 0.35);
    else
    	glColor3f(1, 1, 0.6588);

	// Top
	glBegin(GL_QUADS);
	glNormal3f(-1, 1, 0);
	glTexCoord2f(0, 0); glVertex3f(-1, -1, 1);
	glTexCoord2f(0, 1); glVertex3f(-1, -1, -1);
	glTexCoord2f(1, 1); glVertex3f(1, 1, -1);
	glTexCoord2f(1, 0); glVertex3f(1, 1, 1);
	glEnd();


	// Bottom
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glTexCoord2f(0, 0); glVertex3f(-1, -1, 1);
	glTexCoord2f(0, 1); glVertex3f(-1, -1, -1);
	glTexCoord2f(1, 1); glVertex3f(1, -1, -1);
	glTexCoord2f(1, 0); glVertex3f(1, -1, 1);
	glEnd();


	// Side: +Z
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 0); glVertex3f(-1, -1, 1);
	//glTexCoord2f(0, 1); glVertex3f(-1, 1, 1);
	glTexCoord2f(1, 1); glVertex3f(1, 1, 1);
	glTexCoord2f(1, 0); glVertex3f(1, -1, 1);
	glEnd();


	// Side: -Z
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 0); glVertex3f(-1, -1, -1);
	//glTexCoord2f(0, 1); glVertex3f(-1, 1, -1);
	glTexCoord2f(1, 1); glVertex3f(1, 1, -1);
	glTexCoord2f(1, 0); glVertex3f(1, -1, -1);
	glEnd();


	// Side: +X
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glTexCoord2f(0, 0); glVertex3f(1, -1, 1);
	glTexCoord2f(0, 1); glVertex3f(1, 1, 1);
	glTexCoord2f(1, 1); glVertex3f(1, 1, -1);
	glTexCoord2f(1, 0); glVertex3f(1, -1, -1);
	glEnd();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}



// A scaleable ramp
void draw_big_kicker(double x, double y, double z,
	double dx, double dy, double dz,
	double th, int tex)
{
	//  Set specular color to white
	float white[] = {1,1,1,1};
	float black[] = {0,0,0,1};
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);


	glPushMatrix();
	//  Offset
	glTranslated(x,y,z);
	glRotated(-16.75,1,0,0);
	glScaled(dx,dy,dz);

	//  Enable textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D,texture[tex]);

	// 6 inch thick ramp
	glColor3f(0.35, 0.35, 0.35);
	draw_cube(0, 0, 0, 2.5, 0.25, 3.5, 0, 0, 0);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}



//A scaleable cube used to create any 3D box
void draw_rail(double x, double y, double z,
	double dx, double dy, double dz,
	double th, int tex, int color)
{
	//  Set specular color to white
	float white[] = {1,1,1,1};
	float black[] = {0,0,0,1};
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);


	glPushMatrix();
	//  Offset
	glTranslated(x,y,z);
	glRotated(th,1,0,0);
	glScaled(dx,dy,dz);

	if (color)
    	glColor3f(0, 0.35, 0);
    else
    	glColor3f(0.35, 0, 0);

	// Top
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, 1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, 1, 1);
	glEnd();


	// Bottom
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glVertex3f(-1, -1, 1);
	glVertex3f(-1, -1, -1);
	glVertex3f(1, -1, -1);
	glVertex3f(1, -1, 1);
	glEnd();


	// Side: +Z
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glVertex3f(-1, -1, 1);
	glVertex3f(-1, 1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, -1, 1);
	glEnd();


	// Side: -Z
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, -1, -1);
	glEnd();


	// Side: +X
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glVertex3f(1, -1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, -1, -1);
	glEnd();


	// Side: -X
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glVertex3f(-1, -1, 1);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, -1, -1);
	glEnd();

	glPopMatrix();
}



// Used to draw cylindrical components.  For a quarterpipe that will be
// the ramp, the transition between the ramps, and the coping
void draw_qp_component(double x, double y, double z,
    double dx, double dy, double dz,
    double th, double rotation, int color)
{
    //  Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    glPushMatrix();

    //  Offset
    glTranslated(x,y,z);
    glRotated(th,0,0,1);
    glScaled(dx,dy,dz);

    // Coping color
    if (color)
    	glColor3f(0.75, 0, 0);
    else
    	glColor3f(0.35, 0.35, 0.35);

    //  Enable textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

    glBindTexture(GL_TEXTURE_2D,texture[0]); // Stone texture

    float pi = 3.141592654f;

	float numberOfSegments = 360.0;
	float angleIncrement = (2 * pi) / numberOfSegments;
	float textureCoordinateIncrement = 1 / numberOfSegments;

	glBegin(GL_QUAD_STRIP);
	for (int i = rotation; i <= 270; ++i)
	{
		float c = cos(angleIncrement * i);
		float s = sin(angleIncrement * i);

		glNormal3d(-Cos(i), 1, -Sin(i));
		glTexCoord2f( textureCoordinateIncrement * i, 0); glVertex3f( c, -1, s);
		glTexCoord2f( textureCoordinateIncrement * i, 1); glVertex3f( c, 1, s);
	}

	glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}



void draw_qp_siding(double x, double y, double z,
    double radius, double th, int norm, double degrees)
{
	//  Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

	glPushMatrix();

    //  Offset
    glTranslated(x,y,z);
    glRotated(th,0,1,0);

    //  Enable textures
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, texture[0]);

	// Quarterpipe Ramp Sides
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.35, 0.35, 0.35);
	glVertex3f(0, 0, 1);
	for (int i=-90; i <= degrees; i++)
	{
		glNormal3f(norm * 1, 0, 0);
		glTexCoord2f((i/90), 1); glVertex3f((radius * Cos(i)), ((radius * Sin(i))+radius), 1);
		glTexCoord2f((i/90), 0); glVertex3f(radius, 0, 1);
	}
	glEnd();

	glPopMatrix();
}



// Combines draw_quarterpipe, draw_qp_trans, and draw_qp_platform to
// draw the qp section of the park
void draw_qp_section()
{
	// -X QP
	draw_qp_siding(-26, 0, -52, 5, 90, -1, 0);
	for (float i = -25; i < -10.0; i += 2.5)
		draw_qp_component(i + 1.25, 5, -52, 5, 1.25, 5, 90, 180, 0);
	draw_qp_siding(-11, 0, -52, 5, 90, 1, -10);

	// -X Transition
	draw_qp_component(-8.75, 5, -52, 5, 1.25, 5, 90, 260, 0);

	// Middle QP
	draw_qp_siding(-8.5, 1, -53, 4, 90, -1, -10);
	for (float i = -7.5; i < 7.5; i += 2.5)
		draw_qp_component(i + 1.25, 5, -53, 4, 1.25, 4, 90, 180, 0);
	draw_qp_siding(6.5, 1, -53, 4, 90, 1, -10);

	// +X Transition
	draw_qp_component(8.75, 5, -52, 5, 1.25, 5, 90, 260, 0);

	// +X QP
	draw_qp_siding(9, 0, -52, 5, 90, -1, -10);
	for (float i = 10; i < 25; i += 2.5)
		draw_qp_component(i + 1.25, 5, -52, 5, 1.25, 5, 90, 180, 0);
	draw_qp_siding(24, 0, -52, 5, 90, 1, 0);

	// Coping
	draw_qp_component(0, 5, -57, 0.0625, 25, 0.0625, 90, -90, 1);
}



// Based on information I found the course is 9000 sq. ft. so I am going
// to use 50 x 180
void draw_ground()
{
	for (float i = -24.0; i < 25.0; i += 1.0)
	{
		for (float j = -59.0; j < 63.0; j += 1.0)
		{
			draw_cube(i, -0.1, j, 1.0, 0.1, 1.0, 0, 0, 0);
		}
	}	
}



// A 12 inch platform measuing 15 x 35
void draw_platform_1(double x, double y, double z,
	double dx, double dy, double dz,
	double th, int color)
{
	glPushMatrix();

	glTranslated(x,y,z);
	glRotated(th,0,1,0);
	glScaled(dx,dy,dz);

	// if (color)
	// 	glColor3f(0, 0, 0);
	// else
	// 	glColor3f(1, 1, 0.6588);

	for (float i = -6.5; i < 7.5; i += 1.0)
	{
		for (float j = -56.0; j < -22.0; j += 1.0)
		{
			draw_cube(i, 0.5, j, 1.0, 0.5, 1.0, 0, 0, color);
		}
	}

	glPopMatrix();
}



// Funbox
void draw_funbox(double x, double y, double z,
	double dx, double dy, double dz,
	double th, int color)
{
	glPushMatrix();

	glTranslated(x,y,z);
	glRotated(th,0,1,0);
	glScaled(dx,dy,dz);

	// if (color)
	// 	glColor3f(0, 0, 0);
	// else
	// 	glColor3f(1, 1, 0.6588);

	for (float i = 0; i <= 2.5; i += 0.5)
	{
		for (float j = 0; j <= 5.0; j += 1)
		{
			draw_cube(0, 0.5, 0, i, 0.5, j, 0, 0, color);
		}
	}

	glPopMatrix();
}



void draw_rail_6x6(double x, double y, double z)
{
	glPushMatrix();
	glTranslated(x,y,z);

	// Top of rail
	glColor3f(0.75, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(-0.125, -1, 3.5);
	glVertex3f(-0.125, 1, -3.5);
	glVertex3f(0.125, 1, -3.5);
	glVertex3f(0.125, -1, 3.5);
	glEnd();

	// Bottom of rail
	glColor3f(0.75, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(-0.125, -1.25, 3.5);
	glVertex3f(-0.125, 0.75, -3.5);
	glVertex3f(0.125, 0.75, -3.5);
	glVertex3f(0.125, -1.25, 3.5);
	glEnd();

	// Side of rail
	glColor3f(0.75, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(0.125, -1.25, 3.5);
	glVertex3f(0.125, -1, 3.5);
	glVertex3f(0.125, 1, -3.5);
	glVertex3f(0.125, 0.75, -3.5);
	glEnd();

	// Side of rail
	glColor3f(0.75, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(-0.125, -1.25, 3.5);
	glVertex3f(-0.125, -1, 3.5);
	glVertex3f(-0.125, 1, -3.5);
	glVertex3f(-0.125, 0.75, -3.5);
	glEnd();

	// End of Rail
	glColor3f(0.75, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(-0.125, -1.25, 3.5);
	glVertex3f(-0.125, -1, 3.5);
	glVertex3f(0.125, -1, 3.5);
	glVertex3f(0.125, -1.25, 3.5);
	glEnd();

	// End of Rail
	glColor3f(0.75, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(-0.125, 0.75, -3.5);
	glVertex3f(-0.125, 1, -3.5);
	glVertex3f(0.125, 1, -3.5);
	glVertex3f(0.125, 0.75, -3.5);
	glEnd();



	// Vertical Support
	glColor3f(0, 0.75, 0);
	glBegin(GL_QUADS);
	glVertex3f(-0.1, -0.75, -3.25);
	glVertex3f(-0.1, 0.75, -3.25);
	glVertex3f(0.1, 0.75, -3.25);
	glVertex3f(0.1, -0.75, -3.25);
	glEnd();

	// Vertical Support
	glColor3f(0, 0.75, 0);
	glBegin(GL_QUADS);
	glVertex3f(-0.1, -0.875, -3);
	glVertex3f(-0.1, 0.675, -3);
	glVertex3f(0.1, 0.675, -3);
	glVertex3f(0.1, -0.875, -3);
	glEnd();

	// Vertical Support
	glColor3f(0, 0.75, 0);
	glBegin(GL_QUADS);
	glVertex3f(0.1, -0.875, -3);
	glVertex3f(0.1, 0.675, -3);
	glVertex3f(0.1, 0.675, -3.25);
	glVertex3f(0.1, -0.875, -3.25);
	glEnd();

	// Vertical Support
	glColor3f(0, 0.75, 0);
	glBegin(GL_QUADS);
	glVertex3f(-0.1, -0.875, -3);
	glVertex3f(-0.1, 0.675, -3);
	glVertex3f(-0.1, 0.675, -3.25);
	glVertex3f(-0.1, -0.875, -3.25);
	glEnd();



	// Vertical Support
	glColor3f(0, 0.75, 0);
	glBegin(GL_QUADS);
	glVertex3f(-0.1, -2.5, 3.25);
	glVertex3f(-0.1, -1, 3.25);
	glVertex3f(0.1, -1, 3.25);
	glVertex3f(0.1, -2.5, 3.25);
	glEnd();

	// Vertical Support
	glColor3f(0, 0.75, 0);
	glBegin(GL_QUADS);
	glVertex3f(-0.1, -2.5, 3);
	glVertex3f(-0.1, -1, 3);
	glVertex3f(0.1, -1, 3);
	glVertex3f(0.1, -2.5, 3);
	glEnd();

	// Vertical Support
	glColor3f(0, 0.75, 0);
	glBegin(GL_QUADS);
	glVertex3f(0.1, -2.5, 3);
	glVertex3f(0.1, -1, 3);
	glVertex3f(0.1, -1, 3.25);
	glVertex3f(0.1, -2.5, 3.25);
	glEnd();

	// Vertical Support
	glColor3f(0, 0.75, 0);
	glBegin(GL_QUADS);
	glVertex3f(-0.1, -2.5, 3);
	glVertex3f(-0.1, -1, 3);
	glVertex3f(-0.1, -1, 3.25);
	glVertex3f(-0.1, -2.5, 3.25);
	glEnd();


	glPopMatrix();
}



// Grass texture in a box
void draw_flower_box(double x, double y, double z,
	double dx, double dy, double dz, double th)
{
	glPushMatrix();

	glTranslated(x,y,z);
	glRotated(th,0,1,0);
	glScaled(dx,dy,dz);

	draw_cube(0, 0, 1, 1.125, 0.25, 0.125, 0, 0, 3);
	draw_cube(0, 0, -1, 1.125, 0.25, 0.125, 0, 0, 3);

	draw_cube(1, 0, 0, 0.125, 0.25, 1.125, 0, 0, 3);
	draw_cube(-1, 0, 0, 0.125, 0.25, 1.125, 0, 0, 3);

	draw_cube(0, 0, 0, 0.875, 0.175, 0.875, 0, 2, 0);

	glPopMatrix();
}




void draw_platform_2(double x, double y, double z,
	double dx, double dy, double dz,
	double th, int color)
{
	glPushMatrix();

	glTranslated(x,y,z);
	glRotated(th,0,1,0);
	glScaled(dx,dy,dz);

	for (float i = -6.5; i < 7.5; i += 1.0)
	{
		for (float j = 59.0; j > 22.0; j -= 1.0)
		{
			draw_cube(i, 0.5, j, 1.0, 0.5, 1.0, 0, 0, color);
		}
	}

	glPopMatrix();
}



void draw_funbox_2(double x, double y, double z)
{
	glPushMatrix();

	glTranslated(x,y,z);

	draw_ramp(0, 0, 5, 2.5, 0.75, 2.5, 90, 0, 0);

	// Middle Flat
	draw_cube(0, 0.5, 0, 2.5, 0.25, 2.5, 0, 0, 1);
	draw_cube(0, -0.25, 0, 2.5, 0.5, 2.5, 0, 0, 2);

	// Stairs, 18 inch flats by 6 inch heights
	draw_cube(0, 0.5, -3.25, 2.5, 0.25, 0.75, 0, 0, 1);
	draw_cube(0, -0.25, -3.25, 2.5, 0.5, 0.75, 0, 0, 2);

	draw_cube(0, 0.5, -4.75, 2.5, 0.25, 0.75, 0, 0, 1);
	draw_cube(0, -0.25, -4.75, 2.5, 0.5, 0.75, 0, 0, 2);

	draw_cube(0, 0, -6.25, 2.5, 0.25, 0.75, 0, 0, 1);
	draw_cube(0, -0.5, -6.25, 2.5, 0.25, 0.75, 0, 0, 2);

	draw_cube(0, -0.5, -7.75, 2.5, 0.25, 0.75, 0, 0, 1);

	glPopMatrix();
}



void draw_funbox_3(double x, double y, double z)
{
	glPushMatrix();

	glTranslated(x,y,z);

	draw_ramp(0, 0, 5, 2.5, 0.75, 2.5, 90, 0, 0);

	// Middle Flat
	draw_cube(0, 0.5, 0, 2.5, 0.25, 2.5, 0, 0, 1);
	draw_cube(0, -0.25, 0, 2.5, 0.5, 2.5, 0, 0, 2);

	// Stairs, 18 inch flats by 6 inch heights
	draw_cube(-0.5, 0.5, -3.25, 2, 0.25, 0.75, 0, 0, 1);
	draw_cube(-0.5, -0.25, -3.25, 2, 0.5, 0.75, 0, 0, 2);

	draw_cube(-0.5, 0.5, -4.75, 2, 0.25, 0.75, 0, 0, 1);
	draw_cube(-0.5, -0.25, -4.75, 2, 0.5, 0.75, 0, 0, 2);

	draw_cube(-0.5, 0, -6.25, 2, 0.25, 0.75, 0, 0, 1);
	draw_cube(-0.5, -0.5, -6.25, 2, 0.25, 0.75, 0, 0, 2);

	draw_cube(-0.5, -0.5, -7.75, 2, 0.25, 0.75, 0, 0, 1);

	draw_cube(2, -0.25, -6.5, 0.5, 0.5, 4, 0, 0, 2);
	draw_cube(2, 0.5, -6.5, 0.5, 0.25, 4, 0, 0, 1);


	glPopMatrix();
}


// The big stairs in the center of the +Z plane
void draw_impact_stairs()
{
	draw_cube(0, 0.25, 17.25, 7.5, 0.25, 0.25, 0, 0, 1);

	draw_cube(0, 0.75, 17.75, 7.5, 0.25, 0.25, 0, 0, 3);
	draw_cube(0, 0.25, 17.75, 7.5, 0.25, 0.25, 0, 0, 2);

	draw_cube(0, 1.25, 18.25, 7.5, 0.25, 0.25, 0, 0, 1);
	draw_cube(0, 0.5, 18.25, 7.5, 0.5, 0.25, 0, 0, 2);

	draw_cube(0, 1.75, 18.75, 7.5, 0.25, 0.25, 0, 0, 3);
	draw_cube(0, 0.75, 18.75, 7.5, 0.75, 0.25, 0, 0, 2);

	draw_cube(0, 2.25, 19.25, 7.5, 0.25, 0.25, 0, 0, 1);
	draw_cube(0, 1.0, 19.25, 7.5, 1.0, 0.25, 0, 0, 2);

	draw_cube(0, 2.75, 19.75, 7.5, 0.25, 0.25, 0, 0, 3);
	draw_cube(0, 1.25, 19.75, 7.5, 1.25, 0.25, 0, 0, 2);

	draw_cube(0, 3.25, 20.25, 7.5, 0.25, 0.25, 0, 0, 1);
	draw_cube(0, 1.5, 20.25, 7.5, 1.5, 0.25, 0, 0, 2);

	draw_cube(0, 3.75, 20.75, 7.5, 0.25, 0.25, 0, 0, 3);
	draw_cube(0, 1.75, 20.75, 7.5, 1.75, 0.25, 0, 0, 2);

	draw_cube(0, 4.25, 21.5, 7.5, 0.25, 0.5, 0, 0, 1);
	draw_cube(0, 2.0, 21.5, 7.5, 2.0, 0.5, 0, 0, 2);
}