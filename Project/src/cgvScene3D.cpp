#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "cgvScene3D.h"
#include "cgvLight.h"
#include "cgvMaterial.h"
#include "cgvTexture.h"
#include "cgvFootball.h"

// Constructor methods -----------------------------------

cgvScene3D::cgvScene3D () {
	axes = true;

	diffuseCoeficient = 0.5;
	specularCoeficient = 0.5;
	phongExponent = 120.0;
	x_axis = 3.0;
	y_axis = 1.0;

	Scene[0] = 1;
	Scene[1] = 2;
	Scene[2] = 3;
	Scene[3] = 4;
	Scene[4] = 5;

	Scene_Name[0] = (char *)"White Background";
	Scene_Name[1] = (char*) "Practise 4";
	Scene_Name[2] = (char *)"Ice";
	Scene_Name[3] = (char *)"Night";
	Scene_Name[4] = (char *)"Day";

	selectedScene = 5; 

	bodyAngle = 0;
	thigh1Angle = 0;
	thigh2Angle = 0;
	tibia1Angle = 0;
	tibia2Angle = 0;
	foot1Angle = 0;
	foot2Angle = 0;

	ballsNumber = 0;
	float* col;
	for (int i = 0; i < 100;i++) {
				ballsNumber++;
				GLubyte c[3] = { 0,0,ballsNumber };
				balls.push_back(c);
	}
}

cgvScene3D::~cgvScene3D() {

}

// Public methods ----------------------------------------

void
cgvScene3D::set(int scene) {
	selectedScene = scene;
}

void draw_axes(void) {
  GLfloat red[]={1,0,0,1.0};
  GLfloat green[]={0,1,0,1.0};
  GLfloat blue[]={0,0,1,1.0};

	glBegin(GL_LINES);
    glMaterialfv(GL_FRONT,GL_EMISSION,red);
		glVertex3f(1000,0,0);
		glVertex3f(-1000,0,0);

    glMaterialfv(GL_FRONT,GL_EMISSION,green);
		glVertex3f(0,1000,0);
		glVertex3f(0,-1000,0);

    glMaterialfv(GL_FRONT,GL_EMISSION,blue);
		glVertex3f(0,0,1000);
		glVertex3f(0,0,-1000);
	glEnd();
}

void draw_quad(float div_x,float div_z) {//METHOD TO DRAW WITH MORE REALISM

	float x, z, x_max, z_max,increase_x, increase_z;
	x_max = 5.0;//maxium x coordinate
	z_max = 5.0;//maxium z coordinate
	increase_x = x_max / div_x;//valor to increase x coordinate in the loop
	increase_z = z_max / div_z;//valor to increase z coordinate in the loop
	//loop to get each coordinate
	for (float i = 0.0; i < x_max;i=i+increase_x) {
		for (float j = 0.0; j < z_max;j=j+increase_z) {
			glNormal3f(0, 1, 0);
			glBegin(GL_QUADS);
			glVertex3f(i, 0.0, j);
			glVertex3f(i, 0.0, j+increase_z);
			glVertex3f(i+increase_x, 0.0, j+increase_z);
			glVertex3f(i+increase_x, 0.0, j);
			glEnd();
			
		}	
	}
}
 
void draw() {//METHOD TO DRAW THE FLOOR WITH TILED TEXTURE
	float x, z, x_max, z_max, increase_x, increase_z;
	x_max = 30.0;//maxium x coordinate
	z_max = 30.0;//maxium z coordinate
	increase_x = 5.0;//valor to increase x coordinate in the loop
    increase_z = 5.0;//valor to increase z coordinate in the loop

	//loop to get each coordinate
	for (float i = -30.0; i < x_max; i = i + increase_x) {
		for (float j = -30.0; j < z_max; j = j + increase_z) {
			glNormal3f(0, 1, 0);
			glBegin(GL_QUADS);
			glTexCoord2i(0, 0); glVertex3f(i, -2.25, j);
			glTexCoord2i(0, 1); glVertex3f(i, -2.25, j+increase_z);
			glTexCoord2i(1, 1); glVertex3f(i+increase_x, -2.25, j+increase_z);
			glTexCoord2i(1, 0); glVertex3f(i + increase_x, -2.25, j);

			glEnd();
		}
	}
}
///MODEL
void cgvScene3D::view_model(std::string mode) {
	GLfloat color_piece[] = { 0,0.25,0 };
	GLfloat color_piece_top[] = { 0,0.3,0 };

	GLfloat selected_color[] = { 1,1,0,1.0 };
	
	if (mode == "DISPLAY") {
		if (selected) {
			glMaterialfv(GL_FRONT, GL_EMISSION, selected_color);
			glPushMatrix();
			glTranslatef(posX, 0, posZ);
			glRotatef(angleY, 0, 1, 0);
			glRotatef(angleX, 1, 0, 0);// body
			body();
			view_legs();
			view_hands();
			glPopMatrix();
		}
		else {
			glPushMatrix();
			glTranslatef(posX, 0, posZ);
			glRotatef(angleY, 0, 1, 0);
			glRotatef(angleX, 1, 0, 0);// body
			body();
			view_legs();
			view_hands();
			glPopMatrix();
		}
	}
	else {
		color_as_ID[0] = 11;
		color_as_ID[1] = 11;
		color_as_ID[2] = 11;
		glColor3ubv(color_as_ID);
		glPushMatrix();
		glTranslatef(posX, 0, posZ);
		glRotatef(angleY, 0, 1, 0);
		glRotatef(angleX, 1, 0, 0);// body
		body();
		view_legs();
		view_hands();
		glPopMatrix();
	}

}

void cgvScene3D::view_hands() {
		glPushMatrix();//arm1
		glTranslatef(1.0, 1.2, 0);
		glRotatef(15, 0, 0, 1);
			glRotatef(arm1Angle, 1, 0, 0);
			arm();
				glPushMatrix(); //elbow1
				glTranslatef(0, -1.0, 0);
				glRotatef(-15, 0, 0, 1);
				glRotatef(elbow1Angle, 1, 0, 0);
				elbow();
					glPushMatrix(); //hand1
					glTranslatef(0, -1.0, 0.0);
					glRotatef(hand1Angle, 1, 0, 0);
					hand();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
	
	glPushMatrix();//arm2
	glTranslatef(-1.0, 1.2, 0);
	glRotatef(-15, 0, 0, 1);
		glRotatef(arm2Angle, 1, 0, 0);
		
		arm();
			glPushMatrix(); //elbow2
			glTranslatef(0, -1.0, 0);
			glRotatef(15, 0, 0, 1);
			glRotatef(elbow2Angle, 1, 0, 0);
			elbow();
				glPushMatrix(); //hand2
				glTranslatef(0, -1.0, 0.0);
				glRotatef(hand2Angle, 1, 0, 0);
				hand();
		glPopMatrix();
	glPopMatrix();
glPopMatrix();
}

void cgvScene3D::view_legs() {
	
		glPushMatrix();//thigh1
		glTranslatef(0.4, 0.1, 0);
		glRotatef(thigh1Angle, 1, 0, 0);
		thigh();
			glPushMatrix(); //tibia1
			glTranslatef(0, -1.1, 0);
			glRotatef(tibia1Angle, 1, 0, 0);
			tibia();
					glPushMatrix(); //foot1
					glTranslatef(0, -1.0, 0.0);
					glRotatef(foot1Angle, 1, 0, 0);
					foot();
				glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	
		glPushMatrix();//thigh2
		glTranslatef(-0.4, 0.1, 0);
		glRotatef(thigh2Angle, 1, 0, 0);
		thigh();
			glPushMatrix(); //tibia2
			glTranslatef(0, -1.1, 0);
			glRotatef(tibia2Angle, 1, 0, 0);
			tibia();
				glPushMatrix(); //foot2
				glTranslatef(0, -1.0, 0.0);
				glRotatef(foot2Angle, 1, 0, 0);
				foot();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	
}
/////////////PARTS OF THE MODEL////////////////
void sphere() {//primitive sphere
	glPushMatrix();
	static GLUquadric* quad = gluNewQuadric();
	glTranslatef(0, 1, 0);
	gluSphere(quad, 1, 100, 20);
	glPopMatrix();
}

void cgvScene3D::body() {
	glPushMatrix();
	sphere();//head
	glPushMatrix();
	glTranslatef(0, 0.5, 0.9);//nose
	glScalef(0.25, 0.4, 0.25);
	sphere();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.6, 0.8, 0.5);//eye1
	glScalef(0.3, 0.3, 0.3);
	sphere();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.6, 0.8, 0.5);//eye2
	glScalef(0.3, 0.3, 0.3);
	sphere();
	glPopMatrix();
}

void cgvScene3D::thigh() {
	glPushMatrix();
	glScalef(0.4, -0.55, 0.4);
	sphere();
	glPopMatrix();
}

void cgvScene3D::tibia() {
	glPushMatrix();
	glScalef(0.3, -0.5, 0.3);
	sphere();
	glPopMatrix();
}
void cgvScene3D::foot() {
	glPushMatrix();
	glScalef(0.3, -0.2, 0.4);
	sphere();
	glPopMatrix();
}

void cgvScene3D::arm() {
	glPushMatrix();
	glScalef(0.4, -0.6, 0.5);
	sphere();
	glPopMatrix();
}
void cgvScene3D::elbow() {
	glPushMatrix();
	glScalef(0.3, -0.5, 0.4);
	sphere();
	glPopMatrix();
}
void cgvScene3D::hand() {
	glPushMatrix();
	glScalef(0.2, -0.2, 0.2);
	sphere();
	glPopMatrix();
}

////////FUNCTIONS//////////

void cgvScene3D::assignSelection(GLubyte _c[3]) {
	int cont = 0;
	selected = false;
	////////MODEL SELECTION///////////////
	for (int i = 0; i < 3; i++) {//check in a loop all elements of color_as_ID
		if (_c[i] == color_as_ID[i]) {
			cont++;
		}
	}
	if (cont == 3) {//in case the 3 elements match then is selected
		selected = true;
	}

	/////////FOOTBALLS SELECTION///////////////
	for (int j = 0;j< balls.size(); j++) {
		balls[j].select(_c);
	}
}

void cgvScene3D::render(std::string mode) {
	// create the model
	glPushMatrix(); // store the model matrices

	  // draw the axes
	if (axes) draw_axes();

	//light
	cgvPoint3D pos(1.0, 1.0, 1.0);
	cgvColor4f ambient(0.0, 0.0, 0.0, 1.0);
	cgvColor4f diffuse(1.0, 1.0, 1.0, 1.0);
	cgvColor4f specular(1.0, 1.0, 1.0, 1.0);
	cgvLight light(GL_LIGHT0, pos, ambient, diffuse, specular, 1.0, 0.0, 0.0);
	light.apply();



	cgvPoint3D spotlightPos(x_axis, y_axis, 1.0);
	cgvPoint3D dir(0.0, -1.0, 0.0);
	cgvLight light2(GL_LIGHT1, spotlightPos, ambient, diffuse, specular, 1.0, 0.0, 0.0, dir, 45.0, 2.5);
	light2.apply();

	if (selectedScene==1) {//white background
		cgvColor4f Ka(0.65, 0.0, 0.0);
		cgvColor4f Kb(diffuseCoeficient, 0.0, 0.0);
		cgvColor4f Kc(specularCoeficient, 0.0, 0.0);
		cgvMaterial mat(Ka, Kb, Kc, phongExponent);
		mat.apply();
	}
	else if (selectedScene==2) {//practise 4

		cgvColor4f Ka(0.65, 0.0, 0.0);
		cgvColor4f Kb(diffuseCoeficient, 0.0, 0.0);
		cgvColor4f Kc(specularCoeficient, 0.0, 0.0);
		cgvMaterial mat(Ka, Kb, Kc, phongExponent);
		mat.apply();
		draw_quad(50, 50);
	}else if (selectedScene == 3) { //ice

		cgvColor4f Ka(0.15, 0.0, 1.0);
		cgvColor4f Kb(diffuseCoeficient, 0.0, 0.0);
		cgvColor4f Kc(specularCoeficient, 0.0, 0.0);
		cgvMaterial mat(Ka, Kb, Kc, phongExponent);
		mat.apply();
		char file[] = "ice.jpg";
		cgvTexture tex(file);
		tex.apply();

		draw();


		char file3[] = "sky.jpg";
		cgvTexture tex3(file3);
		tex3.apply();

		GLUquadricObj* sphere = NULL;
		sphere = gluNewQuadric();
		gluQuadricDrawStyle(sphere, GLU_FILL);
		gluQuadricTexture(sphere, TRUE);
		gluQuadricNormals(sphere, GLU_SMOOTH);
		gluSphere(sphere, 20.0, 20, 20);
		glEndList();
		gluDeleteQuadric(sphere);

	}
	else if (selectedScene == 4) {//night
		 
		cgvColor4f Ka(0.10, 0.0, 0.0);
		cgvColor4f Kb(diffuseCoeficient, 0.0, 0.0);
		cgvColor4f Kc(specularCoeficient, 0.0, 0.0);
		cgvMaterial mat(Ka, Kb, Kc, phongExponent);
		mat.apply();
		draw();

		light2.switchOff();
		light2.apply();

		char file3[] = "night.jpg";
		cgvTexture tex3(file3);
		tex3.apply();
		//sky sphere
		GLUquadricObj* sphere = NULL;
		sphere = gluNewQuadric();
		gluQuadricDrawStyle(sphere, GLU_FILL);
		gluQuadricTexture(sphere, TRUE);
		gluQuadricNormals(sphere, GLU_SMOOTH);
		gluSphere(sphere, 20.0, 20, 20);
		glEndList();
		gluDeleteQuadric(sphere);

	}
	if (selectedScene == 5) { //day
		light.apply();
		char file[] = "grass.jpg";
		cgvTexture tex(file);
		tex.apply();

		cgvColor4f Ka(0.65, 0.0, 0.0);
		cgvColor4f Kb(diffuseCoeficient, 0.0, 0.0);
		cgvColor4f Kc(specularCoeficient, 0.0, 0.0);
		cgvMaterial mat(Ka, Kb, Kc, phongExponent);
		mat.apply();
		draw();

		char file3[] = "sky.jpg";
		cgvTexture tex3(file3);
		tex3.apply();
		//sky sphere
		GLUquadricObj* sphere = NULL;
		sphere = gluNewQuadric();
		gluQuadricDrawStyle(sphere, GLU_FILL);
		gluQuadricTexture(sphere, TRUE);
		gluQuadricNormals(sphere, GLU_SMOOTH);
		gluSphere(sphere, 20.0, 20, 20);
		glEndList();
		gluDeleteQuadric(sphere);
	}
	glPushMatrix();
	view_model(mode);
	glPopMatrix();
		//////////FOOTBALLS RENDER/////
		int num = 0;
		for (int i = 0; i < ballsX; i++) {
			for (int j = 0; j < ballsY;j++) {
				for (int k = 0; k < ballsZ;k++) {
					glPushMatrix();
					glTranslatef(i * 2, j, k * 2);
					balls[num].render(mode);
				    glPopMatrix();
					num++;
					
				}
			}
		}
	  cgvMaterial defaultMat(cgvColor4f(0.2, 0.2, 0.2, 1), cgvColor4f(0.8, 0.8, 0.8, 1), cgvColor4f(0.0, 0, 0, 1), 0);
	  defaultMat.apply();

	glPopMatrix (); // restore the modelview matrix 
  
}

//rotation methods
void cgvScene3D::rotateBody(float angle) { angleX = (float)((int)(angleX + angle) % 360); }
void cgvScene3D::rotateThigh1(float angle) { thigh1Angle = (float)((int)(thigh1Angle + angle) % 360); }
void cgvScene3D::rotateThigh2(float angle) { thigh2Angle = (float)((int)(thigh2Angle + angle) % 360); }
void cgvScene3D::rotateTibia1(float angle) { tibia1Angle = (float)((int)(tibia1Angle + angle) % 360); }
void cgvScene3D::rotateTibia2(float angle) { tibia2Angle = (float)((int)(tibia2Angle + angle) % 360); }
void cgvScene3D::rotateFoot1(float angle) { foot1Angle = (float)((int)(foot1Angle + angle) % 360); }
void cgvScene3D::rotateFoot2(float angle) { foot2Angle = (float)((int)(foot2Angle + angle) % 360); }


void cgvScene3D::rotateArm1(float angle) { arm1Angle = (float)((int)(arm1Angle + angle) % 360); }
void cgvScene3D::rotateArm2(float angle) { arm2Angle = (float)((int)(arm2Angle + angle) % 360); }
void cgvScene3D::rotateElbow1(float angle) { elbow1Angle = (float)((int)(elbow1Angle + angle) % 360); }
void cgvScene3D::rotateElbow2(float angle) { elbow2Angle = (float)((int)(elbow2Angle + angle) % 360); }
void cgvScene3D::rotateHand1(float angle) { hand1Angle = (float)((int)(hand1Angle + angle) % 360); }
void cgvScene3D::rotateHand2(float angle) { hand2Angle = (float)((int)(hand2Angle + angle) % 360); }
//ROTATE FOOTBALL
void cgvScene3D::moveFootball(float unitsx, float unitsy) {
	for (int i = 0; i < balls.size();i++) {
		balls[i].move(unitsx, unitsy);
	}
}
//MOVE DOLL
void cgvScene3D::move(float unitsx,float unitsy) {
	posX = posX+unitsx;
	posZ = posZ+unitsy;
}
//ROTATE DOLL
void cgvScene3D::rotateModel(float x,float y) {
	if (selected) {
		if (x < 0) {
			angleY = angleY + 10;
		}
		else {
			angleY = angleY - 10;
		}
	}
}

///////X AXIS FOOTBALLS////////////
void cgvScene3D::subX() {
	if (ballsX > 0.0) {//to avoid negative values
		ballsX--;
	}

}
void cgvScene3D::addX() {
	ballsX++;
}
////////Y AXIS FOOTBALLS///////
void cgvScene3D::subY() {
	if (ballsY > 0.0) {//to avoid negative values
		ballsY--;
	}
}
void cgvScene3D::addY() {
	ballsY++;
}
////////Z AXIS FOOTBALLS///////
void cgvScene3D::subZ() {
	if (ballsZ > 0.0) {//to avoid negative values
		ballsZ--;
	}
}
void cgvScene3D::addZ() {
	ballsZ++;
} 