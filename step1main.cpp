#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include<GL/glut.h>
#include <time.h>
#include <stdio.h>


double w = 1280, h = 720;
double view[3] = { 2,2,12.9 };
double look[3] = { 2,2,2 };
int flag = -1;
void steps(void);
void window(void);
void sgate(void);
void gate(void);
double angle = 0, speed = 5, maino = 0, romo = 0, tro = 0, mgo = 0, sgo = 0;
//declarating quadric objects
GLUquadricObj* Cylinder;
GLUquadricObj* Disk;
struct tm* newtime;
time_t ltime;
time_t startTime = time(NULL);
GLfloat angle1;

//initialisation
void myinit(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1 * w / h, 1 * w / h, 1, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//defining new quadric object
	Cylinder = gluNewQuadric();
	//to set drawing style
	gluQuadricDrawStyle(Cylinder, GLU_FILL);
	//to set automatic normals
	gluQuadricNormals(Cylinder, GLU_SMOOTH);
	Disk = gluNewQuadric();
	gluQuadricDrawStyle(Disk, GLU_FILL);
	gluQuadricNormals(Disk, GLU_SMOOTH);
	GLfloat gam[] = { 0.2,.2,.2,1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gam);
}
//set material property
void matprop(GLfloat amb[], GLfloat dif[], GLfloat spec[], GLfloat shi[])
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shi);
}
//to create wall
void wall(double thickness)
{
	glPushMatrix();
	glTranslated(2, .5 * thickness, 2);
	glScaled(4.0, thickness, 4.0);
	glutSolidCube(1.0);
	glPopMatrix();
}
//to create compound wall
void wall2(double thickness)
{
	glPushMatrix();
	glTranslated(.8, .5 * thickness * 4, 3.5);
	glScaled(1.6, thickness * 4, 7.0);
	glutSolidCube(1.0);
	glPopMatrix();
}
//to create earth
void earth(void)
{
	GLfloat ambient[] = { 1,0,0,1 };
	GLfloat specular[] = { 0,1,1,1 };
	GLfloat diffuse[] = { .5,.5,.5,1 };
	GLfloat shininess[] = { 50 };
	matprop(ambient, diffuse, specular, shininess);
	GLfloat lightIntensity[] = { .7,.7,.7,1 };
	GLfloat light_position[] = { 2,5,-3,0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
	glPushMatrix();
	glTranslated(0, -.25, 0);
	glScaled(10000, .5, 1000000);
	glutSolidCube(1.0);
	glPopMatrix();
	glFlush();
}
void compound(void)
{
	GLfloat ambient[] = { 1,0,0,1 };
	GLfloat specular[] = { 0,1,1,1 };
	GLfloat diffuse[] = { .7,1,.7,1 };
	GLfloat shininess[] = { 50 };
	matprop(ambient, diffuse, specular, shininess);
	GLfloat lightIntensity[] = { .7,.7,.7,1 };
	GLfloat light_position[] = { 2,6,1.5,0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
	//left wall of compound
	glPushMatrix();
	glPushMatrix();
	glTranslated(-4, 0, -1 - .04);
	glRotated(90.0, 0, 0, 1);
	wall2(0.02);
	glPopMatrix();
	//right wall of compound
	glPushMatrix();
	glTranslated(8, 0, -1 - .02);
	glRotated(90.0, 0, 0, 1);
	wall2(0.02);
	glPopMatrix();
	//back wall of compound
	glPushMatrix();
	glTranslated(2, .8, -1);
	glRotated(-90, 1, 0, 0);
	glScaled(12, .02 * 4, 1.6);
	glutSolidCube(1.0);
	glPopMatrix();
	//front whole wall of compound
	glPushMatrix();
	glTranslated(2, .8, 6 - .08);
	glRotated(-90, 1, 0, 0);
	glScaled(12, .02 * 4, 1.6);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();
	GLfloat ambient2[] = { 0,1,0,1 };
	GLfloat specular2[] = { 1,1,1,1 };
	GLfloat diffuse2[] = { .2,.6,0.1,1 };
	GLfloat shininess2[] = { 50 };
	matprop(ambient2, diffuse2, specular2, shininess2);
	//floor
	glPushMatrix();
	glTranslated(-4, -0.05, -1);
	glScaled(3, 3, 1.7);
	wall(0.08);
	glPopMatrix();
	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glTranslated(-1.3, 0, 1.9);
	gate();
	glPopMatrix();
	
	//sgate();
	glFlush();
}



void gate(void)
{
	int i;
	GLfloat ambient1[] = { 1,.5,1,1 };
	GLfloat specular1[] = { 1,1,1,1 };
	GLfloat diffuse1[] = { .5,.5,.5,1 };
	GLfloat mat_shininess[] = { 120 };
	matprop(ambient1, diffuse1, specular1, mat_shininess);
	glPushMatrix();
	//if flag mgo=1 the open the main gate
	if (mgo == 1)
		glTranslated(1.5, 0, 0);
	glTranslated(-1.3, 0, 6);
	//top frame of the main gate
	glPushMatrix();
	glTranslated(0, 1.5, 0);
	glScaled(1.7, .04, .04);
	glutSolidCube(1);
	glPopMatrix();
	//bottom frame of main gate
	glPushMatrix();
	glTranslated(0, .05, 0);
	glScaled(1.7, .04, .04);
	glutSolidCube(1);
	glPopMatrix();
	//left frame of the main gate
	glPushMatrix();
	glTranslated(-.8, .75, 0);
	glScaled(.04, 1.5, .04);
	glutSolidCube(1);
	glPopMatrix();
	//right frame of the main gate
	glPushMatrix();
	glTranslated(.8, .75, 0);
	glScaled(.04, 1.5, .04);
	glutSolidCube(1);
	glPopMatrix();
	//horizantal pipes of the main gate
	for (i = 1;i <= 3;i++)
	{
		glPushMatrix();
		glTranslated(-.85, .4 * i, 0);
		glRotated(90, 0, 1, 0);
		gluCylinder(Cylinder, .02, .02, 1.7, 32, 32);
		glPopMatrix();
	}
	//vertical strips of the main gate
	for (i = 1;i <= 5;i++)
	{
		glPushMatrix();
		glTranslated(-.9 + .3 * i, .75, 0);
		glScaled(.2, 1.5, .02);
		glutSolidCube(1);
		glPopMatrix();
	}
	glPopMatrix();
}


void setupOrthographicProjection() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, w, h, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void renderText(float x, float y, void* font, const char* string) {
	glRasterPos2f(x, y);
	for (const char* c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

int SCORE = 0;
int LEVEL = 1;
int ATTEMPTS = 1;
int TIME = 120;
int initial_time = 120;
int points = 1;

void updateScore(int points) {
	//SCORE += points;
}

void updateTimer() {
	time_t currentTime = time(NULL);
	TIME = initial_time - (currentTime - startTime);
	if (TIME <= 0) {
		// Game over!
	}
}

void drawHUD() {
	setupOrthographicProjection();
	
	int textWidth = 0;
	//int levelWidthScore = 0;
	//int attemptsWidthScore = 0;

	// Set the color to white
	glColor3f(1.0f, 1.0f, 1.0f);
	// Scale the text up by a factor of 2
	//glScalef(3.0f, 3.0f, 1.0f);
		
	// Set the color to white
	glColor3f(1.0f, 1.0f, 1.0f);

	// Render the score board at the top left corner of the screen
	char scoreString[32];
	sprintf(scoreString, "Score: %d", SCORE);
	textWidth = glutBitmapLength(GLUT_BITMAP_8_BY_13, (unsigned char*)scoreString);
	renderText(10.0f, 10.0f, GLUT_BITMAP_8_BY_13, scoreString);
	
	// Set the color to white
	glColor3f(1.0f, 1.0f, 1.0f);

	// Render the level information
	char levelString[32];
	sprintf(levelString, "Level: %d", LEVEL);
	textWidth = glutBitmapLength(GLUT_BITMAP_8_BY_13, (unsigned char*)levelString);
	renderText(10.0f, 30.0f, GLUT_BITMAP_8_BY_13, levelString);

	// Render the attempts information
	char attemptsString[32];
	sprintf(attemptsString, "Attempts: %d", ATTEMPTS);
	textWidth = glutBitmapLength(GLUT_BITMAP_8_BY_13, (unsigned char*)attemptsString);
	renderText(10.0f, 50.0f, GLUT_BITMAP_8_BY_13, attemptsString);

	/* I TRIED TO DRAW A BLACK BACKGROUND BOX BEHIND THE SCOREBOARD DISPLAY
	// Set the color to black
	glColor3f(0.0f, 0.0f, 0.0f);

	// Draw a quad to fill the background behind the score
	glBegin(GL_QUADS);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(textWidth  + 20.0f, 0.0f);
	glVertex2f(textWidth  + 20.0f, 20.0f);
	glVertex2f(0.0f, 20.0f);
	glEnd();

	// Set the color to white
	glColor3f(1.0f, 1.0f, 1.0f);
	*/

	// Render the timer at the top right corner of the screen
	char timerString[32];
	int minutes = TIME / 60;
	int seconds = TIME % 60;
	sprintf(timerString, "%02d:%02d", minutes, seconds);
	int textWidthTimer = glutBitmapLength(GLUT_BITMAP_8_BY_13, (unsigned char*)timerString);
	renderText(w - 10.0f - textWidthTimer, 10.0f, GLUT_BITMAP_8_BY_13, timerString);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}


void display(void)
{
	// Draw 3D scene
	time(&ltime); // Get time
	newtime = localtime(&ltime); // Convert to local time
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluLookAt(view[0], view[1], view[2], look[0], look[1], look[2], 0.0, 1.0, 0.0);
	earth();
	compound();
	//house();

	// Update the score and timer
	updateScore(points);
	updateTimer();
	// Draw HUD on top of 3D scene
	drawHUD();

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		//to move the camera along -ve x axis
	case '4':
		view[0] -= .1;
		glutPostRedisplay();
		break;
		//to move the camera along +ve x axis
	case '6':
		view[0] += .1;
		glutPostRedisplay();
		break;
		//to move the camera along +ve y axis
	case '7':
		view[1] += .1;
		glutPostRedisplay();
		break;
		//to move the camera along -ve y axis
	case '1':
		if (view[1] > 1.9)
			view[1] -= .1;
		glutPostRedisplay();
		break;
		//to move the camera along -ve z axis
	case '8':
		view[2] -= .1;
		glutPostRedisplay();
		break;
		//to move the camera along +ve z axis
	case 'S':
	case 's':
		flag *= -1;
		glutPostRedisplay();
		break;
		//to move the look position along +ve x axis
	case 'r':
	case 'R':
		look[0] += .1;
		break;
		//to move the look position along -ve x axis
	case 'l':
	case 'L':
		look[0] -= .1;
		break;
		//to move the look position along +ve y axis
	case 'U':
	case 'u':
		look[1] += .1;
		break;
		//to move the look position along -ve y axis
	case 'D':
	case 'd':
		look[1] -= .1;
		break;
		//to move the look position along +ve z axis
	case 'f':
	case 'F':
		look[2] += .1;
		break;
		//to move the look position along -ve z axis
	case 'h':
	case 'H':
		if (sgo == 0)
			sgo = 50;
		else
			sgo = 0;
		break;
		//inside view
	case 'i':
	case 'I':
		view[0] = 2.8;
		view[1] = 2;
		view[2] = 4.8;
		look[0] = 2.8;
		look[1] = 2;
		look[2] = 1;
		break;
		//top view
	case 'T':
	case 't':
		view[0] = 6;
		view[1] = 12;
		view[2] = 10;
		look[0] = 2;
		look[1] = 4;
		look[2] = 2;
		break;
		//front view
	case 'j':
	case 'J':
		view[0] = 2;
		view[1] = 2;
		view[2] = 12.9;
		look[0] = 3;
		look[1] = 2;
		look[2] = 3;
		break;
		//back view
	case 'k':
	case 'K':
		view[0] = 1;
		view[1] = 6;
		view[2] = -7;
		look[0] = 2;
		look[1] = 4;
		look[2] = 2;
		break;
	}
}
void mySpecialKeyFunc(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		if (speed < 25.0) {
			speed += 5;
		}
		break;
	case GLUT_KEY_DOWN:
		if (speed > 0) {
			speed -= 5;
		}
		break;
	}
}


void main(int argc, char** argv)
{
	glutInit(&argc, argv);//to initialize the glut library
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(w, h); //initial position of the topleft corner of the window in pixels 
	glutInitWindowPosition(0, 0); // Requests a display with the properties in mode
	glutCreateWindow("er"); //A window on the display. The string title can be used to label the window
	myinit();
	glutDisplayFunc(display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(mySpecialKeyFunc);
	glutFullScreen();//to see o/p in full screen on monitor
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);//smooth shaded
	glEnable(GL_DEPTH_TEST);//to remove hidden surface
	glEnable(GL_NORMALIZE);//to make normal vector to unit vector
	glClearColor(0, .3, .8, 0);
	glViewport(0, 0, w, h);
	glutMainLoop();
}