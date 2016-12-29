//msoftcon.cpp
//provides routines to access Windows console functions
//compiler needs to be able to find this file
//in MCV++, /Tools/Options/Directories/Include/type path name
#include "iostream"
#include <stdlib.h>
using namespace std;
#include "msoftcon.h"
#include"time.h"
#define pie 3.14
int ln=0;
HANDLE hConsole;         //console handle
char fill_char;          //character used for fill
//--------------------------------------------------------------
void init_graphics()
{
	COORD console_size = {410, 410};
	//open i/o channel to console screen
	hConsole = CreateFile("CONOUT$", GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		0L, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0L);
	//set to 410x410 screen size
	SetConsoleScreenBufferSize(hConsole, console_size);
	//set text to white on black
	SetConsoleTextAttribute( hConsole, (WORD)((0 << 4) | 15) );

	fill_char = '\xDB';  //default fill is solid block
}
void set_color(color foreground, color background)
{
	SetConsoleTextAttribute( hConsole,
		(WORD)((background << 4) | foreground) );
}  //end setcolor()
using namespace std;
void numcolor(int a,int b)
{
	SetConsoleTextAttribute( hConsole,
		(WORD)((  b   << 4) | a ) );
}
/* 0  Black          8  Dark gray
1  Dark blue      9  Blue
2  Dark green     10 Green
3  Dark cyan      11 Cyan
4  Dark red       12 Red
5  Dark magenta   13 Magenta
6  Brown          14 Yellow
7  Light gray     15 White
*/
void set_cursor_pos(int x, int y)
{
	COORD cursor_pos;              //origin in upper left corner
	cursor_pos.X = x ;          //Windows starts at (0, 0)
	cursor_pos.Y = y ;          //we start at (1, 1)
	SetConsoleCursorPosition(hConsole, cursor_pos);
}
void clear_screen()
{
	set_cursor_pos(1, 250);
	for(int j=0; j<250; j++){
		for(int i=1;i<250;i++)cout<<" ";
	cout<<endl;}
	set_cursor_pos(1, 1);
}
void wait(int milliseconds)
{
	Sleep(milliseconds);
}
void clear_line()                    //clear to end of line
{                                 //410 spaces
	//.....1234567890123456789012345678901234567890
	//.....0........1.........2.........3.........4
	_cputs("                                        ");
	_cputs("                                        ");
}
void draw_rectangle(int left, int top, int right, int bottom)
{
	char temp[410];
	int width = right - left + 1;

	for(int j=0; j<width; j++)      //string of squares
	{    temp[j] = fill_char;
	temp[j] = 0;}                    //null

	for(int y=top; y<=bottom; y++)  //stack of strings
	{
		set_cursor_pos(left, y);
		_cputs(temp);
	}
}
void draw_circle(int xC, int yC, int radius)
{
	double theta, increment, xF, pi=3.14159;
	int x, xN, yN;

	increment = 0.8 / static_cast<double>(radius);
	for(theta=0; theta<=pi/2; theta+=increment)  //quarter circle
	{
		xF = radius * cos(theta);
		xN = static_cast<int>(xF * 2 / 1); //pixels not square
		yN = static_cast<int>(radius * sin(theta) + 0.5);
		x = xC-xN;
		while(x <= xC+xN)          //fill two horizontal lines
		{                       //one for each half circle
			set_cursor_pos(x,   yC-yN); cout<<fill_char;  //top
			set_cursor_pos(x++, yC+yN); cout<<fill_char;  //bottom
		}
	}  //end for
}
void draw_line(int x1, int y1, int x2, int y2)
{

	int w, z, t, w1, w2, z1, z2;
	double xDelta=x1-x2, yDelta=y1-y2, slope;
	bool isMoreHoriz;

	if( fabs(xDelta) > fabs(yDelta) ) //more horizontal
	{
		isMoreHoriz = true;
		slope = yDelta / xDelta;
		w1=x1; z1=y1; w2=x2, z2=y2;    //w=x, z=y
	}
	else                              //more vertical
	{
		isMoreHoriz = false;
		slope = xDelta / yDelta;
		w1=y1; z1=x1; w2=y2, z2=x2;    //w=y, z=x
	}

	if(w1 > w2)                       //if backwards w
	{
		t=w1; w1=w2; w2=t;             //   swap (w1,z1)
		t=z1; z1=z2; z2=t;             //   with (w2,z2)
	}
	for(w=w1; w<=w2; w++)
	{
		z = static_cast<int>(z1 + slope * (w-w1));
		if( !(w==410 && z==410) )        //avoid scroll at 410,410
		{
			if(isMoreHoriz)
				set_cursor_pos(w, z);
			else
				set_cursor_pos(z, w);
			cout<<fill_char;
		}
	}
}
void draw_pyramid(int x1, int y1, int height)
{
	int x, y;
	for(y=y1; y<y1+height; y++)
	{
		int incr = y - y1;
		for(x=x1-incr; x<=x1+incr; x++)
		{
			set_cursor_pos(x, y);
			cout<<fill_char;
		}
	}
}
void set_fill_style(fstyle fs)
{
	switch(fs)
	{
	case SOLID_FILL:  fill_char = '\xDB'; break;
	case DARK_FILL:   fill_char = '\xB0'; break;
	case MEDIUM_FILL: fill_char = '\xB1'; break;
	case LIGHT_FILL:  fill_char = '\xB2'; break;
	case X_FILL:      fill_char = '*';    break;
	case O_FILL:      fill_char = '.';    break;
	case H_FILL:      fill_char = '_';    break;
	case V_FILL:      fill_char = '|';    break;
	}
}
void myline(int x1, int y1, int x2, int y2,char a)
{
	if((x1==x2)&&(y1==y2)) {set_cursor_pos(x1,y1); cout<<a;}
	else{
		int w, z, t, w1, w2, z1, z2;
		double xDelta=x1-x2, yDelta=y1-y2, slope;
		bool isMoreHoriz;

		if( fabs(xDelta) > fabs(yDelta) ) //more horizontal
		{
			isMoreHoriz = true;
			slope = yDelta / xDelta;
			w1=x1; z1=y1; w2=x2, z2=y2;    //w=x, z=y
		}
		else                              //more vertical
		{
			isMoreHoriz = false;
			slope = xDelta / yDelta;
			w1=y1; z1=x1; w2=y2, z2=x2;    //w=y, z=x
		}

		if(w1 > w2)                       //if backwards w
		{
			t=w1; w1=w2; w2=t;             //   swap (w1,z1)
			t=z1; z1=z2; z2=t;             //   with (w2,z2)
		}
		for(w=w1; w<=w2; w++)
		{
			z = static_cast<int>(z1 + slope * (w-w1));
			if( !(w==410 && z==410) )        //avoid scroll at 410,410
			{
				if(isMoreHoriz)
					set_cursor_pos(w, z);
				else
					set_cursor_pos(z, w);
				cout<<a;
			}
		}
	}
}
void myline(int x1, int y1, int x2, int y2,char a,int s)
{
	if((x1==x2)&&(y1==y2)) {set_cursor_pos(x1,y1); cout<<a;}
	else{
		int w, z, t, w1, w2, z1, z2;
		double xDelta=x1-x2, yDelta=y1-y2, slope;
		bool isMoreHoriz;

		if( fabs(xDelta) > fabs(yDelta) ) //more horizontal
		{
			isMoreHoriz = true;
			slope = yDelta / xDelta;
			w1=x1; z1=y1; w2=x2, z2=y2;    //w=x, z=y
		}
		else                              //more vertical
		{
			isMoreHoriz = false;
			slope = xDelta / yDelta;
			w1=y1; z1=x1; w2=y2, z2=x2;    //w=y, z=x
		}

		if(w1 > w2)                       //if backwards w
		{
			t=w1; w1=w2; w2=t;             //   swap (w1,z1)
			t=z1; z1=z2; z2=t;             //   with (w2,z2)
		}
		for(w=w1; w<=w2; w++)
		{
			z = static_cast<int>(z1 + slope * (w-w1));
			if( !(w==410 && z==410) )        //avoid scroll at 410,410
			{
				if(isMoreHoriz)
					set_cursor_pos(w, z);
				else
					set_cursor_pos(z, w);
				Sleep(s);
				cout<<a;
			}
		}
	}
}
int c=200,d=200,csi=400,len=110;
time_t x; 
int cd=time(&x);
int u=rand()%15+1,v=rand()%15+1,q=rand()%15+1; 
void D3init()
{
	myline(c,d,c-0.7*len,d+0.7*len,'/');
	myline(c,d+len,c,d-len,char(179));
	myline(c-len,d,c+len,d,'_');
	for(int i=1;i<=len/10;i++)
	{
		numcolor(u,0);
		myline(c+10*i,d+len,c+10*i,d-len,char(179));
		myline(c-10*i,d+len,c-10*i,d-len,char(179));
		myline(c-len,d-10*i,c+len,d-10*i,'_');
					}
	for(int i=1;i<=len/10;i++)
	{
	numcolor(v,0);
	myline(c-7*i,d+7*i,c-7*i+len,d+7*i,'_');
	myline(c-7*i-len,d+7*i,c-7*i,d+7*i,'_');
	}
	for(int i=1;i<=len/10;i++)
	{
			numcolor(v,0);
		myline(c+10*i,d,c-0.7*len+10*i,d+0.7*len,'/');
		myline(c-10*i,d,c-10*i-0.7*len,d+0.7*len,'/');
		/*
		myline(c-7*i-len,d+7*i,c+len-7*i,d+7*i,'_');
		myline(c+7*i-len,d-7*i,c+len+7*i,d-7*i,'_');
		
		*/
	//	myline(c,d-10*i,c-0.7*len,d+0.7*len-10*i,'/',0);

	}
	for(int cg=1;cg<=len/5;cg++)
	{
		numcolor(rand()%15+1,0);
		set_cursor_pos(c+5*cg,d);
		cout<<char(179);
		set_cursor_pos(c+5*cg,d+1);
		cout<<5*cg;
		set_cursor_pos(c,d-5*cg);
		cout<<"-";
		set_cursor_pos(c-3,d-5*cg);
		cout<<5*cg;
		if(cg%2==0)
		{
			set_cursor_pos(c-3.5*cg,d+3.5*cg);
			cout<<'\\';
			set_cursor_pos(c-3-3.5*cg,d+3.5*cg);
			cout<<5*cg;
		}
	}
	numcolor(q,0);
	myline(c,d,c-0.7*len,d+0.7*len,'/');
	myline(c,d+len,c,d-len,char(179));
	myline(c-len,d,c+len,d,'_');
}
void line()
{
	float xi,yi,zi,xf,yf,zf,xir,yir,zir,xfr,yfr,zfr;
	set_cursor_pos(10,10+ln++);
	cout<<"\nenter the x,y,z coordinate\n";
	cin>>xi>>yi>>zi;
	xir=xi-zi*0.7;
	yir=-zi*0.7+yi;
	set_cursor_pos(10,10+ln++);
	cout<<"\nenter the x,y,z coordinate\n";
	cin>>xf>>yf>>zf;
	xfr=xf-zf*0.7;
	yfr=-zf*0.7+yf;
	myline(c+xir,d-yir,c+xfr,d-yfr,'.',0);
	char k;
	set_cursor_pos(10,10+ln++);
	cout<<"\npress #to terminate ";
	k=_getch();
	if(k=='#')
		;
	else
	{
line:;
		set_cursor_pos(10,10+ln++);
		cout<<"\nenter the x,y,z coordinate\n";
		cout<<xf<<" ,"<<yf<<" ,"<<zf<<"xf\n";
		cin>>xi>>yi>>zi;
		xir=xi-zi*0.7;
		yir=-zi*0.7+yi;
		myline(c+xir,d-yir,c+xfr,d-yfr,'.',0);
		set_cursor_pos(10,10+ln++);
		cout<<xi<<" ,"<<yi<<" ,"<<zi<<"xi\n";
		cout<<"\npress #to terminate \n";
		k=_getch();
		k=_getch();
		if(k=='#');
		else
		{
			set_cursor_pos(10,10+ln++);
			cout<<"\nenter the x,y,z coordinate\n";
			cin>>xf>>yf>>zf;
			xfr=xf-zf*0.7;
			yfr=-zf*0.7+yf;
			myline(c+xir,d-yir,c+xfr,d-yfr,'.',0);
		}
		set_cursor_pos(10,10+ln++);
		cout<<"\npress #to terminate \n";
		k=_getch();
		k=_getch();
		if(k=='#');
		else
		{
			goto line;
		}
	}
	//myline(100+xir,100-yir,100+xir,100-yir+yi,'^',0);
	//myline(100+xfr,100-yfr,100+xfr,100-yfr+yf,'^',0);
	_getch();
}
void shel1(float x,float y,float z,float radd,char s,int g,int w)
{
	g%=181;w%=181;
	float xi,yi,zi,xir,yir;
	int a,b;//0<=b<=3.14, 0<=a<=6.28
	for(a=0;a<=360;a++)
	{if(a%30==0)
	{
		for(b=g;b<=w;b++)
		{
			xi=x+radd*cos((pie*a)/180)*sin((pie*b)/180);
			yi=y+radd*sin((pie*a)/180)*sin((pie*b)/180);
			zi=z+radd*cos((pie*b)/180);
			xir=xi-zi*0.7;
			yir=-zi*0.7+yi;
			set_cursor_pos(c+xir,d-yir);
			cout<<s;
		}
		}
	}
}
void cylin(int x,int y,int z,int radd,int h)
{
	float xi,yi,zi,xir,yir,zir,xmax,xmin,ymin,ymax;
	ymax=y+1.21*radd-z*0.7;
	ymin=y-1.21*radd-z*0.7;
	xmax=h+x;
	xmin=x;
	for(zi=z;zi<=h+z;zi++)
	{
		for(int i=0;i<=360;i++)
		{
			xi=radd*cos((pie*i)/180)+x;
			yi=radd*sin((pie*i)/180)+y;
			xir=xi-(zi)*0.7;
			yir=(zi)*0.7+yi;
			if(((-0.8<sin((pie*i)/180))&&(sin((pie*i)/180)<-0.5))||(zi==z)||(zi==h+z)||((-0.8<cos((pie*i)/180))&&(cos((pie*i)/180)<-0.5))||(40<i&&i<70))
			{
				set_cursor_pos(c+xir,d+yir);
				cout<<'.';
			}
		}
	}
}
void helix(int x,int y,int z,int radd,int h)
{
	float xi,yi,zi,xir,yir,zir;
	for(yi=y;yi<=y+h;yi+=2)
	{
		for(int i=0;i<=360;i++)
		{
			zi=radd*cos((pie*i)/180)+z;
			xi=radd*sin((pie*i)/180)+x;
			xir=xi-(zi)*0.7;
			yir=-(zi)*0.7+yi;
			set_cursor_pos(c+xir,d-yir);
			cout<<'.';
		}
	}
}
 void stystr(char d[])
{
	for (int i = 0; d[i]!='\0'; i++)
	{
		cout<<d[i];
		Sleep(10);
	}
}
 void stystr(char *d,int x)
	 {
		 for (int i = 0; d[i]!='\0'; i++)
	{
		cout<<d[i];
		Sleep(x);
	}
 };
 void strupper(char d[])
{
	for (int i = 0; d[i]!='\0'; i++)
	{
		if(isalpha(d[i]));
		d[i]=toupper(d[i]);
	}
}
 void backspace(int a)
{
	for(int x=1;x<=a;x++) cout<<'\b';
}
 void space(int a)
{
	for(int i=1;i<=a;i++) cout<<" ";
}
 void BLINK(char *a,int freq,int cycles,int x,int y,int vt)
 {
	 for(int i=0;i<cycles;i++)
	 {
		set_cursor_pos(x,y);
		numcolor(vt,0);
		stystr(a,10);
		Sleep(freq/2);
		for(int j=0;a[j]!='\0';j++)
			cout<<"\b \b";
		Sleep(freq/2);
	 }
 }
 void BLINK(char *a,int freq,int cycles,int x,int y)
 {
	 for(int i=0;i<cycles;i++)
	 {
		set_cursor_pos(x,y);
		q=rand()%15+1;
		numcolor(q,0);
		stystr(a,10);
		Sleep(freq/2);
		for(int j=0;a[j]!='\0';j++)
			cout<<"\b \b";
		Sleep(freq/2);
	 }
 }
 void cleanup(int x,int y)
 {
	 set_cursor_pos(x,y);
	 for(int j=x;j<300;j++)
		 cout<<" ";
	 for(int j=0;j<300;j++)
		 cout <<"\b";
 }
 void stystr(char *s,int time,int x,int y)
 {
	 set_cursor_pos(x,y);
		q=rand()%15+1;
		numcolor(q,0);
		stystr(s,10);
 }
 void stystr(char *s,int time,int x,int y,int colour,int bg)
 {
	 numcolor(colour,bg);
	 set_cursor_pos(x,y);
		stystr(s,10);
 }