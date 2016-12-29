//msoftcon.h
//declarations for Lafore's console graphics functions
//uses Window's console functions
#ifndef _INC_WCONSOLE    //don't let this file be included
#define _INC_WCONSOLE    //twice in the same source file
#include <windows.h>     //for Windows console functions
#include <conio.h>       //for kbhit(), getche()
#include <math.h>        //for sin, cos
#include"time.h"
#include<iostream>
#include<fstream>
#include<string.h>
#include<strstream>
#include<string>
enum fstyle { SOLID_FILL, X_FILL,      O_FILL, 
              LIGHT_FILL, MEDIUM_FILL, DARK_FILL,H_FILL,V_FILL };
enum color {
   cBLACK=0,     cDARK_BLUE=1,    cDARK_GREEN=2, cDARK_CYAN=3, 
   cDARK_RED=4,  cDARK_MAGENTA=5, cBROWN=6,      cLIGHT_GRAY=7,
   cDARK_GRAY=8, cBLUE=9,         cGREEN=10,     cCYAN=11, 
   cRED=12,      cMAGENTA=13,     cYELLOW=14,    cWHITE=15};
//--------------------------------------------------------------
void init_graphics();
void set_color(color fg, color bg = cBLACK);
void set_cursor_pos(int x, int y);
void clear_screen();
void wait(int milliseconds);
void clear_line();
void draw_rectangle(int left, int top, int right, int bottom);                    
void draw_circle(int x, int y, int rad);
void draw_line(int x1, int y1, int x2, int y2);
void draw_pyramid(int x1, int y1, int height);
void set_fill_style(fstyle);
void myline(int x1, int y1, int x2, int y2,char a);
void numcolor(int a,int b);
void myline(int x1, int y1, int x2, int y2,char a,int s);
void D3init();
void line();
void shel1(float x,float y,float z,float radd,char s,int,int);
void cylin(int x,int y,int z,int radd,int h);
void helix(int x,int y,int z,int radd,int h);
 void stystr(char *d);
 void stystr(char *,int);
 void strupper(char *d);
 void backspace(int a);
 void space(int a);
 void BLINK(char *,int freq,int cycle,int x,int y,int colo);
 void BLINK(char *,int freq,int cycle,int x,int y);
 void cleanup(int x,int y);
 void stystr(char *s,int time,int x,int y);
 void stystr(char *s,int time,int x,int y,int colour,int bg=0);
#endif /* _
INC_WCONSOLE */
/*
cone
x=rcos(0)   0<0<2pie
y=rsin(0)   <0r<R
z=r
*/