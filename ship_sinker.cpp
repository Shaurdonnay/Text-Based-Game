// Natasha Johnson, CSC C++ class, August 17th 2021
// Assignment: Putting It All Together
// This is my text based game for the Assignment: Putting It All Together
// I tried to get the sleep function to work to "take a break" before the next line but it wouldn't work so I googled it and it said to use these preprocessors to make usleep work
// The Windows.h is saying for the program to run in windows... This was not working for me
#ifdef _WIN32
#include <Windows.h>
// The next lines tell the program to run unistd.h (linux) if the user is not using Windows
// I am starting to wonder if it is because I use Linux and have to run these programs online
#else
#include <unistd.h>
#endif
/* The next line is a preprocessor directive, it is indicated with the # symbol. The preprocessor
runs before the compiler and substitutes text based on various directived. The # is telling the 
program to include the contents of the iostream and string, which are part of the standard library */
#include <iostream>
// The next line indicates that I want to use the standard namespace for the entire program
// It makes the text shorter and when you type a lot makes your code a little easier
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
// The following is the namespace that holds all the functions called
namespace game
// The following lines are for my rows and colums
{
/* The next lines are the header of a function of rows, columns, and maximum number of ships(). Int indicates that the function will
return a value, in this case it indicates that the functions will return an integer value */
    int rows = 0;
    int columns = 0;
    int maxNumbShips = 0;
// Creates a pointer to point to a string literal "text". This is faster than the array version.
// located in an read only implementation defined memory. 
    const char WATER = '~';
    const char HIT = 'X';
    const char MISS = '/';
    const char SHIP = 'S';
    const char EMPTY = ' ';
}
// The following are my functions for the game. Included are pointers per the assignment.
void initBoard(std::vector<std::vector<char>>& playingBoard);
void displayBoard(std::vector<std::vector<char>> playingBoard);
void initShips(std::vector<std::vector<char>>& ships);
// Bool is a type that can hold only two values: true and false . I used it to determine what to do based on if the asking is true or false.
bool isGameOver(int shipsDestroyed);
// The following are my functions for the game. Included are pointers per the assignment.
void shoot(std::vector<std::vector<char>>& playingBoard, std::vector<std::vector<char>>& ships, int& shipsDestroyed, int& turns);
/* The next lines are the header of a function of row position and column position. Int indicates that the function will
return a value, in this case it indicates that the functions will return an integer value */
int enterRowPosition();
int enterColPosotion();
// The following are my functions for the game. Included are pointers per the assignment.
void selectDifficulty();
/* The next line is the header of a function of main(). Int indicates that the function will
return a value, in this case it indicates that the functions will return an integer value */
int main()
{
    std::vector<std::vector<char>> playingBoard;
    std::vector<std::vector<char>> ships;
//How many ships have been destroyed by the player
    int shipsDestroyed = 0; 
    int turns = 0;
// The following lines set the difficulty of the game. There is easy, medium, and hard. 
    selectDifficulty();
    initBoard(playingBoard);
    initShips(ships);
    displayBoard(playingBoard);
// If the game is over, the following will be displayed. 
    while (!isGameOver(shipsDestroyed))
    {
        shoot(playingBoard, ships, shipsDestroyed, turns);
        displayBoard(playingBoard);
    }
/* As stated in my previus assignment, cout is an object, and is used to send data to the standart output string. The << says
to send the string to cout. At the end the endl string is being sent to the standard output with the << and is the same as saying 
"hit the enter button" It is used throughout the program as it is a text based game and outputs many strings*/
// The number of turns it took all the ships to be destroyed in.
    std::cout << "You destroyed all of the ships in: " << turns << " turns.";

    std::string barn;
    std::cin >> barn;
    return 0;
}
// Definition of my function initBoard
void initBoard(std::vector<std::vector<char>>& playingBoard)
{
    std::vector<char> tempVector;
    for (int i = 0; i < game::rows; i++)
    {
        tempVector.push_back(game::WATER);
    }

    for (int i = 0; i < game::columns; i++)
    {
        playingBoard.push_back(tempVector);
    }
}
// Definition of my function initShips
void initShips(std::vector<std::vector<char>>& ships)
{
    std::vector<char> tempVector;
    for (int i = 0; i < game::rows; i++)
    {
        tempVector.push_back(game::EMPTY);
    }

    for (int i = 0; i < game::columns; i++)
    {
        ships.push_back(tempVector);
    }
// The following line makes use of the computer's internal clock to control the choice of the seed. Since time is continually changing, the seed is going to forever changing.
// The difference between this code and my last assignment, is instead of using a "time" this code is making the keyword called random out of my enumerated words.
    srand(time(NULL));
// Bool is a type that can hold only two values: true and false . I used it to determine what to do based on if the asking is true or false.
    bool emptyPosition = false;

    for (int ship = 0; ship < game::maxNumbShips; ship++)
    {
        do
        {
            int x = rand() % game::rows;
            int y = rand() % game::columns;

            if (ships[x][y] == game::SHIP)
            {
                emptyPosition = false;
            }
            else
            {
                ships[x][y] = game::SHIP;
                emptyPosition = true;
            }
        } while (!emptyPosition);
    }
}
// Definition of my function
void displayBoard(std::vector<std::vector<char>> playingBoard)
{
    std::cout << "\n";
    for (int row = 0; row < game::rows; row++)
    {
        std::cout << "\t";
        for (int col = 0; col < game::columns; col++)
        {
            std::cout << playingBoard[row][col];
            std::cout << "\t";
        }
        std::cout << "\n";
    }
}

// Bool is a type that can hold only two values: true and false . I used it to determine what to do based on if the asking is true or false.
bool isGameOver(int shipsDestroyed)
{
    return shipsDestroyed >= game::maxNumbShips;
}
// Definition of my function
void shoot(std::vector<std::vector<char>>& playingBoard, std::vector<std::vector<char>>& ships, int& shipsDestroyed, int& turns)
{
    int row = enterRowPosition();
    int col = enterColPosotion();

    if (ships[row][col] == game::SHIP)
    {
        playingBoard[row][col] = game::HIT;
        shipsDestroyed++;
    }

    else
    {
        playingBoard[row][col] = game::MISS;
    }
    turns++;
}
// Definition of my function
int enterRowPosition()
{
    int row = 0;
    do
    {
        std::cout << "Enter row: ";
        std::cin >> row;
    }
    while (row < 0 || row >= game::rows);

    return row;
}
// Definition of my function
int enterColPosotion()
{
    int col = 0; 
    do
    {
        std::cout << "Enter column: ";
        std::cin >> col;
    } while (col < 0 || col >= game::columns);

    return col;
}
// Definition of my function to select the difficulty of the game
void selectDifficulty()
{
    int choice = 0;
    std::cout << "Select difficulty.\n";
    std::cout << "1: Easy.\n2: Medium. \n3: Hard.\n";
    std::cin >> choice;

    switch (choice)
    {
// Easy difficulty settings
    case 1:
        game::rows = 2;
        game::columns = 2;
        game::maxNumbShips = 1;
        break;
// Medium difficulty settings
    case 2:
        game::rows = 4;
        game::columns = 4;
        game::maxNumbShips = 4;
        break;
// Hard difficulty settings
    case 3:
        game::rows = 8;
        game::columns = 8;
        game::maxNumbShips = 8;
        break;
// If no valid selection is made for difficulty
    default:
        std::cout << "Please enter valid information.";
        break;
    }
}
