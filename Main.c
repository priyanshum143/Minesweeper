#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

#define BEGINNER 1         // Sides => 9*9, Mines = 10
#define INTERMEDIATE 2     // Sides => 16*16, Mines = 40
#define ADVANCE 3          // Sides => 24*24, Mines = 99
#define MAXSIDES 25

int sides, mines;
bool gameOver = false;

// Initializing realBoard and playingBoard
// Real Board will contain the location of mines
// Playing Board will be visible to the user while playing
char realBoard[MAXSIDES][MAXSIDES];
char playingBoard[MAXSIDES][MAXSIDES];

// Function to check if the given position is valid or not
bool isValid(int row, int col){
    if(row >= 0 && row < sides && col >= 0 && col < sides) return true;
    return false;
}

// Function to check if a mine is present or not on given position
bool isMine(int row, int col){
    if(realBoard[row][col] == '*') return true;
    return false;
}

// Function to find the number of mines present near our current position 
int countAdjacentMines(int row, int col){
    int count = 0;

    // First Neighbour
    if(isValid(row-1, col-1)){
        if(isMine(row-1, col-1)){
            count++;
        }
    }

    // Second Neighbour
    if(isValid(row-1, col)){
        if(isMine(row-1, col)){
            count++;
        }
    }

    // Third Neighbour
    if(isValid(row-1, col+1)){
        if(isMine(row-1, col+1)){
            count++;
        }
    }

    // Fourth Neighbour
    if(isValid(row, col-1)){
        if(isMine(row, col-1)){
            count++;
        }
    }

    // Fifth Neighbour
    if(isValid(row, col+1)){
        if(isMine(row, col+1)){
            count++;
        }
    }

    // Sixth Neighbour
    if(isValid(row+1, col-1)){
        if(isMine(row+1, col-1)){
            count++;
        }
    }

    // Seventh Neighbour
    if(isValid(row+1, col)){
        if(isMine(row+1, col)){
            count++;
        }
    }

    // Eighth Neighbour
    if(isValid(row+1, col+1)){
        if(isMine(row+1, col+1)){
            count++;
        }
    }

    return count;
}

// Function to set the difficulty level
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

// Function to print the board
void printBoard(char board[MAXSIDES][MAXSIDES]){
    printf("\nCurrent Status of the board => \n");
    printf("     ");

    for(int col=0; col<sides; col++){
        printf("%d ", col);
    }
    printf("\n");

    for(int row=0; row<sides; row++){
        if(row<10) printf("  %d  ", row);
        else printf(" %d  ", row);

        for(int col=0; col<sides; col++){
            if(col<10) printf("%c ", board[row][col]);
            else printf(" %c ", board[row][col]);
        }
        printf("\n");
    }
}

// Function to initialize both boards
void initialize(){
    for(int row=0; row<sides; row++){
        for(int col=0; col<sides; col++){
            realBoard[row][col] = playingBoard[row][col] = '-';
        }
    }
}

// Function to place mines on realBoard
void placeMines(){
    srand(time(0));
    for(int i=0; i<mines; ){
        int row = rand() % sides;
        int col = rand() % sides;

        if(realBoard[row][col] == '-'){
            realBoard[row][col] = '*';
            i++;
        }
    }
} 

// Function to replace mine in realBoard if user taps on mine on first move 
void replaceMine(int row, int col){
    realBoard[row][col] = '-';
    for(int i=0; i<sides; i++){
        for(int j=0; j<sides; j++){
            if(realBoard[i][j] == '-'){
                realBoard[i][j] = '*';
                return;
            }
        }
    }
}

// Function to open adjacent cells if there's no mine is present
void openAdjacentCells(int row, int col){
    if(!isValid(row, col)) return;

    int count = 0;
    if(isValid(row-1, col-1)){
        count = countAdjacentMines(row-1, col-1);
        playingBoard[row-1][col-1] = count + '0';
        realBoard[row-1][col-1] = count + '0';

        // int newRow = row-1;
        // int newCol = col-1;
        // if(isValid(newRow, newCol)){
            // if(count == 0) openAdjacentCells(row-1, col-1);
        // }
    }

    if(isValid(row-1, col)){
        count = countAdjacentMines(row-1, col);
        playingBoard[row-1][col] = count + '0';
        realBoard[row-1][col] = count + '0';
        
        // int newRow = row-1;
        // int newCol = col;
        // if(isValid(newRow, newCol)){
            // if(count == 0) openAdjacentCells(row-1, col);
        // }
    }

    if(isValid(row-1, col+1)){
        count = countAdjacentMines(row-1, col+1);
        playingBoard[row-1][col+1] = count + '0';
        realBoard[row-1][col+1] = count + '0';

        // int newRow = row-1;
        // int newCol = col+1;
        // if(isValid(newRow, newCol)){
            // if(count == 0) openAdjacentCells(row-1, col+1);
        // }
    }

    if(isValid(row, col-1)){
        count = countAdjacentMines(row, col-1);
        playingBoard[row][col-1] = count + '0';
        realBoard[row][col-1] = count + '0';

        // int newRow = row;
        // int newCol = col-1;
        // if(isValid(newRow, newCol)){
            // if(count == 0) openAdjacentCells(row, col-1);
        // }
    }

    if(isValid(row, col+1)){
        count = countAdjacentMines(row, col+1);
        playingBoard[row][col+1] = count + '0';
        realBoard[row][col+1] = count + '0';
       
        // int newRow = row;
        // int newCol = col+1;
        // if(isValid(newRow, newCol)){
            // if(count == 0) openAdjacentCells(row, col+1);
        // }
    }
    
    if(isValid(row+1, col-1)){
        count = countAdjacentMines(row+1, col-1);
        playingBoard[row+1][col-1] = count + '0';
        realBoard[row+1][col-1] = count + '0';

        // int newRow = row+1;
        // int newCol = col-1;
        // if(isValid(newRow, newCol)){
            // if(count == 0) openAdjacentCells(row+1, col-1);
        // }
    }

    if(isValid(row+1, col)){
        count = countAdjacentMines(row+1, col);
        playingBoard[row+1][col] = count + '0';
        realBoard[row+1][col] = count + '0';

        // int newRow = row+1;
        // int newCol = col;
        // if(isValid(newRow, newCol)){
            // if(count == 0) openAdjacentCells(row+1, col);
        // }
    }
    
    if(isValid(row+1, col+1)){
        count = countAdjacentMines(row+1, col+1);
        playingBoard[row+1][col+1] = count + '0';
        realBoard[row+1][col+1] = count + '0';
        
        // int newRow = row+1;
        // int newCol = col+1;
        // if(isValid(newRow, newCol)){
            // if(count == 0) openAdjacentCells(row+1, col+1);
        // }
    }
}

// Function to make a move on playingBoard
void makeMove(){
    static int currentMoveIndex = 0;
    int mineCount = 0;

    int row, col;
    printf("Enter row and col -> ");
    scanf("%d", &row);
    scanf("%d", &col);

    if(row == 99 && col == 99){
        int mineX, mineY;
        printf("Enter the location of mine =>> ");
        scanf("%d", &mineX);
        scanf("%d", &mineY);
        playingBoard[mineX][mineY] = '*';
    }
    else if(isValid(row, col)){
        if(currentMoveIndex == 0){
            if(isMine(row, col)){
                replaceMine(row, col);
            } 
        }

        if(isMine(row, col)){
            printf("You Lose!\n");
            printBoard(realBoard);
            gameOver = true;
            return;
        }
        else if(realBoard[row][col] == '-'){
            mineCount = countAdjacentMines(row, col);
            playingBoard[row][col] = mineCount + '0';
            realBoard[row][col] = mineCount + '0';
            
            currentMoveIndex++;
        }
    }
    else{
        printf("Please enter a valid move.\n");
        makeMove();
    }
    
    if(mineCount == 0) openAdjacentCells(row, col);
}

// Function to start and end the game
void startGame(){
    initialize();
    placeMines();

    while(!gameOver){
        printBoard(playingBoard);
        makeMove();
    }
}

// Main Function
int main(){
    chooseDifficulty();

    initialize();
    placeMines();

    printBoard(realBoard);
    startGame();
}
