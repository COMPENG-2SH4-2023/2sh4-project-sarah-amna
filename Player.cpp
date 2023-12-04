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
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList; //no [] because we only have one position list
}

objPosArrayList* Player::getPlayerPos()//objPos &returnPos
{
    return playerPosList;
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
            if(playerPosList->getSize()==0) //if player shrinks
            {
                mainGameMechsRef->setLoseFlag();
                mainGameMechsRef->setExitTrue();
            }
            else if (mainGameMechsRef->getScore()>= 100)
            {
                mainGameMechsRef->setWinFlag();
                mainGameMechsRef->setExitTrue();
            }
            foodRef->generateFood(*playerPosList);
        }
        else
        {
            //new current head should be inserted to the head of the list
            //then, remove tail
            increasePlayerLength(currHead);
            playerPosList->removeTail();
        }

    }
    else //self collided is true
    {
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    }   
}

bool Player::checkSelfCollision(objPos &currHead)
{
    objPos returnPos;

    for(int i=1; i<playerPosList->getSize(); i++) //checks the head of the snake against the rest of the body (i starts at 1)
    {
        playerPosList->getElement(returnPos,i);

        if(currHead.isPosEqual(&returnPos))
        {
            return true;
        }
    }
    return false;
}

bool Player::checkFoodConsumption(objPos &currHead)
{
    objPos tempFoodPos;
    int i, score;
    for (i =0; i < NUMFOOD; i++) //iterates through all the 5 food items and checks for collision with the snake head
    {
        foodRef->getFoodPos(tempFoodPos, i);

        if(currHead.isPosEqual(&tempFoodPos))
        {
            if(tempFoodPos.getSymbol()=='o') //normal food
            {
                score=1;
                mainGameMechsRef->incrementScore(score);
                increasePlayerLength(currHead);
            }
            else if(tempFoodPos.getSymbol()=='e') //energy boost
            {
                score=10;
                mainGameMechsRef->incrementScore(score);
                increasePlayerLength(currHead); 
                increasePlayerLength(currHead);
            }
            else //shrink snake
            {
                score=5;
                mainGameMechsRef->incrementScore(score);
                playerPosList->removeTail();
                playerPosList->removeTail();
            }
            return true;
        }
    }
    return false;
}

void Player::increasePlayerLength(objPos &currHead)
{
    playerPosList->insertHead(currHead);    
}

