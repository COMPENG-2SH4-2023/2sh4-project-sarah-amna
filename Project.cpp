#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer;
objPosArrayList* playerPosList = new objPosArrayList;
Food* myFood; // Global Pointer to this class 

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
    myFood = new Food(); //allocate it on the heap
    myPlayer= new Player(myGM, myFood);
    
    
    //Think about when to generate food..
    myFood->generateFood(*playerPosList); 
    //Think about whether you want to set up a debug key to call the food generation routine for verification

    //remember, generateFood() requires player reference, you will need to provide it AFTER player 
    //obj is instantiated
}

void GetInput(void)
{
    if(myGM->getInput()=='E')
    {
        myGM->setExitTrue();
    }
    if (myGM->getInput() == 'f')
    {
        myFood->generateFood(*playerPosList);
    }
   
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    myGM->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    bool drawn;

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempBody;
    
    objPos tempFoodPos;
    
    

    //Because we are using the async input in MacUILib_printf instead of cout
    //objPos tempPos;
    //myPlayer.getPlayerPos(tempPos);
    MacUILib_printf("%c\n",myGM->getInput());
    int i, j;
    for(i=0; i<myGM->getBoardSizeY(); i++)
    {
        for(j=0; j<myGM->getBoardSizeX(); j++)
        {
            drawn = false;
            //iterate through every element in the list
            for (int k =0; k < playerBody->getSize(); k++)
            {
                playerBody->getElement(tempBody, k);
                if (tempBody.x == j && tempBody.y == i)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break; //breaks out the k for loop
                }
            }
            if (drawn) continue;
            //if player was drawn, don't draw anything below

            // if(i==tempPos.y&& j==tempPos.x) //check if equal to player position
            // {
            //     MacUILib_printf("%c", tempPos.symbol);
            // }
            for (int k = 0; k <5; k++)
            {
                myFood->getFoodPos(tempFoodPos, k);
                if (i ==tempFoodPos.y && j ==tempFoodPos.x)
                {
                    MacUILib_printf("%c", tempFoodPos.symbol);
                    drawn = true;
                    break;
                }
            }
            if (drawn) continue;

            if(i==0 || i==myGM->getBoardSizeY()-1 || j==0 || j==myGM->getBoardSizeX()-1)
            {
                MacUILib_printf("#"); 
            }
            
            else
            {
                MacUILib_printf(" ");
            }
            
        }
        MacUILib_printf("\n");
    }
    //MacUILib_printf("Player: <%d, %d> with %c\n", tempPos.x, tempPos.y, tempPos.symbol);
    MacUILib_printf("Food: <%d, %d> with %c\n", tempFoodPos.x, tempFoodPos.y, tempFoodPos.symbol);
    MacUILib_printf("Score: %d\n", myGM->getScore());
    MacUILib_printf("Player Positions:\n");
    for (int l =0; l<playerBody->getSize() ;l++)
    {
        playerBody->getElement(tempBody, l);
        MacUILib_printf("<%d, %d> ",tempBody.x ,tempBody.y);
    }

    if(myGM->getLoseFlagStatus() == true)
    {
        MacUILib_printf("\nYou lose!");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    //MacUILib_clearScreen();    
    MacUILib_uninit();

    //remove heap instances
    delete myGM;
    delete myPlayer;
    delete myFood;
}
