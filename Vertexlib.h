#ifndef Vertex_
#define Vertex_
	struct vertex3 {
		float xpos,ypos,zpos;
	};
	struct vertex4 {
		float xpos,ypos,zpos,w;
	};
	
	vertex3 add_vertex(vertex3 a, vertex3 b);
	vertex3 subtract_vertex(vertex3 a, vertex3 b);
	vertex3 multiply_vertex(vertex3 a, float b);
	vertex3 normal_vertex(vertex3 a);
	float length_vertex(vertex3 a);
	vertex3 cross_vertex(vertex3 a, vertex3 b);
	vertex4 vertex3_to4(vertex3 a);
	vertex3 vertex4_to3(vertex4 a);
#endif
