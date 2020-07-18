#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cmath>
#include "Bufferlib.h"
#include "Drawinglib.h"
#include "Vertexlib.h"
#include "Rmeshlib.h"
#include "Matrixlib.h"
using namespace std;
//=-----------=-//
const short SCREEN_WIDTH  = 500,
			SCREEN_HEIGHT = 500,
			FONTSIZE      = 2,
			object_WIDTH  = 200,
			object_HEIGHT = 200;
			
float distance_ = -1.f/10.f;
	   
vertex3 *object;
short vertex_amount;
/*short face_amount;
  face  face_object;*/
short *copy_array_vertex_index;  
  
vertex3 cubepos{0,0, 0};

vertex3 eye{0,0, 0},
 	   	eye_target{0, 0, 0},
		worldup{0, 1, 0};
		
POINT   cursorpos,
        last_cursorpos;
bool    is_pressed = false;
bool    like = false;
float   mouse_sensitivity = 0.1f;
float   mouse_xoffset,
		mouse_yoffset;
float   angle_xoffset,
		angle_yoffset;
//=-----------=-//
string file_name = "untitled.obj";
//=-----------=-//
float into_radians(float deegrees) {
	return deegrees * M_PI / 180.f;
}
//=-----------=-//
void draw_object(vertex3* object, short vertex_amount_) {
	vertex3 object_screenpoint[vertex_amount_];
	
	matrix viewport_     = viewport(0, 0, (float)object_WIDTH, (float)object_HEIGHT);
	matrix projection_   = projection(distance_);
	matrix view          = lookat(eye, add_vertex(eye, eye_target), worldup);
	matrix modern_matrix = multiply_matrix(viewport_, projection_);
		   modern_matrix = multiply_matrix(modern_matrix, view);
		   	   	
	for(int i = 0; i < vertex_amount_; i++) {
		vertex3 object_vertex         = add_vertex(object[i], cubepos);
		vertex4 newobject_vertex      = vertex3_to4(object_vertex);
				newobject_vertex      = multiply_matrix_vertex(modern_matrix, newobject_vertex);
		        object_screenpoint[i] = vertex4_to3(newobject_vertex);
	}

	for(int i = 0, j = 0; i < face_amount; i++,j+=3) {
		face_object[i].Atop.xpos = object_screenpoint[copy_array_vertex_index[j]-1].xpos;
		face_object[i].Atop.ypos = object_screenpoint[copy_array_vertex_index[j]-1].ypos;
		face_object[i].Atop.zpos = object_screenpoint[copy_array_vertex_index[j]-1].zpos;
		
		face_object[i].Btop.xpos = object_screenpoint[copy_array_vertex_index[j+1]-1].xpos;
		face_object[i].Btop.ypos = object_screenpoint[copy_array_vertex_index[j+1]-1].ypos;
		face_object[i].Btop.zpos = object_screenpoint[copy_array_vertex_index[j+1]-1].zpos;
			
		face_object[i].Ctop.xpos = object_screenpoint[copy_array_vertex_index[j+2]-1].xpos;
		face_object[i].Ctop.ypos = object_screenpoint[copy_array_vertex_index[j+2]-1].ypos;
		face_object[i].Ctop.zpos = object_screenpoint[copy_array_vertex_index[j+2]-1].zpos;	
	}
	
//	for(int i = 0; i < face_amount; i++) {
//		set_brushcolor((int)i/2);
//		draw_triangle(face_object[i].Atop, face_object[i].Btop, face_object[i].Ctop);
//	}
		   
	for(int i = 0; i < vertex_amount_ - 1; i++) 
		for(int j = 0; j < vertex_amount_; j++) {
			float xpos_1 = object_screenpoint[i].xpos,
			      ypos_1 = object_screenpoint[i].ypos;
			float xpos_2 = object_screenpoint[j].xpos;
			float ypos_2 = object_screenpoint[j].ypos;
			draw_line(xpos_1, ypos_1, 0, xpos_2, ypos_2, 0);
		}
}
//=-----------=-//
int main(int argc, char** argv) {
	set_brushcolor(6);
	init_screen(SCREEN_WIDTH, SCREEN_HEIGHT, FONTSIZE);
	
	get_objectvertexes(); 
	copy_array_vertex_index = new short[face_amount*3]; 
	copy(vertex_index.begin(), vertex_index.end(), copy_array_vertex_index);
	while(1) {
		clear_buffer(SCREEN_WIDTH, SCREEN_HEIGHT);
		
		draw_object(object, vertex_amount);
		//=-----move_the_mouse-----=//
		GetCursorPos(&cursorpos); 
		if(is_pressed == true) {
			mouse_xoffset = cursorpos.x - last_cursorpos.x;
			mouse_yoffset = last_cursorpos.y - cursorpos.y;
		}
		else 
			mouse_xoffset = mouse_yoffset = 0;
		mouse_xoffset *= mouse_sensitivity;
		mouse_yoffset *= mouse_sensitivity;
		
		angle_xoffset += mouse_xoffset;
		angle_yoffset += mouse_yoffset;

		eye_target.xpos = cos(into_radians(angle_yoffset)) * cos(into_radians(angle_xoffset));
		eye_target.ypos = sin(into_radians(angle_yoffset));
		eye_target.zpos = cos(into_radians(angle_yoffset)) * sin(into_radians(angle_xoffset));
		eye_target      = normal_vertex(eye_target);
		
		if( (GetKeyState(VK_RBUTTON) & 0x80) != 0 )
			is_pressed = true;
		else
			is_pressed = false;
		
		last_cursorpos = cursorpos;	
		//=-----press_the_keyboard-----=//	
		if(kbhit()) {
			int key = getch();
			if(key == 100) eye = add_vertex(eye, multiply_vertex(normal_vertex(cross_vertex(eye_target, worldup)), 0.05f));                                                  //d 
			if(key == 97)  eye = subtract_vertex(eye, multiply_vertex(normal_vertex(cross_vertex(eye_target, worldup)), 0.05f));                                                       //w
			if(key == 115) eye = add_vertex(eye, multiply_vertex(normal_vertex(cross_vertex(eye_target, cross_vertex(subtract_vertex(eye, eye_target), worldup))), 0.05f));  //s
			if(key == 119) eye = subtract_vertex(eye, multiply_vertex(normal_vertex(cross_vertex(eye_target, cross_vertex(subtract_vertex(eye, eye_target), worldup))), 0.05f));       //a
			if(key == 101) eye = add_vertex(eye, multiply_vertex(eye_target, 0.1f));                                                                                              //e
			if(key == 113) eye = subtract_vertex(eye, multiply_vertex(eye_target, 0.1f));                                                                                        //q	
		}
		display_buffer(SCREEN_WIDTH, SCREEN_HEIGHT); 
	}
}
