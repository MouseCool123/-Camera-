#ifndef Buffer_
#define Buffer_
	struct buf_Screen {
		bool set_pixel;
		short colornum;
		
		float zpos; //for z-buffer
	};
	
	void set_fontsize(short FONTSIZE_);
	void set_windowsize(short SCREEN_WIDTH_, short SCREEN_HEIGHT_);
	void set_buffersize(short SCREEN_WIDTH_, short SCREEN_HEIGHT_);
	void init_screen(short SCREEN_WIDTH_, short SCREEN_HEIGHT_, short FONTSIZE);
	
	void clear_buffer(short SCREEN_WIDTH_, short SCREEN_HEIGHT_);
	void display_buffer(short SCREEN_WIDTH_, short SCREEN_HEIGHT_); 
	
	void set_brushcolor(short COLOR);
	void put_pel(short XPOS, short YPOS, float ZPOS);
#endif
