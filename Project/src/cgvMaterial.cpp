#include "cgvMaterial.h"

// Constructor and destructor methods 

cgvMaterial::cgvMaterial () {
	
}

cgvMaterial::~cgvMaterial () {

}

cgvMaterial::cgvMaterial (const cgvMaterial& m) {	//copy constructor
	Ka = m.Ka;
	Kd = m.Kd;
	Ks = m.Ks;
	Ns = m.Ns;
}

cgvMaterial::cgvMaterial(cgvColor4f _Ka, cgvColor4f _Kd, cgvColor4f _Ks, double _Ns) {
	Ka = _Ka;
	Kd = _Kd;
	Ks = _Ks;
	Ns = _Ns;
}

// Public methods 

void cgvMaterial::apply(void) {

// Section C
// Apply the attributes of the cgvMaterial object:
// - ambient coefficient 
// - diffuse coefficient
// - specular coefficient
// - Phong exponent

// set the color (0.0, 0.0, 0.0) as emission color (the object is not a light source )
	GLfloat ambient[] = {Ka[0],Ka[1],Ka[2]};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);

	GLfloat diffuse[] = { Ka[0],Ka[1],Ka[2] };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);

	GLfloat specular[] = { Ka[0],Ka[1],Ka[2] };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, Ns);

	GLfloat emision[] = { 0.0,0.0,0.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emision);


}

void cgvMaterial::set(cgvColor4f _Ka, cgvColor4f _Kd, cgvColor4f _Ks, double _Ns) {
	Ka = _Ka;
	Kd = _Kd;
	Ks = _Ks;
	Ns = _Ns;
}



