#ifndef __CGVMATERIAL
#define __CGVMATERIAL

#if defined(__APPLE__) && defined(__MACH__)

#include <GLUT/glut.h>

#include <OpenGL/gl.h>

#include <OpenGL/glu.h>

#else

#include <GL/glut.h>

#endif

#include "cgvColor.h"

class cgvMaterial {

	protected:
		// attributes
		cgvColor4f Ka; // ambient coefficient 
		cgvColor4f Kd; // diffuse coefficient
		cgvColor4f Ks; // specular coefficient
		double   Ns; // Phong exponent
		
		// Methods

	public:
		// Default constructor and destructor
		cgvMaterial();
		~cgvMaterial();

		// Other constructors
		cgvMaterial(const cgvMaterial& m);	//copy constructor
		cgvMaterial(cgvColor4f _Ka, cgvColor4f _Kd, cgvColor4f _Ks, double _Ns);

		// Methods 
		void apply(void);

		void set(cgvColor4f _Ka, cgvColor4f _Kd, cgvColor4f _Ks, double _Ns);
		double getNs() { return Ns; };
};

#endif

