#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum{
    Playing     = 0,
    Player1Wins = 1,
    Player2Wins = 2,
    Draw        = 3
} gameState;

const char emptyboard[8][8] = {
        {'-','-','-','-','-','-','-',' '},
        {'|',' ','|',' ','|',' ','|','3'},
        {'-','-','-','-','-','-','-',' '},
        {'|',' ','|',' ','|',' ','|','2'},
        {'-','-','-','-','-','-','-',' '},
        {'|',' ','|',' ','|',' ','|','1'},
        {'-','-','-','-','-','-','-',' '},
        {' ','a',' ','b',' ','c',' ',' '}
};

void clearScreen();
void resetBoard(char* board[8][8], int* turn);
void drawBoard(char* board[8][8]);
void addToBoard(char* board[8][8], int* player, int* turn, char* posX, char* posY);
void declareWinner(gameState currentGameState);
int getPlayerInput(int player, char* posX, char* posY); //Returns 1 if valid
int checkWin(char* (board)[8][8], int* turn);
int checkVerticalVictory(char* board[8][8]);
int checkHorizontalVictory(char* board[8][8]);
int checkDiagonalVictory(char* board[8][8]);
int checkDraw(int* turn);
int promptReplay();



int main()
{
    char board[8][8] = {
    };
    char posX, posY;
    int player = 1;     //Can be 1 or 2
    int turn = 0;       //Draw at 9
    gameState currentGameState  = Playing;
    int restart = 0;

    do{
        resetBoard(board, &turn);
        do{
            clearScreen();
            drawBoard(board);
            while(!getPlayerInput(player, &posX, &posY));       //Keep prompting until input is valid
            addToBoard(board, &player, &turn, &posX, &posY);
            currentGameState = checkWin(board, &turn);
        }while(currentGameState == Playing);

        clearScreen();
        drawBoard(board);
        declareWinner(currentGameState);

        restart = promptReplay();

    }while(restart);

    return 0;
}

void drawBoard(char* board[8][8])
{
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            putchar(board[i][j]);
        }
        putchar('\n');
    }
}

int getPlayerInput(int player, char* posX, char* posY)
{
    char _posX;
    char _posY;
    char input[3];

    printf("\nPlayer %d, What position do you want to play? (ex. a3) ", player);

    fgets(input, 3, stdin);
    _posX = input[0];
    _posY = input[1];
    fflush(stdin);

    //check if input is valid
    switch(_posX)
    {
        case 'a':
        case 'A':
        case 'b':
        case 'B':
        case 'c':
        case 'C': *posX = _posX; break;
        default:
            printf("\nWrong horizontal input (%c), try again!\n", _posX);
            return 0;
    }
    switch(_posY)
    {
        case '1':
        case '2':
        case '3': *posY = _posY; break;
        default:
            printf("\nWrong vertical input (%c), try again!\n", _posX);
            return 0;
    }

    return 1;
}

void addToBoard(char* board[8][8], int* player, int* turn, char* posX, char* posY)
{
    int arrayRow, arrayCol;

    switch(*posX)
    {
        case 'a':
        case 'A': arrayCol = 1; break;
        case 'b':
        case 'B': arrayCol = 3; break;
        case 'c':
        case 'C': arrayCol = 5; break;
    }
    switch(*posY)
    {
        case '1': arrayRow = 5; break;
        case '2': arrayRow = 3; break;
        case '3': arrayRow = 1; break;
    }

    if(board[arrayRow][arrayCol] == ' ')
    {
        if(*player == 1)
        {
            board[arrayRow][arrayCol] = 'X';
            *player = 2;
        }
        else
        {
            board[arrayRow][arrayCol] = 'O';
            *player = 1;
        }
        (*turn)++;
    }
}

int checkWin(char* board[8][8], int* turn)
{
    /*  Returns 0, 1, 2, 3:

        0 - No victory
        1 - Player 1 Victory
        2 - Player 2 Victory
        3 - Draw
    */

    /*
    Valid positions:
        [1][1], [1][3], [1][5],
        [3][1], [3][3], [3][5],
        [5][1], [5][3], [5][5],
    */

    int winCondition = 0;

    winCondition = checkHorizontalVictory(board);
    if(winCondition) return winCondition;

    winCondition = checkVerticalVictory(board);
    if(winCondition) return winCondition;

    winCondition = checkDiagonalVictory(board);
    if(winCondition) return winCondition;

    winCondition = checkDraw(turn);
    if(winCondition) return winCondition;

    return winCondition;
}

int checkHorizontalVictory(char* board[8][8])
{
    int counterX;
    int counterO;

    for(int i=1; i<=5; i+=2)
    {
        counterX = 0;
        counterO = 0;

        for(int j=1; j<=5; j+=2)
        {
            if(board[i][j] == ' ')
            {
                break;
            }
            else if(board[i][j] == 'X')
            {
                counterX++;
            }
            else if(board[i][j] == 'O')
            {
                counterO++;
            }
        }

        if      (counterX == 3) return 1;
        else if (counterO == 3) return 2;
    }

    return 0;
}

int checkVerticalVictory(char* board[8][8])
{
    int counterX;
    int counterO;

    for(int j=1; j<=5; j+=2)
    {
        counterX = 0;
        counterO = 0;

        for(int i=1; i<=5; i+=2)
        {
            if(board[i][j] == ' ')
            {
                break;
            }
            else if(board[i][j] == 'X')
            {
                counterX++;
            }
            else if(board[i][j] == 'O')
            {
                counterO++;
            }
        }

        if      (counterX == 3) return 1;
        else if (counterO == 3) return 2;
    }

    return 0;
}

int checkDiagonalVictory(char* board[8][8])
{
    int counterX = 0;
    int counterO = 0;

    //Left to Right
    for(int i=1; i<=5; i+=2)
    {
        if(board[i][i] == ' ')
        {
            break;
        }
        else if(board[i][i] == 'X')
        {
            counterX++;
        }
        else if(board[i][i] == 'O')
        {
            counterO++;
        }
    }

    if      (counterX == 3) return 1;
    else if (counterO == 3) return 2;

    //Right to Left
    counterX = 0;
    counterO = 0;

    for(int k=0, i=1, j=5; k<3; k++, i+=2, j-=2)
    {
        if(board[i][j] == ' ')
        {
            break;
        }
        else if(board[i][j] == 'X')
        {
            counterX++;
        }
        else if(board[i][j] == 'O')
        {
            counterO++;
        }
    }

    if      (counterX == 3) return 1;
    else if (counterO == 3) return 2;

    else return 0;
}

checkDraw(int* turn)
{
    if(*turn == 9)
    {
        return 3;
    }

    return 0;
}

int promptReplay()
{
    char choice;
    puts("\n\nPlay Again? (y/n): ");
    choice = getchar();

    if(choice == 'y')
    {
        fflush(stdin);
        return 1;
    }
    else if(choice == 'n')
    {
        fflush(stdin);
        return 0;
    }
    else
    {
        fflush(stdin);
        puts("\nWrong input.\n");
        promptReplay();
    }
}

void resetBoard(char* board[8][8], int* turn)
{
    *turn = 0;

    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            board[i][j] = emptyboard[i][j];
        }
    }
}

void declareWinner(gameState currentGameState)
{
    switch (currentGameState)
    {
        case Player1Wins:
                puts("Player 1 wins!"); break;
        case Player2Wins:
                puts("Player 2 wins!"); break;
        case Draw:
                puts("Player 2 wins!"); break;
    }
}

void clearScreen()
{
    #ifdef _WIN32
    system("cls");

    #elif __linux__
    system("clear");

    #endif
}
