#include "Food.h"

Food::Food()
{
    objPos tempPos;
    foodBucket = new objPosArrayList();
    
    //tempPos.setObjPos(5,5,'o');
    //foodBucket->insertHead(tempPos);

    //foodPos.setObjPos(5, 5, 'o'); //outside the board 
}
Food::~Food()
{
    //delete
    delete foodBucket;
}
void Food::generateFood(objPosArrayList &blockOff) //NEEDS TO BE UPDATED NOW
{
    //Blockoff should contain the player position
    //Generate random x and y coord and make sure they are not border or blockOff pos
    //check x and y against 0 and boardSixeX/Y
    
    //remember in objPos class you have an isPosEqual() method instead of comparing elem-by-elem for your convenience
    int xCount=0;
    int yCount=0;

    objPos returnPos; //stores the x and y of the player
    objPos foodPos;
    foodPos.symbol = 'o';

    int foodX[5] = {0};
    int foodY[5] = {0};

    //5 unique coordinates for food
    int xVec[18] = {0}; //we avoid the borders
    int yVec[8] = {0}; 

    int i = 0;
    int size = blockOff.getSize();
    srand(time(NULL));

    for (i = 0; i < size; i++) // repeats for whole player
    {
        blockOff.getElement(returnPos,i);
        xVec[(returnPos.x)-1] = 1;//
        yVec[(returnPos.y)-1] =1;
    }

    //generate 5 x
    while (xCount < 5)
    {
        foodPos.x = (rand() % 18)+1;
        if (xVec[foodPos.x] == 0 )
        {
            xVec[foodPos.x] = 1;
            foodX[xCount] = foodPos.x;
            xCount++;
        }
    }

    //generate 5 y
    while (yCount < 5)
    {
        foodPos.y = (rand() % 8)+1;
        if (yVec[foodPos.y] == 0 )
        {
            yVec[foodPos.y] = 1;
            foodY[yCount] = foodPos.y;
            yCount++;
        }

    }
    
    for (int i = 0 ; i < 5; i ++)
    {
        foodPos.x = foodX[i];
        foodPos.y = foodY[i];
        if (i ==3)
            foodPos.symbol = 'e';
        else if (i ==4)
            foodPos.symbol = 's';
        else 
            foodPos.symbol = 'o';
        foodBucket->insertHead(foodPos);
    }


    
}

void Food::getFoodPos(objPos &returnPos, int i)
{
    //return a list
    foodBucket->getElement(returnPos, i);
    
}

