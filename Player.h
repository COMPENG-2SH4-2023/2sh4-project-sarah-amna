#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef, Food* myFood);
        ~Player();

        objPosArrayList* getPlayerPos(); // Upgrade this in iteration 3. objPos &returnPos
        void updatePlayerDir();
        void movePlayer();
        //Need more actions in here:
        // after inserting the head but before removing the tail 
        // check if new head position collides with food 
        //- if yes, increment the score in GM, generate new food and 
        // do not remove tail
        //otherwise, remove tail and move on.
        bool checkFoodConsumption();
        void increasePlayerLength();

        //Lastly, add self-collsion check
        //- if self-collided
        //set loseFlag and exitFlag both to true (thru GM)
        // this will break the program loop and end the game
        bool checkSelfCollision();

        //if ending, you need to differentiate the end game state
        // LOST - display LOST msg
        //otherwise, display ENDGAME msg only


    private:
        objPosArrayList *playerPosList;   // Upgraded this in iteration 3.       
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
        Food* foodRef;
};

#endif