#include "cgvLight.h"
#include <iostream>
// Constructor methods 

cgvLight::cgvLight() {
}

cgvLight::cgvLight(const unsigned int _idLight,
  				   const cgvPoint3D  & _position,
				   const cgvColor4f & cAmb, const cgvColor4f & cDif, const cgvColor4f & cEsp,
				   const double a0, const double a1, const double a2) {

  idLight = _idLight;
														 
	position = _position;
														 
	ambientColor = cAmb;
	diffuseColor = cDif;
	specularColor = cEsp;

	atten_a0 = a0;
	atten_a1 = a1;
	atten_a2 = a2;

	// Default values for point lights 
	spotlight_direction = cgvPoint3D(0,0,0);
	spotlight_angle = 180; // with this angle the spotlight becomes a point light source	
	spotlight_exponent = 0;

	on = true;
}

cgvLight::cgvLight(const unsigned int _idLight,
                   const cgvPoint3D & _position, 
                   const cgvColor4f& cAmb, const cgvColor4f& cDif, const cgvColor4f& cEsp,
		           const double a0, const double a1, const double a2,
				   const cgvPoint3D& spotlight_dir, const double spotlight_ang, const double spotlight_exp) {

  idLight = _idLight;
														 
	position = _position;
														 
	ambientColor = cAmb;
	diffuseColor = cDif;
	specularColor = cEsp;

	atten_a0 = a0;
	atten_a1 = a1;
	atten_a2 = a2;

	spotlight_direction = spotlight_dir;
	spotlight_angle = spotlight_ang;
	spotlight_exponent = spotlight_exp;

	on = true;
}

// Public methods ----------------------------------------

cgvPoint3D& cgvLight::getPosition(void) {
	return position;
}

void cgvLight::setPosition(cgvPoint3D pos) {
	position = pos;
}


void cgvLight::set(const cgvColor4f & cAmb, const cgvColor4f & cDif, const cgvColor4f & cEsp) {
	ambientColor = cAmb;
	diffuseColor = cDif;
	specularColor = cEsp;
}

void cgvLight::setAmbient(const cgvColor4f & cAmb) {
	ambientColor = cAmb;
}

void cgvLight::setDiffuse(const cgvColor4f & cDif) {
	diffuseColor = cDif;
}

void cgvLight::setSpecular(const cgvColor4f & cEsp) {
	specularColor = cEsp;
}

cgvColor4f & cgvLight::getAmbient(void) {
	return ambientColor;
}

cgvColor4f & cgvLight::getDiffuse(void) {
	return diffuseColor;
}

cgvColor4f & cgvLight::getSpecular(void) {
	return specularColor;
}

void cgvLight::setAttenuation(double a0, double a1, double a2) {
	atten_a0 = a0;
	atten_a1 = a1;
	atten_a2 = a2;
}

void cgvLight::getAttenuation(double & a0, double & a1, double & a2) {
	a0 = atten_a0;
	a1 = atten_a1;
	a2 = atten_a2;
}

void cgvLight::switchOn(void) {
  on = true;
}

void cgvLight::switchOff(void) {
  on = false;
}

unsigned int cgvLight::is_On(void) {
  return on;
}

void cgvLight::apply(void) {

	if (on) {
		
		glEnable(idLight);
		//position
		float pos[] = { position.data()[0],position.data()[1],position.data()[2],1.0 };
		glLightfv(idLight, GL_POSITION, pos);
		glLightfv(idLight, GL_AMBIENT, ambientColor.data());
		glLightfv(idLight, GL_DIFFUSE, diffuseColor.data());
		glLightfv(idLight, GL_SPECULAR, specularColor.data());
		//attenuations
		glLightf(idLight,GL_CONSTANT_ATTENUATION,atten_a0);
		glLightf(idLight, GL_LINEAR_ATTENUATION, atten_a1);
		glLightf(idLight, GL_QUADRATIC_ATTENUATION, atten_a2);

		//spotlight
		glLightf(idLight, GL_SPOT_CUTOFF, spotlight_angle);
		glLightf(idLight, GL_SPOT_EXPONENT, spotlight_exponent);
		glLightfv(idLight, GL_SPOT_DIRECTION, spotlight_direction.data());
		
	}else {
		glDisable(idLight);
	}
	
}

