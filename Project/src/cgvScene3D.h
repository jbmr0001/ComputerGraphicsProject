#ifndef __CGVSCENE3D
#define __CGVSCENE3D

#if defined(__APPLE__) && defined(__MACH__)

#include <GLUT/glut.h>

#include <OpenGL/gl.h>

#include <OpenGL/glu.h>

#else

#include <GL/glut.h>

#endif

#include "cgvLight.h"
#include <iostream>
#include <vector>
#include "cgvFootball.h"


#define nbScenes 5

class cgvScene3D {
	public:
		int Scene[nbScenes];
		char *Scene_Name[nbScenes];

		bool selected = false;


		int ballsX = 1;
		int ballsY = 1;
		int ballsZ = 1;

		std::vector<cgvFootball> balls;


		int ballsNumber;
	
	protected:
		// Attributes

		bool axes;
		int selectedScene;

		float bodyAngle;
		float thigh1Angle;
		float tibia1Angle;
		float foot1Angle;
		float thigh2Angle;
		float tibia2Angle;
		float foot2Angle;


		float arm1Angle;
		float elbow1Angle;
		float hand1Angle;
		float arm2Angle;
		float elbow2Angle;
		float hand2Angle;

		float posX;
		float posZ;

		float angleX;
		float angleY;
		float angleZ;

		double diffuseCoeficient, specularCoeficient, phongExponent, x_axis,y_axis;

	public:
		// Public attributes

		// Default constructor and destructor
		cgvScene3D();
		~cgvScene3D();

		void set(int scene);

		// Static methods

		// Methods
		// method with the OpenGL calls to render the scene
    void render(std::string mode);
	void view_model(std::string mode);

	GLubyte color_as_ID[3];

	void assignSelection(GLubyte _c[3]);
	

	// method with the OpenGL calls to render the scen
	void view_legs();
	void view_hands();

	void body();
	void thigh();
	void tibia();
	void foot();
	void arm();
	void elbow();
	void hand();

	//////rotation 
	void rotateBody(float angle);
	void rotateThigh1(float angle);
	void rotateThigh2(float angle);
	void rotateTibia1(float angle);
	void rotateTibia2(float angle);
	void rotateFoot1(float angle);
	void rotateFoot2(float angle);
	void rotateArm1(float angle);
	void rotateArm2(float angle);
	void rotateElbow1(float angle);
	void rotateElbow2(float angle);
	void rotateHand1(float angle);
	void rotateHand2(float angle);
	void rotateModel(float distX, float distY);

	void moveFootball(float distX,float distY);
	void move(float distX, float distY);
	

	bool get_axes() {return axes;};
	void set_axes(bool _axes){axes = _axes;};
	void editDiffuse(double d) { diffuseCoeficient = diffuseCoeficient + d; };
	void editSpecular(double s) { specularCoeficient = specularCoeficient + s; };
	void editNs(double ns) { phongExponent = phongExponent + ns; };
	void editX(double x) { x_axis = x_axis + x; };
	void editY(double y) { y_axis = y_axis + y; };
	int getSelectedScene() { return selectedScene; };
	void setSelectedScene(int _selectedScene) { selectedScene = _selectedScene; };
	//footballs
	void addX();
	void addY();
	void addZ();
	void subX();
	void subY();
	void subZ();
};

#endif
