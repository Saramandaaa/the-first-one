#include<cstdio>
#include<Windows.h>
#include<cstdlib>
#include<ctime>
#include<cstring>
HANDLE hIn=GetStdHandle(STD_INPUT_HANDLE);
HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
WORD color1=FOREGROUND_GREEN;
WORD color2=FOREGROUND_RED;
WORD color3=FOREGROUND_BLUE;
HWND hwnd=FindWindow("ConsoleWindowClass",NULL);
DWORD numRead;
INPUT_RECORD inRec;
CONSOLE_SCREEN_BUFFER_INFO bInfo;
COORD crHome={0,0};
const int X[8]={1,0,-1,0,1,1,-1,-1},
	  	  Y[8]={0,1,0,-1,1,-1,1,-1};
const int size[4]={10,15,20,25};
const int mine[4]={12,25,40,125};
int ans=0;
char a[40][40];
bool b[40][40];
bool bo[40][40];
bool bi[40][40];
bool d[40][40];
int s=0,k=1;
void sleep(int x)
{
	clock_t t=clock();
	while(clock()-t<=x);
}
bool check()
{
	for(int i=1;i<=size[s];i++)
		for(int j=1;j<=size[s];j++)
		{
			if(bi[i][j]&&!b[i][j])return false;
			else if(!bi[i][j]&&b[i][j])return false;
		}
	return true;
}
void print();
COORD loc;
void search(int,int);
void clear();
int main()
{
	there:
	clear();
	SMALL_RECT si={0,0,60,30};
	clock_t t;
	int i,j;
	SetConsoleWindowInfo(hOut,true,&si);
	SetConsoleTextAttribute(hOut,color1|color2|color3);
	printf("0表示简单，\n1表示中等，\n2表示困难，\n3表示极难。\n请输入：");
	do
	{
		scanf("%d",&s);
		if(s!=0&&s!=1&&s!=2&&s!=3)printf("请重新输入：");
	}while(s!=0&&s!=1&&s!=2&&s!=3);
	SetConsoleCursorPosition(hOut,crHome);
	memset(a,'0',sizeof(a));
	srand(time(0));
	int t1,t2;
	switch(s)
	{
		case 0:
		{
			while(k<=12)
			{
				while(1)
				{
					t1=rand()%10+1;
					t2=rand()%10+1;
					if(!b[t1][t2])
					{
						b[t1][t2]=1;
						break;
					}
				}
				k++;
			}
			break;
		}
		case 1:
		{
			while(k<=25)
			{
				while(1)
				{
					t1=rand()%15+1;
					t2=rand()%15+1;
					if(!b[t1][t2])
					{
						b[t1][t2]=1;
						break;
					}
				}
				k++;
			}
			break;
		}
		case 2:
		{
			while(k<=40)
			{
				while(1)
				{
					t1=rand()%20+1;
					t2=rand()%20+1;
					if(!b[t1][t2])
					{
						b[t1][t2]=1;
						break;
					}
				}
				k++;
			}
			break;
		}
		case 3:
		{
			while(k<=125)
			{
				while(1)
				{
					t1=rand()%25+1;
					t2=rand()%25+1;
					if(!b[t1][t2])
					{
						b[t1][t2]=1;
						break;
					}
				}
				k++;
			}
			break;
		}
		default:break;
	}
	for(i=1;i<=size[s];i++)
		for(j=1;j<=size[s];j++)
		{
			if(b[i][j])
				for(int z=0;z<=7;z++)
				{
					int x=i+X[z];
					int y=j+Y[z];
					if(!b[x][y]&&x>=1&&x<=size[s]&&y>=1&&y<=size[s])
						a[x][y]++;
				}
		}
	print();
	t=clock();
	while(1)
	{
		ReadConsoleInput(hIn,&inRec,1,&numRead);
		if(inRec.EventType==MOUSE_EVENT)
		{
			loc=inRec.Event.MouseEvent.dwMousePosition;
			int x;
			if((loc.X+1)%2)x=(loc.X+1)/2+1;
			else x=(loc.X+1)/2;
			int y=loc.Y+1;
			if(x>=1&&x<=size[s]&&y>=1&&y<=size[s])
			{
				if(inRec.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED)
				{
					if(b[y][x]&&!bi[y][x])
					{
						int z=MessageBox(hwnd,"这里是地雷，游戏失败！","信息",MB_RETRYCANCEL);
						memset(bo,1,sizeof(bo));
						memset(bi,0,sizeof(bi));
						SetConsoleCursorPosition(hOut,crHome);
						for(int i=1;i<=size[s];i++)
						{
							for(int j=1;j<=size[s];j++)
							{
								if(b[i][j])
								{
									SetConsoleTextAttribute(hOut,color1|color2|FOREGROUND_INTENSITY);
									printf("X ");
									SetConsoleTextAttribute(hOut,color1|color2|color3);
									ans++;
								}
								else if(!bo[i][j])printf("■");
								else if(a[i][j]=='0')printf("  ");
								else
								{
									switch(a[i][j])
									{
										case '1':SetConsoleTextAttribute(hOut,color1|color3|FOREGROUND_INTENSITY);break;
										case '2':SetConsoleTextAttribute(hOut,color1|FOREGROUND_INTENSITY);break;
										case '3':SetConsoleTextAttribute(hOut,color2|FOREGROUND_INTENSITY);break;
										case '4':SetConsoleTextAttribute(hOut,color2|color3|FOREGROUND_INTENSITY);break;
										default:SetConsoleTextAttribute(hOut,color1|color3|FOREGROUND_INTENSITY);break;
									}
									printf("%c ",a[i][j]);
									SetConsoleTextAttribute(hOut,color1|color2|color3);
								}
							}
							printf("\n");
						}
						sleep(2000);
						if(z==4)goto there;
						system("pause");
						printf("                      \n");
						return 0;
					}
					else if(!bi[y][x]&&a[y][x]=='0')search(y,x);
					else if(!bi[y][x])bo[y][x]=1;
				}
				else if(inRec.Event.MouseEvent.dwButtonState==RIGHTMOST_BUTTON_PRESSED)
				{
					if(!bo[y][x]&&bi[y][x])
						bi[y][x]=0;
					else if(!bo[y][x]&&bi[y][x]==0)
						bi[y][x]=1;
				}
				if(inRec.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED&&inRec.Event.MouseEvent.dwEventFlags==DOUBLE_CLICK)
				{
					if(a[y][x]!='0'&&!b[y][x]&&bo[y][x])
					{
						bool bb=1;
						for(int k=0;k<=7;k++)
						{
							if((b[y+Y[k]][x+X[k]]&&!bi[y+Y[k]][x+X[k]])||(!b[y+Y[k]][x+X[k]]&&bi[y+Y[k]][x+X[k]]))
								bb=0;
						}
						for(int k=0;k<=7;k++)
						{
							if(bb&&!bo[y+Y[k]][x+X[k]]&&!b[y+Y[k]][x+X[k]])
							{
								if(a[y+Y[k]][x+X[k]]=='0')search(y+Y[k],x+X[k]);
								bo[y+Y[k]][x+X[k]]=1;
							}
							else if(!bo[y+Y[k]][x+X[k]])
								d[y+Y[k]][x+X[k]]=1;
						}
						
					}
				}
			}
			print();
			if(ans==mine[s])
			{
				if(check())
				{
					int z=MessageBox(hwnd,"恭喜你找对了所有的地雷！","信息",MB_RETRYCANCEL);
					memset(bo,1,sizeof(bo));
					memset(bi,0,sizeof(bi));
					SetConsoleCursorPosition(hOut,crHome);
					for(int i=1;i<=size[s];i++)
					{
						for(int j=1;j<=size[s];j++)
						{
							if(b[i][j])
							{
								SetConsoleTextAttribute(hOut,color1|color2|FOREGROUND_INTENSITY);
								printf("X ");
								SetConsoleTextAttribute(hOut,color1|color2|color3);
								ans++;
							}
							else if(!bo[i][j])printf("■");
							else if(a[i][j]=='0')printf("  ");
							else
							{
								switch(a[i][j])
								{
									case '1':SetConsoleTextAttribute(hOut,color1|color3|FOREGROUND_INTENSITY);break;
									case '2':SetConsoleTextAttribute(hOut,color1|FOREGROUND_INTENSITY);break;
									case '3':SetConsoleTextAttribute(hOut,color2|FOREGROUND_INTENSITY);break;
									case '4':SetConsoleTextAttribute(hOut,color2|color3|FOREGROUND_INTENSITY);break;
									default:SetConsoleTextAttribute(hOut,color1|color3|FOREGROUND_INTENSITY);break;
								}
								printf("%c ",a[i][j]);
								SetConsoleTextAttribute(hOut,color1|color2|color3);
							}
						}
						printf("\n");
					}
					for(int i=1;i<=4;i++)
						printf("                                                         \n");
					printf("用时：%.3fs             \n",(clock()-t)/1000.0);
					sleep(2000);
					if(z==4)goto there;
					system("pause");
					printf("                        \n");
					return 0; 
				}
				else
				{
					MessageBox(hwnd,"你标记的地雷有误！请仔细检查！","信息",0);
					bi[y][x]=0;
					ans--;
				}
			}
		}	
	}
	return 0;
}
void search(int i,int j)
{
	bo[i][j]=1;
	for(int k=0;k<=7;k++)
	{
		int x=i+X[k];
		int y=j+Y[k];
		if(!bo[x][y]&&a[x][y]=='0'&&x>=1&&x<=size[s]&&y>=1&&y<=size[s]&&!b[x][y]&&!bi[x][y])
		{
			search(x,y);
		}
		else if(!bo[x][y]&&a[x][y]>'0'&&a[x][y]<='9'&&!b[x][y]&&!bi[x][y])bo[x][y]=1;
	}
}
void print()
{
	ans=0;
	SetConsoleCursorPosition(hOut,crHome);
	for(int i=1;i<=size[s];i++)
	{
		for(int j=1;j<=size[s];j++)
		{
			if(bi[i][j])
			{
				SetConsoleTextAttribute(hOut,color1|color2|FOREGROUND_INTENSITY);
				printf("X ");
				SetConsoleTextAttribute(hOut,color1|color2|color3);
				ans++;
			}
			else if(d[i][j])
			{
				printf("? ");
				d[i][j]=0;
			}
			else if(!bo[i][j])printf("■");
			else if(a[i][j]=='0')printf("  ");
			else
			{
				switch(a[i][j])
				{
					case '1':SetConsoleTextAttribute(hOut,color1|color3|FOREGROUND_INTENSITY);break;
					case '2':SetConsoleTextAttribute(hOut,color1|FOREGROUND_INTENSITY);break;
					case '3':SetConsoleTextAttribute(hOut,color2|FOREGROUND_INTENSITY);break;
					case '4':SetConsoleTextAttribute(hOut,color2|color3|FOREGROUND_INTENSITY);break;
					default:SetConsoleTextAttribute(hOut,color1|color3|FOREGROUND_INTENSITY);break;
				}
				printf("%c ",a[i][j]);
				SetConsoleTextAttribute(hOut,color1|color2|color3);
			}
		}
		printf("\n");
	}
	printf("按左键点开，右键标记。\n如果某个数字旁边的地雷全部被标出，\n那么双击该数字可以自动展开周围没有点开的方格。\n地雷总数：%d\n已做的标记：%d",mine[s],ans);
}
void clear()
{
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	memset(bo,0,sizeof(bo));
	memset(bi,0,sizeof(bi));
	ans=0;
	SetConsoleCursorPosition(hOut,crHome);
	for(int i=1;i<=size[s]+10;i++)
	{
		for(int j=1;j<=2*size[s]+10;j++)
			printf(" ");
		printf("\n");
	}
	s=0;k=1;
	SetConsoleCursorPosition(hOut,crHome);
}
