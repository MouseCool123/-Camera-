#ifndef Drawing_
#define Drawing_
#include "Vertexlib.h"
	struct face {
		vertex3 Atop;
		vertex3 Btop;
		vertex3 Ctop;
	};
	
	void draw_line(float xpos_1, float ypos_1, float zpos_1, float xpos_2, float ypos_2, float zpos_2);
	void draw_triangle(vertex3 Atop, vertex3 Btop, vertex3 Ctop);
#endif
