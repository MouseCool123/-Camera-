#include "Matrixlib.h"
#include <iostream> 
using namespace std;
matrix viewport(float xpos, float ypos, float width, float height) {
	matrix qq = indentity_matrix();

	qq.value[0] = width / 2.f;
	qq.value[3] = xpos + (width/2.f);
	qq.value[5] = height / 2.f;
	qq.value[7] = ypos + (height/2.f);
	
	return qq;	
}
matrix projection(float distance) {
	matrix qq = indentity_matrix();
	
	qq.value[14] = distance;
	
	return qq;
}
matrix indentity_matrix() {
	matrix qq;
	
	for(int i = 0; i < 16; i++) 
		qq.value[i] = 0;
	qq.value[0]  = 1;
	qq.value[5]  = 1;
	qq.value[10] = 1;
	qq.value[15] = 1;
	
	return qq;
}
vertex4 multiply_matrix_vertex(matrix a, vertex4 b) {
	vertex4 qq;
	
	qq.xpos = (a.value[0 ] * b.xpos) + (a.value[1 ] * b.ypos) + (a.value[2 ] * b.zpos) + (a.value[3 ] * b.w);
	qq.ypos = (a.value[4 ] * b.xpos) + (a.value[5 ] * b.ypos) + (a.value[6 ] * b.zpos) + (a.value[7 ] * b.w);
	qq.zpos = (a.value[8 ] * b.xpos) + (a.value[9 ] * b.ypos) + (a.value[10] * b.zpos) + (a.value[11] * b.w);
	qq.w    = (a.value[12] * b.xpos) + (a.value[13] * b.ypos) + (a.value[14] * b.zpos) + (a.value[15] * b.w);

	return qq;
}
matrix  multiply_matrix(matrix a, matrix b) {
	matrix qq;
	
	qq.value[0 ] = (a.value[0 ] * b.value[0 ]) /**/ 
			    + (a.value[1 ] * b.value[4 ]) /**/ 		 	   
			    + (a.value[2 ] * b.value[8 ]) /**/			   
			    + (a.value[3 ] * b.value[12]);/**/			   
	qq.value[4 ] = (a.value[4 ] * b.value[0 ]) + (a.value[5 ] * b.value[4 ]) + (a.value[6 ] * b.value[8 ]) + (a.value[7 ] * b.value[12]);
	qq.value[8 ] = (a.value[8 ] * b.value[0 ]) /**/ 
			    + (a.value[9 ] * b.value[4 ]) /**/ 		   	   
			    + (a.value[10] * b.value[8 ]) /**/			   
			    + (a.value[11] * b.value[12]);/**/			    
	qq.value[12] = (a.value[12] * b.value[0 ]) + (a.value[13] * b.value[4 ]) + (a.value[14] * b.value[8 ]) + (a.value[15] * b.value[12]);
	qq.value[1 ] = (a.value[0 ] * b.value[1 ]) /**/ 
			    + (a.value[1 ] * b.value[5 ]) /**/ 		 	   
			    + (a.value[2 ] * b.value[9 ]) /**/			   
			    + (a.value[3 ] * b.value[13]);/**/			   
	qq.value[5 ] = (a.value[4 ] * b.value[1 ]) + (a.value[5 ] * b.value[5 ]) + (a.value[6 ] * b.value[9 ]) + (a.value[7 ] * b.value[13]);
	qq.value[9 ] = (a.value[8 ] * b.value[1 ]) /**/ 
			    + (a.value[9 ] * b.value[5 ]) /**/ 		   	   
			    + (a.value[10] * b.value[9 ]) /**/			   
			    + (a.value[11] * b.value[13]);/**/			   			   
	qq.value[13] = (a.value[12] * b.value[1 ]) + (a.value[13] * b.value[5 ]) + (a.value[14] * b.value[9 ])+  (a.value[15] * b.value[13]);
	qq.value[2 ] = (a.value[0 ] * b.value[2 ]) /**/ 
			    + (a.value[1 ] * b.value[6 ]) /**/ 		 	   
			    + (a.value[2 ] * b.value[10]) /**/			   
			    + (a.value[3 ] * b.value[14]);/**/			  	    
	qq.value[6 ] = (a.value[4 ] * b.value[2 ]) + (a.value[5 ] * b.value[6 ]) + (a.value[6 ] * b.value[10]) + (a.value[7 ] * b.value[14]); 
	qq.value[10] = (a.value[8 ] * b.value[2 ]) /**/ 
			    + (a.value[9 ] * b.value[6 ]) /**/ 		   	   
			    + (a.value[10] * b.value[10]) /**/			   
			    + (a.value[11] * b.value[14]);/**/			   
			    
	qq.value[14] = (a.value[12] * b.value[2 ]) + (a.value[13] * b.value[6 ]) + (a.value[14] * b.value[10]) + (a.value[15] * b.value[14]);
	qq.value[3 ] = (a.value[0 ] * b.value[3 ]) /**/  
			    + (a.value[1 ] * b.value[7 ]) /**/ 		 	   
			    + (a.value[2 ] * b.value[11]) /**/			   
			    + (a.value[3 ] * b.value[15]);/**/			   
	qq.value[7 ] = (a.value[4 ] * b.value[3 ]) + (a.value[5 ] * b.value[7 ]) + (a.value[6 ] * b.value[11]) + (a.value[7 ] * b.value[15]);
	qq.value[11] = (a.value[8 ] * b.value[3 ]) /**/ 
			    + (a.value[9 ] * b.value[7 ]) /**/ 		   	   
			    + (a.value[10] * b.value[11]) /**/			   
			    + (a.value[11] * b.value[15]);/**/			   
	qq.value[15] = (a.value[12] * b.value[3 ]) + (a.value[13] * b.value[7 ]) + (a.value[14] * b.value[11]) + (a.value[15] * b.value[15]);

	return qq;
}
matrix lookat (vertex3 eye, vertex3 eyetarget, vertex3 worldup)
{
	vertex3 forward = subtract_vertex(eye, eyetarget);  
		    forward = normal_vertex(forward);
	vertex3 left    = cross_vertex(worldup, forward); 
		    left    = normal_vertex(left);
	vertex3 up	    = cross_vertex(forward, left);
		    up      = normal_vertex(up);

	matrix campos = indentity_matrix(); 
	matrix camrotate = indentity_matrix();
		   
	campos.value[3] = -(left.xpos * eye.xpos + left.ypos * eye.ypos + left.zpos * eye.zpos);
	campos.value[7] = -(up.xpos * eye.xpos + up.ypos * eye.ypos + up.zpos * eye.zpos); 
	campos.value[11]= -(forward.xpos * eye.xpos + forward.ypos * eye.ypos + forward.zpos * eye.zpos);
	
	camrotate.value[0] = left.xpos;
	camrotate.value[1] = left.ypos;
	camrotate.value[2] = left.zpos; 
	camrotate.value[4] = up.xpos;
	camrotate.value[5] = up.ypos;
	camrotate.value[6] = up.zpos; 
	camrotate.value[8] = forward.xpos;
	camrotate.value[9] = forward.ypos;     
	camrotate.value[10] = forward.zpos;
	
	return multiply_matrix(campos, camrotate);
}
