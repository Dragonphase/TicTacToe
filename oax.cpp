#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "grid.h"
#include "player.h"

using namespace std;

void getPlayerDetails(Grid *grid);
void showWelcomeMessage();

Grid* createGrid(){
    string input = "";
    Grid *grid;

    while (true)
    {
        if (!(cin >> input))
        {
            cout << endl << endl <<  "Incorrect value. Please try again:  ";
            cin.ignore();
        }else if(input == "1")
        {
            grid = new Grid(3); //Set instance of grid to a new Grid of size 3
            grid->setExpert(false);
            break;
        }else if( input == "2")
        {
            grid = new Grid(10); //Set instance of grid to a new Grid of size 10
            grid->setExpert(true);
            break;
        }
        else{
            cout << endl << endl <<  "Incorrect value. Please try again:  ";
            cin.ignore();
        }
    }

    clearScreen(100);

    string difficulty = grid->getExpert() ? "Expert" : "Beginner";
    string score = grid->getExpert() ? "four" : "three";

    getPlayerDetails(grid);
    cout << endl << difficulty << " difficulty chosen:";
    cout << endl << "   Player " << grid->getPlayer(true)->getName() << " is X";
    cout << endl << "   Player " << grid->getPlayer(false)->getName() << " is O";
    cout << endl << "Score " << score << " in a row to win." << endl;
    cout << endl << "Enter your co-ordinates like so - \"X,Y\":";

    cout << endl << endl;

    return grid;
}

void getPlayerDetails(Grid *grid){
    Player *p1,*p2; //Declare 2 player object pointers
    string player1, player2, pID1, pID2; //Declare player names and IDs
    cout << "What is the name of player 1: ";
    cin >> player1;
    cout << endl << "What is " << player1 << "'s ID: ";
    cin >> pID1;
    p1 = new Player(player1, pID1); //Initialize player 1
    clearScreen(100);
    cout << "What is the name of player 2: ";
    cin >> player2;
    cout << endl << "What is " << player2 << "'s ID: ";
    cin >> pID2;
    p2 = new Player(player2, pID2); //Initialize player 2
    clearScreen(100);
    grid->setPlayerDetails(p1, p2); //Pass player pointers to grid
}

void showWelcomeMessage(){
    clearScreen(100);
    cout << "Welcome to O's and X's. Please choose a difficulty:" << endl << endl;
    cout << "  1   Beginner difficulty" << endl;
    cout << "  2   Expert difficulty" << endl << endl;
    cout << "Difficulty:  ";
}

int main(){
    showWelcomeMessage();

    Grid *grid = createGrid();

    grid->playGame();

    return 0;
}
