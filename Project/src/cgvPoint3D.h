/************************************************************************************************/
/* The class cgvPoint3D implements the functionality of the objects Point and Vector in 3D */
/************************************************************************************************/

#pragma once

#if defined(__APPLE__) && defined(__MACH__)

#include <GLUT/glut.h>

#include <OpenGL/gl.h>

#include <OpenGL/glu.h>

#else

#include <GL/glut.h>

#endif

#include <array>

#define IGV_EPSILON 0.000001 // for comparisons with 0

#ifndef __ENUM_XYZ
#define __ENUM_XYZ

typedef enum {
	X,
	Y,
	Z, 
	W
};
#endif

class cgvPoint3D {

    public:
	std::array<float, 3> c; // components x, y, z of a point or vector

	public:
		// Constructors
		cgvPoint3D(); 
		cgvPoint3D( const float& x, const float& y, const float& z );
		
		// Copy Constructor 
		cgvPoint3D( const cgvPoint3D& p );

		// Assignment operator
		cgvPoint3D& operator = (const cgvPoint3D& p);

		// Destructor
		~cgvPoint3D();

		// Operators
		inline float& operator[] ( const unsigned char idx ) {return c[idx];};
		inline float operator[] (const unsigned char idx) const {return c[idx];};

		int operator == (const cgvPoint3D& p);
		int operator != (const cgvPoint3D& p);

		void set( const float& x, const float& y, const float& z);

		float *data() { return c.data(); }
};

class cgvPoint4D {
public:
	std::array<float, 4> c; // components x, y, z, w of a point or vector

public:
	// Constructors
	cgvPoint4D();
	cgvPoint4D(const float& x, const float& y, const float& z, const float& w = 1.0f);

	// Copy Constructor 
	cgvPoint4D(const cgvPoint4D& p);
	cgvPoint4D(const cgvPoint3D& p);


	// Assignment operator
	cgvPoint4D& operator = (const cgvPoint4D& p);

	// Destructor
	~cgvPoint4D();

	// Operators
	inline float& operator[] (const unsigned char idx) { return c[idx]; };
	inline float operator[] (const unsigned char idx) const { return c[idx]; };

	int operator == (const cgvPoint4D& p);
	int operator != (const cgvPoint4D& p);

	void set(const float& x, const float& y, const float& z, const float& w);

	float *data() { return c.data(); }
};

