/*  Date   : 25th October, 2022 Tuesday
    Author : Ashish Kumar
    Mini Project in CG Lab     */

/* Header Files Used*/
 #include<ctype.h>
 #include<stdlib.h>
 #include<stdio.h>
 #include<graphics.h>
 #include<conio.h>
 #include<dos.h>
 #include<string.h>

 // Structure to define discs
 struct disc{
   int x , y ;
   int san , ean ;
   int rad , mode ;
 } ;

/* Functions used */
 void record(FILE *,int ,int);
 void border(void) ;
 void welcome(void) ;
 void drw(struct disc*) ;
 void result(int ) ;
 void sidebar1(void);
 void design(void) ;
 void layout1(void);
 void play(void) ;
 void score_list(void);

int a[] = {488,50,629,50,629,70,488,70};
int b[] = {488,100,629,100,629,180,488,180};
int c[] = {488,390,629,390,629,450,488,450};
char ch[2] , msg[80] ;

 void main(){
   int gd = DETECT , gm , errorcode ;
   ch[1]='\0';
   initgraph(&gd ,&gm ,"c:\\turboc3\\bgi") ;

   /* read result of initialization */
   errorcode = graphresult();
   if (errorcode != grOk)
   /* an error occurred */
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);
      /* terminate with an error code */
   }
   welcome();
   do{
    layout1();
    circle(159,159,30);
    floodfill(169,159,1);
    circle(159,318,30);
    circle(318,159,30);
    circle(318,318,30);
    setcolor(12);
    outtextxy(157,157,"1");
    outtextxy(157,316,"3");
    outtextxy(316,157,"2");
    outtextxy(316,316,"4");
    setcolor(3);
    outtextxy(496,400,"Input : ");
    ch[0] = getch();
    outtextxy(560,400,ch);
    switch(ch[0]){
    case 'P' :
    case 'p' : play();
    break ;
    case 'H' :
    case 'h' : score_list();
    break ;
    case 'E' :
    case 'e' : exit(0);
    break ;
    default :   outtextxy(496,414,"Invalid Input");
		outtextxy(496,428,"Choose Again");
		delay(600);
    }
   }while(ch[0]!='E' || ch[0]!='e');
   getch() ;
   closegraph();
   restorecrtmode() ;
 }

void play(void){
   int ans , i , dis , j , task ,dir , l , score = 0 ;
   struct disc disk[4]  ;
   char single ;
   randomize() ;
   disk[0].x=disk[0].y=159;
   disk[1].x =318 ;
   disk[1].y = 159 ;
   disk[2].x = 159 ;
   disk[2].y = 318 ;
   disk[3].x = disk[3].y = 318 ;
   for(i = 0 ; i < 9 ; i++){
      for(j=0;j<4;j++){
	    disk[j].san = 0 ;
	    disk[j].ean = 320 ;
	    disk[j].rad = 30 ;
      }
      task = rand()%3;
      dis = rand()%4 ;
      dir = rand()%2 ;
      if( task == 0 ){
	   disk[dis].san = 0 ;
	   disk[dis].ean = 360 ;
	   if(!dir)  task = 6 ;
	   else dir = 6 ;
      }
      else if(task==1){
	   if(dir)  dir = 5 ;
	   else{
	      task = 5 ;
	      dir = 1 ;
	   }
      }
      else{
	      task = (dir)?2:4;
	      dir=3 ;
      }
      l = 10 ;
      sprintf(msg,"Score : %d/%d ",score,i+1);
      while(l--){
       cleardevice();
       for(j=0;j<4;j++){
		disk[j].mode = (j==dis)?task:dir ;
		drw(disk+j);
       }
       sidebar1() ;
       outtextxy(496,400,"Wait....");
       outtextxy(496,414,msg);
       delay(300);
     }
     sidebar1();
     ch[0]=getch();
     outtextxy(496,400,"Your answer : ") ;
     outtextxy(608,400,ch);
     if(dis==ch[0]-49) score++ ;
     sprintf(msg,"Score : %d/%d ",score,i+1);
     outtextxy(496,414,msg);
     delay(150);
   }
   result(score);
}

// Function which provide randomness to discs
void drw(struct disc *d){
   int temp , r = rand()%12+2;
   switch(d->mode){
   case 0 : if(d->rad<32) d->rad += 1 ;
	    break ;
   case 1 : d->san = (d->san+5)%360 ;
	    d->ean = (d->ean+5)%360 ;
	    break ;
   case 2 : d->san = (d->san+15)%360 ;
	    d->ean = (d->ean+15)%360 ;
	    break ;
   case 3 : d->san = (d->san+r)%360 ;
	    d->ean = (d->ean+r)%360 ;
	    break ;
   case 4 : d->san = (d->san+1)%360 ;
	    d->ean = (d->ean+1)%360 ;
	    break ;
   case 5 : d->san = (d->san+355)%360 ;
	    d->ean = (d->ean+355)%360 ;
	    break ;
   case 6 : if(d->rad>28) d->rad -= 1 ;
	    break ;
   }
   if(d->mode==0 || d->mode==6)   circle(d->x,d->y,d->rad);
   else{
      setcolor(15);
      ellipse(d->x,d->y,d->san,d->ean,d->rad,d->rad);
      setcolor(2);
      ellipse(d->x,d->y,d->ean,d->san,d->rad,d->rad);
   }
}

// Function to welcome the user
void welcome(void){
  setbkcolor(2);
  settextstyle(1,0,5);
  settextjustify(0,1);
  setcolor(4);
  outtextxy(180,156,"Odd in Four");
  settextstyle(6,0,4);
  outtextxy(240,316,"Welcome");
  setfillstyle(6,12);
  fillellipse(0,0,50,50);
  fillellipse(639,0,50,50);
  fillellipse(0,479,50,50);
  fillellipse(639,479,50,50);
  delay(1000);
  settextstyle(0,0,1);
}

// Fucntion to define game structure
void border(void){
  setbkcolor(0);
  setcolor(15);
  setlinestyle(0,0,3);
  line(1,0,1,479) ;
  line(478,0,478,479);
  line(638,0,638,479) ;
  line(0,1,639,1);
  line(0,478,639,478) ;
  setlinestyle(0,1,1);
}

// Function to display and store the score of player
void result(int score){
   int l = 5 ;
   char dat[80],flaag='0';
   FILE * fin,*fout ;
   dat[0]='t';
   layout1();
   settextstyle(1,0,4);
   switch(score){
   case 9 : outtextxy(100,230,"!!You are Brilliant!!");
   break ;
   case 8 : outtextxy(100,230,"!!You are Smart!!");
   break ;
   case 7 : outtextxy(100,230,"!!You are Good!!");
   break ;
   case 6 : outtextxy(100,230,"!!You are Normal!!");
   break ;
   default  : outtextxy(100,230,"!!You are Not Good!!");
   }
   settextstyle(0,0,1);
   sprintf(msg,"Score : %d/%d ",score,9);
   outtextxy(496,400,msg);
   outtextxy(496,414,"GAME OVER");
   fin = fopen("Score_List","r");
   fout = fopen("temp","w");
   while(l--){
	 if(fgets(dat,80,fin)!=NULL){
	   if(score>dat[0]-48 && flaag=='0'){
	     record(fout,5-l,score);
	     flaag='1' ;
	     if(l--)  fputs(dat,fout);
	   }
	   else fputs(dat,fout);
	 }
	 else if(flaag=='0'){
	   record(fout,5-l,score);
	   flaag='1';
	 }
   }
   fclose(fin);
   fclose(fout);
   remove("Score_List");
   rename("temp","Score_List");
   delay(10000);
}

// Function to display player's achievements
void record(FILE *f,int l,int score){
   char *name ,single;
   sprintf(msg,"You got %d rank",l);
   outtextxy(150,300,msg);
   outtextxy(496,428,"Name(max. 25) :") ;
   gotoxy(100,100);
   gets(name);
   outtextxy(496,442,name);
   sprintf(msg,"%d %s\n",score,name);
   fputs(msg,f);
}

// Function to Display sidebar
void sidebar1(){
    border() ;
    setfillstyle(1,0);
    fillpoly(4,a);
    fillpoly(4,b);
    setcolor(6);
    settextstyle(0,0,1);
    outtextxy(512,60,"ODD IN FOUR");
    setcolor(3);
    fillpoly(4,c);
    outtextxy(496,114,"Play (P)");
    outtextxy(496,128,"High Score (H)");
    outtextxy(496,142,"Exit (E)");
}
void design(void){
  int q , w ;
  setcolor(14);
  for(q=w=3;q<474;q += 5,w += 5) line(q,3,476,w);
  w=476 ;
  for(q=3;q<474;q += 5,w -= 5) line(476,q,w,476);
  for(q=w=476;q>2;q -= 5,w -= 5) line(q,476,3,w);
  w=3 ;
  for(q=476;q>2;q -= 5,w += 5) line(3,q,w,3);
}

// Function to clear device screen and display game layout with design.
void layout1(void){
  cleardevice();
  design();
  sidebar1();
}

// Function to display the high score 
void score_list(void){
  int l =239;
  char *ptr1 ,*ptr;
  FILE *in ;
  cleardevice();
  layout1();
  settextstyle(0,0,3);
  outtextxy(120,200,"Score List");
  settextstyle(0,0,1);
  in=fopen("Score_List","r");
  if(in!=NULL){
     ptr = fgets(msg,80,in) ;
     if(ptr==NULL)   outtextxy(165,l,"No match played");
     else{
       while(ptr!=NULL){
	 l += 14 ;
	 ptr1 = strchr(msg,'\n');
	 *(ptr1)= ' ';
	 outtextxy(70,l,msg);
	 ptr = fgets(msg,80,in) ;
       }
     }
  }
  else    fprintf(stderr, "Cannot open output file.\n");
  fclose(in);
  delay(5000);
}
