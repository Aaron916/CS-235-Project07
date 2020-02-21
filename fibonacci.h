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
#include list.h

// the interactive fibonacci program
void fibonacci();
list<int> algorithmOne(int fibonacci) { // This can be Renamed, its just named for the sake of simplicity -AR//
    list<int> fList = new list<int>();
    for (i = 0; i < fibonacci; i++) {
        if (fibonacci <= 0) // we cant have negative fibonacci numbers right? //
        break;
        else if (i < 2) // our first two fibonacci numbers are 1 //
        {
            fList.pushback(1);
        }
        else // we only want to have to iterate through our list once per loop to make sure that its linear, be careful about this //
        {
            
        }
    }
    return fList;
}
#endif // FIBONACCI_H

