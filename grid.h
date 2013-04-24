#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED
#include <iostream>
#include <stdarg.h> //For the messageBox function
#include <fstream>
#include <sstream>
#include "player.h"

using namespace std;

void clearScreen(int iterations); //Simple screen-clearing function.
void addSpace(int iterations); //Simplified way to add a number of spaces.
void messageBox(int args, ...); //messageBox function to display a formatted designed message box.
string convert(int number); //convert an integer to a string.
void resizeWindow(int width, int height);
void resizeWindow();

const char tl = '\x0DA';
const char tr = '\x0BF';
const char bl = '\x0C0';
const char br = '\x0D9';
const char h = '\x0C4';
const char v = '\x0B3';
const char a = '\x0C5';

int leaderboard[4][10]; //leaderboard array, used to store and manipulate player scores based on ID

class Grid
{
    public:
        Grid(int gridSize);
        int getGridSize();
        void setGridSize(int gridSize);
        bool getExpert();
        void setExpert(bool isExpert);
        bool getDraw();
        void setDraw(bool isDraw);
        void setPlayerDetails(Player *player1, Player *player2);
        Player *getPlayer(bool player);
        void printGrid();
        void playGame();
        void saveLeaderboard(Player *player);
        void saveLeaderboard();
        bool checkDirections(bool player);
        bool setGridIndex(int x, int y, bool player);
        ~Grid();
    private:
        char **grid;
        int size;
        bool expert, draw;
        Player *p1, *p2;
};
/**
    Constructor, defines the size of the grid.
    NOTE: Only one integer parameter is needed; grid width and height will be the same.
**/
Grid::Grid(int gridSize){
    Grid::setGridSize(gridSize); //Set the size
    int sizePrime = gridSize * 2;
    grid = new char *[sizePrime]; //Create a new char array of sizePrime

    for (int i = 0; i < sizePrime-1; i ++){
        grid[i] = new char[sizePrime]; //Store a char array within the char array indexed to grid[i]
        for (int j = 0; j < sizePrime-1; j ++){
            grid[i][j] = ' '; //set the default character of each point in the grid to an empty space.
        }
    }
}

int Grid::getGridSize(){
    return size;
}

void Grid::setGridSize(int gridSize){
    size = gridSize;
}

bool Grid::getExpert(){
    return expert;
}

void Grid::setExpert(bool isExpert){
    expert = isExpert;
}

bool Grid::getDraw(){
    return draw;
}

void Grid::setDraw(bool isDraw){
    draw = isDraw;
}

void Grid::setPlayerDetails(Player *player1, Player *player2){
    p1 = player1;
    p2 = player2;
}

Player *Grid::getPlayer(bool player){
    return player ? p1 : p2;
}

void Grid::printGrid(){
    int spacing = 35 - Grid::getGridSize();
    for (int i = 0; i < spacing; i ++) cout << " "; cout << "  " << v;
    for (int i = 0; i < Grid::getGridSize(); i ++){
        cout << " " << i;
    }
    cout << endl;
    for (int i = 0; i < spacing; i ++) cout << " "; cout << h << h << a << h;
    for (int i = 0; i < Grid::getGridSize(); i ++){
        cout << "\x0C4\x0C4";
    }
    cout << endl;
    for (int i = 0; i < Grid::getGridSize(); i ++){
        for (int i = 0; i < spacing; i ++) cout << " "; cout << i << " " << v;
        for (int j = 0; j < Grid::getGridSize(); j ++){
            cout << " " << grid[j][i];
        }
        cout << endl;
    }
    cout << endl << endl;
}

void Grid::saveLeaderboard(Player *player){ //player won
    ofstream os;
    os.open("leaderboard.dat");
    for (int i = 0; i < 10; i ++){
        int record[4];
        record[0] = i;
        record[1] = leaderboard[1][i]; //Total
        record[2] = leaderboard[2][i]; //Wins
        record[3] = leaderboard[3][i]; //Draws

        /*
            We check using i+1 because we want to store the data so it can be picked
            up by an array easily, but so it is displayed as 1-10 on the leaderboards
            instead of 0-9.
        */
        if (convert(i+1) == player->getID()){
            record[1]++;
            record[2]++;
        }
        if (convert(i+1) == getPlayer(false)->getID()){
            record[1]++;
        }
        os << record[0] << " " << record[1] << " " << record[2] << " " << record[3] << endl;
    }
    os.close();
}

void Grid::saveLeaderboard(){ //Game was a draw
    ofstream os;
    os.open("leaderboard.dat");
    for (int i = 0; i < 10; i ++){
        int record[4];
        record[0] = i;
        record[1] = leaderboard[1][i]; //Total
        record[2] = leaderboard[2][i]; //Wins
        record[3] = leaderboard[3][i]; //Draws
        if (convert(i+1) == getPlayer(true)->getID()){
            record[1]++;
            record[3]++;
        }
        if (convert(i+1) == getPlayer(false)->getID()){
            record[1]++;
            record[3]++;
        }
        os << record[0] << " " << record[1] << " " << record[2] << " " << record[3] << endl;
    }
    os.close();
}

void Grid::playGame(){
    string input = "";

    bool player = true; //true = player 1, false = player 2
    bool winner = false;

    printGrid();

    addSpace(27); cout << getPlayer(player)->getName() << " -> Input value:  ";

    while (!winner && !draw){
        if (!(cin >> input))
        {
            cout << endl << endl;
            addSpace(10); cout <<  "Incorrect value. Please try again:  ";
            cin.ignore();
        }else if(input != "" && input.length() == 3)
        {
            int x = input.at(0)-48; //Get the first character entered. -48 to get the char value of the integer.
            int y = input.at(2)-48; //Get the second character entered. -48 to get the char value of the integer.
            if (!Grid::setGridIndex(x, y, player)){
                cout << endl << endl;
                addSpace(20); cout <<  "Position already set. Enter another value:  ";
            }else{
                system("cls");

                clearScreen(11+Grid::getGridSize()/2-Grid::getGridSize());

                Grid::printGrid();
                if (Grid::checkDirections(player)){
                    system("cls");
                    string winMessage = getPlayer(player)->getName() + " won!";
                    clearScreen(2);
                    Grid::printGrid();
                    messageBox(1, winMessage.c_str());

                    resizeWindow(677, 342+Grid::getGridSize()*10/2);

                    saveLeaderboard(getPlayer(player));
                    winner = true;
                }else{
                    if (Grid::getDraw()){
                        system("cls");
                        clearScreen(2);
                        Grid::printGrid();
                        messageBox(1, "The game is a draw!");

                        resizeWindow(677, 342+Grid::getGridSize()*10/2);

                        saveLeaderboard();
                        winner = false;
                        draw = true;
                    }else{
                        player = !player;
                        addSpace(27); cout << getPlayer(player)->getName() << " -> Input value:  ";
                    }
                }
            }
        }
        else{
            cout << endl << endl;
            addSpace(10); cout <<  "Incorrect value. Please try again:  ";
            cin.ignore();
        }
    }
}

bool Grid::checkDirections(bool player){ //This is where the magic happens
    const int needed = Grid::getExpert() ? 4 : 3;
    const int gridSize = Grid::getGridSize();

    const char character = player ? 'X' : 'O';

    //Set draw to true automatically - draw is set to false if a space character is found
    Grid::setDraw(true);

    //Vertical Check
    for(int col = 0; col < gridSize; col ++){
        int consecutive = 0; //Counter -> number of consecutive identical vertical characters
        for (int row = 0; row < gridSize && consecutive < needed; row ++){
            if (grid[row][col] == character){
                consecutive ++;
                if (consecutive == needed) return true;
            }else{
                consecutive = 0;
            }
            if (grid[row][col] == ' '){
                Grid::setDraw(false);
            } //Only called in one direction check (it iterates through the entire grid)
        }
    }

    //Horizontal Check
    for(int col = 0; col < gridSize; col ++){
        int consecutive = 0; //Counter -> number of consecutive identical horizontal characters
        for (int row = 0; row < gridSize && consecutive < needed; row ++){
            if (grid[col][row] == character){
                consecutive ++;
                if (consecutive == needed) return true;
            }else{
                consecutive = 0;
            }
        }
    }

    //Right Diagonal Check
    for (int col = 0; col < gridSize; col ++){
        for (int row = 0; row < gridSize; row ++){
            if (grid[col][row] != character) continue; //We haven't found the character yet
            int consecutive = 0; //Counter -> number of consecutive identical right-diagonal characters

            //Found the corresponding character, iterate through each right diagonal character from this spot
            for (int x = row, y = col; x < gridSize && y < gridSize && consecutive < needed; x++, y++){
                if (grid[y][x] == character){
                    consecutive ++;
                    if (consecutive == needed) return true;
                }else break; //Incorrect character, break from loop
            }
        }
    }

    //Left Diagonal Check
    for (int col = 0; col < gridSize; col ++){
        for (int row = 0; row < gridSize; row ++){
            if (grid[col][row] != character) continue; //We haven't found the character yet
            int consecutive = 0; //Counter -> number of consecutive identical left-diagonal characters

            //Found the corresponding character, iterate through each left diagonal character from this spot
            for (int x = row, y = col; x >= 0 && y < gridSize && consecutive < needed; x--, y++){
                if (grid[y][x] == character){
                    consecutive ++;
                    if (consecutive == needed) return true;
                }else break; //Incorrect character, break from loop
            }
        }
    }
}

bool Grid::setGridIndex(int x, int y, bool player){
    char character = player ? 'X' : 'O';
    if (grid[x][y] == ' '){
        grid[x][y] = character;
        return true; //Set the grid co-ordinates to the corresponding character and return true
    }else{
        return false;
    }
}

void clearScreen(int iterations)
{
    for (int i = 0; i < iterations; i ++) cout << endl;
}

/**
    This function simply prints out a defined number of space characters.
**/
void addSpace(int iterations){
    for (int i = 0; i < iterations; i ++) cout << ' ';
}

/**
    This function creates a message box using the constant chars defined above as a border
    It then calculates the length of the string(s) in order to create a position for the string,
    then calculates the length of the remaining space to finish the edge of the box off.
**/
void messageBox(int args, ...){
    va_list arguments;
    va_start(arguments, args);

    addSpace(13); cout << tl; for (int i = 0; i < 50; i ++) cout << h; cout << tr; cout << endl;
    for (int i = 0; i < args; i ++){
        string message = va_arg(arguments, const char *);
        int total = (50-message.length())/2;
        for (int x = 0; x < total; x ++) message = " " + message;
        addSpace(13); cout << v; cout << message; addSpace(50-message.length()); cout << v << endl;
    }
    addSpace(13); cout << bl; for (int i = 0; i < 50; i ++) cout << h; cout << br; cout << endl;
    va_end(arguments);
}

string convert(int number){
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

/**
    Custom window size
**/
void resizeWindow(int width, int height){
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}

/**
    Default window size
**/
void resizeWindow(){
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 677, 342, TRUE);
}

#endif // GRID_H_INCLUDED
