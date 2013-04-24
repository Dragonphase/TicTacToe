#define _WIN32_WINNT 0x0500
#include <windows.h>
#include "grid.h"

/**
    Function constructor declarations
**/
Grid* createGrid();
void getPlayerDetails(Grid *grid);
void showWelcomeMessage();
void showLeaderboard();
void loadLeaderboard();

/**
    This creates the grid, which is accessed in the main method in order to issue the playGame function.
**/
Grid* createGrid(){
    string input = "";
    Grid *grid;
    while (true)
    {
        if (!(cin >> input)) //Store input from cin into the input string
        {
            cout << endl << "Incorrect value. Please try again:  ";
            cin.ignore();
        }else if(input == "1")
        {
            grid = new Grid(3); //Set instance of grid to a new Grid of size 3
            break;
        }else if(input == "2")
        {
            grid = new Grid(10); //Set instance of grid to a new Grid of size 10
            break;
        }else if(input == "3"){
            showLeaderboard(); //Show the leaderboard if option 3 is chosen
        }
        else{
            cout << endl << "Incorrect value. Please try again:  ";
            cin.ignore();
        }
    }

    resizeWindow(); //Set the window size back to default

     //Using the ?: operator, determine the difficulty of the grid based on its' size
    grid->setExpert(grid->getGridSize() == 10 ? true : false);

    //Store these details in strings so they can be converted to char sequences for the messageBox function
    //This method is elaborated in the getPlayerDetails function
    string difficulty = grid->getExpert() ? "Expert difficulty chosen:" : "Beginner difficulty chosen:";
    string score = grid->getExpert() ? "Score four in a row to win." : "Score three in a row to win.";

    getPlayerDetails(grid);

    string p1message = "Player " + grid->getPlayer(true)->getName() + " is X";
    string p2message = "Player " + grid->getPlayer(false)->getName() + " is O";
    string instruction = "Enter your co-ordinates like so - \"X,Y\":";

    messageBox(5, difficulty.c_str(),
               p1message.c_str(),
               p2message.c_str(),
               score.c_str(),
               instruction.c_str());

    cout << endl << endl;

    return grid;
}

/**
    Retrieve the details of both players.
**/
void getPlayerDetails(Grid *grid){
    Player *p1,*p2; //Declare 2 player object pointers
    string tempName, tempID; //Declare player names and IDs

    string message;

    system("cls");

    messageBox(1, "What is player 1's name:");
    addSpace(24); cout << "Enter here:  ";
    cin >> tempName;

    clearScreen(1);

    /*
        We can't pass this directly to the messageBox function as it cannot retrieve objects of non-trivially-copyable type.
        Instead, we concatenate the strings to pass and convert it to a character sequence using message.c_str();
    */
    message = "What is " + tempName + "'s ID (1-10): ";
    messageBox(1, message.c_str());
    addSpace(24); cout << "Enter here:  ";
    cin >> tempID;

    p1 = new Player(tempName, tempID); //Initialize player 1

    system("cls");

    messageBox(1, "What is player 2's name:");
    addSpace(24); cout << "Enter here:  ";
    cin >> tempName;

    clearScreen(1);
    message = "What is " + tempName + "'s ID (1-10): ";
    messageBox(1, message.c_str());
    addSpace(24); cout << "Enter here:  ";
    cin >> tempID;

    p2 = new Player(tempName, tempID); //Initialize player 2

    system("cls");
    grid->setPlayerDetails(p1, p2); //Pass player pointers to grid
}

void showWelcomeMessage(){
    clearScreen(1);

    /*
        The welcome message box. To compensate for the difficulty section central spacing,
        we need to make the strings the same length.
    */
    messageBox(8, "Welcome to O's and X's.",
               "",
               "Please choose an option:",
               "",
               "1   Beginner Difficulty             ",
               "2   Expert Difficulty               ",
               "3   Scoreboard                      ",
               "");

    addSpace(24); cout << "Input:  ";
}

void showLeaderboard(){
    resizeWindow(800, 370);
    system("cls");
    messageBox(1, "ID         Total     Wins     Draws     Losses");
    string record[10];
    for (int i = 0; i < 10; i ++){
            record[i] =
                convert(leaderboard[0][i]+1) + "          " +
                convert(leaderboard[1][i]) + "         " +
                convert(leaderboard[2][i]) + "         " +
                convert(leaderboard[3][i]) + "         " +
                convert(leaderboard[1][i] - (leaderboard[2][i] + leaderboard[3][i]));
    }

    messageBox(10,
               record[0].c_str(),
               record[1].c_str(),
               record[2].c_str(),
               record[3].c_str(),
               record[4].c_str(),
               record[5].c_str(),
               record[6].c_str(),
               record[7].c_str(),
               record[8].c_str(),
               record[9].c_str()
    );
    showWelcomeMessage();
}

void loadLeaderboard(){
    ifstream is;
    is.open("leaderboard.dat");

    if (is){
        for (int i = 0; i < 10; i ++){
            is >> leaderboard[0][i] >>  leaderboard[1][i] >>  leaderboard[2][i] >>  leaderboard[3][i];
        }
    }
    is.close();
}

int main(){
    while (true){
        loadLeaderboard();
        showWelcomeMessage();

        Grid *grid = createGrid();

        grid->playGame();
    }

    return 0;
}
