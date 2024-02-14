//Windows includes - DO NOT EDIT AS LOTS OF INTERDEPENDENCE


#include <math.h>						
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>	//Needed for console output (debugging)
#include <iostream>
#include <string>

//#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include "Vector3.h"
#include "Football.h"
#include "GUI.h"
#include "Target.h"
#include "TexturedPlane.h"
#include "Wall.h"

//#include "Source/COMP371Helper.h"
//#include "Source/Model.h"
//#include <vector>
//#include "Source/Particles.h"
//
//#include "ThirdParty/irrKlang-1.6.0/include/irrKlang.h"
//#include "shared/glfrustum.h"
//#include "gltools.h"
//
////#include "ThirdParty/glew-2.1.0/include/GL/glew.h"
//
//using namespace irrklang;
//
//using namespace glm;
//using namespace std;


#ifdef WIN32
#include "gltools.h"
#include <windows.h>		// Must have for Windows platform builds
//#include <gl\gl.h>			// Microsoft OpenGL headers (version 1.1 by themselves)
#include "shared\GLee.h"
#include <gl\glu.h>			// OpenGL Utilities
#include "glm.h"
#include "shared\glfrustum.h"
#endif
#include "3DExample1/glext.h"





//can define any number of textures here - we just have 2 images
//these are just integers so you can use them as such
#define GRASS_TEX      2
#define WALL_TEX      3
#define WALL_OLD_TEX      4
#define FLOWER_ORANGE_TEX      5
#define FLOWER_PALM_TEX      6
#define FLOWER_YELLOW_TEX      7
#define BALL_TEX 8    //football map
#define SKY_TEX 9
#define TARGET_BLUE_TEX 10
#define TARGET_RED_TEX 11
#define TARGET_GREEN_TEX 12
#define TARGET_DULL_TEX 13
#define GUI_HORIZONTAL 14
#define GUI_VERTICAL 15
#define TARGET_50_TEX 16
//#define GUI_BUTTON 16


#define TEXTURE_COUNT 15 //15
GLuint  textures[TEXTURE_COUNT];

//Game Constants
#define NUMBER_OF_WALLS 3
#define MAX_VELOCITY 4.0f
#define SPIN_MULTIPLIER 3.0f
#define NUM_ATTEMPTS 14;
#define BOUNDARY 1000
#define SB_SIZE 500.0f
#define SB_ROTATION 0.01f

const Vector3 vertBarPos = { 100, 600, 0 };
const Vector3 horzBarPos = { 200, 625, 0 };
int firstTime = 0;


// Global object initialization
//Football ball = Football(BALL_TEX, 5);
Football ball = Football(BALL_TEX, 5, 0 , 5, 0); //ball.transform.position = {0, 5, 0};
TexturedPlane lawn = TexturedPlane(GRASS_TEX, 0, 0, 30, 90, 0, 0, 1*15, 1*20, 1);



TexturedPlane start = TexturedPlane(TARGET_DULL_TEX, 0,1,0,270,0,0);
//start.transform.rotation = { 270, 0, 0 };
//start.transform.position = { 0,1,0 };

//parameters: (tex,score,radius,px,py,pz,rx,ry,rz)
Target target20_1 = Target(TARGET_BLUE_TEX, 20, 7.5, 0, 25, 173, 0, 180, 0);
Target target20_2 = Target(TARGET_BLUE_TEX, 20, 7.5, 40, 12, 173, 0, 180, 0);
Target target20_3 = Target(TARGET_BLUE_TEX, 20, 7.5, -40, 32, 173, 0, 180, 0);
Target target10_1 = Target(TARGET_GREEN_TEX, 10, 10, -45, 12, 173, 0, 180, 0);
Target target10_2 = Target(TARGET_GREEN_TEX, 10, 10, -22 ,18, 173, 0, 180, 0);
Target target10_3 = Target(TARGET_GREEN_TEX, 10, 10, 22, 22, 173, 0, 180, 0);
Target target30_1 = Target(TARGET_RED_TEX, 30, 5, 42, 29, 173, 0, 180, 0);
Target target30_2 = Target(TARGET_RED_TEX, 30, 5, -13, 33, 173, 0, 180, 0);
Target target30_3 = Target(TARGET_RED_TEX, 30, 5, 60, 20, 173, 0, 180, 0);
Target target50_1 = Target(TARGET_50_TEX, 50, 2, 70, 30, 173, 0, 180, 0);


//parameters: (tex,px,py,pz,rx,ry,rz,sx,sy,sz)
Wall wall1 = Wall(WALL_OLD_TEX, -80, 17, 80, 0, 90, 0, 1*4, 1, 1);
Wall wall2 = Wall(WALL_OLD_TEX , 0, 16.9, 177, 0, 180, 0, 1*3.2, 1, 1);
Wall wall3 = Wall(WALL_OLD_TEX, 80, 17, 80, 0, 270, 0, 1*4, 1, 1);

GUI horzBar = GUI(GUI_HORIZONTAL);
GUI vertBar = GUI(GUI_VERTICAL);
GUI options_button = GUI(WALL_TEX ,600,350);

Target* targets[10] = {&target20_1, &target20_2, &target20_3,  &target10_1, &target10_2, &target10_3, &target30_1, &target30_2, &target30_3, &target50_1 };

float Wwidth;
float Wheight;


GLfloat fAspect;

Vector3 kickVelocity = { 0,0,5 };
Vector3 gravity = { 0, -0.11, 0 };
Vector3 ballVelocity;
bool isShooting;


void* font = GLUT_BITMAP_9_BY_15;

int score;
int attempts;

//below is simply a character array to hold the file names
//note that you may need to replace the below with the full directory root depending on where you put your image files
//if you put them where the exe is then you just need the name as below - THESE IMAGES  ARE IN THE DEBUG FOLDER, YOU CAN ADD ANY NEW ONES THERE 
const char* textureFiles[TEXTURE_COUNT] = { "grass_diff.tga", "KALE.tga"/*"brick_texture_lo_res.tga"*/,"old_wall_texture_TGA.tga","orangeFlowerFinal5.tga",
	"palmBranchA.tga", "yellowFlowerFinal.tga","FootballCompleteMap.tga", "stormydays_large.tga", "targetBlue.tga", "targetRed.tga","targetGreen.tga", "targetDull.tga", "fillBarHorizontal.tga", "fillBarVerticalR.tga", "target50.png"};


//for lighting if you want to experiment with these
GLfloat mKa[4] = { 0.11f,0.06f,0.11f,1.0f }; //ambient
GLfloat mKd[4] = { 0.43f,0.47f,0.54f,1.0f }; //diffuse
GLfloat mKs[4] = { 1.0f,1.0f,1.0f,1.0f }; //specular
GLfloat mKe[4] = { 0.5f,0.5f,0.0f,1.0f }; //emission

//spot position and direction
GLfloat	 lightPos[] = { 0.0, 100.0, 300.0, 0.0f };
GLfloat  spotDir[] = { 50.0, 25.0, 0.0 };

GLfloat	 lightPos2[] = { 50.0, 100.0, 300.0, 0.0f };
GLfloat  spotDir2[] = { 50.0, 15.0, 0.0 };

GLfloat	 lightPos3[] = { -50.0, 100.0, 300.0, 0.0f };
GLfloat  spotDir3[] = { 50.0, 15.0, 0.0 };



// Useful lighting colour values
GLfloat  whiteLightBright[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat  redLight[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat  greenLight[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat  blueLight[] = { 0.0f, 1.0f, 1.0f, 1.0f };
GLfloat  whiteLightLessBright[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat  orangeLight[] = { 1.0f, 0.9f, 0.85f, 1.0f };


//we need these for the texture loader
//they are to do with the image format and size
GLint iWidth, iHeight, iComponents;
GLenum eFormat;
// this is a pointer to memory where the image bytes will be held 
GLbyte* pBytes0;

// INITIAL LOOK
double view[3] = { 0.00, 20.00, -40.00, };
double look[3] = { 0.00, 15.00, 0.00 };

// TIMER PARAMETERS
time_t startTime = time(NULL);
int TIME = 120;
int initial_time = 120;
bool buttonPressed = false;


// Button dimensions
const int BUTTON_WIDTH = 100;
const int BUTTON_HEIGHT = 50;


bool hudVisible = false; // Flag to track whether the HUD panel is currently visible
float hudPosition = 0.5; // Variable to store the current position of the HUD panel (0.0 = fully closed, 1.0 = fully open)




void DisplayText(GLfloat x, GLfloat y, std::string message, int num)
{

	glDisable(GL_TEXTURE_2D); //added this
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, Wwidth, 0.0, Wheight);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(10, 10);
	std::string output = message + std::to_string(num); // Score converted to string
	glPushMatrix();
	if (num < 0) { glColor3f(1.0, 0.0, 0.0); } // Red
	else { glColor3f(0.0, 0.0, 0.0); } // Green
	glRasterPos2i(x, y); // changes the raster position for the text to a specified point.

	for (std::string::iterator i = output.begin(); i != output.end(); ++i) // Iterator for message.
	{
		char c = *i;
		glutBitmapCharacter(font, c);
	}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

//camera
GLfloat cameraX = 0.0;
GLfloat cameraY = 150.0;
GLfloat cameraZ = -20.0;

bool repeatOn = false;
bool repeatWallOn = false;
bool moveCamera = false;


void drawHUD() {
	// Set the projection matrix to a 2D orthographic projection
	glMatrixMode(GL_PROJECTION);
	glPushMatrix(); // Save the current projection matrix
	glLoadIdentity(); // Reset the projection matrix
	gluOrtho2D(0, 100, 0, 100); // Set up an orthographic projection with the bottom-left corner at (0,0) and the top-right corner at (100,100)

	// Set the modelview matrix to the identity matrix
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix(); // Save the current modelview matrix
	glLoadIdentity(); // Reset the modelview matrix

	// Set the color to white
	glColor3f(0.0, 1.0, 1.0);

	//glClear(GL_COLOR_BUFFER_BIT);
	//glFlush();

	int initial_HUD_x = 10;
	int initial_HUD_y = 85;
	const int elem_num = 17;
	const char* control_panel[elem_num] = {"CONTROL PANEL:", " ","Up Arrow - Aim Higher", "Down Arrow - Aim Lower",
	"Left Arrow - Aim Left", "Right Arrow - Aim Right", "Space or Z - Shoot", "R - Restart", "F - Follow ball", 
	"T - Top View", "I - Side View", "4 and 6 - move the camera along x axis", "7 and 1 - move the camera along y axis",
	"8 - move the camera along z axis","S - Initial Camera View", "K - Close Control Panel","Hit the targets to win."};

	

	for (int j = 0; j < elem_num; j++) {
		
		// Draw the text on the HUD panel
		glRasterPos2f(initial_HUD_x, initial_HUD_y - j*3); // Set the position of the text to (5,95)
		char text2[256]; // Create a character array to store the text
		sprintf(text2, control_panel[j]); // Set the text to display
		
		for (int i = 0; i < 256 && text2[i] != '\0'; i++) {
			
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text2[i]); // Draw the character
		}
		
	}

	// Set the color to white
	glColor3f(1.0, 0.0, 1.0);
	// Draw the HUD panel
	glBegin(GL_QUADS);
	glVertex2f(initial_HUD_x - 5, initial_HUD_y + 5);
	glVertex2f(initial_HUD_x + 35, initial_HUD_y + 5);
	glVertex2f(initial_HUD_x + 35, initial_HUD_y - 50);
	glVertex2f(initial_HUD_x - 5, initial_HUD_y - 50);
	
	glEnd();

	// Reset the modelview matrix
	glPopMatrix();

	// Reset the projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}



// Scene setup.
void scene()
{


	

	lawn.scale(3);

	/*
	//Move the objects to their locations at the scene
	//start.transform.rotation = { 270, 0, 0 };
	//start.transform.position = { 0,1,0 };
	
	//ball.transform.position = {0, 5, 0};
	//lawn.transform.position = Vector3(0, 0, 30);
	//lawn.scale(3);
	
	
	//wall1.transform.position = Vector3(-80, 17, 80);
	//wall1.transform.rotation.y = 90;
	//wall1.transform.scale.x *= 4;

	wall2.transform.position = Vector3(0, 16.9, 177);
	wall2.transform.rotation.y = 180;
	wall2.transform.scale.x *= 3.2;

	wall3.transform.position = Vector3(80, 17, 80);
	wall3.transform.rotation.y = 270;
	wall3.transform.scale.x *= 4;
	
	lawn.transform.scale.x *= 15;
	lawn.transform.scale.y *= 20;
	lawn.transform.rotation.x = 90;
	
	
	
	for (Target* target : targets)
	{
		(*target).transform.position.z = 173;
		(*target).transform.rotation.y = 180;
	}
	
	target20_1.transform.position.y = 25;

	target20_2.transform.position.y = 12;
	target20_2.transform.position.x = 40;

	target20_3.transform.position.y = 32;
	target20_3.transform.position.x = -40;

	target10_1.transform.position.y = 12;
	target10_1.transform.position.x = -45;

	target10_2.transform.position.y = 18;
	target10_2.transform.position.x = -22;

	target10_3.transform.position.y = 22;
	target10_3.transform.position.x = 22;

	target30_1.transform.position.y = 29;
	target30_1.transform.position.x = 42;

	target30_2.transform.position.y = 33;
	target30_2.transform.position.x = -13;

	target30_3.transform.position.y = 20;
	target30_3.transform.position.x = 60;
	
	target50_1.transform.position.y = 30;
	target50_1.transform.position.x = 70;

	*/

	horzBar.transform.position = horzBarPos;
	horzBar.transform.scale.y /= 4;

	vertBar.transform.position = vertBarPos;
	vertBar.transform.scale.y /= 4;

	vertBar.transform.rotation.z = 90;


	
	score = 0;
	ballVelocity = kickVelocity;
	attempts = NUM_ATTEMPTS
	

	glClearColor(0.0, 0.7, 0.8, 0.5); // Set the clear color to red
	glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

}


void resetBall()
{
	isShooting = false;
	ball.transform.position = { 0, 5, 0 };
	ball.transform.rotation = { 0,0,0 };
	ballVelocity = kickVelocity;
}


void ChangeSize(int w, int h)
{
	//assign width and height values
	Wwidth = w;
	Wheight = h;

	// Prevent a divide by zero
	if (h == 0)
		h = 1;

	// Set Viewport to window dimensions
	glViewport(0, 0, w, h); //The viewport is specified as a rectangle in pixels, with the lower-left corner of the window being at (0,0).

	// Calculate aspect ratio of the window
	fAspect = (GLfloat)w / (GLfloat)h;

	// Set the perspective coordinate system
	glMatrixMode(GL_PROJECTION); //GL_PROJECTION matrix is used to transform the 3D scene to the 2D window, such as specifying the field of view and aspect ratio. 
	glLoadIdentity(); //resets the current matrix to the identity matrix

	// field of view of 45 degrees, near and far planes 1.0 and 1000
	//that znear and zfar should typically have a ratio of 1000:1 to make sorting out z depth easier for the GPU
	//sets the perspective projection matrix. 
	//It takes four arguments: the field of view angle in degrees, the aspect ratio, the distance to the near clipping plane, and the distance to the far clipping plane.
	gluPerspective(45.0f, fAspect, 1.0, 1000.0);

	// Modelview matrix reset
	glMatrixMode(GL_MODELVIEW);//GL_MODELVIEW matrix is used to transform objects in the scene, such as translating, rotating, or scaling them
}

void resetGame() // Resets the ball and every target. Also sets score back to zero and attempts back to maximum. Resets the Velocity to keep it consistent.
{
	
	for(Target* target: targets)
	{
		(*target).reset();
	}
	score = 0;
	attempts = NUM_ATTEMPTS
	kickVelocity.x = 0;
	kickVelocity.y = 0;
	ballVelocity = kickVelocity;
	TIME = 120;
	startTime = time(NULL);
	initial_time = 120;

	resetBall();
}

void updateTimer() {
	time_t currentTime = time(NULL);
	TIME = initial_time - (currentTime - startTime);
	
	if (TIME <= 0) {
		resetGame();
	}
	
}

void checkWin() // Checks if all targets are hit, if yes, resets the game.
{
	bool win = true;
	for(Target* target: targets)
	{
		win = (win && (*target).isHit());
	}
	if (win) { resetGame(); }
}

void mouseButton(int button, int state, int x, int y) {
	// Check if the left mouse button was pressed
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// Check if the mouse cursor is inside the button
		if (x >= Wwidth - BUTTON_WIDTH - 10 && x <= Wwidth - 10 &&
			y >= 10 && y <= 10 + BUTTON_HEIGHT) {
			// Update the button state
			buttonPressed = true;
		}
	}
	// Check if the left mouse button was released
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		// Update the button state
		buttonPressed = false;
	}
}


void drawButton() {

	glPushMatrix();
	////add some lighting normals for each vertex
	////draw the texture on the front
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, Wwidth, Wheight, 0, -1, 1); // Sets to an orthographic projection mode so that the GUI can be displayed in 2D space.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// glFrontFace(GL_CW); //use glFrontFace(GL_CW) to texture the other side - not needed here as we set this elsewhere
	
	
	// Draw the button outline

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(Wwidth - BUTTON_WIDTH - 10, Wheight - 10 - BUTTON_HEIGHT);
	glVertex2f(Wwidth - 10, Wheight - 10 - BUTTON_HEIGHT);
	glVertex2f(Wwidth - 10, Wheight - 10);
	glVertex2f(Wwidth - BUTTON_WIDTH - 10, Wheight - 10);

	glEnd();


	// Fill the button with a color based on the button state
	if (buttonPressed) {
		glColor3f(0.5f, 0.5f, 0.5f);
	}
	else {
		glColor3f(0.8f, 0.8f, 0.8f);
	}
	glBegin(GL_QUADS);
	glVertex2f(Wwidth - BUTTON_WIDTH - 10, Wheight - 10 - BUTTON_HEIGHT);
	glVertex2f(Wwidth - 10, Wheight - 10 - BUTTON_HEIGHT);
	glVertex2f(Wwidth - 10, Wheight - 10);
	glVertex2f(Wwidth - BUTTON_WIDTH - 10, Wheight - 10);

	glEnd();
	//glFlush();
	glPopMatrix();
}



// Called to draw scene
void RenderScene(void)
{		
	// Clear the window with current clearing colour
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Frustum Culling
	GLFrustum frustum = GLFrustum(45.0f, fAspect, 1.0, 1000.0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glLoadIdentity();


		
	if (moveCamera) // If bool is true, follows the ball, otherwise, sits at a predetermined position.
	{
		// view the scene
		gluLookAt(ball.transform.position.x + cameraX, ball.transform.position.y + cameraY, ball.transform.position.z + cameraZ,//eye
			ball.transform.position.x, ball.transform.position.y, ball.transform.position.z+50,//center
			0.00, 1.00, 0.00);//up
	}
	else // Hardcoded, could be improved.
	{

		gluLookAt(view[0], view[1], view[2], look[0], look[1], look[2], 0.0, 1.0, 0.0);
	}
	
	//Occlusion Culling
	GLuint query;
	glGenQueries(1, &query);
	glBeginQuery(GL_SAMPLES_PASSED, query);
	
	if (!frustum.TestSphere(ball.transform.position.x, ball.transform.position.y, ball.transform.position.z, ball.getRadius())) {
		
		ball.draw();
		glEndQuery(GL_SAMPLES_PASSED);
	}
	
	GLuint samplesPassedBall;
	glGetQueryObjectuiv(query, GL_QUERY_RESULT, &samplesPassedBall);
	if (samplesPassedBall == 0)
		std::cout << "Not visible\n";
		
	if (!frustum.TestSphere(lawn.transform.position.x, lawn.transform.position.y, lawn.transform.position.z, lawn.transform.scale.x)) {
		lawn.draw();
	}
	

	glGenQueries(1, &query);
	glBeginQuery(GL_SAMPLES_PASSED, query);
	
	if (!frustum.TestSphere(wall2.transform.position.x, wall2.transform.position.y, wall2.transform.position.z, wall2.transform.scale.x)) {
		wall2.draw();
		glEndQuery(GL_SAMPLES_PASSED);
	}

	GLuint samplesPassedWall;
	glGetQueryObjectuiv(query, GL_QUERY_RESULT, &samplesPassedWall);
	if (samplesPassedWall == 0)
		std::cout << "Not visible\n";
	
		
		
	wall1.draw();
	wall3.draw();
	target20_1.draw();
	target20_2.draw();
	target20_3.draw();
	target10_1.draw();
	target10_2.draw();
	target10_3.draw();
	target30_1.draw();
	target30_2.draw();
	target30_3.draw();
	start.draw();
	
	
	
	if(isShooting) // If the ball is currently shooting, sets the position vector of the ball to be the sum of position and velocity.
	{
		ballVelocity = ballVelocity + gravity; // Gravity acceleration
		ball.transform.position = ball.transform.position + ballVelocity;
		ball.transform.rotation.x += ballVelocity.z * SPIN_MULTIPLIER;

		for (Target* target : targets) // Checks collision for targets first, if true, adds score.
		{
			if(ball.checkPlaneCollision(*target) && !(*target).isHit())
			{
				(*target).hit(TARGET_DULL_TEX);
				score += (*target).getScore();
				resetBall();
				attempts--;
			}
		}
		// Checks collision for wall boundaries, if colliding, removes attempt and resets ball.
		if (ball.checkPlaneCollision(wall1) || ball.checkPlaneCollision(wall2) || ball.checkPlaneCollision(wall3)) 
		{
			resetBall();
			attempts--;
		}
		for(int i = 0; i < 3; i++)
		{
			// if any of the ball's axes are outside of the boundary limit, resets the ball.
			if (abs(ball.transform.position[i]) > BOUNDARY || ball.transform.position.y <= 0 + ball.transform.scale.y/2)
			{
				resetBall();
				attempts--;
			}
		}
		
	}
	checkWin();
	if (attempts <= 0) { resetGame(); }
	
	if (hudVisible)
	{
		drawHUD();
	}

	horzBar.value = kickVelocity.x / MAX_VELOCITY / 2;
	vertBar.value = kickVelocity.y / MAX_VELOCITY - 0.5;
	horzBar.draw(Wwidth, Wheight);
	vertBar.draw(Wwidth, Wheight);
	
	
	//options_button.DRAW(Wwidth, Wheight);
	DisplayText(240, Wheight-20, "Score: ", score);
	DisplayText(100, Wheight - 20, "Attempts: ", attempts);
	
	updateTimer();
	char timerString[32];
	int minutes = TIME / 60;
	int seconds = TIME % 60;
	sprintf(timerString, "%02d:%02d", minutes, seconds);
	int textWidthTimer = glutBitmapLength(GLUT_BITMAP_8_BY_13, (unsigned char*)timerString);
	DisplayText(Wwidth - 6.0f - textWidthTimer, Wheight - 20, timerString, 0);

	
	

	//drawButton();
	

	glutSwapBuffers();

}


// This function does any needed initialization on the rendering context.
void SetupRC()
{
	//textures

	GLuint texture;
	// allocate a texture name
	glGenTextures(1, &texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// photoshop is a good converter to targa (TGA)
	//the gltLoadTGA method is found in gltools.cpp and is orignally from the OpenGL SuperBible book
	//there are quite a few ways of loading images
	// Load textures in a for loop
	glGenTextures(TEXTURE_COUNT, textures);
	//this puts the texture into OpenGL texture memory
 //   glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); - not defined so probably need to update GLEW - not needed here so ignore
	for (int iLoop = 0; iLoop < TEXTURE_COUNT; iLoop++)
	{
		// Bind to next texture object
		glBindTexture(GL_TEXTURE_2D, textures[iLoop]);

		// Load texture data, set filter and wrap modes
		// note that gltLoadTGA is in the glm.cpp file and not a built-in openGL function
		pBytes0 = gltLoadTGA(textureFiles[iLoop], &iWidth, &iHeight,
			&iComponents, &eFormat);

		glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBytes0);

		//set up texture parameters

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		//try these too
	   // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
		// glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		free(pBytes0);
	}

	//enable textures
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_DEPTH_TEST);	// Hidden surface removal    
	glFrontFace(GL_CCW);// Counter clock-wise polygons face out
 //	glEnable(GL_CULL_FACE);		// Do not calculate inside

//    glCullFace(GL_FRONT_AND_BACK);

// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_POINT_SMOOTH);
	// Setup and enable light 0
	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLightBright); // Spotlight
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mKs);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0f);
	glEnable(GL_LIGHT0);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, orangeLight); // Ambient light
	glLightfv(GL_LIGHT2, GL_DIFFUSE, orangeLight);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos3);
	glLightfv(GL_LIGHT2, GL_SPECULAR, mKa);
	glLightf(GL_LIGHT2, GL_AMBIENT, 200.0f);
	glEnable(GL_LIGHT2);

	// Enable colour tracking
	glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// All materials hereafter have full specular reflectivity
	// with a high shine
	glMaterialfv(GL_FRONT, GL_SPECULAR, mKs);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	// Black blue background clear colour
	glClearColor(0.0f, 0.0f, 0.03f, 1.0f);
}


void TimerFunc(int value)
{
	glutPostRedisplay(); // Update display
	glutTimerFunc(25, TimerFunc, 1); // Set up the next timer callback
}

void specialKeyboard(int key, int x, int y) // Keyboard actions
{
	if (!isShooting) // If not shooting, stops player from cheating after the ball has been shot.
	{
		switch (key)
		{

		case GLUT_KEY_UP:
			if (kickVelocity.y < MAX_VELOCITY) { kickVelocity.y += 0.1; } // Adds velocity to axis-assigned buttton.
			break;
		case GLUT_KEY_DOWN:
			if (kickVelocity.y > 0) { kickVelocity.y -= 0.1; }
			else { kickVelocity.y = 0; }
			break;
		case GLUT_KEY_RIGHT:
			if (kickVelocity.x > -MAX_VELOCITY) { kickVelocity.x -= 0.1; }
			break;
		case GLUT_KEY_LEFT:
			if (kickVelocity.x < MAX_VELOCITY) { kickVelocity.x += 0.1; }
			break;
		}
	}
}




void keyboard(unsigned char key, int x, int y) // Keyboard actions
{
	switch (key)
	{
	case ' ': // space and z shoot
	case 'z':
		isShooting = true;
		ballVelocity = kickVelocity;
		break;
	case 'r': // r to manually reset the game.
		resetGame();
		break;
	case 'f': //f to follow ball with cam.
		moveCamera = !moveCamera;
		break;

		//to move the camera along -ve x axis
	case '4':
		view[0] -= 1;
		glutPostRedisplay();
		break;
		//to move the camera along +ve x axis
	case '6':
		view[0] += 1;
		glutPostRedisplay();
		break;
		//to move the camera along +ve y axis
	case '7':
		view[1] += 1;
		glutPostRedisplay();
		break;
		//to move the camera along -ve y axis
	case '1':
		//if (view[1] > 1.9)
		view[1] -= 1;
		glutPostRedisplay();
		break;
		//to move the camera along -ve z axis
	case '8':
		view[2] -= 1;
		glutPostRedisplay();
		break;
		//to move the camera along +ve z axis
	case 'S':
	case 's':

		view[0] = 0.00;
		view[1] = 20.00;
		view[2] = -40.00;

		look[0] = 0.00;
		look[1] = 15.00;
		look[2] = 0.00;

		glutPostRedisplay();
		break;
		//to move the look position along +ve x axis
	case 'e':
	case 'E':
		look[0] += 1;
		break;
		//to move the look position along -ve x axis
	case 'l':
	case 'L':
		look[0] -= 1;
		break;
		//to move the look position along +ve y axis
	case 'U':
	case 'u':
		look[1] += 1;
		break;
		//to move the look position along -ve y axis
	case 'D':
	case 'd':
		look[1] -= 1;
		break;
		//to move the look position along +ve z axis
	case 'y':
	case 'Y':
		look[2] += 1;
		break;
		//to move the look position along -ve z axis
		// 
		//inside view
	case 'i':
	case 'I':
		view[0] = 28;
		view[1] = 20;
		view[2] = -48;
		look[0] = 18;
		look[1] = 20;
		look[2] = 10;
		break;
		//top view
	case 'T':
	case 't':
		view[0] = 60;
		view[1] = 120;
		view[2] = -100;
		look[0] = 20;
		look[1] = 40;
		look[2] = 20;
		break;
		//front view
	case 'j':
	case 'J':
		view[0] = 2;
		view[1] = 2;
		view[2] = -12.9;
		look[0] = 3;
		look[1] = 2;
		look[2] = 3;
		break;
		//back view
	case 'k':
	case 'K':
		if (hudVisible) {
			hudVisible = false;
			break;
		}
		else  {
			hudVisible = true;
			break;
		}
	}
	
}




int main(int argc, char* argv[])
{
	glutInit(&argc, argv); //to initialize the glut library
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // specify display mode (RGB color buffer, double buffering, and depth testing) for a window
	glutInitWindowSize(1280, 720);// a 16:9 ratio
	glutCreateWindow("Football Game"); //A window on the display. The string title can be used to label the window
	glutReshapeFunc(ChangeSize); // when the size of the window is changed, ChangeSize is called with the new width and height of the window, in pixels.
	glutDisplayFunc(RenderScene);// when the window needs to be redisplayed, RenderScene is called whenever the window needs to be redrawn
	glutTimerFunc(25, TimerFunc, 1);
	glutKeyboardFunc(keyboard); // for camera angles
	glutSpecialFunc(specialKeyboard); // for arrow buttons
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	
	
	// Set up the display callback function
	SetupRC();
	scene();

	glutMainLoop();
	return 0;
}





