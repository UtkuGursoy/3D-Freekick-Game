#include "GUI.h"

GUI::GUI(GLuint tex) : GameObject(), m_texture(tex)
{
	scale(10);
}

GUI::GUI(GLuint tex, float x, float y) : GameObject(x, y, 0), m_texture(tex)
{
	scale(10);
}

void GUI::DRAW(float w, float h)
{
	glPushMatrix();
	//add some lighting normals for each vertex
	//draw the texture on the front
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, h, 0, -1, 1); // Sets to an orthographic projection mode so that the GUI can be displayed in 2D space.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	// glFrontFace(GL_CW); //use glFrontFace(GL_CW) to texture the other side - not needed here as we set this elsewhere
	glColor3f(0.8, 0.8, 0.8);


	// translates to object position.
	glTranslatef(transform.position.x, transform.position.y, 0);
	glRotatef(transform.rotation.x, 1, 0, 0);
	glRotatef(transform.rotation.y, 0, 1, 0);
	glRotatef(transform.rotation.z, 0, 0, 1);

	//binds the texture 
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// BUTTON
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-transform.scale.x / 2, -transform.scale.y / 2, 0);
	glTexCoord3f(1.0, 0.0, 0.0);
	glVertex3f(transform.scale.x / 2, -transform.scale.y / 2, 0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(transform.scale.x / 2, transform.scale.y / 2, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-transform.scale.x / 2, transform.scale.y / 2, 0);
	glEnd();

	

	glDisable(GL_TEXTURE_2D);



	glFlush();
}
void GUI::draw(float w, float h)
{
	glPushMatrix();
	//add some lighting normals for each vertex
	//draw the texture on the front
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, h, 0, -1, 1); // Sets to an orthographic projection mode so that the GUI can be displayed in 2D space.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	// glFrontFace(GL_CW); //use glFrontFace(GL_CW) to texture the other side - not needed here as we set this elsewhere
	glColor3f(0.8, 0.8, 0.8);
	

	// translates to object position.
	glTranslatef(transform.position.x, transform.position.y, 0);
	glRotatef(transform.rotation.x, 1, 0, 0);
	glRotatef(transform.rotation.y, 0, 1, 0);
	glRotatef(transform.rotation.z, 0, 0, 1);

	//binds the texture 
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// K���k �ubuklar
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-transform.scale.x / 2, -transform.scale.y / 2, 0);
	glTexCoord3f(1.0, 0.0, 0.0);
	glVertex3f(transform.scale.x / 2, -transform.scale.y / 2, 0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(transform.scale.x / 2, transform.scale.y / 2, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-transform.scale.x / 2, transform.scale.y / 2, 0);
	glEnd();

	// BAR
	glTranslatef(-value*transform.scale.x, 0, 0); // Bar is in the same place regardless of scale.
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-transform.scale.x / 32, -transform.scale.y / 1.5, 0.1);
	glTexCoord3f(0.01, 0.0, 0.0);
	glVertex3f(transform.scale.x / 32, -transform.scale.y / 1.5, 0.1);
	glTexCoord2f(0.01, 0.01);
	glVertex3f(transform.scale.x / 32, transform.scale.y / 1.5, 0.1);
	glTexCoord2f(0.0, 0.01);
	glVertex3f(-transform.scale.x / 32, transform.scale.y / 1.5, 0.1);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);

	
	
	glFlush();
}
