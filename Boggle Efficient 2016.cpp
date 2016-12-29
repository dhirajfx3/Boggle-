#include<iostream>
#include<fstream>
#include<string.h>
#include<strstream>
#include<string>
#include"commons for boggle.h"
#include"msoftcon.h"
using namespace std;
struct graphic
{
	int x,y,txt_i,txt_f,bg_i,wid,higt;
	bool var;
};
bool search(char *word,int R,int C,bool **visited,char **boggle);
bool search(char *word,int R,int C,bool **visited,char **boggle,graphic g);
bool search_char_around(char *word,int index,int r,int c,int R,int C,bool **visited,char **boggle);
bool search_char_around(char *word,int index,int r,int c,int R,int C,bool **visited,char **boggle,graphic g);
bool full_search(int &x,int &y,int R,int C,char **boggle,bool **visited,char **dict,int len);
void one_time_search(int &x,int &y,int R,int C,char **boggle,bool **visited,graphic g);
int main()
{
	char **dict=make<char>(200,50),**boggle,vert='\xB1',join='\xB1',hori='\xB1';
	bool **visited;
	int R,C,option=0, x=10,y=5,freq=1000,cycles=5,width=5,height=3;
	init_graphics();
	welcome(freq,cycles,x,y);
	get_row_length(R,x,y);
	get_col_length(C,x,y);
	visited=make<bool>(R,C);
	boggle=make<char>(R,C);
	get_boggle(boggle,R,C,x,y);
	while(option!=2)
	{
		init_visited(R,C,false,visited);
	system("cls");
	x=10,y=5;
	matrix_print(width,height,R,C,boggle,x,y,vert,join,hori);
	select_(x,y,option);
	system("cls");
	x=10,y=5;
	int d;
	time_t tt;
	d=time(&tt);
	srand(d);
	d=rand()%15+1;
	set_cursor_pos(x,y-1);
	numcolor(d,0);
	cout<<"BOGGLE";
	matrix_print(width,height,R,C,boggle,x,y,vert,join,hori);
	if(option==0)
	{
		graphic g={10,5,d,(d+1)%15+1,(d+2)%15+1,width,height,true};
		one_time_search(x,y,R,C,boggle,visited,g);
	}
	else
		if(option==1)
		{
			full_search(x,y,R,C,boggle,visited,dict,200);
		}
	set_cursor_pos(x,y+2);
	system("pause");
	}
	set_cursor_pos(x,y+2);
	system("pause");
	return 0;
}
bool search(char *word,int R,int C,bool **visited,char **boggle)
{

	for(int i=0;i<R;i++)
		for(int j=0;j<C;j++)
		{
			if(word[0]==boggle[i][j])
			{
				visited[i][j]=true;
				if(search_char_around(word,1,i,j,R,C,visited,boggle))
				{
					return true;
				}
				visited[i][j]=false;
			}
		}
		return false;
}
bool search(char *word,int R,int C,bool **visited,char **boggle,graphic g)
{

	for(int i=0;i<R;i++)
		for(int j=0;j<C;j++)
		{
			if(word[0]==boggle[i][j])
			{
				visited[i][j]=true;
				if(g.var)
						{
							char p[2]={boggle[i][j],'\0'};
							stystr(p,0,g.x+(g.wid+1)*j+(g.wid+1)/2,g.y+(g.higt+1)*i+(g.higt+1)/2,12,10);
						}
				if(search_char_around(word,1,i,j,R,C,visited,boggle,g))
				{
					return true;
				}
				visited[i][j]=false;
				if(g.var)
						{
							char p[2]={boggle[i][j],'\0'};
							stystr(p,0,g.x+(g.wid+1)*j+(g.wid+1)/2,g.y+(g.higt+1)*i+(g.higt+1)/2,g.txt_i);
						}
			}
		}
		return false;
}
bool search_char_around(char *s,int index,int r,int c,int R,int C,bool **visited,char **boggle,graphic g)
{
	if(index==strlen(s))
		return true;
	for(int i=r-1;i<=r+1 && i<R ;i++)
		for(int  j=c-1;j<=c+1&&j<C;j++)
		{
			if(i>=0&&j>=0)
			{
				if(!visited[i][j])
				{
					if(s[index]==boggle[i][j])
					{
						visited[i][j]=true;
						if(g.var)
						{
							Sleep(300);
							char p[2]={boggle[i][j],'\0'};
							set_cursor_pos(g.x+(g.wid+1)*j+(g.wid+1)/2,g.y+(g.higt+1)*i+(g.higt+1)/2);
							stystr(p,0,g.x+(g.wid+1)*j+(g.wid+1)/2,g.y+(g.higt+1)*i+(g.higt+1)/2,12,10);
						}
						if( search_char_around(s,index+1,i,j,R,C,visited,boggle,g))
							return true;
						visited[i][j]=false;
						if(g.var)
						{
							char p[2]={boggle[i][j],'\0'};
							set_cursor_pos(g.x+(g.wid+1)*j+(g.wid+1)/2,g.y+(g.higt+1)*i+(g.higt+1)/2);
							stystr(p,0,g.x+(g.wid+1)*j+(g.wid+1)/2,g.y+(g.higt+1)*i+(g.higt+1)/2,g.txt_i);
						}
					}
				}
			}
		}
		return false;
}
bool search_char_around(char *s,int index,int r,int c,int R,int C,bool **visited,char **boggle)
{
	if(index==strlen(s))
		return true;
	for(int i=r-1;i<=r+1 && i<R ;i++)
		for(int  j=c-1;j<=c+1&&j<C;j++)
		{
			if(i>=0&&j>=0)
			{
				if(!visited[i][j])
				{
					if(s[index]==boggle[i][j])
					{
						visited[i][j]=true;
						if( search_char_around(s,index+1,i,j,R,C,visited,boggle))
							return true;
						visited[i][j]=false;
					}
				}
			}
		}
		return false;
}
void one_time_search(int &x,int &y,int R,int C,char **boggle,bool **visited,graphic g)
{
	char a[50];
	stystr("Enter the word you want to search : ",100,x,y);
	cin>>a;
	if(search(a,R,C,visited,boggle,g))
		{
			BLINK("Match Found ",1000,5,x,y+1,10);
	}
	else
	{
		BLINK("Match Not Found ",1000,5,x,y+1,12);
	}
}
bool full_search(int &x,int &y,int R,int C,char **boggle,bool **visited,char **dict,int len)
{
	bool z=true;
	read(dict,len);
	for(int i=0;i<len;i++)
	{
		if(search(dict[i],R,C,visited,boggle))
		{
			if(z)
				z=!z,stystr("The words of dictionary which are present are :",100,x,y++);
			stystr(dict[i],100,x,y++);
		}
	}
	if(z)
		BLINK("No Words Found ",1000,5,x,y+1,12);
	return !z;
}