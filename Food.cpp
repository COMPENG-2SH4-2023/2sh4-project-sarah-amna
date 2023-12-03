#include "Food.h"
#include <iostream>
#include "MacUILib.h"
using namespace std;
Food::Food()
{
    objPos tempPos;
    foodBucket = new objPosArrayList();    
}
Food::~Food()
{
    delete foodBucket;
}
void Food::generateFood(objPosArrayList &blockOff) 
{
    int count = 0;
    

    objPos returnPos; 
    objPos foodPos;

    //5 unique coordinates for food
    int foodX[NUMFOOD] = {0};
    int foodY[NUMFOOD] = {0};

    //created a 18 x 8 2-D array to hold pairs of coordinates for the snake and the 5 food items
    int coords[18*8][2] = {0, 0}; //18*8 are the possible spaces on the board
    int i;
    int size = blockOff.getSize();
    int index = size;
    srand(time(NULL));

    for (i = 0; i < size; i++) // repeats for whole player
    {
        blockOff.getElement(returnPos,i);
        //block offs the player positions
        coords[i][0] = returnPos.x;
        coords[i][1] = returnPos.y;
    }

    while (count < NUMFOOD) //generate 5 unique food item coordinates
    {
        foodPos.x = (rand() % 18)+1;
        foodPos.y = (rand() % 8)+1;
        for(i = 0; i < index + NUMFOOD; i++)//checks generated values against the values in coords 2-D array
        {
        	if ((foodPos.x == coords[i][0]) && (foodPos.y == coords[i][1])) //Checks if the generated value is already taken by the player or another food item
        	{
                break;
            }
        }
        if (i == index + NUMFOOD) //didn't overlap with any of the existing food or player coords
        {
            coords[index][0] = foodPos.x;
            coords[index][1]= foodPos.y;
            foodX[count] = foodPos.x; //save the position in our FoodX array
            foodY[count] = foodPos.y;
            index++;
            count++;
        }
        
    }
    
    for (int i = 0; i < NUMFOOD; i ++)
    {
        //iterates through the food arrays and assigns values to the food object
        foodPos.x = foodX[i];
        foodPos.y = foodY[i];

        if (i ==3)
            foodPos.symbol = 'e';
        else if (i ==4)
            foodPos.symbol = 's';
        else 
            //assigns 3 normal foods each time
            foodPos.symbol = 'o';

        foodBucket->insertHead(foodPos);
    }
  
}

void Food::getFoodPos(objPos &returnPos, int i)
{
    foodBucket->getElement(returnPos, i);
}

