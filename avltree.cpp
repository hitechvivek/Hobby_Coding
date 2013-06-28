#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>

struct avl
{	long int d;
	struct avl *lc,*rc;
	int h;
}*t,*p,*q,*r,*t1;


struct avl * llrot(struct avl* &p);
struct avl * rrrot(struct avl* &p);
struct avl * lrrot(struct avl* &p);
struct avl * rlrot(struct avl* &p);

void show(struct avl *t1);

int gdriver=DETECT,gmode=0,errorcode;
char temp[3];
int maxx,midx,x1,y1,lvl=275;

int height(struct avl *x)
{	if(x==NULL)
	{	return(-1);	}
	else
	{	return(x->h);	}
}

int balance(struct avl *x)
{	int t1,t2;
	t1= height(x->lc);
	t2= height(x->rc);
	return t2-t1;
}

void Display(struct avl *p,int x1,int y1)
{	if (p!=NULL)
	{	lvl=lvl/2;
		setcolor(CYAN);
		if(p->lc->d!=NULL)
			line(x1,y1,x1-lvl,y1+50);
		if(p->rc->d!=NULL)
			line(x1,y1,x1+lvl,y1+50);
		setfillstyle(1,CYAN);
		fillellipse(x1,y1,10,10);
		sprintf(temp,"%d",p->d,x1,y1);
		settextstyle(2,0,4);
		setcolor(YELLOW);
		outtextxy(x1-7,y1-7,temp);
		sprintf(temp,"%d",balance(p),x1,y1);
		outtextxy(x1-15,y1-15,temp);
		settextstyle(2,0,6);
		setcolor(YELLOW);
		Display(p->lc,x1-(lvl),y1+50);
		Display(p->rc,x1+(lvl),y1+50);
		lvl=lvl*2;
	}
}

int max(int a,int b)
{	if(a>b)
	{	return a;	}
	else
	{	return b;	}
}

long int  dt;

long int get(long int dt1)
{	char x[20];
	gets(x);
	dt1=atol(x);
	if((dt1<=0)||(dt1>=1000))
	{	cout<<"\n\nINVALID DATA....";
		cout<<"\n\nRE-ENTER THE DATA ";
		dt1=get(dt1);
	}
	return dt1;
}

void insert1(long int x,struct avl * &p)
{	if (p == NULL)
	{	p = new avl;
		p->d = x;
		p->lc=NULL;
		p->rc = NULL;
		p->h=0;
	}
	else
	{	if (x<p->d)
		{	insert1(x,p->lc);
			if ((height(p->lc) - height(p->rc))==2)
			{	if (x < p->lc->d)
					p = llrot(p);
				else
				p = lrrot(p);
			}
		}
		else if (x>p->d)
		{	insert1(x,p->rc);
			if ((height(p->rc) - height(p->lc))==2)
			{	if (x > p->rc->d)
					p = rrrot(p);
				else
					p = rlrot(p);
			}
		}
		else
		{	cout<<"\n\n SORRY ALREADY EXISTS.....RE- ENTER A VALUE CORRECTLY..";
			getch();
		}
	}
	p->h=max(height(p->lc),height(p->rc))+1;
}

struct avl* llrot(struct avl* &p)
{	initgraph(&gdriver, &gmode, "e:\\tc\\bgi");
	Display(t,getmaxx()/2,40);
	getch();
	struct avl *q;
	q=p->lc;
	p->lc=q->rc;
	q->rc=p;
	p->h=max(height(p->lc),height(p->rc))+1;
	q->h=max(height(q->lc),height(q->rc))+1;
	return q;
}

struct avl* rrrot(struct avl* &p)
{	initgraph(&gdriver, &gmode, "e:\\tc\\bgi");
	Display(t,getmaxx()/2,40);
	getch();
	struct avl *q;
	q=p->rc;
	p->rc=q->lc;
	q->lc=p;
	p->h=max(height(p->lc),height(p->rc))+1;
	q->h=max(height(q->lc),height(q->rc))+1;
	return q;
}

struct avl* lrrot(struct avl* &p)
{
	initgraph(&gdriver, &gmode, "e:\\tc\\bgi");
	struct avl *q,*r;
	q=new avl;	r=new avl;
	q=p->lc;	r=q->rc;
	p->lc=r->rc;	q->rc=r->lc;
	r->lc=q;	r->rc=p;
	return(r);

}

struct avl* rlrot(struct avl* &p)

{
	initgraph(&gdriver, &gmode, "e:\\tc\\bgi");
	struct avl *q,*r;
	q=new avl;	r=new avl;
	q=p->rc;	r=q->lc;
	p->rc=r->lc;	q->lc=r->rc;
	r->rc=q;	r->lc=p;
	return(r);
}

void main()
{
	int op;
	int again;
	clrscr();
	while(1)
	{	cout<<"\n\n1.INSERT\n\n2.EXIT";
		cout<<"\n\nENTER THE OPTION : ";
		op=get(op);
		if(op==1)
		{	cout<<"\nENTER THE DATA : ";
			dt=get(dt);
			insert1(dt,t);
			initgraph(&gdriver, &gmode, "e:\\tc\\bgi");
			Display(t,getmaxx()/2,40);
			getch();
		}
		else
		{	exit(0);	}
	}
}