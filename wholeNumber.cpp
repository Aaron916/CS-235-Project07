#include "wholeNumber.h"
#include <iostream>
#include "fibonacci.h"   // for fibonacci
#include "list.h"        // for LIST
using namespace std;

// Non-default constructor
wholeNumber :: wholeNumber(unsigned int nbr) {
   nbrs.push_front(0);
   list <unsigned int>::iterator it = nbrs.rbegin();
   unsigned int total = *it + nbr;

   while (total > 0) // Divide the number and store the smaller numbers into the list
   {
      *it = total % 1000;
      total = total / 1000;

      if (total > 0)
      {
         if (--it == nbrs.rend())
         {
            this->nbrs.push_front(0);
            it = nbrs.begin();
         }
         total += *it;
      }
   }
}


//Assignment operator
wholeNumber & wholeNumber :: operator = (wholeNumber& rhs)
{
   this->nbrs = rhs.nbrs;
   return *this;
}

// Add rhs to lhs operator
wholeNumber & wholeNumber :: operator += (wholeNumber& rhs)
{
   list <unsigned int>::iterator rIt;
   list <unsigned int>::iterator lIt;
   rIt = rhs.nbrs.rbegin();
   lIt = this->nbrs.rbegin();

   // nothing to add
   if (rIt == NULL)
      return *this;

   // Check for NULL.
   if (lIt == NULL)
   {
      this->nbrs.push_front(0);
      lIt = this->nbrs.begin();
   }

   unsigned int total = *lIt + *rIt;
   while (total > 0 || rIt != rhs.nbrs.rend())
   {
      *lIt = total % 1000;
      total = total / 1000;

      // Check if there are more rhs numbers
      if (rIt != rhs.nbrs.rend() && --rIt != rhs.nbrs.rend())
         total += *rIt;

      // Check for carry over numbers
      if (rIt != rhs.nbrs.rend() || total > 0)
      {
         // Check if the next iterator is null
         if (--lIt == this->nbrs.rend())
         {
            this->nbrs.push_front(0);
            lIt = this->nbrs.begin();
         }
         total += *lIt;
      }
   }

   return *this;
}
