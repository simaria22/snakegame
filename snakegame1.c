#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
void setup();
void pinakas();
void print();
int kbhit(void);
char move();
void select_button();
void movement();
int x;
int y;
int g;
int fruitX,fruitY,game_over,score;
int tailX[200],tailY[200];
int tail=0;
char **p;
int i,j,rows,cols,choice,score;
int previousX,previousY,previous2X,previous2Y;
int main()
{
     print();
     setup();
     pinakas();
while(!game_over)
{
   pinakas();
   select_button();
   movement();


}
if(game_over) printf("GAME OVER!\n");

return 0;


}



//sunarthsh gia na orizontai oi diastaseis tou pinaka apo ton xrhsth
void print()
{
   printf("Dwse to platos tou pinaka tou paixidiou:");
   scanf("%d",&cols);

   printf("Dwse to ipsos tou pinaka tou paixidiou:");
   scanf("%d",&rows);

   p=(char**)malloc(rows * sizeof(char*));
   if(p==NULL)
   {
   printf("Adynamia desmeusis mnimis");
   exit(1);
   }
    for(i=0;i<rows;i++)
     {
       p[i]=(char*)malloc(cols * sizeof(char));

     }
}

   
void setup()
{
  game_over=0;
  x=rows/2;
  y=cols/2;
  srand(time(NULL));
  fruitX=rand()%rows;
  fruitY=rand()%cols;

  if(fruitX==0) fruitX=rand()%rows;
  if(fruitY==0) fruitY=rand()%cols;

  score=0;
}
//kataskeuh pinaka gia na paizetai to paixnidi
void pinakas()
{
  system("clear");
  printf("SCORE:%d\n",score);
  for(i=0;i<rows;i++)
   {
      for(j=0;j<cols;j++)
       {
          if(i==0 || i==rows-1)
         {
         printf("-");
         }

          else if((j==0 || j==cols-1) && (i>0 && i<rows-1))
             {
              printf("|");
             }
        else
         {
               if(i==x && j==y)
                  {
                    printf("@");
                  }
               else if(i==fruitX && j==fruitY)
                 {
                  printf("X");
                 }
        else
           {
            int ch=0;
             for(g=0;g<tail;g++)
              {
                if(i==tailX[g] && j==tailY[g])
                  {
                     printf("*");
                      ch=1;
                  }
               }
              if(ch==0) printf(" ");
             }
           }
         }printf("\n");
       }
    }
//sunarthsh h opoia elegxei an exei paththei kapoio koumpi apo ton xrhsth
int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}

void sleepcp(int milliseconds) // sunarthsh pou kanei to fidaki na kineitai pio arga 
{
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end)
    {
    }
}

char move()
{
    int flags;
    char key[2];

    flags = fcntl(STDIN_FILENO, F_GETFL);
    fcntl(STDIN_FILENO, F_SETFL, flags|O_NONBLOCK);

    // To get the input from the terminal without pressing the enter button
    system ("/bin/stty raw");
    read(STDIN_FILENO, key, 2);
    // Reset the "system ("/bin/stty raw")" to display correctly the output
    system ("/bin/stty cooked");

    return key[0];
}
//sunarthsh h opoia anagnwrizei to pathma koumpiou
void select_button()
{
sleepcp(200);
if(kbhit())
 {
    switch(move())
  {
    case 'a':
    choice=1;
    break;

    case 'd':
    choice=2;
    break;

    case 'w':
    choice=3;
    break;

    case 's':
    choice=4;
    break;

    case 'x':
    game_over=1;
    break;
  }
 }

}
//sunarthsh pou kinei to fidaki analoga me to koumpi pou paththhke
void movement()
{

previousX=tailX[0];
previousY=tailY[0];
tailX[0]=x;
tailY[0]=y;

for(i=1;i<tail;i++)   //dhmiourgia ouras
  {
  previous2X=tailX[i];
  previous2Y=tailY[i];
  tailX[i]=previousX;
  tailY[i]=previousY;
  previousX=previous2X;
  previousY=previous2Y;

  }


  switch(choice)
 {
  case 1:
  y--;
  break;
 
  case 2: 
  y++;
  break;

  case 3: 
  x--;
  break;

  case 4:
  x++;
  break;

  default:
  break;
 }
   if(x<0 || x>rows || y<0 ||y>cols)       //periptwseis stis opoies uparxei game over
   {
     game_over=1;
   }
  for(i=0; i<tail;i++)
   {
     if(x==tailX[i] && y==tailY[i])
       {
       game_over=1;
       }
   }
 if(x==fruitX && y==fruitY)    //otan to fidaki trwei to frouto na allazei thesi to X
 {
  srand(time(NULL));
  fruitX=rand()%rows;
  fruitY=rand()%cols;

  if(fruitX==0) fruitX=rand()%rows;
  if(fruitY==0) fruitY=rand()%cols;

  score+=10;
  tail++;
 }

}



















