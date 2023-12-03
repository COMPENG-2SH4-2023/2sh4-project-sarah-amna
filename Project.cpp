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
Food* myFood; 
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

    myGM= new GameMechs(20,10); 
    myFood = new Food(); 
    myPlayer= new Player(myGM, myFood);

    myFood->generateFood(*playerPosList); //starting food items
}

void GetInput(void)
{
    if(myGM->getInput()=='!') //exit key
    {
        myGM->setExitTrue();
    }
    else if (myGM->getInput() == 'f') //debugging key for generating random food items
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
    
    int i, j;
    for(i=0; i<myGM->getBoardSizeY(); i++)
    {
        for(j=0; j<myGM->getBoardSizeX(); j++)
        {
            drawn = false;
            //prints the snake
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
            if (drawn) continue; // if snake is drawn, go to next iteration in the j for loop
 
            //draws food
            for (int k = 0; k <NUMFOOD; k++)
            {
                myFood->getFoodPos(tempFoodPos, k);
                if (i ==tempFoodPos.y && j ==tempFoodPos.x)
                {
                    MacUILib_printf("%c", tempFoodPos.symbol);
                    drawn = true;
                    break;
                }
            }
            if (drawn) continue; // if food is drawn, go to next iteration in the j for loop
            
            //draws game boundaries
            else if(i==0 || i==myGM->getBoardSizeY()-1 || j==0 || j==myGM->getBoardSizeX()-1)
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
    //Display Messages
    MacUILib_printf("Sarah and Amna's Snake Game\n");
    MacUILib_printf("Collect 'o' to score 1 point.\nCollect 'e' to score 10 points and grow the snake by 2.\nCollect 's' to score 5 points and shrink the snake length by 2.\n");
    MacUILib_printf("Enter '!' to exit.\n");
    MacUILib_printf("\n");
    MacUILib_printf("~ Score 200 points to win ~\n");
    MacUILib_printf("Score: %d\n", myGM->getScore());

    if(myGM->getLoseFlagStatus() == true)
    {
        MacUILib_printf("\nYou lose!");
    }
    else if(myGM->getWinFlagStatus() == true)
    {
       MacUILib_printf("\nYou win!"); 
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
