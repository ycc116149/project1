#include<ncurses/curses.h>
#include<iostream>
#include<ctime>
#include<unistd.h>
#include"func.cpp"
using namespace std;

int main()
{
	int width,height;
	double u,v,x,y;
	int c,go_on;
	int ran1,ran2,ran3,ran4,ran5,ran6;
	int score=0;
	int length=6;
	time_t t1,t2,t3;//計時
	Time f1;
	Score p1;
	initscr();
	cbreak();
	noecho();
	keypad(stdscr,TRUE);
	nodelay(stdscr,TRUE);
	getmaxyx(stdscr,height,width);
	t1=time(NULL);//進入遊戲時間
	u=v=0;
	x=y=1;
	go_on=1;
	while(go_on){
		while((c=getch())==ERR){
			move(y,x);
			t2=time(NULL);
			t3=t2-t1;//elapsed time
			attrset(A_NORMAL);
			mvaddstr(0,0,"Welcome!!!");
			mvaddstr(1,0,"Press arrow to start");
			for(int i=15;i<20;i++){
				for(int j=15;j<20;j++){
					start_color();//牆壁上色
					init_pair(1,COLOR_BLUE,COLOR_BLUE);
					attrset(COLOR_PAIR(1));
					mvaddstr(i,j,"v");//印牆
				}
			}
			for(int i=6;i<14;i++){
				for(int j=48;j<68;j++){
					mvaddstr(i,j,"v");//印牆
				}
			}
			for(int i=25;i<32;i++){
				for(int j=32;j<38;j++){
					mvaddstr(i,j,"v");//印牆
				}
			}
			attrset(A_NORMAL);//關牆壁顏色
			x+=u/10000;
			if(t3%5==1)
				x+=u/10000;
			for(int i=0;i<=length/2;i++){//印蛇
				if(i!=length/2){
					mvaddstr(y+1,x+i," ");
					mvaddstr(y+1,x-i," ");//把之前經過的消掉
					mvaddstr(y-1,x-i," ");
					mvaddstr(y-1,x+i," ");
					//if(t3%4==0)
					//	attrset(A_BLINK);//test
					mvaddstr(y,x-i,"*");//從中間有蛇
					mvaddstr(y,x+i,"*");
				}
				else{
					mvaddstr(y+1,x+i," ");
					mvaddstr(y+1,x-i," ");
					mvaddstr(y-1,x-i," ");
					mvaddstr(y-1,x+i," ");
					mvaddstr(y,x-i," ");
					mvaddstr(y,x+i," ");
				}
			}
			y+=v/10000;
			if(t3%5==1)
				y+=v/10000;
			for(int i=0;i<=length/2;i++){
				if(i!=length/2){
					mvaddstr(y-1,x+i," ");
					mvaddstr(y-1,x-i," ");
					mvaddstr(y+1,x+i," ");
					mvaddstr(y-1,x-i," ");
				}
				else{
					mvaddstr(y-1,x-i," ");
					mvaddstr(y-1,x+i," ");
					mvaddstr(y+1,x-i," ");
					mvaddstr(y-1,x+i," ");
				}
			}		
			while(x<0)
				x+=width;//從右出現
			while(x>=width)
				x-=width;//從左出現
			while(y<0)
				y+=height;//從下出現
			while(y>=height)
				y-=height;//從上出現
			
		}//while((c=getch())==ERR)	
		switch(c){
			case KEY_LEFT:
				--u;
		 		break;
			case KEY_RIGHT: 
				++u;
				break;
			case KEY_UP: 
				--v;
				break;
			case KEY_DOWN:
			       	++v;
 				break;
			default:
				go_on=0;
		}//switch(c)
		if((15+length/2)<=x && x<=(20-length/2)){
			 if(15<=y && 20>=y)
				 go_on=0;
		}//撞到牆能停
		if((48+length/2)<=x && x<=(68-length/2)){
                         if(6<=y && 14>=y)
                                 go_on=0;
                }//撞到牆能停
		if((32+length/2)<=x && x<=(38-length/2)){
                         if(25<=y && 32>=y)
                                 go_on=0;
                }//撞到牆能停
		if(t3%5==0){
			 srand(time(NULL));
			 ran1=(rand()%50);
			 ran2=(rand()%50);
			 start_color();
			 init_pair(2,COLOR_GREEN,COLOR_BLACK);
			 attrset(COLOR_PAIR(2));
			 mvaddstr(ran1,ran2,"$");//印綠$
			 attrset(A_NORMAL);
			 if(x<=(ran2-length/2) && y==ran1 && x>=(ran2+length/2))//加分
				 score+=10;
		}
		if(t3%5==2){
                         srand(time(NULL));
                         ran3=(rand()%50)-2;
                         ran4=(rand()%50)-2;
                         start_color();
                         init_pair(3,COLOR_RED,COLOR_BLACK);
                         attrset(COLOR_PAIR(3));
                         mvaddstr(ran3,ran4,"$");//印紅$
                         attrset(A_NORMAL);
                         if(x<=(ran4-length/2) && y==ran3 && x>=(ran4+length/2))//毒蘋果
                                 go_on=0;
                }
		if(t3%4==3){
			 srand(time(NULL));
			 ran5=(rand()%50)-3;
    			 ran6=(rand()%50)-3;
			 start_color();
			 init_pair(4,COLOR_YELLOW,COLOR_BLACK);
			 attrset(COLOR_PAIR(4));
			 mvaddstr(ran5,ran6,"?");//印黃?
			 attrset(A_NORMAL);
			 if(x<=(ran6-length/2) && y==ran5 && x>=(ran6+length/2)){//隨機
                                if(t3%2==1)
					 length+=4;//隨機加長
				else{
					 for(int i=0;i<=length/2;i++){//印蛇
				    		 if(i!=length/2){
							 mvaddstr(y+1,x+i," ");
							 mvaddstr(y+1,x-i," ");//把之前經過的消掉
							 mvaddstr(y-1,x-i," ");
							 mvaddstr(y-1,x+i," ");
							 attrset(A_BLINK);
							 mvaddstr(y,x-i,"*");//從中間有蛇
							 mvaddstr(y,x+i,"*");			
						 }
			 		 }
				 }
			 }
		}
		++length;
		refresh();
		if(t3>=60)
			go_on=0;
	}//while(go_on)
	start_color();
	init_pair(3,COLOR_RED,COLOR_BLACK);
	attrset(COLOR_PAIR(3));
	attrset(A_BOLD|A_BLINK|COLOR_PAIR(3));
	if(t3<=60)
		mvaddstr(0,0,"gameover!!");//印gameover
	else
		mvaddstr(0,0,"YOU WIN!!!");//印win
	f1.func();
	cout<<t3<<endl;//印時間
	p1.print();
	cout<<score<<endl;
	attrset(A_NORMAL);
	refresh();
	sleep(5);//停一下看結果
	endwin();
	return 0;
}
