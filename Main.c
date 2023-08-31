#include<stdio.h>

#define BEGINNER 1
#define INTERMEDIATE 2
#define ADVANCE 3

int sides, mines;

void chooseDifficulty(){
    printf("Choose a difficulty level\n");
    printf("Press 1 for BEGINNER\n");
    printf("Press 2 for INTERMEDIATE\n");
    printf("Press 3 for ADVANCE\n");
    printf("--> ");

    int level = 1;
    scanf("%d", &level);

    if(level == BEGINNER){
        sides = 9;
        mines = 10;
    }
    else if(level == INTERMEDIATE){
        sides = 16;
        mines = 40;
    }
    else if(level == ADVANCE){
        sides = 24;
        mines = 99;
    }
    else{
        printf("Choose a valid Difficulty level");
    };
}

int main(){
    chooseDifficulty();

    char realBoard[sides][sides], playingBoard[sides, sides];
    for(int row=0; row<sides; row++){
        for(int col=0; col<sides; col++){
            realBoard[row][col] = playingBoard[row][col] = '-';
        }
    }
}
