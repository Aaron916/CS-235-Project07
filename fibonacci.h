/***********************************************************************
 * Header:
 *    FIBONACCI
 * Summary:
 *    This will contain just the prototype for fibonacci(). You may
 *    want to put other class definitions here as well.
 * Author
*     Adam Goff, Aaron Rook, Martin Melerio, Tanner Stratford
 ************************************************************************/

#ifndef FIBONACCI_H
#define FIBONACCI_H
#include "list.h"

// the interactive fibonacci program
void fibonacci();
list<int> algorithmOne(int fibonacci) { // This can be Renamed, its just named for the sake of simplicity -AR//
    list<int> fList;;
    int current = 1; // these values will be used to prevent us from having to iterate through our data structure more than once //
    int minOne = 1;
    int minTwo = 0;
    
    for (int i = 0; i < fibonacci; i++) {
        if (fibonacci <= 0) // we cant have negative fibonacci numbers right? -AR//
        break;
        else // we only want to have to iterate through our list once per loop to make sure that its linear, be careful about this -AR//
        {
            fList.push_back(minTwo + minOne); // using this method we only have to iterate through our data structure in order to assign, and not to retrieve the values thus being linear in its performance //
            current = minTwo + minOne;
            minOne = current - 1;
            minTwo = current = 2;
        }
    }
    return fList;
}

int algorithmTwo(int number) { // this one finds the value of a specified fibonacci number
    int current = 1; // Just reusing code here
    int minOne = 1;
    int minTwo = 0;

    for (int i = 0; i < number; i++) {
        if (fibonacci <= 0) // we cant have negative fibonacci numbers right? -AR//
        break;
        else
        {
            current = minOne + minTwo;
            minOne = current - 1;
            minTwo = current = 2;
        }
    }

    return current;
}
#endif // FIBONACCI_H

