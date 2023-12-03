#ifndef Food_H
#define Food_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#define NUMFOOD 5


class Food 
{
    private:
        //objPos foodPos;
        objPosArrayList *foodBucket;
        
    public:
        Food();// Constructor
        ~Food();// Destructor
        void generateFood(objPosArrayList &blockOff);
        void getFoodPos(objPos &returnPos, int i);  //

        // Need to accept the player body array list
        // go thru each array list element to make sure they are all
        // blocked off from random food generation 

};

#endif
