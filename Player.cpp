#include "Player.h"
#include <iostream>
#include "MacUILib.h"
using namespace std;
Player::Player(GameMechs* thisGMRef, Food* myFood)
{
    mainGameMechsRef = thisGMRef;
    foodRef= myFood;
    myDir = STOP;
    //myDir = UP;


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
    //char input= 0;
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
    MacUILib_printf("mydirupdates\n");

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

    MacUILib_printf("currmovementworks");
    //Collision Detection
    
    if(checkSelfCollision(currHead)==false)
    {
        if(checkFoodConsumption(currHead)==true)
        {
            if(playerPosList->getSize()==0)
            {
                //MacUILib_printf("you loose\n");
                mainGameMechsRef->setLoseFlag();
                mainGameMechsRef->setExitTrue();
            }
            MacUILib_printf("food gen");
            foodRef->generateFood(*playerPosList);
        }

        else
        {
            //new current head should be inserted to the head of the list
            //then, remove tailPla
            //foodRef->generateFood(*playerPosList);
            MacUILib_printf("this runs");
            increasePlayerLength(currHead);
            playerPosList->removeTail();
        }

    }
    else
    {
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();

    }
    MacUILib_printf("moveplayerupdates");
   
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
            return true;
        }
    }
    return false;
}

bool Player::checkFoodConsumption(objPos &currHead)
{
    objPos tempFoodPos;
    int i, score;
    for (i =0; i < 5; i++)
    {
        foodRef->getFoodPos(tempFoodPos, i);
        if(currHead.isPosEqual(&tempFoodPos))
        {
            MacUILib_printf("food this runs");
            if(tempFoodPos.getSymbol()=='o')
            {
                MacUILib_printf("o this runs");
                score=1;
                mainGameMechsRef->incrementScore(score);
                increasePlayerLength(currHead);
            }

            else if(tempFoodPos.getSymbol()=='e')
            {
                MacUILib_printf("e this runs");
                score=10;
                mainGameMechsRef->incrementScore(score);
                increasePlayerLength(currHead);
                //increasePlayerLength(currHead);
            }
            else
            {
                MacUILib_printf("s this runs");
                score=5;
                mainGameMechsRef->incrementScore(score);
                playerPosList->removeTail();
                //playerPosList->removeTail();
            }
            return true;
        }
    }
    return false;

    //currHead.x == tempFoodPos.x && currHead.y == tempFoodPos.y
}

void Player::increasePlayerLength(objPos &currHead)
{
    playerPosList->insertHead(currHead);
    MacUILib_printf("head inserted");
    
}

