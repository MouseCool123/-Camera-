#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Rmeshlib.h"
using namespace std;

extern short    vertex_amount;
extern vertex3 *object;
 	   face    *face_object;
 	   short    face_amount;
	   list<float> vertex_index;
extern string    file_name;

void get_objectvertexes() {
	list<float> temp_vertexes_x;
	list<float> temp_vertexes_y;
	list<float> temp_vertexes_z;
	
	
	ifstream file(file_name);
	if(file.is_open()) {
		string line;
		while(getline(file, line)) {
			if(line[0] == 'v' && line[1] == ' ') {
				stringstream x;
				x << line;
				
				for(int i = 0; i < 2; i++)
					x >> line;
				temp_vertexes_x.push_back(atof(line.c_str()));
					x >> line;
				temp_vertexes_y.push_back(atof(line.c_str()));
					x >> line;
				temp_vertexes_z.push_back(atof(line.c_str()));
				
				vertex_amount++;
			}
			else if (line[0] == 'f' && line[1] == ' ') {
				stringstream x;
				x << line;
				
				for(int i = 0; i < 2; i++)
					x >> line;
				
				vertex_index.push_back((short)line[0] - 48);
				
					x >> line;
				vertex_index.push_back((short)line[0] - 48);
					x >> line;
				vertex_index.push_back((short)line[0] - 48);
				
				face_amount++;
			} 
		}
		file.close();
	}
	else
		cout << "Impossible to open the file!\n"; 
				
	object = new vertex3[vertex_amount];
	face_object = new face[face_amount];
	
	short copy_array_vertex_index[face_amount*3];
	copy(vertex_index.begin(), vertex_index.end(), copy_array_vertex_index);	
	
	float copy_array_x[vertex_amount];
	copy(temp_vertexes_x.begin(), temp_vertexes_x.end(), copy_array_x);
	
	float copy_array_y[vertex_amount];
	copy(temp_vertexes_y.begin(), temp_vertexes_y.end(), copy_array_y);
	
	float copy_array_z[vertex_amount];
	copy(temp_vertexes_z.begin(), temp_vertexes_z.end(), copy_array_z);
	
	for(int i = 0; i < vertex_amount; i++) {
		object[i].xpos = copy_array_x[i];
		object[i].ypos = copy_array_y[i];
		object[i].zpos = copy_array_z[i];
	}
	
	for(int i = 0, j = 0; i < face_amount; i++, j+=3) {
		face_object[i].Atop.xpos = copy_array_x[copy_array_vertex_index[j]-1];
		face_object[i].Atop.ypos = copy_array_y[copy_array_vertex_index[j]-1];
		face_object[i].Atop.zpos = copy_array_z[copy_array_vertex_index[j]-1];
		
		face_object[i].Btop.xpos = copy_array_x[copy_array_vertex_index[j+1]-1];
		face_object[i].Btop.ypos = copy_array_y[copy_array_vertex_index[j+1]-1];
		face_object[i].Btop.zpos = copy_array_z[copy_array_vertex_index[j+1]-1];
			
		face_object[i].Ctop.xpos = copy_array_x[copy_array_vertex_index[j+2]-1];
		face_object[i].Ctop.ypos = copy_array_y[copy_array_vertex_index[j+2]-1];
		face_object[i].Ctop.zpos = copy_array_z[copy_array_vertex_index[j+2]-1];
	}
}
