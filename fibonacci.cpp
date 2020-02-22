/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *    Adam Goff, Aaron Rook, Martin Melerio, Tanner Stratford
 **********************************************************************/

#include <iostream>
#include "fibonacci.h"   // for fibonacci
#include "list.h"        // for LIST
#include "wholeNumber.h"
using namespace std;
using namespace custom;


/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibonacci()
{
   // show the first serveral Fibonacci numbers
   int number;
   cout << "How many Fibonacci numbers would you like to see? ";
   cin  >> number;


   // your code to display the first <number> Fibonacci numbers
   int displayNumber = 0;
   int nextNumber = 1;
   int temp;

   for (int i = 0; i < number; i++)
   {
      temp = displayNumber;
      displayNumber = nextNumber;
      nextNumber = nextNumber + temp;
      cout << '\t' << displayNumber << endl;
   }

   // prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin  >> number;

   // your code to display the <number>th Fibonacci number
   wholeNumber wDisplayNumber = wholeNumber(0);
   wholeNumber wNextNumber = wholeNumber(1);
   wholeNumber wTemp = wholeNumber(0);

   for (int i = 0; i < number; i++)
   {
      wTemp = wDisplayNumber;
      wDisplayNumber = wNextNumber;
      wNextNumber += wTemp;
   }
   cout << '\t' << wDisplayNumber << endl;
}
