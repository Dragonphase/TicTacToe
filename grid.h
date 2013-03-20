#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED
#include "player.h"

using namespace std;

void clearScreen(int iterations);

class Grid
{
    public:
        Grid(int gridSize);
        Grid* createGrid();
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
        bool checkDirections(bool player);
        bool hasCharacter(int x, int y, bool player);
        bool setGridIndex(int x, int y, bool player);
        ~Grid();
    private:
        char **grid;
        int size;
        bool expert, draw;
        Player *p1, *p2;
};

Grid::Grid(int gridSize){
    Grid::setGridSize(gridSize);
    int sizePrime = gridSize * 2;
    grid = new char *[sizePrime];

    for (int i = 0; i < sizePrime-1; i ++){
        grid[i] = new char[sizePrime];
        for (int j = 0; j < sizePrime-1; j ++){
            grid[i][j] = ' ';
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
    cout << "  |";
    for (int i = 0; i < Grid::getGridSize(); i ++){
        cout << " " << i;
    }
    cout << endl;
    cout << "--+-";
    for (int i = 0; i < Grid::getGridSize(); i ++){
        cout << "--";
    }
    cout << endl;
    for (int i = 0; i < Grid::getGridSize(); i ++){
        cout << i << " |";
        for (int j = 0; j < Grid::getGridSize(); j ++){
            cout << " " << grid[j][i];
        }
        cout << endl;
    }
    cout << endl << endl;
}

void Grid::playGame(){
    string input = "";

    bool player = true; //true = player 1, false = player 2
    bool winner = false;

    Grid::printGrid();

    cout << getPlayer(player)->getName() << " -> Input value:  ";

    while (!winner){
        if (!(cin >> input))
        {
            cout << endl << endl <<  "Incorrect value. Please try again:  ";
            cin.ignore();
        }else if(input != "")
        {
            int x = input.at(0)-48;
            int y = input.at(2)-48;
            if (!Grid::setGridIndex(x, y, player)){
                cout << endl << endl <<  "Position already set. Enter another value:  ";
            }else{
                clearScreen(100);
                Grid::printGrid();
                if (Grid::checkDirections(player)){
                    cout << getPlayer(player)->getName() << " won!";
                    winner = true;
                }else{
                    if (Grid::getDraw()){
                        cout << "The game is a draw!";
                        winner = true;
                    }else{
                        player = !player;
                        cout << getPlayer(player)->getName() << " -> Input value:  ";
                    }
                }
            }
        }
        else{
            cout << endl << endl <<  "Incorrect value. Please try again:  ";
            cin.ignore();
        }
    }
}

bool Grid::checkDirections(bool player){ //This is where the magic happens
    int needed = Grid::getExpert() ? 4 : 3;

    char character = player ? 'X' : 'O';

    //Set draw to true automatically - draw is set to false if a space character is found
    Grid::setDraw(true);

    //Vertical Check
    for(int row = 0; row < size; row ++){
        int consecutive = 0; //Counter -> number of consecutive identical vertical characters
        for (int col = 0; col < size && consecutive < needed; col ++){
            if (grid[col][row] == character){
                consecutive ++;
                if (consecutive == needed) return true;
            }else{
                consecutive = 0;
            }
            if (grid[col][row] == ' '){
                Grid::setDraw(false);
            } //Only called in one direction check (it iterates through the entire grid)
        }
    }

    //Horizontal Check
    for (int row = 0; row < size; row ++){
        int consecutive = 0; //Counter -> number of consecutive identical horizontal characters
        for (int col = 0; col < size && consecutive < needed; col ++){
            if (grid[row][col] == character){
                consecutive ++;
                if (consecutive == needed) return true;
            }else{
                consecutive = 0;
            }
        }
    }

    //Right Diagonal Check
    for (int col = 0; col < size; col ++){
        for (int row = 0; row < size; row ++){
            if (grid[col][row] != character) continue; //We haven't found the character yet
            int consecutive = 0; //Counter -> number of consecutive identical right-diagonal characters

            //Found the corresponding character, iterate through each right diagonal character from this spot
            for (int x = row, y = col; x < size && y < size && consecutive < needed; x++, y++){
                if (grid[y][x] == character){
                    consecutive ++;
                    if (consecutive == needed) return true;
                }else break; //Incorrect character, break from loop
            }
        }
    }

    //Left Diagonal Check
    for (int col = 0; col < size; col ++){
        for (int row = 0; row < size; row ++){
            if (grid[col][row] != character) continue; //We haven't found the character yet
            int consecutive = 0; //Counter -> number of consecutive identical left-diagonal characters

            //Found the corresponding character, iterate through each left diagonal character from this spot
            for (int x = row, y = col; x > 0 && y < size && consecutive < needed; x--, y++){
                if (grid[y][x] == character){
                    consecutive ++;
                    if (consecutive == needed) return true;
                }else break; //Incorrect character, break from loop
            }
        }
    }
}

bool Grid::hasCharacter(int x, int y, bool player){
    char character = player ? 'X' : 'O';
    return grid[x][y] == character; //Return whether the specific grid co-ordinates contain the corresponding character
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

#endif // GRID_H_INCLUDED
