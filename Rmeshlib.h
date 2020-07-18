#ifndef Mesh_
#define Mesh_
#include <list>
#include "Drawinglib.h"
	extern vertex3 *object;
	extern face    *face_object;
	extern short   vertex_amount;
	extern short   face_amount;
	extern std::list<float> vertex_index;
	extern std::string file_name;
	
	void get_objectvertexes();
	void read_objectvertexes();
#endif
