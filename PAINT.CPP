#include<iostream.h>
#include<stdio.h>
#include<conio.h>
//#include<windows.h>
//#include"helper.h"
#include<dos.h>
#include<graphics.h>
int k=0;
union REGS in ,out;

     void showmouse_graphics()
     {

	in.x.ax=1;
	int86(0X33,&in,&out);
       //	delay(5000);


     }
     void hide_mouse()
     {

	in.x.ax=2;
	int86(0X33,&in,&out);
       //	printf("\nMouse has been hidden");
     }
     void detect()
     {

	while(!kbhit())
	{
		int x,y;
		showmouse_graphics();
		in.x.ax=3;
		int86(0X33,&in,&out);

	      //	printf("%d",out.x.bx);

		if(out.x.bx==1)
		{
			x=out.x.cx;
			y=out.x.dx;
			printf("\nLeft|| X-%d Y-%d",x,y);
		}
		delay(100);
	}
     }
     void detect_mouse()
     {
	in.x.ax=0;
	int86(0X33,&in,&out);
	if(out.x.ax==0)
	printf("\nMouse failed to initialize");
     //	else
      //	printf("\nMouse was successfully loaded");
     }
     void set()
     {
		in.x.ax=4;
		in.x.cx=300;
		in.x.dx=250;
		int86(0X33,&in,&out);
     }
     get_mouse_pos(int *x,int *y,int *button)
     {
	in.x.ax=3;
	int86(0X33,&in,&out);
	*x=out.x.cx ;
	*y=out.x.dx;
	*button=out.x.bx&1;
     }
    // long int size=imagesize(60,50,600,400);
     save_image()
     {
		FILE *fp=fopen("image.dat","wb");
		for(int i=60;i<=600;i++)
		{
			for(int j=50;j<=400;j++)
			{
				int cr=getpixel(i,j);
				fwrite(&cr,2,1,fp);
			}
		}

		fclose(fp);
		setcolor(15);
		outtextxy(230,410,"IMAGE SAVED SUCCESSFULLY");
     }
	void save_undo()
	{
		char fnm[20];
		if(k==4)
		k=0;
		printf("%d ",k);
		sprintf(fnm,"image%d.dat",k);
		k++;
		FILE *fp=fopen(fnm,"wb");
		for(int i=60;i<=600;i++)
		{
			for(int j=50;j<=400;j++)
			{
				int cr=getpixel(i,j);
				fwrite(&cr,2,1,fp);
			}
		}

		fclose(fp);
     }
     void undo()
     {
		char fnm[20];
		 int d=--k;
		sprintf(fnm,"image%d.dat",d);
		FILE *fp=fopen(fnm,"rb");
		int cr;
		for(int i=60;i<=600;i++)
		{
			for(int j=50;j<=400;j++)
			{
				fread(&cr,2,1,fp);
				putpixel(i,j,cr);
			}
		}
		fclose(fp);

     }
     load_image()
     {
		FILE *fp=fopen("image.dat","rb");
		int cr;
		for(int i=60;i<=600;i++)
		{
			for(int j=50;j<=400;j++)
			{
				fread(&cr,2,1,fp);
				putpixel(i,j,cr);
			}
		}
		fclose(fp);
     }
     void Flood_Fill(int x,int y,int i)
     {
    //	cout<<i;
	if(getpixel(x,y)!=15)
	return;
	putpixel(x,y,i);
	Flood_Fill(x, y+1,i);
	Flood_Fill( x+1, y,i);
	Flood_Fill( x, y-1,i);
	Flood_Fill( x-1, y,i);
	return;
     }
     int main()
     {
	int gd=DETECT,gm,errorcode;
	int x1,i,y1,x2,y2,button,cr=0;
	int flg1=1,flg2=0,flg10=0,flg4=0,flgu=0;
	initgraph(&gd,&gm,"C:\\tc\\bgi");
	detect_mouse();
	outtextxy(230,400,"Press any key to exit");
	for(i=0;i<=15;i++)
	{       setcolor(15);
		setfillstyle(1,i);
		rectangle(1,30+20*(i+1),50,30+20*(i+2));
		floodfill(2,30+(20*(i+1))+1,15);
	}
	rectangle(300,20,350,40);
	rectangle(350,20,400,40);
	rectangle(400,20,450,40);
	rectangle(450,20,500,40);
	rectangle(500,20,550,40);
	rectangle(550,20,600,40);
	rectangle(600,20,650,40);
	rectangle(250,20,300,40);
	outtextxy(250,22,"UNDO");
	outtextxy(300,22,"ERASER");
	outtextxy(350,22,"PENCIL");
	outtextxy(400,22,"SAVE");
	outtextxy(450,22,"LOAD");
	outtextxy(500,22,"CLEAR");
	outtextxy(550,22,"COLOUR");
	outtextxy(600,22,"BOLD");
	setcolor(15);
	setfillstyle(1,15);
	rectangle(60,50,600,400);
	floodfill(61,51,15);
	while(!kbhit())
	{
		showmouse_graphics();
		get_mouse_pos(&x1,&y1,&button);
		if(x1<=50)
		for(i=0;i<=15;i++)
		{
			if(x1>1&&x1<50&&y1>30+20*(i+1)&&y1<30+20*(i+2))
			{setcolor(i);
			cr=i;
			}
		}
	     //	get_mouse_pos(&x1,&y1,&button);
		if(x1>250 &&x1<300&&y1>20&&y1<40&&button==1)
		{
		       undo();
		}
		if(x1>300 &&x1<350&&y1>20&&y1<40&&button==1)
		{
			flg1=0;flg2=1;flg10=0;flg4=0;
		}
	   //	get_mouse_pos(&x1,&y1,&button);
		if(x1>350&&x1<400&&y1>20&&y1<40&&button==1)
		{
			flg1=1;flg2=0;flg10=0;flg4=0;
		}
	     //	get_mouse_pos(&x1,&y1,&button);
		if(x1>400&&x1<450&&y1>20&&y1<40&&button==1)
		{
			save_image();
		}
	     //	get_mouse_pos(&x1,&y1,&button);
		if(x1>450&&x1<500&&y1>20&&y1<40&&button==1)
		{
			load_image();
		}
	   //	get_mouse_pos(&x1,&y1,&button);
		if(x1>500&&x1<550&&y1>20&&y1<40&&button==1)
		{

			setcolor(15);
			setfillstyle(1,15);
			bar(60,50,600,400);
		}
	   //	get_mouse_pos(&x1,&y1,&button);
		if(x1>550&&x1<600&&y1>20&&y1<40&&button==1)
		{
			outtextxy(230,420,"floodfill");
			flg10=1;
			flg1=0;flg2=0;flg4=0;
		}
		if(x1>600&&x1<650&&y1>20&&y1<40&&button==1)
		{
			 flg4=1;flg1=0;flg2=0;flg10=0;
		}
		if(flg10==1)
		{
		      //	get_mouse_pos(&x1,&y1,&button);
			if(button==1)
			Flood_Fill(x1,y1,cr);
		}
      //		get_mouse_pos(&x1,&y1,&button);
		x2=x1;
		y2=y1;
		while(button==1)
		{
			hide_mouse();
			if(flg1==1)
			line(x1,y1,x2,y2);
			if(flg2==1)
			{
				showmouse_graphics();
				setcolor(15);
				setfillstyle(1,15);
				if((x1>290&&x1<360&&y1>10&&y1<50))
				{
				}
				else
				{
					circle(x1,y1,10);
					floodfill(x1,y1,15);
				}
			}
			if(flg4==1)
			{
			     //	showmouse_graphics();
				hide_mouse();
				setcolor(cr);
				setfillstyle(1,cr);
				if((x1>590&&x1<660&&y1>10&&y1<50))
				{
				}
				else if(x1>490&&x1<560&&y1>10&&y1<50)
				{
				}
				else
				{
					circle(x1,y1,10);
					floodfill(x1,y1,cr);
				}


			}

			x1=x2;
			y1=y2;
			get_mouse_pos(&x2,&y2,&button);
			flgu=1;
		}
	       /*	if(flgu==1)
		{
			save_undo();
			flgu=0;
		}
		 */
	  }

	getch();
	return 1;
     }
