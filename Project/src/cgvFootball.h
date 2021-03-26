#pragma once

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

typedef enum {
	CGV_DISPLAY,
	CGV_SELECT
} RenderMode;


class cgvFootball {

	GLubyte color_as_ID[3];
	bool selected;//bool to store if is selected

	int selectedScene;

	float vX=0, vZ=0;
	void spheres();

public:
	cgvFootball(GLubyte _color_as_ID[3]):selected(false) {
		for (int i = 0; i < 3; ++i) {
			color_as_ID[i] = _color_as_ID[i];
		}
	}

	void render(std::string mode);

	void select(GLubyte c[3]); 

	bool isSelected() const { return selected; }

	void setSelected(bool _selected) { selected = _selected; };

	void move(float unitsx, float unitsy);
	
};

