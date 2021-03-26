#include "cgvFootball.h"
#include <iostream>
#include "cgvTexture.h"

void cgvFootball::render(std::string mode) {

	GLfloat color_piece[] = { 0,0.25,0 };
	GLfloat color_piece_top[] = { 0,0.3,0 };

	GLfloat selected_color[] = { 1,1,0,1.0 };


// TODO: Section A. Add the required code to render in selection mode. Use glColor instead of glMaterial. 
	// TODO: Section A. Add the required code to render the selected box as yellow (selected_color). 
	
	if (mode == "DISPLAY") {
		if (selected) {
			glMaterialfv(GL_FRONT, GL_EMISSION, selected_color);
			glPushMatrix();
			glTranslatef(vX, 0, vZ);
			glTranslatef(0, -1.8, 2);
			spheres();
			glPopMatrix();
		}
		else {
			glPushMatrix();
			char file3[] = "football.jpg";
			cgvTexture tex3(file3);
			tex3.apply();
			glPushMatrix();
			glTranslatef(vX, 0, vZ);
			glTranslatef(0, -1.8, 2);
			spheres();
			glPopMatrix();
		}
	}
	else {
		glColor3ubv(color_as_ID);
		glPushMatrix();
		glTranslatef(vX, 0, vZ);
		glTranslatef(0, -1.8, 2);
		spheres();
		glPopMatrix();
	}

}

void cgvFootball::select(GLubyte c[3]) {
	// TODO: Section A. Add the required code to check and select the appropriate box. 
	int cont = 0;
	selected = false;
	for (int i = 0; i < 3;i++) {//check in a loop all elements of color_as_ID
		if (c[i]==color_as_ID[i]) {
			cont++;
		}
	}
	if (cont == 3) {//in case the 3 elements match then is selected
		selected = true;
	}
}

void cgvFootball::spheres() {//primitive sphere
	
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluSphere(sphere, 0.5, 20, 20);
	glEndList();
	gluDeleteQuadric(sphere);
	glPopMatrix();
}

void cgvFootball::move(float unitsx, float unitsy) {
	if (selected) {
		vZ = vZ + unitsx;
		vX = vX - unitsy;
	}
}
