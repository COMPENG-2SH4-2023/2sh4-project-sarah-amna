#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
    // return the reference to the playerPos arrray list

}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic  
    char input= mainGameMechsRef->getInput();
    switch(input)
    {
        case 'a':
        case 'A':
            if(myDir != RIGHT)
            {
                myDir = LEFT;
            }
            break;

        case 'd':
        case 'D':
            if(myDir != LEFT)
            {
                myDir = RIGHT;

            }
            break;
        
        case 'w':
        case 'W':
            if(myDir != DOWN)
            {
                myDir = UP;
            }
            break;
            

        case 's':
        case 'S':
            if(myDir != UP)
            {
                myDir = DOWN;
            }
            break;
    }

}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    switch(myDir)
    {
        case LEFT:
            playerPos.x -= 1;

            if(playerPos.x <1)
                playerPos.x = mainGameMechsRef->getBoardSizeX() - 2;
            break;
        
        case RIGHT:
            playerPos.x += 1;

            if(playerPos.x >mainGameMechsRef->getBoardSizeX() -2)
                playerPos.x = 1;
            break;

        case UP:
            playerPos.y -= 1;
            if(playerPos.y <1)
                playerPos.y = mainGameMechsRef->getBoardSizeY()-2;
            break;
            
        case DOWN:
            playerPos.y += 1;
            if(playerPos.y >mainGameMechsRef->getBoardSizeY()-2)
                playerPos.y = 1;
            break;
    }
}

