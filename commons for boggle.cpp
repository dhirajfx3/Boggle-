#include"commons for boggle.h"
using namespace std;
void get_row_length(int &R,int &x,int &y)
{
	string s;
	bool loop =true;
	while(loop)
	{
		strstream tmp;
		system("cls");
		stystr("Enter the number of Rows : \a",100,x,y);
		cin >> s ;
		tmp << s ;
		if ( tmp >> R )
		{
			if ( R <= 0 )
			{
				BLINK("INVALID INPUT\a",1000,5,x,y+1,12);
			}
			else
				loop=false;
		}
		else
		{
			BLINK("INVALID INPUT\a",1000,5,x,y+1,12);
		}
	}
	y+=2;
}
void get_col_length(int &C,int &x,int &y)
{
	string s;
	bool loop = true;
	while(loop)
	{
		strstream tmp;
		cleanup(x,y);
		stystr("Enter the number of Columns : \a",100,x,y);
		cin >>s;
		tmp<<s;
		if(tmp>>C)
		{
			if(C<=0)
			{
				BLINK("INVALID INPUT\a",1000,5,x,y+1,12);
			}
			else
				loop=false;
		}
		else
		{
			BLINK("INVALID INPUT\a",1000,5,x,y+1,12);
		}
	}
	y+=2;
}
void get_boggle(char **boggle,int R,int C,int &x,int &y)
{
	string s;
	strstream stream;
	bool loop;
	for(int i = 0 ;i<R;i++)
	{
		cleanup(x,y+2*i);
		stystr("Enter Row ",100,x,y+2*i);
		cout << i+1 << " : " ;
		cin>>s;
		char t;
		stream<<s;
		int j=0;
		loop=true;
		while(loop)
		{
			if(!stream)
			{
				if(j!=C+1)
				{
					BLINK("INVALID INPUT\a",1000,5,x,y+1+2*i,12);
					stream.clear();
					--j , --i ;
				}
				loop=false;
			}
			else
			{
				stream >> t ;
				tolower( t ) ;
				if(( t < 'a' || t > 'z') &&(j<C))
				{
					BLINK("INVALID INPUT\a",1000,5,x,y+1+2*i,12);
					--j , --i ;
					loop=false;
				}
				else
					boggle[i][j] = t ;
				++j;
			}
		}
		stream.clear();
	}
	y+=2*R;
}
void matrix_print(int width,int height,int row,int column,char **matrix,int &cl,int &r,char vert,char join,char hori)
{
	int blockw=width,blockh=height;
	linev2(cl,r++,column,blockw,join,hori);
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<blockh/2;j++)
		{
			set_cursor_pos(cl,r+j);
			cout<<vert;
			for(int g=0;g<column;g++)
			{
				for(int p=0;p<blockw;p++)
					cout<<" ";
				cout<<vert;
			}
		}
		set_cursor_pos(cl,r+blockh/2);
		cout<<vert;
		for(int g=0;g<column;g++)
		{
			for(int p=0;p<blockw/2;p++)
				cout<<" ";
			cout<<matrix[i][g];
			for(int p=0;p<blockw/2;p++)
				cout<<" ";
			cout<<vert;
		}
		for(int j=blockh/2+1;j<blockh;j++)
		{
			set_cursor_pos(cl,r+j);
			cout<<vert;
			for(int g=0;g<column;g++)
			{
				for(int p=0;p<blockw;p++)
					cout<<" ";
				cout<<vert;
			}
		}
		r+=(blockh);
		linev2(cl,r++,column,blockw,join,hori);
		cout<<"";
	}
	r+=2;
}
void linev2(int x,int y,int c,int cw,char join,char hori )
{
	int i=0;
	set_cursor_pos(x,y);
	cout<<join;
	for(int k=0;k<c;k++)
	{
		for(int j=0;j<cw;j++)
			cout<<hori;
		cout<<join;
	}
}
void init_visited(int R,int C,bool val,bool **visited)
{
	for(int i=0;i<R;i++)
		for(int j=0;j<C;j++)
			visited[i][j]=val;
}
void read(char **dictionary,int len)
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
void welcome(int freq,int cycle,int x,int y)
{
	system("cls");
	BLINK("WELCOME",freq,cycle,x,y);
	stystr("This is program to solve BOGGLE\a",100,x,y+1);
	set_cursor_pos(x,y+5);
	system("pause");
}
void select_(int &cl,int &r,int &selection)
{
	time_t t;
	int q=time(&t);
	srand(q);
	q=rand()%15+1;
	int g=((q+1)%15)+1;
	stystr("Select option:",100,cl,r);
	stystr("1.To search a particular word",0,cl,r+1,q,g);
	stystr("2.Search all words",100,cl,r+2,q);
	stystr("3.Exit",100,cl,r+3,q);
	stystr("-->",10,cl-5,r+1);
	set_cursor_pos(cl,r+4);
	int option = 7;
	selection=0;
	{
		int tmp=3;
		char a[][50]={"1.To search a particular word","2.Search all words","3.Exit"};
		while(option!=5)
		{
			option=key();
			stystr(a[selection],0,cl,r+selection+1,q);
			set_cursor_pos(cl-5,r+1+selection);
			cout <<"   ";
			if(option==1)
			{
				tmp = 3+((tmp-1)%3);
				selection=tmp-3;
			}
			else if(option==3)
			{
				tmp=3+((tmp+1)%3);
				selection=tmp-3;
			}
			stystr(a[selection],0,cl,r+selection+1,q,g);
			stystr("-->",10,cl-5,r+1+selection);
		}
	}
}
int key()
{
	strstream sfd;
	string s;
	int retval=0;
	sfd <<_getch();
	int shy;
	sfd>>shy;
	if(shy==13)
		return 5;
	else
		if(shy==224)
		{
			sfd.clear();
			sfd << _getch();
			sfd >> shy;
			switch(shy)
			{
			case 72:
				retval=1;
				break;
			case 77:
				retval=2;
				break;
			case 80:
				retval=3;
				break;
			case 75:
				retval=4;
				break;
			}
		}
		return retval;
}