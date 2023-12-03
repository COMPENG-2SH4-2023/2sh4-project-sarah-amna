#include "Food.h"
#include <iostream>
#include "MacUILib.h"
using namespace std;
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
    int count = 0;

    objPos returnPos; //stores the x and y of the player
    objPos foodPos;
    foodPos.symbol = 'o';

    int foodX[5] = {0};
    int foodY[5] = {0};

    //5 unique coordinates for food
    //created a 18 x 8 twoD array to hold pairs of coordinates
    int coords[18*8][2] = {0, 0}; 
    int i;
    
    int size = blockOff.getSize();
    int index = size;
    srand(time(NULL));

    for (i = 0; i < size; i++) // repeats for whole player
    {
        blockOff.getElement(returnPos,i);
        coords[i][0] = returnPos.x;
        coords[i][1] = returnPos.y;
    }
    //first size number of elements in the array contain the snake body positions
    //generate 5 x
    while (count < 5)
    {
        foodPos.x = (rand() % 18)+1;
        foodPos.y = (rand() % 8)+1;
        for(i = 0; i < index + 5; i++)//checks generated values against the values in coords
        {
        	if ((foodPos.x == coords[i][0]) && (foodPos.y == coords[i][1])) //Checks if the generated value is already taken 
        	{
                break;
            }
        }
        if (i == index + 5) //didn't overlap with any of the coords
        {
            coords[index][0] = foodPos.x;
            coords[index][1]= foodPos.y;
            foodX[count] = foodPos.x; //save the position in our FoodX array
            foodY[count] = foodPos.y;
            index++;
            count++;
        }
        
    }
    
    for (int i = 0; i < 5; i ++)
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

