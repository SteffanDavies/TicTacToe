#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

void clearScreen();
void clearBoard();
void drawBoard();
int getPlayerInput(); //Returns 1 if valid
void addToBoard();
int checkWin();
int promptReplay();


int main()
{
    char board[8][8] = {
    };
    char posX, posY;
    int player = 1;     //Can be 1 or 2
    int turn = 0;      //Draw at 9
    int gameover = 0;
    int restart = 0;
    do{
        clearBoard(board, &turn);
        do
        {
            drawBoard(board);
            while(!getPlayerInput(player, &posX, &posY));
            addToBoard(board, &player, &turn, &posX, &posY);
            gameover = checkWin(board, &turn);
        }while(!gameover);
        restart = promptReplay();
    }while(restart);

    return 0;
}

void drawBoard(char* (board)[][8])
{
    clearScreen();

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

void addToBoard(char* (board) [][8], int* player, int* turn, char* posX, char* posY)
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

int checkWin(char* (board)[][8], int* turn)
{
    int counterX = 0;
    int counterO = 0;
    /*
    Valid positions:
        [1][1], [1][3], [1][5],
        [3][1], [3][3], [3][5],
        [5][1], [5][3], [5][5],
    */

    //Check Horizontal Trio
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

        if(counterX == 3)
        {
            drawBoard(board);
            printf("\nPlayer 1 wins!\n\n");
            return 1;
        }

        else if(counterO == 3)
        {
            drawBoard(board);
            printf("\nPlayer 2 wins!\n\n");
            return 1;
        }
    }

    //Check Vertical Trio
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

        if(counterX == 3)
        {
            drawBoard(board);
            printf("\nPlayer 1 wins!\n\n");
            return 1;
        }

        else if(counterO == 3)
        {
            drawBoard(board);
            printf("\nPlayer 2 wins!\n\n");
            return 1;
        }
    }

    //Check Diagonal Trio - Left to Right
    counterX = 0;
    counterO = 0;
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

        if(counterX == 3)
        {
            drawBoard(board);
            printf("\nPlayer 1 wins!\n\n");
            return 1;
        }

        else if(counterO == 3)
        {
            drawBoard(board);
            printf("\nPlayer 2 wins!\n\n");
            return 1;
        }
    }

    //Check Diagonal Trio - Right to Left
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

    if(counterX == 3)
    {
        drawBoard(board);
        printf("\nPlayer 1 wins!\n\n");
        return 1;
    }

    else if(counterO == 3)
    {
        drawBoard(board);
        printf("\nPlayer 2 wins!\n\n");
        return 1;
    }

    //Check draw
    if(*turn == 9)
    {
        drawBoard(board);
        printf("\nDraw!\n\n");
        return 1;
    }

    return 0;
}


int promptReplay()
{
    char choice;
    puts("\n\nPlay Again (y/n): ");
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

void clearBoard(char* (board)[][8], int* turn)
{
    *turn = 0;

    char emptyboard[8][8] = {
        {'-','-','-','-','-','-','-',' '},
        {'|',' ','|',' ','|',' ','|','3'},
        {'-','-','-','-','-','-','-',' '},
        {'|',' ','|',' ','|',' ','|','2'},
        {'-','-','-','-','-','-','-',' '},
        {'|',' ','|',' ','|',' ','|','1'},
        {'-','-','-','-','-','-','-',' '},
        {' ','a',' ','b',' ','c',' ',' '}
    };

    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            board[i][j] = emptyboard[i][j];
        }
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
