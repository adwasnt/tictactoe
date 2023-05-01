//Tic Tac Toe game made in C Source Code in Xcode Complier by Joseph Graves
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //library is used for sleep() function for AI's turn.
#include <time.h>

void introScreen(void);

void displayScreen(int);

char getLetter(int);

int getSquare(char, int, int, int[]);

int getResults(char[], int);

int getMode(void);

void clearscr(void);

int getDifficulty(void);

int main(void)
{
    int mode = 0, difficulty = 0;
    
    clearscr();
    introScreen(); // calls boot up screen and tutorial
    clearscr();
    mode = getMode();//gets whether the play wants to play singleplayer or multiplayer
    if(mode == 1)
    {
        difficulty = getDifficulty();
    }
    clearscr();
    displayScreen(mode); //starts the game
    return 0;
    
}

void introScreen(void)
{
    printf("%s\n%s\n%s\n\n%s\n",
           "Tic Tac Toe",
           "-----------",
           "How to play:\n-- Two players wil take turns placing either X's or O's\n-- Type where you want your piece to be on the board\n-- Whoever gets 3 in a row wins the game\n\nSingleplayer Mode:\n-- Play against a computer player if you are by yourself.\n\nMultiplayer:\n-- Grab a friend and takes turns placing pieces on the board.",
           "Press ENTER to continue...");
    getchar();
}

void displayScreen(int mode)
{
    int i, k, displayType, arrayCounter = 0, square[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1}, number = -1, turn = 0, retry = 1;
    char squareArray[9] = {'-','-','-','-','-','-','-','-','-'}, value = 'a';
    
    do{
        if (number != -1) // will not start the for loop if there is no sqaure inputted
        {
            if(squareArray[number] == 'X' || squareArray[number] == 'O') //check for if the piece the player placed is already occupied by                                                              another piece and will only increase the turn if it's not.
            {
                clearscr();
            }
            else
            {
                turn++;
            }
            
            for(k = 0; k < 9; k++) //for loop sets the display for players if the sqaure contains a piece (will start after 1 turn)
            {
                if(k == number && k != square[k])
                {
                    squareArray[k] = value;
                    square[k] = number;
                }
            }
        }
        
        for(i = 1; i <= 24; i++) //for loop displays the board to the terminal
        {
            displayType = i % 2;
            
            if (i % 8 == 0) //creates a new line if the counter reaches a limit based on modulo statement
            {
                printf("\n");
            }
            else
            {
                switch(displayType) //switches between a display piece and what is in the character array
                {
                    case 0:
                        printf("%c",squareArray[arrayCounter]);
                        arrayCounter++; //keeps track on what array number it's on with going out of index
                        break;
                    case 1:
                        printf("|");
                        break;
                }
            }
        }
        
        printf("\n");
        
        if (turn % 2 == 1 && mode == 1)
        {
            sleep(1);
        }
        
        retry = getResults(squareArray, turn);
        
        if (retry == 0)
        {
            break;
        }
        
        arrayCounter = 0; //resets array counter after board has been displayed
        value = getLetter(turn); //function call for getting either X or O
        number = getSquare(value, turn, mode, square); //asks the player what sqaure they want to put their piece on
        clearscr();
        fflush(stdin);
    }while(retry == 1 && turn < 9);

}

char getLetter(int turn)
{
    char value = 'a';
    int switchValue;
    
    switchValue = turn % 2;
    
    switch(switchValue)
    {
        case 0:
            value = 'X';
            break;
        case 1:
            value = 'O';
            break;
    }
    
    return value;
}

int getSquare(char value, int turn, int mode, int squareArray[])
{
    int square, userInput, i, sqaureFound = 0;
    
    srand(time(NULL));
    
    if (turn % 2 == 1 && mode == 1)
    {
        square = rand() % 9 + 1;
        
        if(mode == 2)
        {
            for(i = 0; i < 9; i++)
            {
                if(squareArray[i] != -1 && squareArray[i + 2] != -1 && i % 2 == 1)
                {
                    square = i + 1;
                    sqaureFound = 1;
                    break;
                }
            }
            
            if(sqaureFound == 0)
            {
                for(i = 0; i < 9; i++)
                {
                    if(squareArray[i] != -1 && squareArray[i + 1] != -1)
                    {
                        if(squareArray[i + 2] == -1)
                        {
                            square =  i + 2;
                            sqaureFound = 1;
                            break;
                        }
                        else if(squareArray[i - 1] == -1)
                        {
                            square = i - 1;
                            sqaureFound = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
    else
    {
        do{
            printf("What square do you want to put %c in?\n", value);
            userInput = scanf("%d", &square);
            if (userInput == 0)
            {
                fflush(stdin);
            }
        }while(userInput == 0);
    }
    
    square -= 1;
    
    return square;
}

int getResults(char square[], int turn)
{
    int retry = 1;
    
    //win conditions are based on if the user matches 3 in a row
    
    if(square[0] == 'X' && square[4] == 'X' && square[8] == 'X')
    {
        retry = 0; // ends the game if retry is 0> otherwise, it keeps going.
        printf("X Wins!\n\n"); // winning display
    }
    
    if(square[2] == 'X' && square[4] == 'X' && square[6] == 'X')
    {
        retry = 0;
        printf("X Wins!\n\n");
    }
    
    if(square[0] == 'O' && square[4] == 'O' && square[8] == 'O')
    {
        retry = 0;
        printf("O Wins!\n\n");
    }
    
    if(square[2] == 'O' && square[4] == 'O' && square[6] == 'O')
    {
        retry = 0;
        printf("O Wins!\n\n");
    }
    
    if(square[0] == 'X' && square[1] == 'X' && square[2] == 'X')
    {
        retry = 0;
        printf("X Wins!\n\n");
    }
    
    if(square[3] == 'X' && square[4] == 'X' && square[5] == 'X')
    {
        retry = 0;
        printf("X Wins!\n\n");
    }
    
    if(square[6] == 'X' && square[7] == 'X' && square[8] == 'X')
    {
        retry = 0;
        printf("X Wins!\n\n");
    }
    
    if(square[0] == 'O' && square[1] == 'O' && square[2] == 'O')
    {
        retry = 0;
        printf("O Wins!\n\n");
    }
    
    if(square[3] == 'O' && square[4] == 'O' && square[5] == 'O')
    {
        retry = 0;
        printf("O Wins!\n\n");
    }
    
    if(square[6] == 'O' && square[7] == 'O' && square[8] == 'O')
    {
        retry = 0;
        printf("O Wins!\n\n");
    }
    
    if(square[0] == 'X' && square[3] == 'X' && square[6] == 'X')
    {
        retry = 0;
        printf("X Wins!\n\n");
    }
    
    if(square[1] == 'X' && square[4] == 'X' && square[7] == 'X')
    {
        retry = 0;
        printf("X Wins!\n\n");
    }
    
    if(square[2] == 'X' && square[5] == 'X' && square[8] == 'X')
    {
        retry = 0;
        printf("X Wins!\n\n");
    }
    
    if(square[0] == 'O' && square[3] == 'O' && square[6] == 'O')
    {
        retry = 0;
        printf("O Wins!\n\n");
    }
    
    if(square[1] == 'O' && square[4] == 'O' && square[7] == 'O')
    {
        retry = 0;
        printf("O Wins!\n\n");
    }
    
    if(square[2] == 'O' && square[5] == 'O' && square[8] == 'O')
    {
        retry = 0;
        printf("O Wins!\n\n");
    }
    
    if (turn > 8)
    {
        retry = 0;
        printf("Game Over!\n\n");
    }
    return retry;
}

int getMode(void)
{
    int mode, userInput;
    
    do{
        printf("Select a Mode:\n|\nType 1 for singleplayer\n|\nType 2 for multiplayer\n");
        userInput = scanf("%d", &mode);
        if (userInput != 1)
        {
            fflush(stdin);
        }
    }while(userInput != 1 || mode < 1 || mode > 2);
    
    return mode;
}


void clearscr(void)
{
    int i;
    
    for(i = 0; i < 50; i++)
    {
        printf("\n");
    }
}

int getDifficulty(void)
{
    int mode, userInput;
    
    do{
        printf("Select a Difficulty:\n|\nType 1 for Easy\n|\nType 2 for Hard\n");
        userInput = scanf("%d", &mode);
        if (userInput != 1)
        {
            fflush(stdin);
        }
    }while(userInput != 1 || mode < 1 || mode > 2);
    
    return mode;
}
