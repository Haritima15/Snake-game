#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;
const int width=20;     //width of the frame
const int height=20;    //height of the frame
int x , y , fruitX , fruitY;    //co-ordinates of the snake and fruit
int score;  //for game score
int tailX[100] , tailY[100] , nTail;
enum eDirection {STOP=0,LEFT,RIGTH,UP,DOWN};
eDirection dir;


void Setup()
{
    gameOver = false;
    dir = STOP;       //so that snake dont move until we move
    x = width / 2;        //int the center
    y = height / 2;       //int the center
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;

}

void Draw()
{
    system("cls");      //clear console window

    //fro top wall
    for(int i=0 ; i<width+2 ; i++)
        cout<<"+";
    cout<<endl;

    for(int i=0 ; i<height ; i++)
    {
        for(int j=0 ; j<width ; j++)
        {
            if(j==0)
                cout<<"+";
            if(i==y && j==x)
                cout<<"O";      //snake head
            else if(i==fruitY && j==fruitX)
                cout<<"@";      //fruit
            else
            {
               bool print = false;
               for(int k=0 ; k < nTail ; k++)
               {
                    if(tailX[k] == j && tailY[k] == i)
                    {
                        cout<<"o";
                        print = true;
                    }
               } 
               if(!print)
                cout<<" ";
            }
                

            if(j==width-1)
                cout<<"+";
            
        }
        cout<<endl;
    }

    //for bottom wall
    for(int i=0 ; i<width+2 ; i++)
        cout<<"+";
    cout<<endl;
    cout<<"Score="<<score<<endl;
}

void Input()        //controls
{
    if(_kbhit())
    {
        switch(_getch())
        {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGTH;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
            
        }
    }
}

void Logic()
{
    int preX=tailX[0];
    int preY=tailY[0];
    int pre2X,pre2Y;
    tailX[0] = x;
    tailY[0] = y;

    for(int i=1 ; i<nTail ; i++)
    {
        pre2X = tailX[i];
        pre2Y = tailY[i];
        tailX[i] = preX;
        tailY[i] = preY;
        preX = pre2X;
        preY = pre2Y; 
    }
    switch (dir)
    {
        case LEFT:
            x--; 
            break;
        case RIGTH:
            x++; 
            break;
        case UP:
            y--; 
            break;
        case DOWN:
            y++; 
            break;
    }  

    if(x > width || x < 0 || y > height || y < 0 )
        gameOver = true;                        //if the snake hit the wall

    for(int i=0 ; i<nTail ; i++)
        if(tailX[i] == x && tailY[i] == y)
            gameOver = true;
    
    if(x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(10);
    }
    

    return(0);
}