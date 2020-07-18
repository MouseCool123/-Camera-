#ifndef Matrix_
#define Matrix_
#include "Vertexlib.h"
	struct matrix {
		float value[16];
	};
	
	matrix indentity_matrix       ();
	vertex4 multiply_matrix_vertex(matrix a, vertex4 b);
	matrix  multiply_matrix       (matrix a, matrix b);
	
	matrix viewport  (float xpos, float ypos, float width, float height);
	matrix projection(float distance);
	matrix lookat    (vertex3 eye, vertex3 eyetarget, vertex3 worldup);
	
#endif
