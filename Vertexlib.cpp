#include <cmath>
#include "Vertexlib.h"

vertex3 add_vertex(vertex3 a, vertex3 b) {
	vertex3 qq;
	
	qq.xpos = a.xpos + b.xpos;
	qq.ypos = a.ypos + b.ypos;
	qq.zpos = a.zpos + b.zpos;
	
	return qq;
}
vertex3 subtract_vertex(vertex3 a, vertex3 b) {
	vertex3 qq;
	
	qq.xpos = a.xpos - b.xpos;
	qq.ypos = a.ypos - b.ypos;
	qq.zpos = a.zpos - b.zpos;
	
	return qq;
}
vertex3 multiply_vertex(vertex3 a, float b) {
	vertex3 qq;
	
	qq.xpos = a.xpos * b;
	qq.ypos = a.ypos * b;
	qq.zpos = a.zpos * b;
	
	return qq;
}
float length_vertex(vertex3 a) {
	float leng = sqrt(a.xpos * a.xpos + a.ypos * a.ypos + a.zpos * a.zpos);
	
	return leng;
}
vertex3 normal_vertex(vertex3 a) {
	vertex3 qq;
	float l = length_vertex(a);
	
	qq.xpos = a.xpos/l;
	qq.ypos = a.ypos/l;
	qq.zpos = a.zpos/l;
	
	return qq;
}
vertex3 cross_vertex(vertex3 a, vertex3 b) {
	vertex3 qq;
	
	qq.xpos = a.ypos * b.zpos - a.zpos * b.ypos;
	qq.ypos = a.zpos * b.xpos - a.xpos * b.zpos;
	qq.zpos = a.xpos * b.ypos - a.ypos * b.xpos;
	
	return qq;
}
vertex4 vertex3_to4(vertex3 a) {
	vertex4 qq;
	
	qq.xpos = a.xpos;
	qq.ypos = a.ypos;
	qq.zpos = a.zpos;
	qq.w    = 1;
	
	return qq;
}
vertex3 vertex4_to3(vertex4 a) {
	vertex3 qq;
	
	qq.xpos = a.xpos/a.w;
	qq.ypos = a.ypos/a.w;
	qq.zpos = a.zpos/a.w;
	
	return qq;
}
