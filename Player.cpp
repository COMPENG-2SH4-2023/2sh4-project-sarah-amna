#include "Player.h"
#include <iostream>
#include "MacUILib.h"
using namespace std;
Player::Player(GameMechs* thisGMRef, Food* myFood)
{
    mainGameMechsRef = thisGMRef;
    foodRef= myFood;
    myDir = STOP;


    // more actions to be included
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,
                      mainGameMechsRef->getBoardSizeY()/2, 
                      '*');

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);

    //For Debugging Purpose 
    // playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);
    // playerPosList->insertHead(tempPos);
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList; //no [] because we only have one position list
}

objPosArrayList* Player::getPlayerPos()//objPos &returnPos
{
    return playerPosList;
    // return the reference to the playerPos arrray list

}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic  
    char input= mainGameMechsRef->getInput();
    //char input= 'a';
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
    objPos currHead;
    playerPosList->getHeadElement(currHead);
    
    switch(myDir)
    {
        case LEFT:
            currHead.x -= 1;

            if(currHead.x <1)
                currHead.x = mainGameMechsRef->getBoardSizeX() - 2;
            break;
        
        case RIGHT:
            currHead.x += 1;

            if(currHead.x >mainGameMechsRef->getBoardSizeX() -2)
                currHead.x = 1;
            break;

        case UP:
            currHead.y -= 1;
            if(currHead.y <1) 
                currHead.y = mainGameMechsRef->getBoardSizeY()-2;
            break;
            
        case DOWN:
            currHead.y += 1;
            if(currHead.y >mainGameMechsRef->getBoardSizeY()-2)
                currHead.y = 1;
            break;
        case STOP:
        default:
            break;
    }
    
    //Collision Detection
    
    if(checkSelfCollision(currHead)==false)
    {
        if(checkFoodConsumption(currHead)==true)
        {
            increasePlayerLength(currHead);
            foodRef->generateFood(*playerPosList);
            mainGameMechsRef->incrementScore();
        }

        else
        {
            //new current head should be inserted to the head of the list
            //then, remove tailPla
            increasePlayerLength(currHead);
            playerPosList->removeTail();
        }

    }
    
}

bool Player::checkSelfCollision(objPos &currHead)
{
    objPos returnPos;

    for(int i=1; i<playerPosList->getSize(); i++)
    {
        playerPosList->getElement(returnPos,i);

        //returnPos.x==currHead.x && returnPos.y == currHead.y
        //returnPos.isPosEqual(currHead)
        if(currHead.isPosEqual(&returnPos))
        {
            MacUILib_printf("self colided");
            return true;
        }
    }
    return false;
}

bool Player::checkFoodConsumption(objPos &currHead)
{
    objPos tempFoodPos;
    foodRef->getFoodPos(tempFoodPos);

    //currHead.x == tempFoodPos.x && currHead.y == tempFoodPos.y
    if(currHead.isPosEqual(&tempFoodPos))
    {
        return true;
    }

    else
    {
        return false;
    }
}

void Player::increasePlayerLength(objPos &currHead)
{
    playerPosList->insertHead(currHead);
    
}

