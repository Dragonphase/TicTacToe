#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

using namespace std;

class Player
{
    public:
        Player(string playerName, string playerID);
        string getName();
        string getID();
        ~Player();
    private:
        string Name, ID;
};

Player::Player(string playerName, string playerID){
    Name = playerName;
    ID = playerID;
}

string Player::getName(){
    return Name;
}

string Player::getID(){
    return ID;
}

#endif // PLAYER_H_INCLUDED
