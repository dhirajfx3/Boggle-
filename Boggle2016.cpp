// C++ program for Boggle game
#include<iostream>
#include<string>
#include"msoftcon.h"
#include<fstream>
#include<strstream>
#include<string.h>
#include<time.h>
#include"commons for boggle.h"
using namespace std;
string dictionary[201];
int n = 200;
int r,cl;
char join='\xB1',vert='\xB1',hori='\xB1';
char*convert(string str);
void read_for_dictionary();
bool isWord(string &str);
char*convert(string str);
void findWordsUtil(char **boggle, bool **visited,int i,int j, string &str,int R,int C);
void findWords(char **boggle,int R,int C);
int boggle1_main()
{
	string s;
	cl=10,r=5;
	time_t t;
	int q=time(&t);
	srand(q);
	char **boggle;
	int R,C,option,selection=0;
	strstream stream;
	init_graphics();
	welcome(1000,5,cl,r);
	r=6,cl=10;
	bool loop;
	get_row_length(R,cl,r);
	get_col_length(C,cl,r);
	boggle=make<char>(R,C);
	r=11,cl=10;
	get_boggle(boggle,R,C,cl,r);
	system("cls");
	int width=5,height=3;
	r=6,cl=10;
	matrix_print(width,height,R,C,boggle,cl,r,vert,join,hori);
	select_(cl,r,selection);
	system("cls");
	r=6,cl=10;
	matrix_print(width,height,R,C,boggle,cl,r,vert,join,hori);
	if(selection==0)
	{
		n=1;
		stystr("Enter the word to search for : ",10,cl,r);
		cin>>dictionary[0];
	}
	else if(selection==1)
	{
		read_for_dictionary();
		stystr("Following words of dictionary are present",10,cl,r);
	}
	cl,r++;
	if(selection==0||selection==1)
		findWords(boggle,R,C);
	set_cursor_pos(cl,r+10);
	system("pause");
	return 0;
}
void findWords(char **boggle,int R,int C)
{
	// Mark all characters as not visited
	bool **visited=new bool*[R];
	for(int i = 0 ;i<R;i++)
	{
		visited[i]=new bool[C];
		for(int j=0;j<C;j++)
			visited[i][j]=false;
	}

	// Initialize current string
	string str = "";

	// Consider every character and look for all words
	// starting with this character
	for (int i=0; i<R; i++)
		for (int j=0; j<C; j++)
			findWordsUtil(boggle, visited, i, j, str,R,C);
}
void findWordsUtil(char **boggle, bool **visited,int i,int j, string &str,int R,int C)
{

	// Mark current cell as visited and append current character
	// to str
	visited[i][j] = true;
	str = str + boggle[i][j];
	// If str is present in dictionary, then print it
	if (isWord(str))
	{
		if(n==1)
			stystr("Word Found",10,cl,r++);
		else
		{

			stystr(convert(str),10,cl,r++);
		}
	}
	// Traverse 8 adjacent cells of boggle[i][j]
	for (int row=i-1; row<=i+1 && row<R; row++)
		for (int col=j-1; col<=j+1 && col<C; col++)
			if (row>=0 && col>=0 && !visited[row][col])
				findWordsUtil(boggle,visited, row, col, str,R,C);

	// Erase current character from string and mark visited
	// of current cell as false
	str.erase(str.length()-1);
	visited[i][j] = false;
}
char*convert(string str)
{
	char *a=new char[str.length()];
	//cout<<str.length()<<endl;
	for(int i=0;i<str.length();i++)
	{
		a[i]=str[i];
	}
	a[str.length()]='\0';
	return a;
}
bool isWord(string &str)
{
	// Linearly search all words
	for (int i=0; i<n; i++)
		if (str.compare(dictionary[i]) == 0)
			return true;
	return false;
}
void read_for_dictionary()
{
	int i = -1 ;
	ifstream f("input.txt") ;
	while( (!f.eof()) && (++i < 200) )
	{
		f >> dictionary[i] ;
	}
	f.close() ;
	return ;
}