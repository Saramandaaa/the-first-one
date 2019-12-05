#include<cstdio>
#include<conio.h>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<Windows.h>
char a[60][60],ab[60][60];
HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
WORD color1=FOREGROUND_GREEN;
WORD color2=FOREGROUND_RED;
WORD color3=FOREGROUND_BLUE;
int tot=0;
int bi=3;
int live=3;
int num=0;
int bomb=15;
void sleep(int t)
{
	clock_t now=clock();
	while(clock()-now<=t);
}
CHAR_INFO cha[11],chara[11],chr[11];
COORD r,ra,rn;
COORD size,si,siz;
SMALL_RECT st,str,strr;
void print()
{
	COORD loc,strat;
	strat.X=0;strat.Y=0;
	SMALL_RECT region;
	CHAR_INFO ch[1];
	char s[5];
	int l;
	for(int i=1;i<=51;i++)
	{
		for(int j=1;j<=33;j++)
		{
			int ls=0;
			sprintf(s,"%d",live);
			cha[5].Char.AsciiChar=s[0];
			cha[5].Attributes=color1|color2|color3|FOREGROUND_INTENSITY;
			ch[0].Char.AsciiChar=a[i][j];
			sprintf(s,"%d",bi);
			chr[5].Char.AsciiChar=s[0];
			chr[5].Attributes=color1|color2|color3|FOREGROUND_INTENSITY;
			sprintf(s,"%d",tot);
			l=6;
			while(ls<strlen(s))
			{
				chara[l].Char.AsciiChar=s[ls];
				chara[l++].Attributes=color1|color2|color3|FOREGROUND_INTENSITY;
				ls++;
			}
			if(a[i][j]!=ab[i][j])
			{
				if(a[i][j]=='H'||a[i][j]=='V'||a[i][j]=='W')
					ch[0].Attributes=color2|FOREGROUND_INTENSITY;
				else if(a[i][j]=='X')
					ch[0].Attributes=color2|color3|FOREGROUND_INTENSITY;
				else if(a[i][j]=='!'||a[i][j]=='\\'||a[i][j]=='/')
					ch[0].Attributes=color1|FOREGROUND_INTENSITY;
				else ch[0].Attributes=color1|color2|color3|FOREGROUND_INTENSITY;
				loc.X=1;loc.Y=1;
				region.Left=j-1;
				region.Right=j;
				region.Top=i-1;
				region.Bottom=i;
				WriteConsoleOutput(hOut,ch,loc,strat,&region);
			}
			WriteConsoleOutput(hOut,cha,size,r,&st);
			WriteConsoleOutput(hOut,chara,si,ra,&str);
			WriteConsoleOutput(hOut,chr,siz,rn,&strr);
			ab[i][j]=a[i][j];
		}
	}
}
int p[60];
int q[60][60];
int e[16][3];
bool b[60],bo[60];
int pe[60];
int qe[60][60];
int ke=1,kE=1,kV=1;
bool ee[16];
int E[5][3];
int pE[60];
int qE[60][60];
int pV[60];
int qV[60][60];
int V[5][3];
bool Vn[3]={0,0,0},En[3]={0,0,0};
bool Vl,El;
int Enum=1,Vnum=1;
int bnow,by;
int qb[60][3];
bool EEE=1,VVV=1;
SMALL_RECT rc={0,0,100,40};
main()
{
	int kb=1;
	cha[0].Char.AsciiChar='L';
	cha[1].Char.AsciiChar='i';
	cha[2].Char.AsciiChar='f';
	cha[3].Char.AsciiChar='e';
	cha[4].Char.AsciiChar=':';
	chr[0].Char.AsciiChar='B';
	chr[1].Char.AsciiChar='o';
	chr[2].Char.AsciiChar='m';
	chr[3].Char.AsciiChar='b';
	chr[4].Char.AsciiChar=':';
	chara[0].Char.AsciiChar='G';
	chara[1].Char.AsciiChar='r';
	chara[2].Char.AsciiChar='a';
	chara[3].Char.AsciiChar='d';
	chara[4].Char.AsciiChar='e';
	chara[5].Char.AsciiChar=':';
	for(int i=0;i<=4;i++)
	{
		chr[i].Attributes=cha[i].Attributes=color1|color2|color3|FOREGROUND_INTENSITY;
	}
	for(int i=0;i<=5;i++)
		chara[i].Attributes=color1|color2|color3|FOREGROUND_INTENSITY;
	size.X=6;size.Y=1;
	si.X=13;si.Y=1;
	siz.X=6;siz.Y=1;
	ra.X=0;ra.Y=0;
	r.X=0;r.Y=0;
	rn.X=0;rn.Y=0;
	st.Left=0;
	st.Right=6;
	st.Top=51;
	st.Bottom=52;
	str.Left=0;
	str.Right=13;
	str.Top=52;
	str.Bottom=53;
	strr.Left=0;
	strr.Right=6;
	strr.Top=53;
	strr.Bottom=54;
	memset(a,' ',sizeof(a));
	memset(ab,'Z',sizeof(ab));
	SetConsoleWindowInfo(hOut,true,&rc);
	char c='z';
	int i,j;
	bool en=1;
	bool bk=0;
	bool big=0;
	int now=15;
	clock_t n,m=clock(),v; 
	a[51][15]='X';
	printf("按\"A\"、\"D\"键左右移动，按\"W\"键开炮\n");
	printf("或者按\"←\"、\"→\"键左右移动，按\"↑\"键开炮\n");
	printf("敌人飞机：\nH：1*分数\nW：5*分数\nV：5*分数\nW只在分数大于10时出现，V只在分数大于20时出现，\nW和V在被打死之后15s内不会再次出现");
	printf("\n每打完15发炮弹需要1s时间装填。\n按空格可以发大招。");
	printf("\n按任意键开始，按回车键退出\n等待中...\n");
	sleep(3000);
	system("pause");
	system("cls");
	print();
	c=getch();
	n=-15000;
	v=-15000;
	Vl=0;
	El=0;
	while(c!=13&&live>0)
	{
		Vnum=1;
		Enum=1;
		ke++;
		if(El)kE++;
		if(Vl)kV++;
		memset(a,' ',sizeof(a));
		if(c==-32)c=getch();
		if((c=='a'||c=='A'||c==75)&&now>2)
		{
			a[51][--now]='X';
		}
		else if((c=='d'||c=='D'||c==77)&&now<32) 
		{
			a[51][++now]='X';
		}
		else if(c=='w'||c=='W'||c==72)
		{
			if(bomb>0)
			{
				p[now]++;
				bomb--;
				q[now][p[now]]=51;
			}
		}
		else if(c==' '&&bi>0&&!big)
		{
			big=1;
			bi--;
			bnow=51;
			by=now;
		}
		if(bomb==0)kb++;
		if(kb==10)
		{
			kb=1;
			bomb=15;
		}
		if(tot>=150)
		{
			Vnum=2;
			Enum=1;
		}
		if(tot>=250)
		{
			Vnum=2;
			Enum=2;
		}
		if(tot>=500)
		{
			Vnum=3;
			Enum=3;
		}
		if(tot>=20&&Vl==false&&clock()-v>=15000)
		{
			srand(time(0));
			memset(b,1,sizeof(b));
			memset(bo,1,sizeof(bo));
			for(i=1;i<=Vnum;i++)
			{
				int t1=rand()%30+1;
				int t2=rand()%31+2;
				if(b[t1]&&bo[t2])
				{
					V[i][1]=t1;
					V[i][2]=t2;
					V[i][0]=1;
					Vn[i]=1;
				}
			}
			Vl=1;
			VVV=1;
		}
		if(tot>=10&&El==false&&clock()-n>=15000)
		{
			srand(time(0));
			memset(b,1,sizeof(b));
			memset(bo,1,sizeof(bo));
			for(i=1;i<=Enum;i++)
			{
				int t1=rand()%30+1;
				int t2=rand()%31+2;
				if(b[t1]&&bo[t2])
				{
					E[i][1]=t1;
					E[i][2]=t2;
					E[i][0]=1;
					En[i]=1;
				}
			}
			El=1;
			EEE=1;
		}
		if(num==0&&en&&clock()-m>=5000)
		{
			srand(time(0));
			memset(ee,1,sizeof(ee));
			memset(e,0,sizeof(e));
			memset(b,1,sizeof(b));
			memset(bo,1,sizeof(bo));
			num=rand()%3+2;
			if(tot>=300)num=rand()%6+10;
			else if(tot>=200)num=rand()%7+6;
			else if(tot>=100)num=rand()%5+6;
			else if(tot>=50)num=rand()%3+4;
			else if(tot>=30)num=rand()%5+2;
			e[0][0]=1;
			for(i=1;i<=num;i++)
			{
				while(1)
				{
					int t1=rand()%30+1;
					int t2=rand()%31+2;
					if(b[t1]&&bo[t2])
					{
						e[i][0]=-e[i-1][0];
						e[i][1]=t1;
						e[i][2]=t2;
						break;
					}
				}
			}
			en=0;
		}
		if(Vl)
		for(i=1;i<=Vnum;i++)
			if(Vn[i])
			{
				if(kV>=6&&V[i][2]>=3&&V[i][2]<=31)
				{
					pV[V[i][2]]++;
					pV[V[i][2]-1]++;
					pV[V[i][2]+1]++;
					qV[V[i][2]][pV[V[i][2]]]=V[i][1];
					qV[V[i][2]-1][pV[V[i][2]-1]]=V[i][1];
					qV[V[i][2]+1][pV[V[i][2]+1]]=V[i][1];
				}
				if(V[i][2]>=31||V[i][2]<=3)
				{
					V[i][0]=-V[i][0];
					if(V[i][2]>=31)V[i][2]=31;
					else V[i][2]=3;
				}
				if(V[i][0]==1)V[i][2]+=2;
				else V[i][2]-=2;
			}
		if(kV>=6)kV=1;
		if(El)
		for(i=1;i<=Enum;i++)
			if(En[i])
			{
				if(E[i][2]>=2&&E[i][2]<=32)
				{
					pE[E[i][2]]++;
					qE[E[i][2]][pE[E[i][2]]]=E[i][1];
				}
				if(kE>=5)
				{
					if(E[i][2]>=32||E[i][2]<=2)
					{
						E[i][0]=-E[i][0];
						if(E[i][2]>=32)E[i][2]=32;
						else E[i][2]=2;
					}
					if(E[i][0]==1)E[i][2]+=2;
					else E[i][2]-=2;
				}
			}
		if(kE>=5)kE=1;
		for(i=2;i<=32;i++)
		{
			if(p[i]>0)
			{
				for(j=1;j<=p[i];j++)
				{
					q[i][j]--;
					if(q[i][j]>=1)
						a[q[i][j]][i]='!';
				}
				if(q[i][1]<1)
				{
					p[i]--;
					for(int z=1;z<=p[i];z++)
						q[i][z]=q[i][z+1];
					q[i][p[i]+1]=0;
				}
			}
			if(pe[i]>0)
			{
				for(j=1;j<=pe[i];j++)
				{
					qe[i][j]++;
					if(qe[i][j]==51&&i==now)
					{
						live--;
						pe[i]--;
						for(int z=1;z<=pe[i];z++)
							qe[i][z]=qe[i][z+1];
						qe[i][pe[i]+1]=0;
					}
					else if(qe[i][j]<=51)
						a[qe[i][j]][i]='*';
				}
				if(qe[i][1]>51)
				{
					pe[i]--;
					for(int z=1;z<=pe[i];z++)
						qe[i][z]=qe[i][z+1];
					qe[i][pe[i]+1]=0;
				}
			}
			if(pE[i]>0)
			{
				for(j=1;j<=pE[i];j++)
				{
					qE[i][j]++;
					if(qE[i][j]==51&&i==now)
					{
						live--;
						pE[i]--;
						for(int z=1;z<=pE[i];z++)
							qE[i][z]=qE[i][z+1];
						qE[i][pE[i]+1]=0;
					}
					else if(qE[i][j]<=51)
						a[qE[i][j]][i]='^';
				}
				if(qE[i][1]>51)
				{
					pE[i]--;
					for(int z=1;z<=pE[i];z++)
						qE[i][z]=qE[i][z+1];
					qE[i][pE[i]+1]=0;
				}
			}
			if(pV[i]>0)
			{
				for(j=1;j<=pV[i];j++)
				{
					qV[i][j]++;
					if(qV[i][j]==51&&i==now)
					{
						live--;
						pV[i]--;
						for(int z=1;z<=pV[i];z++)
							qV[i][z]=qV[i][z+1];
						qV[i][pV[i]+1]=0;
					}
					else if(qV[i][j]<=51)
						a[qV[i][j]][i]='.';
				}
				if(qV[i][1]>51)
				{
					pV[i]--;
					for(int z=1;z<=pV[i];z++)
						qV[i][z]=qV[i][z+1];
					qV[i][pV[i]+1]=0;
				}
			}
		}
		if(big)
		{
			bnow--;
			if(bnow>=1)
				a[bnow][by]='!';
			if(bnow>=1)
			{
				qb[bnow][1]=by;
				qb[bnow][2]=by;
			}
			for(i=1;i<=51;i++)
			{
				if(qb[i][1]>1)
				{
					qb[i][1]--;
					if(qb[i][1]>=2)
					{
						a[i][qb[i][1]]='/';
						a[i][qb[i][1]-1]='/';
					}
				}
				if(qb[i][2]<33&&qb[i][2]!=0)
				{
					qb[i][2]++;
					if(qb[i][2]<=32)
					{
						a[i][qb[i][2]]='\\';
						a[i][qb[i][2]+1]='\\';	
					}
				}
			}
			if(qb[1][1]==1&&qb[1][2]==33)
			{
				big=0;
				memset(qb,0,sizeof(qb));
			}
		}
		if(ke>=6)
		{
			ke=1;
			for(i=1;i<=num;i++)
			{
				if(ee[i])
				{
					pe[e[i][2]]++;
					qe[e[i][2]][pe[e[i][2]]]=e[i][1];
				}
			}
		}
		for(i=1;i<=num;i++)
			if(ee[i]&&!en)
			{
				if(a[e[i][1]][e[i][2]]=='!'||a[e[i][1]][e[i][2]]=='/'||a[e[i][1]][e[i][2]]=='\\')
				{
					ee[i]=0;
					tot++;
					bk=1;
				}
				else a[e[i][1]][e[i][2]]='H';
			}
		for(i=1;i<=num;i++)
		{
			if(ee[i]&&!en)
			{	
				if(e[i][2]>=32||e[i][2]<=2)e[i][0]=-e[i][0];
				if(e[i][2]>=32)e[i][2]=32;
				else if(e[i][2]<=2)e[i][2]=2;
				if(e[i][0]==1)e[i][2]++;
				else e[i][2]--;
			}
		}
		if(Vl)
		for(i=1;i<=Vnum;i++)
			if(Vn[i]&&a[V[i][1]][V[i][2]]=='!'||a[V[i][1]][V[i][2]]=='/'||a[V[i][1]][V[i][2]]=='\\')
			{
				Vn[i]=0;
				tot+=5;
			}
		if(El)
		for(i=1;i<=Enum;i++)
			if(En[i]&&a[E[i][1]][E[i][2]]=='!'||a[E[i][1]][E[i][2]]=='/'||a[E[i][1]][E[i][2]]=='\\')
			{
				En[i]=0;
				tot+=5;
			}
		if(Vl)VVV=0;
		if(El)EEE=0;
		for(i=1;i<=Vnum;i++)
			if(Vn[i])
			{
				a[V[i][1]][V[i][2]]='V';
				VVV=1;
			}
		for(i=1;i<=Enum;i++)
			if(En[i])
			{
				a[E[i][1]][E[i][2]]='W';
				EEE=1;
			}
		if(!VVV)
		{
			v=clock();
			Vl=0;
			VVV=1;
		}
		if(!EEE)
		{
			n=clock();
			El=0;
			EEE=1;
		}
		a[51][now]='X';
		for(i=1;i<=51;i++)a[i][1]=a[i][33]='|';
		print();
		sleep(50);
		if(kbhit())c=getch();
		else c='z';
		en=1;
		for(i=1;i<=num;i++)
		{
			if(ee[i])
			{
				en=0;
				break;
			}
		}
		if(en)
		{
			num=0;
			if(bk)
			{
				m=clock();
				bk=0;
			}
		}
	}
	if(live<=0)
	{
		SetConsoleTextAttribute(hOut,color2|FOREGROUND_INTENSITY);
		printf("\n     YOU   DIE     \n");
		SetConsoleTextAttribute(hOut,color1|color2|color3|FOREGROUND_INTENSITY);
		printf("     分数：%d\n",tot);
		sleep(2000);
	}
	system("pause");
	return 0;
}
