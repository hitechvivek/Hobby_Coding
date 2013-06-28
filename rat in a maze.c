#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>
void size();
void createmaze();
void path();

int gd=DETECT,gm,mazerow,mazecol,maze[30][30],mark[30][30],move[8][2]={-1,0,0,1,-1,1,1,1,1,0,1,-1,0,-1,-1,-1};
int stack[1000][3],sx,sy,fx,fy,top;

void main()
{
size();
clrscr();
createmaze();
}

void size()
{
int i,checkrow=0,checkcol=0,checksx=0,checksy=0,checkfx=0,checkfy=0;
char mr[10],mc[10],msx[10],msy[10],mfx[10],mfy[10];
clrscr();
initgraph(&gd,&gm,"c:\\tc\\bgi");
settextstyle(1,0,3);
printf("\n\tENTER THE SIZE OF THE MAZE \n");
do
{
printf("\n\tROW SIZE (Less than 20)\t:");
gets(mr);
mazerow=atoi(mr);
checkrow=0;
if(mazerow>20||mazerow<1)
{
printf("\n\tINVALID ENTRY\n");
checkrow=1;
}
}while(checkrow==1);

do
{
printf("\n\tCOLUMN SIZE (Less than 20)\t:");
gets(mc);
mazecol=atoi(mc);
checkcol=0;
if(mazecol>20||mazecol<1)
{
printf("\n\tINVALID ENTRY\n");
checkcol=1;
}
}while(checkcol==1);


do
{
printf("\n\tENTER THE X COORDINATE OF THE STARTING POINT\t:");
gets(msx);
sx=atoi(msx);
checksx=0;
if(sx>mazerow||sx<1)
{
printf("\n\tINVALID ENTRY (Enter Value Less than %d)\n",mazerow);
checksx=1;
}
}while(checksx==1);

do
{
printf("\n\tENTER THE Y COORDINATE OF THE STARTING POINT\t:");
gets(msy);
sy=atoi(msy);
checksy=0;
if(sy>mazecol||sy<1)
{
printf("\n\tINVALID ENTRY (Enter Value Less than %d)\n",mazecol);
checksy=1;
}
}while(checksy==1) ;

do
{
printf("\n\tENTER THE X COORDINATE OF THE END POINT\t:");
gets(mfx);
fx=atoi(mfx);
checkfx=0;
if(fx>mazerow||fx<1)
{
printf("\n\tINVALID ENTRY (Enter Value Less than %d)\n",mazerow);
checkfx=1;
}
}while(checkfx==1);

do
{
printf("\n\tENTER THE Y COORDINATE OF THE END POINT\t:");
gets(mfy);
fy=atoi(mfy);
checkfy=0;
if(fy>mazecol||fy<1)
{
printf("\n\tINVALID ENTRY (Enter Value Less than %d)\n",mazecol);
checkfy=1;
}
}while(checkfy==1);
}

void createmaze()
{
int getx=getmaxx(),gety=getmaxy(),x,y,i,j;
char changemaze;
initgraph(&gd,&gm, "c:\\tc\\bgi");
for(i=0;i<13;i++)
{
setcolor(i);
setlinestyle(i,i+1,3);
rectangle(1+i,1+i,getx-1-i,gety-1-i);
delay(65);
}
setlinestyle(0,0,0);
setcolor(WHITE);
randomize();
for(i=1;i<=mazerow;i++)
{
for(j=1;j<=mazecol;j++)
{
maze[i][j]=random(3)%2;
mark[i][j]=maze[i][j];
}
}

for(i=0;i<=mazecol+1;i++)
{
mark[0][i]=1;
maze[0][i]=1;
}

for(i=0;i<=mazerow+1;i++)
{
mark[i][mazecol+1]=1;
maze[i][mazecol+1]=1;
}

for(i=0;i<=mazecol+1;i++)
{
maze[mazerow+1][i]=1;
mark[mazerow+1][i]=1;
}

for(i=0;i<=mazerow+1;i++)
{
mark[i][0]=1;
maze[i][0]=1;
}

maze[sx][sy]=0;
mark[sx][sy]=maze[sx][sy];
maze[fx][fy]=0;
mark[fx][fy]=maze[fx][fy];

for(i=0,y=35;i<=mazerow+1;i++,y=y+18)
{
for(j=0,x=35;j<=mazecol+1;j++,x=x+18)
{
if(mark[i][j]==1)
{
setfillstyle(INTERLEAVE_FILL,RED);
bar(x,y,x+18,y+18);
rectangle(x,y,x+18,y+18);
}

else
{
setfillstyle(SOLID_FILL,BLACK);
bar(x,y,x+18,y+18);
rectangle(x,y,x+18,y+18);
}
}
}


for(i=0,y=35;i<=mazerow+1;i++,y=y+18)
{
for(j=0,x=35;j<=mazecol+1;j++,x=x+18)
{
if(i==sx && j==sy)
{
setcolor(WHITE);
outtextxy(x+5,y+5,"S");
}
else
if(i==fx&&j==fy)
{
setcolor(WHITE);
outtextxy(x+5,y+5,"E");
}
}
}
setcolor(WHITE);
for(i=0;i<12;i++)
			      {
			      setcolor(i);
			      outtextxy(35,20,"FOR NEW MAZE PRESS 'N'");
			      delay(100);
			      }
			      changemaze=getch();
			      if(changemaze=='n'||changemaze=='N')
			   {
			   createmaze();
			   }
else
path();
}

void path()
{
int row,col,dir,nextrow,nextcol,i;
stack[1][0]=sx;
stack[1][1]=sy;
stack[1][2]=-1;
top=1;
while(top!=0)
{
	row=stack[top][0];
	col=stack[top][1];
	dir=stack[top][2]+1;
	mark[sx][sy] =1;
	top=top-1;
	while(dir<=7)
		{
			      nextrow=row+move[dir][0];
			      nextcol=col+move[dir][1];
			      if(nextrow==fx && nextcol==fy)
			      {
			      setcolor(CYAN);
			      outtextxy(35+(fy*18)+5,35+(fx*18)+5,"\2");
			      outtextxy(270,20,"DESTINATION REACHED");
			      sound(435);
			      delay(250);
			      nosound();
			      getch();
			      exit(0);
			      restorecrtmode();
			      closegraph();
			      }
		else if(maze[nextrow][nextcol]==0  && mark[nextrow][nextcol]==0)
				{
					setcolor(YELLOW);
					mark[nextrow][nextcol]=1;
					top=top+1;
					stack[top][0]=row;
					stack[top][1]=col;
					stack[top][2]=dir;
					row=nextrow;
					col=nextcol;
				setcolor(YELLOW);
				outtextxy(35+col*18+5,35+row*18+5,"\2");
				delay(300);
				setcolor(MAGENTA);
				delay(5);
				outtextxy(35+col*18+5,35+row*18+5,"\1"); 				dir=-1;
				}
				dir=dir+1;
		}
	setcolor(BLUE);
	outtextxy(35+col*18+5,35+row*18+5,"\2");
	setcolor(BLACK);
	outtextxy(35+18*(col)+5,35+18*(row)+5,"\1");
	delay(200);
	}
outtextxy(300,18,"NO PATH");
getch();
closegraph();
restorecrtmode();
}