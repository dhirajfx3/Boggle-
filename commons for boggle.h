#include"msoftcon.h"
using namespace std;
void get_row_length(int &R,int &x,int &y);
void get_col_length(int &C,int &x,int &y);
void matrix_print(int width,int height,int row,int column,char **m,int &cl,int &r,char vert,char join,char hori);
void linev2(int x,int y,int c,int cw ,char join,char hori);
void init_visited(int R,int C,bool val,bool **visited);
void read(char **dictionary,int len=200);
void welcome(int freq,int cycle,int x,int y);
template<typename T>
T** make(int n,int m)
{
	T **x;
	x=new T*[n];
	for(int i = 0 ; i < n ; i++ )
	{
		x[i]=new T[m];
	}
	return x;
}
void get_boggle(char **boggle,int R,int C,int &x,int &y);
int key();
void select_(int &x,int &y,int &selection);