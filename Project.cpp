#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"


using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer;
objPos myPos;

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }
    CleanUp();
}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM= new GameMechs(20,10); // x-cols, y-rows
    myPlayer= new Player(myGM);

    //Think about when to generate food..

    //Think about whether you want to set up a debug key to call the food generation routine for verification

    //remember, generateFood() requires player reference, you will need to provide it AFTER player 
    //obj is instantiated

}

void GetInput(void)
{
    if(myGM->getInput()=='!')
    {
        myGM->setExitTrue();
    }
   
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 
    objPos tempPos;
    myPlayer->getPlayerPos(tempPos);
    //MacUILib_printf("Object: <%d, %d> with %c\n", myPos.x, myPos.y, myPos.symbol);
    //Because we are using the async input in MacUILib_printf instead of cout
    //objPos tempPos;
    //myPlayer.getPlayerPos(tempPos);
    MacUILib_printf("%c\n",myGM->getInput());
    int i, j;
    for(i=0; i<myGM->getBoardSizeY(); i++)
    {
        for(j=0; j<myGM->getBoardSizeX(); j++)
        {
            if(i==tempPos.y&& j==tempPos.x) //check if equal to player position
            {
                MacUILib_printf("%c", tempPos.symbol);
            }

            else
            {
                if(i==0 || i==myGM->getBoardSizeY()-1 || j==0 || j==myGM->getBoardSizeX()-1)
                {
                   MacUILib_printf("#"); 
                }
                
                else
                {
                    MacUILib_printf(" ");
                }
            }
        }
        MacUILib_printf("\n");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    MacUILib_uninit();
}
