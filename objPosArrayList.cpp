#include "objPosArrayList.h"

// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.

#include <iostream>
// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

using namespace std;
objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP]; //256 elements on the heap
    listSize = 0; //no valid element in the list upon startup
    arrayCapacity= ARRAY_MAX_CAP; //array capacity should be max
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList; //remember to use delete[] to call all the destructors of all instances in the array, otherwise only the first element will be deleted
}

int objPosArrayList::getSize()
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    //need error checking to check if listSize is at capacity
    if(listSize == arrayCapacity)
    {
        cout << "Array list is full." << endl;
        return;
    }

    for(int i = listSize ; i>0; i--)
    {
        aList[i].setObjPos(aList[i-1]); //this will shuffle all the elements towards the right
    }
    aList[0].setObjPos(thisPos);
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        cout << "Array list is full." << endl;
        return;
    }
    aList[listSize] = thisPos;
    listSize++;
}

void objPosArrayList::removeHead()
{
    if(listSize != 0)
    {
        for(int i = 0 ; i <listSize; i++)
        {
            aList[i].setObjPos(aList[i+1]); //this will shuffle all the elements towards the left
        }
        listSize--;
    }
}

void objPosArrayList::removeTail()
{
    if(listSize != 0)
        listSize--;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[listSize-1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.setObjPos(aList[index]);
}
