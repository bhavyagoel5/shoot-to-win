#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<dos.h>
#define ARROW_SIZE 7
#define BUBBLE_SIZE 3

int flag_arrow=0,flag_bubble=1,count_arrow=6,count_bubble=10;
void *bubble,*bow,*arrow,*boom;
void *clear_bubble,*clear_boom;
void draw_bubble(int ,int );
void draw_boom (int x, int y );
void draw_bow(int x,int y);
void draw_arrow(int x, int y);
void shoot(int *x, int *y);
void fly(int *x, int *y);
struct arccoordstype arcinfo;
void start();

void main()
{
int i;
int maxx = getmaxx() ;
int maxy = getmaxy() ;
int p=400,q=300,m=100,n=100,x=m,y=n,key,score=0,finish=0,level=1,l_flag=1;
char score1[5],ch,cnt_ball[5],char_level[2];
int gmode = DETECT, gdriver , area ;
front();
initgraph ( &gmode, &gdriver, "c:/tc/bgi") ;

setbkcolor(8);
start();

	rectangle ( 0, 0, maxx, maxy - 10 ) ;

	draw_boom(300,400);
	area=imagesize(0,0,32,24);
	boom=malloc(area);
	getimage(300-16,400-12,300+16,400+12,boom);
	putimage(300-16,400-12,boom,XOR_PUT);

	draw_bubble(p,q);

area=imagesize(p-5*BUBBLE_SIZE,q-6*BUBBLE_SIZE,p+5*BUBBLE_SIZE,q+8*BUBBLE_SIZE);
bubble=malloc(area);

getimage(p-5*BUBBLE_SIZE,q-6*BUBBLE_SIZE,p+5*BUBBLE_SIZE,q+8*BUBBLE_SIZE,bubble);
	putimage(p-5*BUBBLE_SIZE, q-6*BUBBLE_SIZE, bubble, COPY_PUT);

	draw_arrow(x ,y  );
	area = imagesize(x, y-ARROW_SIZE, x+(7*ARROW_SIZE), y+ARROW_SIZE);
	arrow=malloc(area);
	getimage(x, y-ARROW_SIZE, x+(7*ARROW_SIZE), y+ARROW_SIZE,arrow);
	putimage(x, y-ARROW_SIZE,arrow,XOR_PUT);

	draw_bow(x,y);
	area=imagesize(x+26,y-66,x+67,y+66);
	bow=malloc(area);
	getimage(x+26,y-66,x+67,y+66,bow);

	if ( bubble == NULL || boom == NULL || bow == NULL )
	{
		printf( "ERROR ERROR... Press any key " ) ;
		getch() ;
		closegraph() ;
		restorecrtmode() ;
		exit( 0 ) ;
	}

	while (!finish)
	{
		setbkcolor(YELLOW);
		settextstyle(8,0,1);
		setusercharsize(5,5,4,4);
		outtextxy(getmaxx()/2-100,5,"LEVEL : ");
		itoa(level,char_level,10);
		setfillstyle(0,0);
		bar(getmaxx()/2+40,15,getmaxx()/2+70,45);
		outtextxy(getmaxx()/2+50,5,char_level);
		rectangle(6,360,250,460);
	   if( kbhit() )
		{
		key = getch();
		if(key==77)
		flag_arrow = 1;
		shoot(&x,&y);
		draw_bow(m,y);

		}

		if( key == 27 )
		break;
		if(count_arrow > 0 && count_bubble > 0)
		{
	if(score==100 && l_flag==1)
	{
		  level=2;
		  count_bubble=8;
		  count_arrow=6;
		  l_flag=2;
	}
	if(score==180 && l_flag==2)
	{
		 level=3;
		 count_bubble=6;
		 count_arrow=6;
		 l_flag=0;
	}
		if( flag_bubble && count_bubble >0 )
		fly( &p, &q );
		else
	{
		q = 400;
		flag_bubble = 1;
		continue;
	}
	if( key == 77 || flag_arrow)
		  {
		shoot(&x,&y);
		draw_bow(m,y);
		if(x>(p-12) && x<(p+12) && y>(q-15) && y<(q+25))
		{
		putimage(p-16,q-12,boom,COPY_PUT);
		sound(1500);
		delay(100);
		nosound();
		putimage(p-16,q-12,boom,XOR_PUT);
		count_bubble--;
		settextstyle(10,0,1);
		setusercharsize(30,70,20,70);
		outtextxy(20,380,"BUBBLES LEFT:");
		setfillstyle(0,0);
		bar(200,370,230,400);
		itoa(count_bubble,cnt_ball,10);
		outtextxy(200,380,cnt_ball);
		flag_bubble=0;
		score+=20;
		itoa(score,score1,10);
		setfillstyle(0,0);
		bar(190,getmaxy()-50,230,getmaxy()-30);
		setcolor(BLUE);
		outtextxy(20,getmaxy()-50,"SCORE          : ");
		outtextxy(190,getmaxy()-50,score1);
		}
		 shoot(&x,&y);
		 draw_bow(m,y);
		fly( &p, &q );
		key=0;
		 }
		}
		else
		{
	clearviewport();
	for(i=1;i<=51;i+=4)

{
sound(400-i);


	setbkcolor(11);
	setcolor(MAGENTA);
	settextstyle(0,0,7);
	setusercharsize(120,50,120,40);
	outtextxy(getmaxx()/2-220,getmaxy()/2-180,"GAME OVER ");

	settextstyle(8,0,1);
	setusercharsize(50,60,40,50);
	if(count_arrow<=0)
	outtextxy(getmaxx()/2-100,getmaxy()/2-70,"NO MORE ARROWS");

	if(count_bubble<=0)
	outtextxy(getmaxx()/2-120,getmaxy()/2-70,"NO MORE BUBBLES");

	outtextxy(getmaxx()/2-120,getmaxy()/2-20,"YOUR SCORE IS : ");
	itoa(score,score1,10);
	outtextxy(getmaxx()/2+150,getmaxy()/2-20,score1);

	if(level==1)
	outtextxy(getmaxx()/2-220,getmaxy()/2+20,"BETTER LUCK NEXT TIME");
	if(level==2)
	outtextxy(getmaxx()/2-70,getmaxy()/2+20,"WELL PLAYED");
	if(level==3)
	outtextxy(getmaxx()/2-220,getmaxy()/2+20,"IMPRESSIVE AND EFFICIENT SHOOTER");

	outtextxy(getmaxx()/2-30,getmaxy()/2+50,"(Q)UIT ");

	settextstyle(1,0,1);
	setusercharsize(30,65,30,60);
	while( getch() != 'q' || getch() != 'Q');
	finish=1;
	break;
	}

nosound();

go(0,60,20,80,random(15),random(15));

delay(10);

go(400,460,420,480,random(15),random(15));

 delay(10);

		 }
	}
   free(bow);
   free(arrow);
   free(bubble);
   closegraph();
}

void draw_bubble(int x,int y)
{
	 setcolor(BLUE);
	 setfillstyle(1,BLUE);
	 fillellipse(x,y,4*BUBBLE_SIZE,5*BUBBLE_SIZE);
	// line(x,y+5*BUBBLE_SIZE,x,y+7*BUBBLE_SIZE);
}

void draw_boom ( int x, int y )
{
	setlinestyle(0,0,3);
	line ( x - 16, y - 12, x - 10, y - 2 ) ;
	line ( x - 10, y - 2, x - 16, y ) ;
	line ( x - 16, y, x - 10, y + 2 ) ;
	line ( x - 10, y + 2, x - 16, y + 12 ) ;

	line ( x - 16, y + 12, x - 6, y + 2 ) ;
	line ( x - 6, y + 2, x, y + 12 ) ;
	line ( x, y + 12, x + 6, y + 2 ) ;
	line ( x + 6, y + 2, x + 16, y + 12 ) ;

	line ( x - 16, y - 12, x - 6, y - 2 ) ;
	line ( x - 6, y - 2, x, y - 12 ) ;
	line ( x, y - 12, x + 6, y - 2 ) ;
	line ( x + 6, y - 2, x + 16, y - 12 ) ;

	line ( x + 16, y - 12, x + 10, y - 2 ) ;
	line ( x + 10, y - 2, x + 16, y ) ;
	line ( x + 16, y, x + 10, y + 2 ) ;
	line ( x + 10, y + 2, x + 16, y + 12 ) ;

}

void draw_bow(int x,int y)
{
	setcolor(RED);
	setlinestyle(0,0,3);
	line(x+32,y-49,x+32,y+49);
	setlinestyle(0,0,3);
	arc(x,y,300,60,60);
	arc(x+34,y-56,100,220,6);
	arc(x+34,y+56,140,260,6);
}

void shoot(int *x, int *y)
{
	char cnt_arrow[5];
	putimage(*x, *y-ARROW_SIZE, arrow, COPY_PUT);
	delay(2);
	putimage(*x, *y-ARROW_SIZE, arrow, XOR_PUT);
	*x+=ARROW_SIZE;

	if (*x>590)
	{
		*x=155;
		flag_arrow=0;
		count_arrow--;
		settextstyle(10,0,1);
		setusercharsize(30,70,20,70);
		outtextxy(20,400,"ARROWS LEFT :");
		setfillstyle(0,WHITE);
		bar(200,400,220,425);
		itoa(count_arrow,cnt_arrow,10);
		outtextxy(200,400,cnt_arrow);
	}

}
void draw_arrow(int x, int y)
{
   setcolor(RED);
	setlinestyle(0,0,3);
	moveto(x, y);
	linerel(6*ARROW_SIZE, 0);
	linerel(-2*ARROW_SIZE, -1*ARROW_SIZE+1);
	linerel(0, 2*ARROW_SIZE-1);
	linerel(2*ARROW_SIZE, -1*ARROW_SIZE);
}

void fly(int *x, int *y)
{
	int x1;
	char cnt_ball[5];
	putimage(*x-5*BUBBLE_SIZE, *y-6*BUBBLE_SIZE, bubble, COPY_PUT);
	delay(20);

	putimage(*x-5*BUBBLE_SIZE, *y-6*BUBBLE_SIZE, bubble, XOR_PUT);
	*y-=BUBBLE_SIZE;

	if(*y<= 20)
	{
		*y=400;
		x1=450+rand()%150;
		*x=x1;
		count_bubble--;
		settextstyle(10,0,1);
		setusercharsize(30,70,20,70);
		outtextxy(20,380,"BUBBLES LEFT:");
		setfillstyle(0,0);
		bar(200,370,230,400);
		itoa(count_bubble,cnt_ball,10);
		outtextxy(200,380,cnt_ball);
	}
}

void start()
{       float octave[7] = { 130.81, 146.83, 164.81, 174.61, 196, 220, 246.94};
       setbkcolor(14);
       setcolor(3);
	settextstyle(7,0,0);

	outtextxy(10,400,"  PRESS ANY KEY TO CONTINUE....");
	settextstyle(0,0,5);
	setcolor(5);
	setusercharsize(25,15,20,4);
	outtextxy(85,120,"SHOOT TO WIN");

	while( !kbhit() )
	{
		sound( octave[ random(7) ]*4 );
		delay(250);
	}
	nosound();
	getch();
	clearviewport();
	rectangle(1,1,638,478);
	settextstyle(3,0,1);
	setusercharsize(50,30,50,30);
	outtextxy(150,10,"INSTRUCTIONS");
	setbkcolor(11);
	settextstyle(1,0,1);
	setusercharsize(40,70,20,20);
	outtextxy(10,70,"1. There are three levels.");
	outtextxy(10,110,"2. Press right arrow key to shoot the arrow.");
	outtextxy(10,150,"3. You score 20 points every time you shoot the bubble.");
	outtextxy(10,190,"4. First level has 6 arrows and 10 bubbles.");
	outtextxy(10,230,"5. You require to score 100 points to enter the second level.");
	outtextxy(10,270,"6. Second level has 6 arrows and 8 bubble.");
	outtextxy(10,310,"7. You require to score 200 points to enter the third level.");
	outtextxy(10,350,"8. Third level has 6 arrows and 6 bubbles.");
	settextstyle(7,0,1);
	outtextxy(150,440,"PRESS ANY KEY TO CONITINUE............");

	getch();
	setusercharsize(1,1,1,1);
	settextstyle(0,0,0);
	setbkcolor(11);
	setcolor(BROWN);
	clearviewport();
	}


go(int sy1,int ey1,int sy2,int ey2,int k,int h)

{

int i,j;

for(j=sy1;j<=ey1;j+=40)

{



for(i=0;i<=640;i+=40)

{



setcolor(k);

rectangle(i,1+j,20+i,21+j);

setfillstyle(SOLID_FILL,k);

floodfill(10+i,10+j,k);

setcolor(h);

rectangle(20+i,1+j,40+i,21+j);

setfillstyle(SOLID_FILL,h);

floodfill(25+i,10+j,h);

}

}

for(j=sy2;j<=ey2;j+=40)

{



for(i=0;i<=640;i+=40)

{



setcolor(h);

rectangle(i,1+j,20+i,21+j);

setfillstyle(SOLID_FILL,h);

floodfill(10+i,10+j,h);

setcolor(k);

rectangle(20+i,1+j,40+i,21+j);

setfillstyle(SOLID_FILL,k);

floodfill(25+i,10+j,k);

}

}

//

}

 sta()

{

 int x,y=200,st,kl;

 //initgraph(&gd,&gm,"");

  setcolor(5);



 for(st=190;st>=-20;st-=9)

 {

 setcolor(GREEN);

 arc(320,290,st,st+2,190);

	   getarccoords(&arcinfo);

			  delay(5);

	   x=arcinfo.xend;

	   y=arcinfo.yend;

	   sound(300-st);

      star(x,y);

      delay(24);

 }

 for(st=190;st>=-17;st-=9)

 {

 setcolor(YELLOW);

 arc(320,285,st,st+2,230);

	   getarccoords(&arcinfo);

			  delay(5);

	   x=arcinfo.xend;

	   y=arcinfo.yend;

	   sound(320-st);

      star(x,y);

      delay(24);

 }

 nosound();

 settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
  delay(1);

  setcolor(4);


 outtextxy(420,230,"E");  //440
  outtextxy(390,230,"M");   // 420
  outtextxy(360,230,"O");  //400
  outtextxy(330,230,"C"); //380
  outtextxy(300,230,"L");  //360
  outtextxy(270,230,"E");     // 340
  outtextxy(240,230,"W");   //320
  delay(500);
 }

 star(x,y)

 {

 delay(80);

 line(x,y,x+5,y-7);    // /1     x=320, y=240

 line(x+5,y-7,x+10,y);    // 1

 line(x+10,y,x+17,y);    // right hori

 line(x,y,x-7,y); //left hori

 line(x-7,y,x-2,y+7);  // left horiz to right

 line(x+17,y,x+12,y+7); // right horiz to left /

 line(x+12,y+7,x+14,y+13); // left / to right

 line(x-2,y+7,x-4,y+13); // right  to left /

 line(x-4,y+13,x+5,y+7);

 line(x+14,y+13,x+5,y+7);

 }

front()

{

int gm=0,gd=DETECT,i,j,k,gh;

initgraph(&gd,&gm,"c:/turboc3/bgi");

setcolor(MAGENTA);

rectangle(10,10,639,469);

rectangle(12,12,637,467);

for(i=12;i<=627;i+=12)

{



setcolor(YELLOW);

line(i,12,i,467);

//clearviewport();

for(j=15;j<=464;j+=5)

ellipse(i+6,j,-180,0,6,4);



}

for(i=3;i<=452;i+=5)

{ for(j=15;j<=627;j+=3)

  {setcolor(0);

   ellipse(j,467-i,-180,0,3,4);

   }delay(40);

   setcolor(BLACK);

   for(k=1;k<=5;k++)

   {

   line(12,467-i+k,637,467-i+k); }

 //setcolor(25);

  setcolor(GREEN+MAGENTA+WHITE+BLUE+YELLOW);

rectangle(10,10,639,469);

rectangle(12,12,637,467);



}

sta();

sleep(.1);

//closegraph();

}
