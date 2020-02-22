#ifndef WHOLENUMBER_H
#define WHOLENUMBER_H
#include <iostream>
#include <iomanip>
#include "list.h"

namespace custom
{
/***********************************************
* WHOLE NUMBER CLASS
************************************************/
class wholeNumber
{
public:
   wholeNumber() // Default Constructor
   {
      nbrs.push_front(0);
   }

   wholeNumber(unsigned int nbr); // Non-default Contructor

   wholeNumber & operator += (wholeNumber& rhs);
   wholeNumber & operator =  (wholeNumber& rhs);

   friend std::ostream & operator << (std::ostream & o, wholeNumber & rhs) // To display the numbers
   {
      list <unsigned int>::iterator it;
      for (it = rhs.nbrs.begin(); it != rhs.nbrs.end(); ++it)
      {
         if (it == rhs.nbrs.begin())
            o << *it;
         else
            o << ',' << std::setfill('0') << std::setw(3) << *it;
      }

      return o;
   }

   list<unsigned int> nbrs; // List of smaller numbers used to store a bigger one.
};


}

#endif //WHOLENUMBER_H
