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
        string name, id;
};

Player::Player(string playerName, string playerID){
    name = playerName;
    id = playerID;
}

string Player::getName(){
    return name;
}

string Player::getID(){
    return id;
}

#endif // PLAYER_H_INCLUDED
