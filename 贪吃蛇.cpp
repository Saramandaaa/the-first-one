#include<Windows.h>
#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<conio.h>
#include<cstring>
HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
WORD color1=FOREGROUND_GREEN;
WORD color2=FOREGROUND_RED;
WORD color3=FOREGROUND_BLUE;
HWND hwnd=FindWindow("ConsoleWindowClass",NULL);
COORD crHome={0,0},now={24,12},snake[501],a;
bool b[52][26];
int lenth=0;
int direction=5;
bool a_a=0;
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void sleep(int x)
{
	clock_t t=clock();
	while(clock()-t<=x);
}
void clear()
{
	memset(b,0,sizeof(b));
	now={24,12};
	direction=5;
	lenth=0;
	a_a=0;
}
void move();
void print();
int main()
{
	there:
	clear();
	SetConsoleCursorPosition(hOut,crHome);
	HideCursor();
	SetConsoleTextAttribute(hOut,color1|color3|FOREGROUND_INTENSITY);
	char ch;
	int i,j,x,y;
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□\n");
	for(i=1;i<=23;i++)printf("□■■■■■■■■■■■■■■■■■■■■■■■□\n");
	printf("□□□□□□□□□□□□□□□□□□□□□□□□□\n\n");
	SetConsoleTextAttribute(hOut,color1|color2|color3|FOREGROUND_INTENSITY);
	printf("按\"A\",\"S\",\"D\",\"W\"键\n或者\"←\"\"↓\"\"→\"\"↑\"键操控方向。\n按空格键可暂停。\n分数：0\n");
	for(i=0;i<=49;i++)
		b[i][0]=b[i][24]=1;
	for(i=0;i<=24;i++)
		b[0][i]=b[1][i]=b[48][i]=b[47][i]=1;
	srand(time(0));
	while(!a_a)
	{
		x=rand()%47+2;
		y=rand()%23+1;
		if(!b[x][y]&&!(x%2)&&!(y%2))
		{
			a.X=x;
			a.Y=y;
			a_a=1;
		}
	}
	print();
	ch=getch();
	while(1)
	{
		if(ch==-32)ch=getch();
		if(ch==' ')
		{
			ch=getch();
			continue;
		}
		else if(ch=='a'||ch=='A'||ch==75)
		{
			if(direction!=1&&direction!=3)
				direction=1;
		}
		else if(ch=='s'||ch=='S'||ch==80)
		{
			if(direction!=2&&direction!=4)
				direction=2;
		}
		else if(ch=='d'||ch=='D'||ch==77)
		{
			if(direction!=1&&direction!=3)
				direction=3;
		}
		else if(ch=='w'||ch=='W'||ch==72)
		{
			if(direction!=2&&direction!=4)
				direction=4;
		}
		ch='z';
		for(i=1;i<=lenth;i++)
			b[snake[i].X][snake[i].Y]=1;
		while(!a_a)
		{
			x=rand()%47+2;
			y=rand()%23+1;
			if(!b[x][y]&&!(x%2)&&!(y%2))
			{
				a.X=x;
				a.Y=y;
				a_a=1;
			}
		}
		if(b[now.X][now.Y])
		{
			if(MessageBox(hwnd,"Game Over!","信息",MB_RETRYCANCEL)==4)goto there;
			break;
		}
		SetConsoleCursorPosition(hOut,now);
		printf("■");
		switch(direction)
		{
			case 1:
			{
				if(lenth>=1)
					move();
				now.X-=2;
				break;
			}
			case 2:
			{
				if(lenth>=1)
					move();
				now.Y++;
				break;
			}
			case 3:
			{
				if(lenth>=1)
					move();
				now.X+=2;
				break;
			}
			case 4:
			{
				if(lenth>=1)
					move();
				now.Y--;
				break;
			}
			default:break;
		}
		print();
		if(a_a&&now.X==a.X&&now.Y==a.Y)
		{
			lenth++;
			switch(direction)
			{
				case 1:
				{
					snake[lenth]=snake[lenth-1];
					snake[lenth].X+=2;
					if(snake[lenth].X==48);
					else break;
				}
				case 2:
				{
					snake[lenth]=snake[lenth-1];
					snake[lenth].Y--;
					if(snake[lenth].Y==0);
					else break;
				}
				case 3:
				{
					snake[lenth]=snake[lenth-1];
					snake[lenth].X-=2;
					if(snake[lenth].X==0);
					else break;
				}
				case 4:
				{
					snake[lenth]=snake[lenth-1];
					snake[lenth].Y++;
					if(snake[lenth].Y==24);
					else break;
				}
				default:break;
			}
			a_a=0;
		}
		sleep(150);
		if(kbhit())ch=getch();
	}
	SetConsoleCursorPosition(hOut,{0,25});
	system("pause");
	return 0;
}
void move()
{
	for(int i=1;i<=lenth;i++)
	{
		SetConsoleCursorPosition(hOut,snake[i]);
		printf("■");
		b[snake[i].X][snake[i].Y]=0;
	}
	snake[1]=now;
	for(int i=lenth;i>=2;i--)
		snake[i]=snake[i-1];
}
void print()
{
	SetConsoleTextAttribute(hOut,color1|color2|FOREGROUND_INTENSITY);
	for(int i=1;i<=lenth;i++)
	{
		SetConsoleCursorPosition(hOut,snake[i]);
		printf("★");
	}
	SetConsoleCursorPosition(hOut,now);
	printf("⊙");
	if(a_a)
	{
		SetConsoleTextAttribute(hOut,color2|FOREGROUND_INTENSITY);
		SetConsoleCursorPosition(hOut,a);
		printf("●");
	}
	SetConsoleTextAttribute(hOut,color1|color2|color3|FOREGROUND_INTENSITY);
	SetConsoleCursorPosition(hOut,{6,29});
	printf("%d",lenth);
	SetConsoleTextAttribute(hOut,color1|color3|FOREGROUND_INTENSITY);
}
