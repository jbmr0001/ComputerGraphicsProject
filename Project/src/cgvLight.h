#pragma once

#if defined(__APPLE__) && defined(__MACH__)

#include <GLUT/glut.h>

#include <OpenGL/gl.h>

#include <OpenGL/glu.h>

#else

#include <GL/glut.h>

#endif

#include "cgvPoint3D.h"
#include "cgvColor.h"

class cgvLight {

	protected:
		// Attributes
		unsigned int idLight; // light identifier (GL_LIGHT0 to GL_LIGHT7)

		cgvPoint3D position; // light position

		cgvColor4f ambientColor; // ambient color of the light
		cgvColor4f diffuseColor; // diffuse color of the light
		cgvColor4f specularColor; // specular color of the light

		double atten_a0; // attenuation coefficient a0
		double atten_a1; // attenuation coefficient a1
		double atten_a2; // attenuation coefficient a2

		// parameters to define a spotlight
		cgvPoint3D spotlight_direction;
		double spotlight_angle;
		double spotlight_exponent;

		bool on; // Indicate whether the light is on or not. 

		// Methods 

	public:
		// Default constructors and destructor
		cgvLight();

		// Other constructors
		// point light source
		cgvLight(const unsigned int _idLight,
			     const cgvPoint3D & _position, 
			     const cgvColor4f & cAmb, const cgvColor4f & cDif, const cgvColor4f & cEsp,
				 const double a0, const double a1, const double a2);

		// spotlight
		cgvLight(const unsigned int _idLight,
			     const cgvPoint3D & _position, 
			     const cgvColor4f& cAmb, const cgvColor4f& cDif, const cgvColor4f& cEsp,
				 const double a0, const double a1, const double a2,
								 const cgvPoint3D& spotlight_dir, const double spotlight_ang, const double spotlight_exp);

		// Methods
		cgvPoint3D & getPosition(void); // it returns the position of the light
		void setPosition(cgvPoint3D pos); // set the position of the light 

		void set(const cgvColor4f& cAmb, const cgvColor4f& cDif, const cgvColor4f& cEsp);
		void setAmbient(const cgvColor4f& cAmb);
		void setDiffuse(const cgvColor4f& cDif);
		void setSpecular(const cgvColor4f& cEsp);
		cgvColor4f& getAmbient(void);
		cgvColor4f& getDiffuse(void);
		cgvColor4f& getSpecular(void);

		void setAttenuation(double a0, double a1, double a2);
		void getAttenuation(double & a0, double & a1, double & a2);

		void switchOn(void);
		void switchOff(void);
		unsigned int is_On(void);

		void apply(void);
};


