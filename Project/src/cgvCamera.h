#ifndef __CGVCAMERA
#define __CGVCAMERA

#if defined(__APPLE__) && defined(__MACH__)

#include <GLUT/glut.h>

#include <OpenGL/gl.h>

#include <OpenGL/glu.h>

#else

#include <GL/glut.h>

#endif

#include "cgvPoint3D.h"

typedef enum {
	CGV_PARALLEL,
	CGV_PERSPECTIVE
} cameraType;

class cgvCamera {
public:
	cameraType camType;
	int n = 0;
	protected:
		// attributes
		// Camera Type
		
		
		// view plane: parameters parallel projection and frustum
		GLdouble xwmin, xwmax, ywmin, ywmax;

		// perspective projection parameters
		double fovy, aspect;

		// distances of near and far planes
		GLdouble znear, zfar;

		// point of view
		cgvPoint3D PV;

		// view reference point	
		cgvPoint3D rp;

		// up vector 
		cgvPoint3D up;

		// zoom factor
		double currentZoom;


		// Methods

	public:
		// Default Constructors and destructor
		cgvCamera() :xwmin(-1), xwmax(1), ywmin(-1), ywmax(1), znear(0.1), zfar(100),
			PV(cgvPoint3D(-1, 0, 0)), rp(cgvPoint3D(0,0,0)), up(cgvPoint3D(0,1,0)) {}
		cgvCamera(cgvPoint3D _PV, cgvPoint3D _rp, cgvPoint3D _up);	
		~cgvCamera();


		// Methods
		// Defining the camera parameters
		void setCameraParameters(cgvPoint3D _PV, cgvPoint3D _rp, cgvPoint3D _up);
		void getCameraParameters(cgvPoint3D& _PV, cgvPoint3D& _rp, cgvPoint3D& _up);

		// Defining the projection
		void setParallelParameters(double _xwhalfdistance, double _ywhalfdistance,
			double _znear, double _zfar);
		void getParallelParameters(double& _xwmin, double& _xwmax, double& _ywmin, double& _ywmax,
			double& _znear, double& _zfar);

		void setPerspParameters(double _fovy, double _aspect, double _znear, double _zfar);
		void getPerspParameters(double& _fovy, double& _aspect, double& _znear, double& _zfar);

		// Apply the camera
		void apply(); // apply the view and projection transformations to the object of the scene. 


		void zoom(double factor);
		void nearp(double units);
		void move();
		                    

		cgvCamera &operator=(const cgvCamera &cam) {
			this->xwmin = cam.xwmin; 
			this->xwmax = cam.xwmax; 
			this->ywmin = cam.ywmin;
			this->ywmax = cam.ywmax;

			this->znear = cam.znear; 
			this->zfar = cam.zfar; 

			this->PV = cam.PV;

			this->rp = cam.rp;

			this->up = cam.up; 
			return *this; 
		}


};

#endif

