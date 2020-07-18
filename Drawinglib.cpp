#include "Drawinglib.h"
#include "Bufferlib.h"
#include <cmath>
#include <iostream>
using namespace std;

void draw_line(float xpos_1, float ypos_1, float zpos_1, float xpos_2, float ypos_2, float zpos_2) {
	float x_distance = xpos_2 - xpos_1;
	   if(x_distance < 0) x_distance *= -1;
	   
	float y_distance = ypos_2 - ypos_1;
	   if(y_distance < 0) y_distance *= -1;
	//=---------------------------------------------=//
	if(x_distance == 0 && y_distance == 0){
		if(xpos_1 >= 0 && ypos_1 >= 0 && ypos_2 >= 0 && xpos_2 >= 0)
			put_pel((int)round(xpos_1), (int)round(ypos_1), zpos_1);	
	}
	else if(x_distance >= y_distance) {
		if(xpos_1 <= xpos_2)
			for(float xpos = xpos_1; xpos <= xpos_2; xpos++) {
				float ypos = (ypos_2 - ypos_1)*(xpos - xpos_1)/(xpos_2 - xpos_1) + ypos_1;	
				float zpos = (zpos_2 - zpos_1)*(xpos - xpos_1)/(xpos_2 - xpos_1) + zpos_1;	
				
					put_pel((int)round(xpos), (int)round(ypos), zpos);
			}
		else
			for(float xpos = xpos_2; xpos <= xpos_1; xpos++) {
				float ypos = (ypos_2 - ypos_1)*(xpos - xpos_1)/(xpos_2 - xpos_1) + ypos_1;	
				float zpos = (zpos_2 - zpos_1)*(xpos - xpos_1)/(xpos_2 - xpos_1) + zpos_1;	
					
					put_pel((int)round(xpos),(int)round(ypos), zpos);
		}
	}  
	else {
		if(ypos_1 <= ypos_2)
			for(float ypos = ypos_1; ypos <= ypos_2; ypos++) {
				float xpos = (ypos - ypos_1)*(xpos_2 - xpos_1)/(ypos_2 - ypos_1) + xpos_1;
				float zpos = (ypos - ypos_1)*(zpos_2 - zpos_1)/(ypos_2 - ypos_1) + zpos_1;
				
					put_pel((int)round(xpos), (int)round(ypos), zpos);
			}
			
		else
			for(float ypos = ypos_2; ypos <= ypos_1; ypos++) {
				float xpos = (ypos - ypos_1)*(xpos_2 - xpos_1)/(ypos_2 - ypos_1) + xpos_1;
				float zpos = (ypos - ypos_1)*(zpos_2 - zpos_1)/(ypos_2 - ypos_1) + zpos_1;
				
					put_pel((int)round(xpos), (int)round(ypos), zpos);
				
			}
 	}
}
void draw_triangle(vertex3 Atop, vertex3 Btop, vertex3 Ctop) {
	while(Atop.ypos > Btop.ypos || Atop.ypos > Ctop.ypos || Btop.ypos > Ctop.ypos) {
	   if(Atop.ypos > Btop.ypos) {swap(Atop.xpos, Btop.xpos); swap(Atop.ypos, Btop.ypos); swap(Atop.zpos, Btop.zpos);}
	   if(Atop.ypos > Ctop.ypos) {swap(Atop.xpos, Ctop.xpos); swap(Atop.ypos, Ctop.ypos); swap(Atop.zpos, Ctop.zpos);}
	   if(Btop.ypos > Ctop.ypos) {swap(Btop.xpos, Ctop.xpos); swap(Btop.ypos, Ctop.ypos); swap(Btop.zpos, Ctop.zpos);}
	}
	
	for(float ypos = Atop.ypos; ypos <= Btop.ypos; ypos++) {
		float xpos_1 = (ypos - Atop.ypos)*(Ctop.xpos - Atop.xpos)/(Ctop.ypos - Atop.ypos) + Atop.xpos;
		float zpos_1 = (ypos - Atop.ypos)*(Ctop.zpos - Atop.zpos)/(Ctop.ypos - Atop.ypos) + Atop.zpos;
		float xpos_2 = (ypos - Atop.ypos)*(Btop.xpos - Atop.xpos)/(Btop.ypos - Atop.ypos) + Atop.xpos;
		float zpos_2 = (ypos - Atop.ypos)*(Btop.zpos - Atop.zpos)/(Btop.ypos - Atop.ypos) + Atop.zpos;
		draw_line(xpos_1, ypos, zpos_1, xpos_2, ypos, zpos_2);
	}
	for(float ypos = Btop.ypos; ypos <= Ctop.ypos; ypos++) {
		float xpos_1 = (ypos - Atop.ypos) * (Ctop.xpos - Atop.xpos) / (Ctop.ypos - Atop.ypos) + Atop.xpos;
		float zpos_1 = (ypos - Atop.ypos) * (Ctop.zpos - Atop.zpos) / (Ctop.ypos - Atop.ypos) + Atop.zpos;
		float xpos_2 = (ypos - Btop.ypos) * (Ctop.xpos - Btop.xpos) / (Ctop.ypos - Btop.ypos) + Btop.xpos;
		float zpos_2 = (ypos - Btop.ypos) * (Ctop.zpos - Btop.zpos) / (Ctop.ypos - Btop.ypos) + Btop.zpos;
		draw_line(xpos_1, ypos, zpos_1, xpos_2, ypos, zpos_2);
	}
}
