#include "GameMechs.h"
#include "MacUILib.h"

//Think about where to seed the RNG PPA3 design

GameMechs::GameMechs()
{
    input  = 0;
    score=0;

    exitFlag= false;
    loseFlag= false;
    boardSizeX= 20;
    boardSizeY= 10;

    foodPos.setObjPos(-1, -1, 'o'); //outside the board 
    
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    boardSizeX= boardX;
    boardSizeY= boardY;
    
    foodPos.setObjPos(-1, -1, 'o'); //outside the board 
}

// do you need a destructor?



bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

char GameMechs::getInput()
{
    if(MacUILib_hasChar())
    {
        input = MacUILib_getChar();
        
    } 
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

int GameMechs::getScore()
{
    return score;
}
void GameMechs::incrementScore()
{
    score++;
}
void GameMechs::generateFood(objPos blockOff)
{
    //Generate random x and y coord and make sure they are not border or blockOff pos
    //check x and y against 0 and boardSixeX/Y

    //remember in objPos class you have an isPosEqual() method instead of comparing elem-by-elem for your convenience
    int randX;
    int randY;
    
    do {
        srand(time(NULL));
        foodPos.x = randX;
        foodPos.y = randY;
    }  while (foodPos.isPosEqual(&blockOff) == true); 

}
void GameMechs::getFoodPos(const objPos &returnPos)
{
    returnPos = foodPos
    return returnPos;
}


void GameMechs::setExitTrue()
{
    exitFlag= true;
}

void GameMechs::setInput(char this_input)
{
    input= this_input;
}

void GameMechs::clearInput()
{
    input= ' ';
}


