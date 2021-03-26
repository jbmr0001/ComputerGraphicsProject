#pragma once


#include <array>

typedef enum {
	R,
	G,
	B,
	A
};


class cgvColor4f {

	std::array<float, 4> color; 

public:
	cgvColor4f() {
		color = {0,0,0,1};
	}
	cgvColor4f(float r, float g, float b, float a=1) {
		color = { r,g,b,a };
	}

	float *data() { return color.data(); }

	double operator[](const unsigned char pos)const { return color[pos]; };



};


