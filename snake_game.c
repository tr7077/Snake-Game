/*-----------------------------------------------------------------------------------------------------
- I am using some functions and a library which they only run on ms-dos systems, 
  so if you run this on linux or mac-os you'll probably get some errors __> [system("cls"), getch(), conio.h]
- try it with lowercase i was bored to writte more code just for uppercase 
- also only w a s d keys work because i was bored again to writte more code to get the arrows to work 
- left and right walls are not walls!
- have fun with my billion-dollar project but please don't steal it
-----------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>

#define height 40
#define width 100
int gameover;
int score;
int food_x, food_y;
int snake_x, snake_y;
char user_input;
char direction;
char sel;
int tail_x[(width-2)*(height-2)] = {0};
int tail_y[(width-2)*(height-2)] = {0};
int tail_len;
//-----------------------------|

void printgraphics();
void logic();

int main()
{
    do{
        gameover = 0;
        score = 0;
        food_x = 0, food_y = 0;
        snake_x = 0; snake_y = 0;
        user_input = 'N';
        direction = 'N';
        tail_len = 0;

        system("cls");
        printf("Press ANY KEY to start...");
        getch();

        snake_x = width / 2;
        snake_y = height / 2;

        srand(time(NULL));
        do{
            food_x = (rand()%(width-2))+2;
        }while(food_x == snake_x);
        do{
            food_y = (rand()%(height-2))+2;
        }while(food_y == snake_y);
        //----------------------------------------------------------------------|
        while(!gameover){

            printgraphics();
            if(kbhit()){
                user_input = getch();
            }
            logic();

        }
        printf("..GAME~OVER..\n");

        sleep(2);
        fflush(stdin);
        printf("Score: %d\n--------------------------\n", score);
        printf("Press ESC to exit\nPress SPACE to play again\n");
        do{
            sel = getch(); 
        }while(sel != 27 && sel != 32);
    }while(sel == 32);

    return 0;
}

void printgraphics(void){
    system("cls");
    printf("SCORE: %d | Press ESC to reset or quit\n", score);
    for(int y=1; y<=height; y++){
        for(int x=1; x<=width; x++){
            if(y==1 || y==height || x==1 || x==width){
                printf("O");
            }
            else if(x==food_x && y==food_y){
                printf("+");
            }
            else if(x==snake_x && y==snake_y){
                printf("$");
            }
            else{
                int temp = 1;
                for(int i=0; i<tail_len; i++){
                    if(y==tail_y[i] && x==tail_x[i]){
                        printf("*");
                        temp = 0;
                    }
                }
                if(temp){
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}

void logic(void){
    int tail0_x, tail1_x;
    int tail0_y, tail1_y;

    tail0_x = tail_x[0];
    tail0_y = tail_y[0];

    tail_x[0] = snake_x;
    tail_y[0] = snake_y;
    for(int i=1; i<tail_len; i++){
        tail1_x = tail_x[i];
        tail1_y = tail_y[i];

        tail_x[i] = tail0_x;
        tail_y[i] = tail0_y;

        tail0_x = tail1_x;
        tail0_y = tail1_y;
    }
    switch(user_input){
        case 27://esc
            gameover = 1;
            break;
        case 'w'://up
            if(direction != 's'){
                snake_y--;
                direction = 'w';
            }
            else{
                snake_y++;
            }
            break;
        case 's'://down
            if(direction != 'w'){
                snake_y++;
                direction = 's';
            }
            else{
                snake_y--;
            }
            break;
        case 'a'://left
            if(direction != 'd'){
                snake_x--;
                direction = 'a';
            }
            else{
                snake_x++;
            }
            break;
        case 'd'://right
            if(direction != 'a'){
                snake_x++;
                direction = 'd';
            }
            else{
                snake_x--;
            }
            break;
        default:
            switch(direction){
                case 'w':
                    snake_y--;
                    break;
                case 's':
                    snake_y++;
                    break;
                case 'a':
                    snake_x--;
                    break;
                case 'd':
                    snake_x++;
                    break;
            }
            break;
    }
    if(snake_y==1 || snake_y==height){ // || snake_x==1 || snake_x==width){
        gameover = 1;
    }
    if(snake_x==1){
        snake_x = width-1;
    }
    if(snake_x==width){
        snake_x = 2;
    }
    if(snake_x==food_x && snake_y==food_y){
        score++;
        do{
            food_x = (rand()%(width-2))+2;
        }while(food_x == snake_x);
        do{
            food_y = (rand()%(height-2))+2;
        }while(food_y == snake_y);
        tail_len++;
    }
    for (int i=0; i<tail_len; i++){
        if (snake_x == tail_x[i] && snake_y == tail_y[i]){
            gameover = 1;
            break;
        }
    }
    if(tail_len == (width-2)*(height-2)){
        printf("\n\t\tCONGRATULATIONS!\n");
        sleep(2);
        printf("\n\t\tYOU BEAT THE SYSTEM!\n");
        sleep(2);
        gameover = 1;
    }
}
