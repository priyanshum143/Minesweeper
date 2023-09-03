#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

#define BEGINNER 1         // Sides => 9*9, Mines = 10
#define INTERMEDIATE 2     // Sides => 16*16, Mines = 40
#define ADVANCE 3          // Sides => 24*24, Mines = 99
#define MAXSIDES 24

// Structure to store the location of mines
struct minesLocation{
    int rowLoc;
    int colLoc;
};
struct minesLocation minesLoc[99];

// Some Global variables that we are gonna use in our programme
int sides, mines;
bool gameOver = false;
int flagCount = 0;

// Initializing realBoard and playingBoard
// Real Board will contain the location of mines
// Playing Board will be visible to the user while playing
char realBoard[MAXSIDES][MAXSIDES];
char playingBoard[MAXSIDES][MAXSIDES];

// Arrays to store adjacent cell's location
int adjRowLoc[8] = {-1,-1,-1,0,0,1,1,1};
int adjColLoc[8] = {-1,0,1,-1,1,-1,0,1};


// Function to check if all the mines are placed correctly by user
bool checkMines(){
    for(int i=0; i<mines; i++){
        if(playingBoard[minesLoc[i].rowLoc][minesLoc[i].colLoc] != '*') return false;
    }
    return true;
}

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

// Function to find the number of mines present adjacent to our current position 
int countAdjacentMines(int row, int col){
    int count = 0;

    for(int i=0; i<8; i++){
        if(isValid(row + adjRowLoc[i], col + adjColLoc[i])){
            if(isMine(row + adjRowLoc[i], col + adjColLoc[i])){
                count++;
            }
        }
    }
    return count;
}

// Function to print the board
void printBoard(char board[MAXSIDES][MAXSIDES]){
    printf("\nFlags = %d", flagCount);
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

// Function to replace mine in realBoard if user taps on a mine on first move 
void replaceMine(int row, int col){
    for(int i=0; i<sides; i++){
        for(int j=0; j<sides; j++){
            if(realBoard[i][j] == '-'){
                realBoard[i][j] = '*';
                realBoard[row][col] = '-';
                return;
            }
        }
    }
}

// Function to open adjacent cells if there's no mine is present
void openAdjacentCells(int row, int col){
    int count = 0;
    for(int i=0; i<8; i++){
        if(isValid(row + adjRowLoc[i], col + adjColLoc[i])){
            count = countAdjacentMines(row + adjRowLoc[i], col + adjColLoc[i]);
            playingBoard[row + adjRowLoc[i]][col + adjColLoc[i]] = count + '0';
            realBoard[row + adjRowLoc[i]][col + adjColLoc[i]] = count + '0';
        }
    }
}

// Function to make a move on playingBoard
void makeMove(){
    static int currentMoveIndex = 0;
    int mineCount = 0;

    int row, col;
    printf("Enter row and col -> ");
    scanf("%d %d", &row, &col);

    if(row == 99 && col == 99){
        int mineX, mineY;
        printf("Enter the location of mine => ");
        scanf("%d %d", &mineX, &mineY);

        if(!isValid(mineX, mineY)){
            printf("Enter a valid location.\n");
            return;
        }
        else{
            if(playingBoard[mineX][mineY] == '*'){
                printf("Do you really wanna remove a flag from %d, %d?\n", mineX, mineY);

                int decision = 1;
                printf("Press 1 for yes and 0 for no -> ");
                scanf("%d", &decision);

                if(decision == 1){
                    playingBoard[mineX][mineY] = '-';
                    flagCount--;
                }
                return;
            } 
            else{
                playingBoard[mineX][mineY] = '*';
                flagCount++;
            }
        }
    }
    else if(isValid(row, col)){
        if(currentMoveIndex == 0){
            if(isMine(row, col)) replaceMine(row, col);
        }

        if(isMine(row, col)){
            printf("\nYou Lose!");
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
        return;
    }
    
    if(mineCount == 0) openAdjacentCells(row, col);
}

// Function to place mines on realBoard
void placeMines(){
    srand(time(0));

    for(int i=0; i<mines; ){
        int row = rand() % sides;
        int col = rand() % sides;

        if(realBoard[row][col] == '-'){
            realBoard[row][col] = '*';
            minesLoc[i].rowLoc = row;
            minesLoc[i].colLoc = col;
            i++;
        }
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

// Function to start and end the game
void startGame(){
    initialize();
    placeMines();

    while(!gameOver){
        if(flagCount == mines && checkMines()){
            printf("\nYou Win!");
            printBoard(playingBoard);
            return;
        }
        printBoard(playingBoard);
        makeMove();
    }
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
        chooseDifficulty();
    }
}

// Main Function
int main(){
    chooseDifficulty();

    startGame();
}
