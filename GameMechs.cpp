#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    input  = 0;
    exitFlag= false;
    loseFlag= false;
    boardSizeX= 20;
    boardSizeY= 10;
    score=0;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input  = NULL;
    exitFlag= false;
    loseFlag= false;
    boardSizeX= boardX;
    boardSizeY= boardY;
    score=0;
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


