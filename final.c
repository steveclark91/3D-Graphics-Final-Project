/*
*	Name: Stephen Clark
*	Date: 06/28/2016
*
*	CSCI 4229 - Summer 2016
*	Final Project
*
*	final.c
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

int axes=0;		//  Display axes
int mode=2;		//  Projection mode
int th=180;		//  Azimuth of view angle
int ph=0;		//  Elevation of view angle
int fov=55;		//  Field of view (for perspective)
double asp=1;	//  Aspect ratio
double dim=5;	//  Size of world



// Variables from example 13 and 15
int move=1;       //  Move light

int ntex=0;       //  Cube faces
int light=1;      //  Lighting
int rep=1;        //  Repitition

// Light values
int one       =   1;  // Unit value
int x_distance  =   50;  // Light distance
int z_distance  =   125;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model

int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shinyvec[1];    // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   25;  // Elevation of light
unsigned int texture[7]; // Texture names



// My variables
int grid = 0;	// Turn grid on/off
const char *modes[] = {"Orthogonal", "Perspective", "First Person"};

// Default Ex, Ey, Ez values for first person
double xOffset = 0;
double yOffset = 6;
double zOffset = 0;

// Default Cx, Cy, Cz values for first person
double Cx = 0;
double Cy = 0;
double Cz = 0;

// Path for animated tour
int run = 0;
const int PATH_SIZE = 930;
int pathIndex = 0;
double path[PATH_SIZE][3];

// Skatepark Bounds
const int X_MAX = 25;
const int X_MIN = -25;

const int Z_MAX = 63;
const int Z_MIN = -57;

const float SPEED = 0.5;


// Initializes the path the camera will follow during the demo
void setPath()
{
	double new_z = 0.0;

	for (int i = 0; i < PATH_SIZE; i++)
	{
		if (i == 0)
		{
			path[i][0] = 20;
			path[i][1] = 6;
			path[i][2] = Z_MAX;
		}
		else if (i > 0 && i <= 240)
		{
			path[i][0] = 20;


			// Set Y
			if (i >= 6 && i < 26)
				path[i][1] = path[i-1][1] - (SPEED * (4.5/10));
			else if (i >= 66 && i < 76)
				path[i][1] = path[i - 1][1] + (SPEED * (1.5/5.0));
			else if (i >= 86 && i < 102)
				path[i][1] = path[i - 1][1] - (SPEED * (1.5/8.0));
			else if (i >= 230)
				path[i][1] = path[i-1][1] + (2 * SPEED * SPEED);
			else
				path[i][1] = path[i - 1][1];


			// Set Z
			new_z = Z_MAX - (i * SPEED);
			if (new_z > Z_MAX || new_z < Z_MIN)
				path[i][2] = path[i - 1][2];
			else
				path[i][2] = new_z;
		}
		else if (i > 240 && i <= 260)
		{
			path[i][0] = path[i-1][0] - SPEED;
			path[i][1] = 7;
			path[i][2] = Z_MIN;
		}
		else if (i > 260 && i <= 500)
		{
			path[i][0] = path[i-1][0];
			path[i][2] = path[i-1][2] + SPEED;

			if (i >= 260 && i < 270)
				path[i][1] = path[i-1][1] - (2 * SPEED * SPEED);
			else if (i >= 300 && i < 320)
				path[i][1] = path[i-1][1] + (SPEED * (1.5/10.0));
			else if (i >= 320 && i < 340)
				path[i][1] = path[i-1][1] - (SPEED * (1.5/10.0));
			else if(i >= 408 && i < 418)
				path[i][1] = path[i-1][1] + (SPEED * (2.0/5.0));
			else if(i >= 484 && i < 494)
				path[i][1] = path[i-1][1] + (SPEED * (2.5/5.0));
			else
				path[i][1] = path[i-1][1];
		}
		else if (i > 500 && i <= 550)
		{
			path[i][0] = path[i-1][0] - SPEED;
			path[i][1] = 7;
			path[i][2] = Z_MAX;
		}

		else if (i > 550 && i <= 790)
		{
			path[i][0] = path[i-1][0];
			path[i][2] = path[i-1][2] - SPEED;
			if (i >= 556 && i < 566)
				path[i][1] = path[i-1][1] - (SPEED * (2.0/5.0));
			else if (i >= 642 && i < 662)
				path[i][1] = path[i - 1][1] - (SPEED * (1.25/5.0));
			else if (i >= 703 && i < 713)
				path[i][1] = path[i - 1][1] + (SPEED * (1.0/5.0));
			else if (i >= 743 && i < 753)
				path[i][1] = path[i - 1][1] - (SPEED * (1.0/5.0));
			else if (i >= 780)
				path[i][1] = path[i-1][1] + (2 * SPEED * SPEED);
			else
				path[i][1] = path[i - 1][1];
		}
		else if (i > 790 && i <= 810)
		{
			path[i][0] = path[i-1][0] + SPEED;
			path[i][1] = 7;
			path[i][2] = Z_MIN;
		}
		else if (i > 810 && i <= 930)
		{
			path[i][0] = path[i-1][0];
			path[i][2] = path[i-1][2] + SPEED;

			if (i >= 810 && i < 820)
				path[i][1] = path[i-1][1] - (2 * SPEED * SPEED);
			else if (i >= 870 && i < 880)
				path[i][1] = path[i - 1][1] + (SPEED * (1.0/5.0));
			else if (i >= 880 && i < 895)
				path[i][1] = path[i - 1][1] - (SPEED * (2.0/7.5));
			else
				path[i][1] = path[i-1][1];
		}	
	}
}


//  Macro for sin & cos in degrees
#define Cos(th) cos(3.1415927/180*(th))
#define Sin(th) sin(3.1415927/180*(th))

// Macros for grid size
#define GRID_SIZE 5.0
#define GRID_SPACING 0.1



// Load functions
unsigned int LoadTexBMP(const char* file);

// -Z Functions
void draw_cube(double x, double y, double z, double dx, double dy, double dz, double th, int tex, int color);
void draw_ramp(double x, double y, double z, double dx, double dy, double dz, double th, int tex, int color);
void draw_big_kicker(double x, double y, double z, double dx, double dy, double dz, double th, int tex);
void draw_rail(double x, double y, double z, double dx, double dy, double dz, double th, int tex, int color);
void draw_quarterpipe(double x, double y, double z, double dx, double dy, double dz, double th, float radius);
void draw_qp_component(double x, double y, double z, double dx, double dy, double dz, double th, double rotation, int color);
void draw_qp_platform();
void draw_qp_section();
void draw_ground();
void draw_platform_1(double x, double y, double z, double dx, double dy, double dz, double th, int color);
void draw_funbox(double x, double y, double z, double dx, double dy, double dz, double th, int color);
void draw_rail_6x6(double x, double y, double z);

// +Z Functions
void draw_platform_2(double x, double y, double z, double dx, double dy, double dz, double th, int color);
void draw_funbox_2(double x, double y, double z);
void draw_funbox_3(double x, double y, double z);
void draw_impact_stairs();

void draw_flower_box(double x, double y, double z, double dx, double dy, double dz, double th);

/*
*  Convenience routine to output raster text
*  Use VARARGS to make this more flexible
*/
#define LEN 8192  //  Maximum length of text string
void Print(const char* format , ...)
{
	char    buf[LEN];
	char*   ch=buf;
	va_list args;
	//  Turn the parameters into a character string
	va_start(args,format);
	vsnprintf(buf,LEN,format,args);
	va_end(args);
	//  Display the characters one at a time at the current raster position
	while (*ch)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}



/*
*  Set projection
*/
static void Project()
{
	//  Tell OpenGL we want to manipulate the projection matrix
	glMatrixMode(GL_PROJECTION);
	//  Undo previous transformations
	glLoadIdentity();
	//  Perspective transformation
	if (mode)
		//gluPerspective(fov,asp,dim/10,10*dim);
		gluPerspective(fov,asp,0.1,1000);
	//  Orthogonal projection
	else
		glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
	//  Switch to manipulating the model matrix
	glMatrixMode(GL_MODELVIEW);
	//  Undo previous transformations
	glLoadIdentity();
}



// Sphere for lighting - Taken from example 13
/*
 *  Draw vertex in polar coordinates with normal
 */
static void Vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius (r)
 */
static void ball(double x,double y,double z,double r)
{
   int th,ph;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=2*inc)
      {
         Vertex(th,ph);
         Vertex(th,ph+inc);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
}


/*
*  OpenGL (GLUT) calls this routine to display the scene
*/
void display()
{
	//int i,j,k;
	//const double len=1.5;  //  Length of axes

	//  Erase the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//  Enable Z-buffering in OpenGL
	glEnable(GL_DEPTH_TEST);
	//  Undo previous transformations
	glLoadIdentity();
	//  Perspective - set eye position
	if (mode == 1)
	{
		double Ex = -2*dim*Sin(th)*Cos(ph);
		double Ey = +2*dim        *Sin(ph);
		double Ez = +2*dim*Cos(th)*Cos(ph);
		gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
	}
	else if (mode == 0)
	{

		glRotatef(ph,1,0,0);
		glRotatef(th,0,1,0);
		// The following is taken from
		// https://github.com/untra/final_project/blob/master/final.c
		// lines 250 - 254
		//
		// I calculated xOffset and zOffset in the key() function
		// depending on if the user is moving forward or strafing.

	}
	//  Orthogonal - set world orientation
	else
	{
		// Set up first person projection
        Cx = -2 * dim * Sin(th) * Cos(ph) + xOffset;
        Cy = 2 * dim * Sin(ph) + yOffset;
        Cz = 2 * dim * Cos(th) * Cos(ph) + zOffset;
        gluLookAt(xOffset,yOffset,zOffset ,Cx,Cy,Cz, 0,Cos(ph),0);
	}

	//-------------------- LIGHTING - LEAVE ALONE --------------------//
	// Set Lighting Variables
	glShadeModel(GL_SMOOTH);
	//  Translate intensity to color vectors
	float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
	float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
	float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
	//  Light position
	//float Position[]  = {distance*Cos(zh),ylight,distance*Sin(zh),1.0};
	float Position[]  = {x_distance*Cos(zh),ylight,z_distance*Sin(zh),1.0};
	//  Draw light position as ball (still no lighting here)
	glColor3f(1,1,1);
	ball(Position[0],Position[1],Position[2] , 0.1);
	//  OpenGL should normalize normal vectors
	glEnable(GL_NORMALIZE);
	//  Enable lighting
	glEnable(GL_LIGHTING);
	//  Location of viewer for specular calculations
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
	//  glColor sets ambient and diffuse color materials
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	//  Enable light 0
	glEnable(GL_LIGHT0);
	//  Set ambient, diffuse, specular components and position of light 0
	glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
	glLightfv(GL_LIGHT0,GL_POSITION,Position);
	//----------------------------------------------------------------//





	//----------------------------- DRAW SCENE -----------------------------//
	draw_ground();

	draw_platform_1(0, 0, 0, 1, 0.5, 1, 0, 2);
	draw_platform_1(0, 0.5, 0, 1, 0.5, 1, 0, 1);

	draw_qp_section();

	draw_ramp(-10, 0.75, -32, 5, 0.75, 2.5, -90, 0, 0);
	draw_ramp(10, 0.75, -32, 5, 0.75, 2.5, -90, 0, 0);

	draw_ramp(-5.0, 1.5, -24.5, 2.5, 0.5, 2.5, -90, 0, 0);
	draw_ramp(5.0, 1.5, -24.5, 2.5, 0.5, 2.5, -90, 0, 0);

	draw_ramp(-5.0, 1, -18.25, 3.75, 1, 2.5, 90, 0, 0);
	draw_ramp(5.0, 1, -18.25, 3.75, 1, 2.5, 90, 0, 0);


	draw_funbox(-15, 0, -25.5, 1, 0.5, 1, 0, 2);
	draw_funbox(-15, 0.5, -25.5, 1, 0.5, 1, 0, 1);

	draw_funbox(15, 0, -25.5, 1, 0.5, 1, 0, 2);
	draw_funbox(15, 0.5, -25.5, 1, 0.5, 1, 0, 1);


	// Middle kicker
	draw_big_kicker(0, 1.6, -24.16, 1, 1, 1, 0, 0);
	draw_cube(0, 1, -22, 2.5, 1, 0.01, 0, 0, 2);
	draw_flower_box(0, 0.25, -18.25, 2.225, 1, 3.325, 0);


	draw_rail_6x6(-7.375, 2.5, -18);
	draw_rail_6x6(7.375, 2.5, -18);


	draw_flower_box(-10, 0.25, -23.75, 2.25, 1, 2.875, 0);
	draw_flower_box(10, 0.25, -23.75, 2.25, 1, 2.875, 0);
	draw_flower_box(-15, 0.25, 16.25, 2.23, 1, 0.675, 0);

	// Flower Boxes for Quarter Pipe Section
	draw_flower_box(8.75, 0.5, -55.95, 1.12, 2, 0.85, 0);
	draw_flower_box(-8.75, 0.5, -55.95, 1.12, 2, 0.85, 0);


	// +Z Half
	for (float i = 0.0; i < 4.0; i += 0.5)
		draw_platform_2(0, i, 0, 1, 0.5, 1, 0, 2);
	draw_platform_2(0, 4, 0, 1, 0.5, 1, 0, 1);


	// Right side platforms
	for (float i = 0.0; i < 2; i += 0.5)
	{
		draw_platform_2(-12.5, i, 0, 0.6667, 0.5, 1, 0, 2);
	}
	draw_platform_2(-12.5, 2, 0, 0.6667, 0.5, 1, 0, 1);


	// Left side platforms
	for (float i = 0.0; i < 1.5; i += 0.5)
	{
		draw_platform_2(12.5, i, 0, 0.6667, 0.5, 1, 0, 2);
	}
	draw_platform_2(12.5, 1.5, 0, 0.6667, 0.5, 1, 0, 1);


	draw_ramp(-10, 1.25, 19.5, 2.5, 1.25, 2.5, 270, 0, 1);
	draw_ramp(10, 1, 19.5, 2.5, 1, 2.5, 270, 0, 1);


	// Right side middle stair gap
	draw_cube(-15, 0.5, 19.5, 2.5, 0.5, 2.5, 0, 0, 2);
	draw_cube(-15, 1.25, 19.5, 2.5, 0.25, 2.5, 0, 0, 1);

	draw_cube(-15, 1.75, 19.75, 2.5, 0.25, 0.25, 0, 0, 1);
	draw_cube(-15, 1.75, 21, 2.5, 0.25, 1, 0, 0, 2);
	draw_cube(-15, 2.25, 21, 2.5, 0.25, 1, 0, 0, 1);


	// Left side middle stair gap
	draw_cube(14.5, 0.25, 17.5, 2, 0.25, 0.5, 0, 0, 1);

	draw_cube(14.5, 0.75, 18.5, 2, 0.25, 0.5, 0, 0, 1);
	draw_cube(14.5, 0.25, 18.5, 2, 0.25, 0.5, 0, 0, 2);

	draw_cube(14.5, 1.25, 19.5, 2, 0.25, 0.5, 0, 0, 1);
	draw_cube(14.5, 0.5, 19.5, 2, 0.5, 0.5, 0, 0, 2);

	draw_cube(15, 1.75, 21, 2.5, 0.25, 1, 0, 0, 1);
	draw_cube(15, 0.75, 21, 2.5, 0.75, 1, 0, 0, 2);

	// left side middle rail platform
	draw_cube(17, 0.5, 17, 0.5, 0.5, 3, 0, 0, 2);
	draw_cube(17, 1.25, 17, 0.5, 0.25, 3, 0, 0, 1);

	// Far right ramp to stair funbox
	draw_funbox_2(-20, 0.75, 22.5);

	// Far Left ramp to stair funbox
	draw_funbox_3(20, 0.75, 22.5);


	// Rails for right side
	draw_rail(-12.5833, 3.5, 26, 0.08333, 0.08333, 3.98, 0, 0, 0);		// Rail
	draw_rail(-12.5833, 2.75, 26, 0.08333, 0.08333, 0.75, 90, 0, 0);	// Support
	draw_rail(-12.5833, 2.75, 29.9, 0.08333, 0.08333, 0.75, 90, 0, 0);	// Support
	draw_rail(-12.5833, 2.75, 22.1, 0.08333, 0.08333, 0.75, 90, 0, 0);	// Support

	draw_rail(-12.5833, 3.5, 20, 0.08333, 0.08333, 2.98, 0, 0, 0);		// Rail
	draw_rail(-12.584, 2.92, 20.084, 0.08333, 0.08333, 0.5, 90, 0, 0);	// Support
	draw_rail(-12.5833, 2.5, 17.1, 0.08333, 0.08333, 1, 90, 0, 0);		// Support

	draw_rail(-15, 2.75, 17.1, 2.5, 0.08333, 0.08333, 0, 0, 0);				// Rail
	draw_rail(-15, 2.0833, 17.1, 0.08333, 0.08333, 0.75, 90, 0, 0);			// Support
	draw_rail(-17.4167, 2.0833, 17.1, 0.08333, 0.08333, 0.75, 90, 0, 0);	// Support	

	draw_rail(-22.3, 2.25, 15, 0.08333, 0.08333, 3.98, -11.21, 0, 0);		// Rail
	draw_rail(-22.3, 1.75, 15, 0.08333, 0.08333, 3.98, -11.21, 0, 0);		// Rail	
	draw_rail(-22.3, 2.225, 18.83, 0.08333, 0.08333, 0.75, 90, 0, 0);	// Support
	draw_rail(-22.3, 1.25, 15, 0.08333, 0.08333, 1, 90, 0, 0);		// Support
	draw_rail(-22.3, 0.75, 11.2, 0.08333, 0.08333, 0.75, 90, 0, 0);	// Support	



	// Rails for left side
	draw_rail(22, 2.5833, 18.5, 0.08333, 0.08333, 6.48, -4.3987, 0, 0);	// Rail
	draw_rail(22, 1.6667, 12.133, 0.08333, 0.08333, 0.5, 90, 0, 0);		// Support
	draw_rail(22, 1.7, 16.133, 0.08333, 0.08333, 0.75, 90, 0, 0);		// Support
	draw_rail(22, 1.75, 20.133, 0.08333, 0.08333, 1, 90, 0, 0);			// Support
	draw_rail(22, 1.8, 24.88, 0.08333, 0.08333, 1.25, 90, 0, 0);		// Support

	draw_rail(12.4167, 3.5, 26, 0.08333, 0.08333, 3.98, 0, 0, 0);		// Rail
	draw_rail(12.4167, 2.8, 26, 0.08333, 0.08333, 3.98, 0, 0, 0);		// Rail	
	draw_rail(12.4167, 2.75, 26, 0.08333, 0.08333, 0.75, 90, 0, 0);		// Support
	draw_rail(12.4167, 2.75, 29.9, 0.08333, 0.08333, 0.75, 90, 0, 0);	// Support
	draw_rail(12.4167, 2.75, 22.1, 0.08333, 0.08333, 0.75, 90, 0, 0);	// Support	

	draw_rail(17, 2.75, 17.75, 0.5, 0.25, 3.75, 0, 0, 0);	// Rail
	draw_rail(17, 2, 14.25, 0.5, 0.25, 0.5, 90, 0, 1);	// Support
	draw_rail(17, 2.25, 21.25, 0.5, 0.25, 0.25, 90, 0, 1);	// Support


	// Impact Stairs
	draw_impact_stairs();
	draw_rail(7.25, 4.5, 19, 0.25, 0.125, 3, -41.99, 0, 0);		// +X Rail
	draw_rail(7.25, 4.125, 20.75, 0.245, 0.125, 2, 90, 0, 1);	// +X Upper Rail Support
	draw_rail(7.25, 0.9375, 17.25, 0.245, 0.125, 2, 90, 0, 1);	// +X Lower Rail Support

	draw_rail(-7.25, 4.5, 19, 0.25, 0.125, 3, -41.99, 0, 0);	// -X Rail
	draw_rail(-7.25, 4.125, 20.75, 0.245, 0.125, 2, 90, 0, 1);	// -X Upper Rail Support
	draw_rail(-7.25, 0.9375, 17.25, 0.245, 0.125, 2, 90, 0, 1);	// -X Lower Rail Support


	draw_ramp(21.25, 2.25, 55, 5, 2.25, 3.75, 270, 0, 1);
	draw_ramp(12.5, 3.25, 57.5, 2.5, 1.25, 5, 270, 0, 1);
	draw_ramp(-21.25, 2.25, 55, 5, 2.25, 3.75, 270, 0, 1);
	draw_ramp(-12.5, 3.25, 57.5, 2.5, 1.25, 5, 270, 0, 1);

	// +Z Back standing platform
	draw_cube(0, 2.25, 61.5, 25, 2.25, 1.5, 0, 0, 4);

	// -Z Back standing platform
	draw_cube(0, 2.5, -58.5, 25, 2.5, 1.5, 0, 0, 4);

	//-----------------------------------------------------------------------//



	// Switch color back to white just in case I missed something along the way
	glColor3f(1, 1, 1);


	//  Display parameters - Take from Example 13
	glWindowPos2i(5,5);
	// Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s Light=%s",
	// th,ph,dim,fov,mode?"Perpective":"Orthogonal",light?"On":"Off");
	Print("Path Index:%d \t\t X:%.2f \t\t Y:%.2f \t\t Z:%.2f \t\t Yaw:%d \t\t Pitch:%d", pathIndex, xOffset, yOffset, zOffset, th, ph);
	//  Render the scene and make it visible
	glFlush();
	glutSwapBuffers();

}



/*
 *  GLUT calls this routine when the window is resized
 *  Adopted from ex13
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   //double delta_X = 0.1;

   zh = fmod(30*t,360.0);

	if (mode == 2 && run == 1)
	{
   		if (pathIndex == 0)
   		{
   			th = 180;
   			xOffset = 20;
   			yOffset = 6;
   			zOffset = Z_MAX;
   		}

   		xOffset = path[pathIndex][0];
   		yOffset = path[pathIndex][1];
   		zOffset = path[pathIndex][2];
   		//pathIndex++;

   		if (pathIndex < (PATH_SIZE - 1))
   			pathIndex++;
   		else
   			pathIndex = 0;
   	}

   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}



/*
*  GLUT calls this routine when an arrow key is pressed
*/
void special(int key,int x,int y)
{
	//  Right arrow key - increase angle by 5 degrees
	if (key == GLUT_KEY_RIGHT)
		th += 5;
	//  Left arrow key - decrease angle by 5 degrees
	else if (key == GLUT_KEY_LEFT)
		th -= 5;

	//	Up arrow key - increase elevation by 5 degrees
	//	If in first person mode limit to 25 degrees
	else if (key == GLUT_KEY_UP)
	{
			if (ph < 75)
				ph += 5;
			else
				ph = 75;
	}
	//  Down arrow key - decrease elevation by 5 degrees
	//	If in first person mode limit to -25 degrees
	else if (key == GLUT_KEY_DOWN)
	{
			if (ph > -75)
				ph -= 5;
			else
				ph = -75;
	}

	th %= 360;
	ph %= 360;
	//  Update projection
	Project();
	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}



/*
*  GLUT calls this routine when a key is pressed
*/
void key(unsigned char ch,int x,int y)
{
	//  Exit on ESC
	if (ch == 27)
		exit(0);

	//  Reset view angle
	else if (ch == '0')
	{
		th=-30;
		ph=-5;	
		xOffset = -35;
		yOffset = 15;
		zOffset = -70;
	}

	// Start and stop the demo
	else if (ch == 'r' || ch == 'R')
	{
		// Reset the demo on R, otherwise just pause
		if (ch == 'R')
			pathIndex = 0;
		run = 1 - run;
	}


	// Forward and Sideways movement
	else if (ch == 'w' && mode == 2 && (!run))
	{
		xOffset += 0.1 * (Cx - xOffset);
		zOffset += 0.1 * (Cz - zOffset);
	}
	else if (ch == 's' && mode == 2 && (!run))
	{
		xOffset -= 0.1 * (Cx - xOffset);
		zOffset -= 0.1 * (Cz - zOffset);
	}
	else if (ch == 'a' && mode == 2 && (!run))
	{
		xOffset += 0.015 * ((yOffset * Cz) - (zOffset * Cy));
		zOffset += 0.015 * ((xOffset * Cy) - (yOffset * Cx));
	}
	else if (ch == 'd' && mode == 2 && (!run))
	{
		xOffset -= 0.015 * ((yOffset * Cz) - (zOffset * Cy));
		zOffset -= 0.015 * ((xOffset * Cy) - (yOffset * Cx));
	}

	else if (ch == 'h' && mode == 2 && (!run))
	{
		if (yOffset > 0.1)
			yOffset -= 0.25;
		else
			yOffset = 0.1;
	}

	else if (ch == 'H' && mode == 2 && (!run))
	{
		if (yOffset < 25.0)
			yOffset += 0.25;
		else
			yOffset = 12.0;
	}


	// LIGHTING CONTROLS

	// Toggle Lighting Animation
	else if (ch == 'l')
		move = 1 - move;

	// Move Light
	else if (ch == '>')
		zh += 1;
	else if (ch == '<')
		zh -= 1;

	//  Light elevation
	else if (ch=='[')
		ylight -= 0.1;
	else if (ch==']')
		ylight += 0.1;

	//  Ambient level
	else if (ch=='1' && ambient>0)
		ambient -= 5;
	else if (ch=='2' && ambient<100)
		ambient += 5;

	//  Diffuse level
	else if (ch=='3' && diffuse>0)
		diffuse -= 5;
	else if (ch=='4' && diffuse<100)
		diffuse += 5;

	//  Specular level
	else if (ch=='5' && specular>0)
		specular -= 5;
	else if (ch=='6' && specular<100)
		specular += 5;

	//  Emission level
	else if (ch=='7' && emission>0)
		emission -= 5;
	else if (ch=='8' && emission<100)
		emission += 5;

	//  Shininess level
	else if (ch=='9' && shininess>-1)
		shininess -= 1;
	else if (ch=='0' && shininess<7)
		shininess += 1;

	//  Translate shininess power to value (-1 => 0)
	shinyvec[0] = shininess<0 ? 0 : pow(2.0,shininess);

	//  Animate if requested
	glutIdleFunc(move?idle:NULL);

	//  Reproject
	Project();
	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}



/*
*  GLUT calls this routine when the window is resized
*/
void reshape(int width,int height)
{
	//  Ratio of the width to the height of the window
	asp = (height>0) ? (double)width/height : 1;
	//  Set the viewport to the entire window
	glViewport(0,0, width,height);
	//  Set projection
	Project();
}



/*
*  Start up GLUT and tell it what to do
*/
int main(int argc,char* argv[])
{
	//  Initialize GLUT
	glutInit(&argc,argv);
	//  Request double buffered, true color window with Z buffering at 600x600
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(600,600);
	glutCreateWindow("Final Project: Stephen Clark");
	//  Set callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	setPath();

	// Load textures
	texture[0] = LoadTexBMP("concrete.bmp");
	texture[1] = LoadTexBMP("wood.bmp");
	texture[2] = LoadTexBMP("grass.bmp");
	texture[3] = LoadTexBMP("dirt.bmp");


	//  Pass control to GLUT so it can interact with the user
	glutMainLoop();
	return 0;
}
