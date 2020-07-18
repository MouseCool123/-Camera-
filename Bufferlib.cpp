#include <windows.h>
#include <iostream>
#include "Bufferlib.h"

short SCREEN_WIDTH, SCREEN_HEIGHT;
//=--------------------------------------------------------=//
short BRUSH_COLOR;

CHAR_INFO *pchar_info;
HANDLE     console;
COORD      buffer_size  = {0, 0};
COORD	   buffer_coord = {0, 0};
SMALL_RECT window_size  = {0, 0, 0, 0};

buf_Screen *buf_4drawing;
//=--------------------------------------------------------=//
void set_fontsize(short FONTSIZE) {    //..Setting the correct(!) font size of symbols
	CONSOLE_FONT_INFOEX ops;
	ops.cbSize = sizeof(ops);
	ops.nFont  = 0;
	ops.dwFontSize.X = FONTSIZE;
	ops.dwFontSize.Y = FONTSIZE;
	ops.FontFamily   = FF_DONTCARE;
	ops.FontWeight   = FW_NORMAL;
	wcscpy(ops.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(console, FALSE, &ops);
}
void set_windowsize(short SCREEN_WIDTH_, short SCREEN_HEIGHT_) {  //..Setting the window size
	short width  = SCREEN_WIDTH_-1;
	short height = SCREEN_HEIGHT-1;
	window_size = {0, 0, width, height};
	if(!SetConsoleWindowInfo(console, TRUE, &window_size)) {
		MessageBox(NULL, "ERROR: setconsolewindowinfo didn't work\nPlease restart the program", "Console Error", MB_OK);
	}	
}
void set_buffersize(short SCREEN_WIDTH_, short SCREEN_HEIGHT_) { //..Setting the buffersize
	buffer_size = {SCREEN_WIDTH_, SCREEN_HEIGHT_};
	SetConsoleScreenBufferSize(console, buffer_size);
}
void init_screen(short SCREEN_WIDTH_, short SCREEN_HEIGHT_, short FONTSIZE_) { //..Screen initialization and buffer declaration
	SCREEN_WIDTH  = SCREEN_WIDTH_;
	SCREEN_HEIGHT = SCREEN_HEIGHT_; 
	
	buf_4drawing = new struct buf_Screen[SCREEN_WIDTH_ * SCREEN_HEIGHT_];
	pchar_info    = new CHAR_INFO[SCREEN_WIDTH_ * SCREEN_HEIGHT_];
	
	console = GetStdHandle(STD_OUTPUT_HANDLE);
	set_buffersize(SCREEN_WIDTH_, SCREEN_HEIGHT_);
	set_windowsize(SCREEN_WIDTH_, SCREEN_HEIGHT_);
	set_fontsize(FONTSIZE_);
	clear_buffer(SCREEN_WIDTH_, SCREEN_HEIGHT_);
}
void clear_buffer(short SCREEN_WIDTH_, short SCREEN_HEIGHT_) { //..Clearing buffer for the next displaying
	for(int ypos = 0; ypos < SCREEN_HEIGHT_; ypos++) {
		for(int xpos = 0; xpos < SCREEN_WIDTH_; xpos++) { 
			buf_4drawing[ypos * SCREEN_WIDTH_ + xpos].set_pixel = false;
			buf_4drawing[ypos * SCREEN_WIDTH_ + xpos].colornum  = 0;
			buf_4drawing[ypos * SCREEN_WIDTH_ + xpos].zpos      = '\0';
		}
	}
}
void display_buffer(short SCREEN_WIDTH_, short SCREEN_HEIGHT_) {
	for(int ypos = 0; ypos < SCREEN_HEIGHT_; ypos++) {
		for(int xpos = 0; xpos < SCREEN_WIDTH_; xpos++) { //..Set the color and put them where you need them.
			if(buf_4drawing[ypos * SCREEN_WIDTH_ + xpos].set_pixel == true)
				pchar_info[ypos * SCREEN_WIDTH_ + xpos].Attributes = (WORD)((buf_4drawing[ypos * SCREEN_WIDTH_ + xpos].colornum<<4)|buf_4drawing[ypos * SCREEN_WIDTH_ + xpos].colornum);
			else
				pchar_info[ypos * SCREEN_WIDTH_ + xpos].Attributes = (WORD)((0 << 4) | 0);
		}
	}
	WriteConsoleOutputA(console, pchar_info, buffer_size, buffer_coord, &window_size);
}
void set_brushcolor(short COLOR) {
	if(COLOR > 0 && COLOR < 16)
		BRUSH_COLOR = COLOR;
}
void put_pel(short XPOS, short YPOS, float ZPOS) {
	if ((XPOS >= 0 && XPOS <= SCREEN_WIDTH) && (YPOS >= 0 && YPOS <= SCREEN_HEIGHT) && (YPOS * SCREEN_WIDTH + XPOS) <= (SCREEN_WIDTH * SCREEN_HEIGHT))
		if(buf_4drawing[YPOS * SCREEN_WIDTH + XPOS].zpos == '\0' || ZPOS > buf_4drawing[YPOS * SCREEN_WIDTH + XPOS].zpos)
		{
			buf_4drawing[YPOS * SCREEN_WIDTH + XPOS].set_pixel = true;
			buf_4drawing[YPOS * SCREEN_WIDTH + XPOS].colornum  = BRUSH_COLOR;
			buf_4drawing[YPOS * SCREEN_WIDTH + XPOS].zpos      = ZPOS;
		}
}
