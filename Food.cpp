#include "Food.h"

Food::Food()
{
    foodPos.setObjPos(5, 5, 'o'); //outside the board 
}
Food::~Food()
{
    //delete
}
void Food::generateFood(objPosArrayList &blockOff) //NEEDS TO BE UPDATED NOW
{
    //Blockoff should contain the player position
    //Generate random x and y coord and make sure they are not border or blockOff pos
    //check x and y against 0 and boardSixeX/Y
    
    //remember in objPos class you have an isPosEqual() method instead of comparing elem-by-elem for your convenience
    objPos returnPos;
    int i = 0;
    int size = blockOff.getSize();

    do {
        srand(time(NULL));
        foodPos.x = (rand() % 18)+1;  // Use boardsize somehow mainGameMechsRef->getBoardSizeX()-2;
        foodPos.y = (rand() % 8)+1;

        for (i = 0; i < size; i++)
        {
            blockOff.getElement(returnPos,i);
            if (returnPos.x == foodPos.x && returnPos.y == foodPos.y) //if there's overlap
            {
                break;
            }  
        }

    }  while (i != size);  
}

void Food::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}

