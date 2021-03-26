#include <stdio.h>
#include <math.h>

#include "cgvPoint3D.h"

// Constructors
cgvPoint3D::cgvPoint3D() {
	c[X] = c[Y] = c[Z] = 0.0;
}

cgvPoint3D::cgvPoint3D (const float& x, const float& y, const float& z ) {
	c[X] = x;
	c[Y] = y;
	c[Z] = z;	
}

// Copy constructor 
cgvPoint3D::cgvPoint3D (const cgvPoint3D& p ) {
	c[X] = p.c[X];
	c[Y] = p.c[Y];
	c[Z] = p.c[Z];
}

// Assignment operator 
cgvPoint3D& cgvPoint3D::operator = (const cgvPoint3D& p) {
	c[X] = p.c[X];
	c[Y] = p.c[Y];
	c[Z] = p.c[Z];
	return(*this);
}

// Destructor
cgvPoint3D::~cgvPoint3D() {
}

// Operators
int cgvPoint3D::operator == (const cgvPoint3D& p) {
	return ((fabs(c[X]-p[X])<IGV_EPSILON) && (fabs(c[Y]-p[Y])<IGV_EPSILON) && (fabs(c[Z]-p[Z])<IGV_EPSILON));
}

int cgvPoint3D::operator != (const cgvPoint3D& p) {
	return ((fabs(c[X]-p[X])>=IGV_EPSILON) || (fabs(c[Y]-p[Y])>=IGV_EPSILON) || (fabs(c[Z]-p[Z])>=IGV_EPSILON));
}

void cgvPoint3D::set( const float& x, const float& y, const float& z) {
	c[X] = x;
	c[Y] = y;
	c[Z] = z;
}


/////////////////////////////////////////////////////////////////////////////////////

// Constructors
cgvPoint4D::cgvPoint4D() {
	c[X] = c[Y] = c[Z] = 0.0f; 
	c[W] = 1.0f;
}

cgvPoint4D::cgvPoint4D(const float& x, const float& y, const float& z, const float& w) {
	c[X] = x;
	c[Y] = y;
	c[Z] = z;
	c[W] = w; 
}

// Copy constructor 
cgvPoint4D::cgvPoint4D(const cgvPoint4D& p) {
	c[X] = p.c[X];
	c[Y] = p.c[Y];
	c[Z] = p.c[Z];
	c[W] = p.c[W];
}

cgvPoint4D::cgvPoint4D(const cgvPoint3D& p) {
	c[X] = p[X];
	c[Y] = p[Y];
	c[Z] = p[Z];
	c[W] = 1.0f; 
}

// Assignment operator 
cgvPoint4D& cgvPoint4D::operator = (const cgvPoint4D& p) {
	c[X] = p.c[X];
	c[Y] = p.c[Y];
	c[Z] = p.c[Z];
	c[W] = p.c[W];
	return(*this);
}

// Destructor
cgvPoint4D::~cgvPoint4D() {
}

// Operators
int cgvPoint4D::operator == (const cgvPoint4D& p) {
	return ((fabs(c[X] - p[X]) < IGV_EPSILON) && (fabs(c[Y] - p[Y]) < IGV_EPSILON) && (fabs(c[Z] - p[Z]) < IGV_EPSILON) && (fabs(c[W] - p[W]) < IGV_EPSILON));
}

int cgvPoint4D::operator != (const cgvPoint4D& p) {
	return ((fabs(c[X] - p[X]) >= IGV_EPSILON) || (fabs(c[Y] - p[Y]) >= IGV_EPSILON) || (fabs(c[Z] - p[Z]) >= IGV_EPSILON) || (fabs(c[W] - p[W]) >= IGV_EPSILON));
}

void cgvPoint4D::set(const float& x, const float& y, const float& z, const float& w) {
	c[X] = x;
	c[Y] = y;
	c[Z] = z;
	c[W] = w; 
}


