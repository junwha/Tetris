#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define TURN 42
#define SIZE 20

int i,j,k,flag;
int score = 0, highscore=0;
int beforeTime;
int gameover = 0;
//?? ????
int matrix[SIZE][SIZE+5] = {0};

typedef struct block{
    int matrix[4][4];
    int x,y;
    int tp, bp, rp, lp; //Top Point, Bottom Point
} BLOCK, *pBLOCK;

BLOCK block;


//????? ??? ???
int key(){
    int key = getch();
    if(key==224 || key ==0){
        return getch();
    }else if(key==TURN){
        return TURN;
    }else{
        return ERROR;
    }
}


void initBlock(){
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            block.matrix[i][j]=0;
        }
    }
}

void initMatrix(){
    for(i=0;i<SIZE;i++){
        matrix[i][SIZE+4]=15;
    }
    if(gameover){
        for(i=0;i<SIZE+4;i++){
            for(j=0;j<SIZE;j++){
                matrix[j][i]=0;
            }
            
        }
    }
}
void measureColider(){
    flag = 0;
    int bottom = 3;
    int top = 0;
    int left = 0;
    int right = 3;
    for(top = 0; top<3; top++){
        for(i=0;i<4;i++){
            if(block.matrix[i][top]>0){
                flag = 1;
                break;
            }
        }
        if(flag){
            break;
        }

    }
    flag = 0;
    for(bottom = 3; bottom>0; bottom--){
        for(i=0;i<4;i++){
            if(block.matrix[i][bottom]>0){
                flag = 1;
                break;
            }
        }
        if(flag){
            break;
        }
    }
    flag = 0;
    for(left = 0; left<3; left++){
        for(i=0;i<4;i++){
            if(block.matrix[left][i]>0){
                flag = 1;
                break;
            }
        }
        if(flag){
            break;
        }

    }
    flag = 0;
    for(right = 3; right>0; right--){
        for(i=0;i<4;i++){
            if(block.matrix[right][i]>0){
                flag = 1;
                break;
            }
        }
        if(flag){
            break;
        }
    }
    block.tp = top;
    block.bp = bottom;
    block.lp = left;
    block.rp = right;
}
void turnBlock(){
    for(int i=0; i<4; i++){
        for(int j=0; j<4;j++){
            matrix[j+block.x][i+block.y] -= block.matrix[j][i];
        }
    }



    int newArr[4][4] = {0};

    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            newArr[i][j] = block.matrix[i][j];
        }
    }
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            block.matrix[4-1-i][j]=newArr[j][i];
        }
    }

    measureColider();

    for(int i=0; i<4; i++){
        for(int j=0; j<4;j++){
            matrix[j+block.x][i+block.y] = block.matrix[j][i];
        }
    }
}


void createBlock(){
    initBlock();
    srand(time(NULL));
    int randIndex = rand()%7;
    srand(time(NULL));
    int randTurn = rand()%4;
    
    switch(randIndex){
    //x,y
        case 0:
            block.matrix[2][0] = 1; 
            block.matrix[2][1] = 1;
            block.matrix[2][2] = 1;
            block.matrix[2][3] = 1;
            break;
        case 1:
            block.matrix[1][1] = 2;
            block.matrix[1][2] = 2;
            block.matrix[2][1] = 2;
            block.matrix[2][2] = 2;
            break;
        case 2:
            block.matrix[0][1] = 3;
            block.matrix[1][1] = 3;
            block.matrix[1][2] = 3;
            block.matrix[2][1] = 3;
            break;
        case 3:
            block.matrix[1][2] = 4;
            block.matrix[2][1] = 4;
            block.matrix[2][2] = 4;
            block.matrix[3][1] = 4;
            break;
        case 4:
            block.matrix[1][1] = 5;
            block.matrix[2][1] = 5;
            block.matrix[2][2] = 5;
            block.matrix[3][2] = 5;
            break;
        case 5:
            block.matrix[2][0] = 6;
            block.matrix[2][1] = 6;
            block.matrix[2][2] = 6;
            block.matrix[1][2] = 6;
            break;
        case 6:
            block.matrix[1][0] = 7;
            block.matrix[1][1] = 7;
            block.matrix[1][2] = 7;
            block.matrix[2][2] = 7;
            break;
    }

    measureColider();
    
    block.x = (SIZE/2);
    block.y = 0;
    for(int i=0; i<4; i++){
        for(int j=0; j<4;j++){
            matrix[j+block.x][i+block.y] = block.matrix[j][i];
        }
    }
    
}


void getScore(){
    for(i=0;i<SIZE+4;i++){
        flag = 0;
        for(j=0;j<SIZE;j++){
            if(matrix[j][i]==0){
                flag = 1;
                break;
            }
        }
        if(!flag){
            for(j=0;j<SIZE;j++){
                matrix[j][i] = 0;
            }
            for(j=i;j>0;j--){
                for(k=0;k<SIZE;k++){
                    matrix[k][j]= matrix[k][j-1];
                }
            }
            score+=100;
        }
    }
}

void move(int direction){
    for(int i=0; i<=block.bp; i++){
        for(int j=0; j<4;j++){
            matrix[j+block.x][i+block.y] -= block.matrix[j][i];
        }
    }
    if(direction==DOWN){
        block.y += 1;
    }else if(direction==RIGHT){
        if(block.x+block.rp+1<SIZE){
            flag = 0;
            for(i=block.tp;i<=block.bp;i++){
                for(j=block.lp;j<=block.rp;j++){
                    if(block.matrix[j][i]>0&&matrix[block.x+j+1][block.y+i]>0){
                        flag = 1;
                        break;
                    }
                }
                if(flag){
                    break;
                }
            }
            if(!flag){
                block.x+=1;
            }
            
        }
    }else if(direction==LEFT){
        if(block.x+block.lp-1>=0){
            flag = 0;
            for(i=block.tp;i<=block.bp;i++){
                for(j=block.lp;j<=block.rp;j++){
                    if(block.matrix[j][i]>0&&matrix[block.x+j-1][block.y+i]>0){
                        flag = 1;
                        break;
                    }
                }
                if(flag){
                    break;
                }
            }
            if(!flag){
                block.x-=1;
            }
            
        }
    }
    for(int i=0; i<=block.bp; i++){
        for(int j=0; j<4;j++){
            if(block.matrix[j][i]>0){
                matrix[j+block.x][i+block.y] = block.matrix[j][i];
            }

        }
    }
    flag = 0;
    for(j=block.bp;j>=0;j--){
        for(i=0;i<4;i++){
            if(block.matrix[i][j]>0&&matrix[block.x+i][block.y+j+1]>0&&block.matrix[i][j+1]==0){
                flag = 1;
                break;
            }
        }
        if(flag){
            break;
        }
    }
    if(flag){
        for(int i=0;i<SIZE;i++){
            if(matrix[i][4]>0){
                gameover = 1;
                break;
            }
        }
        getScore();
        createBlock();
    }
}
void cur(short x, short y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main(){
    CONSOLE_CURSOR_INFO ConsoleCursor;

    ConsoleCursor.bVisible = 0; // true ????, false ?????

    ConsoleCursor.dwSize = 1; // ии????????

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE) , &ConsoleCursor); // ????

    beforeTime = GetTickCount() ;
    initMatrix();
    initBlock();
    createBlock();
    while(1){
        initMatrix();
        initBlock();
        createBlock();
        gameover = 0;

        while(!gameover){
            if(GetTickCount()-beforeTime>300-score/100){
                move(DOWN);
                beforeTime = GetTickCount() ;
            }
            
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            if(highscore<=score){
                highscore = score;
            }
            printf("SCORE: %d               HIGH SCORE: %d\n",score,highscore);
            for(i=0;i<SIZE+5;i++){
                for(j=0;j<SIZE;j++){
                    if(matrix[j][i]>0){
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),matrix[j][i]);
                        printf("бс");
                    }else{
                        printf("  ");
                    }
            
                }
                printf("\n");
            }
            if(kbhit()){
                int _key = key();
                if(_key==UP){  
                    turnBlock();
                }else{
                    move(_key);
                }
            }
            cur(0,0);//system("cls");
        }
        highscore = score;
        score = 0;
        printf("                                                  \n");
        cur(0,0);//system("cls");
        printf("GAME OVER!\n");
        Sleep(3000);
        cur(0,0);//system("cls");
        printf("           \n");
        cur(0,0);//system("cls");
        
    }
}