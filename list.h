/***********************************************************************
* Header:
*    list.h
* Summary:
*    This file declares and implements the methods of the list class.
* Author:
*    Adam Goff, Aaron Rook, Martin Melerio, Tanner Stratford
************************************************************************/

#ifndef LIST_H
#define LIST_H
#include <cassert>
#include <iostream>

namespace custom
{
/************************************************
* list
* A class that holds stuff
***********************************************/
template <class T>
class list
{
public:
    // constructors and destructors
    list() : numElements(0), pHead(NULL), pTail(NULL) {}
    list(const list <T>& rhs) :
        numElements(0), pHead(NULL), pTail(NULL) {
        *this = rhs;
    }
    ~list() { clear(); }
    list<T>& operator = (const list <T>& rhs);

    // standard container interfaces
    int size() const { return numElements; }
    bool empty() const { return size() == NULL; }
    void clear();

    // the various iterator interfaces
    class iterator;
    iterator begin() { return iterator(pHead); }
    iterator end() { return iterator(NULL); }

    class const_iterator;
    const_iterator cbegin() const { return const_iterator(pHead); }
    const_iterator cend() const { return const_iterator(NULL); }

    class reverse_iterator;
    reverse_iterator rbegin() { return reverse_iterator(pTail); }
    reverse_iterator rend() { return reverse_iterator(NULL); }

    class const_reverse_iterator;
    const_reverse_iterator crbegin()const { return const_reverse_iterator(pTail); }
    const_reverse_iterator crend() const { return const_reverse_iterator(NULL); }

    // list-specific interfaces
    void push_front(const T& t);
    void push_back(const T& t);
    //void pop_front();
    //void pop_back();
    iterator erase(iterator it);
    iterator find(const T& t);
    iterator insert(iterator& it, const T& t);
    T & front() const;
    T & back() const;

private:
    // declaring nested Node class
    class Node;

    // member variables
    Node* pHead;
    Node* pTail;
    int numElements;
};

/**************************************************
* NODE
* Code for our Node struct
*************************************************/
template <class T>
class list<T>::Node {
public:
    T data; // user data
    Node* pNext; // pointer to next node
    Node* pPrev; // pointer to previous node

    // constructors
    Node() : pNext(NULL), pPrev(NULL), data() {}
    Node(const T& data) : pNext(NULL), pPrev(NULL), data(data) {}
};

/**************************************************
* LIST iterator
*************************************************/
template <class T>
class list <T> ::iterator
{
public:
    // constructors, destructors, and assignment operator
    iterator() : p(NULL) {              }
    iterator(Node * it) : p(it) {              }
    iterator(const reverse_iterator& it) : p(it.p) { }
    iterator(const iterator& rhs) { *this = rhs; }
    iterator& operator = (const iterator& rhs)
    {
        this->p = rhs.p;
        return *this;
    }

    // equals, not equals operator
    bool operator != (const iterator& rhs) const { return rhs.p != this->p; }
    bool operator == (const iterator& rhs) const { return rhs.p == this->p; }

    // dereference operator
    T& operator * ()
    {
        if (p)
            return p->data;
        else
            throw "ERROR: Trying to dereference a NULL pointer";
    }

    // prefix increment
    iterator& operator ++ ()
    {
        if (p)
            p = p->pNext;
        return *this;
    }

    // postfix increment
    iterator operator ++ (int postfix)
    {
        iterator tmp(*this);
        if (p)
            p = p->pNext;
        return tmp;
    }

    //prefix decrement
    iterator& operator -- ()
    {
        if (p)
            p = p->pPrev;
        return *this;
    }

    //postfix decrement
    iterator operator -- (int postfix)
    {
        iterator tmp(*this);
        if (p)
            p = p->pPrev;
        return tmp;
    }

    T getValue()
    {
        return p->data;
    }

    //friends who need to access p
    friend iterator list <T> ::insert(iterator& it, const T& data);
    friend iterator list <T> ::erase(iterator it);



    typename list <T> ::Node* p;
};

 /**************************************************
 * LIST const_iterator
 *************************************************/
template <class T>
class list <T> ::const_iterator
{
public:
    // constructors, destructors, and assignment operator
    const_iterator() : p(NULL) {              }
    const_iterator(Node* it) : p(it) {              }
    const_iterator(const const_iterator& rhs) { *this = rhs; }
    const_iterator& operator = (const const_iterator& rhs) {}

    // equals, not equals operator
    bool operator != (const const_iterator& rhs) const { return rhs.p != this->p; }
    bool operator == (const const_iterator& rhs) const { return rhs.p == this->p; }

    // dereference operator
    T& operator * ()
    {
        if (p)
            return p->data;
        else
            throw "ERROR: Trying to dereference a NULL pointer";
    }

    // prefix increment
    const_iterator& operator ++ ()
    {
        if (p)
            p = p->pNext;
        return *this;
    }

    // postfix increment
    const_iterator operator ++ (int postfix)
    {
        iterator tmp(*this);
        if (p)
            p = p->pNext;
        return tmp;
    }

    //prefix decrement
    const_iterator& operator -- ()
    {
        if (p)
            p = p->pPrev;
        return *this;
    }

    //postfix decrement
    const_iterator operator -- (int postfix)
    {
        iterator tmp(*this);
        if (p)
            p = p->pPrev;
        return tmp;
    }


    list <T> ::Node* p;
};

/**************************************************
* LIST : reverse iterator
*************************************************/
template <class T>
class list <T> ::reverse_iterator
{
public:
    // constructors, destructors, and assignment operator
    reverse_iterator() : p(NULL) {              }
    reverse_iterator(Node* it) : p(it) {              }
    reverse_iterator(const iterator& it) : p(it.p) { }
    reverse_iterator(const reverse_iterator& rhs) { *this = rhs; }
    reverse_iterator& operator = (const reverse_iterator& rhs)
    {
        this->p = rhs.p;
        return *this;
    }

    // equals, not equals operator
    bool operator != (const iterator& rhs) const { return rhs.p != this->p; }
    bool operator == (const iterator& rhs) const { return rhs.p == this->p; }

    // dereference operator
    T& operator * ()
    {
        if (p)
            return p->data;
        else
            throw "ERROR: Trying to dereference a NULL pointer";
    }

    // prefix increment
    reverse_iterator& operator ++ ()
    {
        if (p)
            p = p->pPrev;
        return *this;
    }

    // postfix increment
    reverse_iterator operator ++ (int postfix)
    {
        iterator tmp(*this);
        if (p)
            p = p->pPrev;
        return tmp;
    }

    //prefix decrement
    reverse_iterator& operator -- ()
    {
        if (p)
            p = p->pNext;
        return *this;
    }

    //postfix decrement
    reverse_iterator operator -- (int postfix)
    {
        iterator tmp(*this);
        if (p)
            p = p->pNExt;
        return tmp;
    }

    T getValue()
    {
        return p->data;
    }


    typename list <T> ::Node* p;
};

/*******************************************
* list :: Assignment
*******************************************/
template <class T>
list <T>& list <T> :: operator = (const list <T>& rhs)
{
    // clear the elements in this
    this->clear();

    Node* source = rhs.pHead;
    while (source)
    {
        push_back(source->data);
        source = source->pNext;
    }
    return *this;
}

/*******************************************
* list :: Clear
*******************************************/
template <class T>
void list <T>::clear()
{
    // loop through list and delete everything
    list <T> ::Node* pNext;
    for (list <T> ::Node* p = pHead; p; p = pNext)
    {
        pNext = p->pNext;
        delete p;
    }

    //set member variables to a cleared state
    pHead = pTail = NULL;
    numElements = 0;
}

/*******************************************
* list :: push_front
*******************************************/
template <class T>
void list <T> ::push_front(const T& t)
{
    try
    {
        // create the node
        list <T> ::Node* pNew = new list <T> ::Node(t);

        //empty case
        if (pHead == NULL)
            pHead = pTail = pNew;
        else
        {

            // point to old head
            pNew->pNext = pHead;

            // point old head to new node
            pHead->pPrev = pNew;

            // this is the new head
            pHead = pNew;
        }
        numElements++;
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: unable to allocate a new node for a list";
    }
}
/*******************************************
* list :: push_back
*******************************************/
template <class T>
void list <T> ::push_back(const T& t)
{
    try
    {
        // create the node
        list <T> ::Node* pNew = new list <T> ::Node(t);

        // point it to the old tail
        pNew->pPrev = pTail;

        // now point tail to the new guy
        if (pTail)
            pTail->pNext = pNew;

        // // finally, this is the new tail
        pTail = pNew;

        // if previously empty this is new head as well
        if (pHead == NULL)
            pHead = pNew;

        numElements++;

    }
    catch (std::bad_alloc)
    {
        throw "ERROR: unable to allocate a new node for a list";
    }
}

//template <class T>
//void list <T> ::pop_front()
//{
//    if (!empty())
//        iFront++;
//    return;
//}
//
//template <class T>
//void list <T> ::pop_back()
//{
//    if (!empty())
//        iBack--;
//    return;
//}

/*******************************************
* list :: front
*******************************************/
template <class T>
T &list <T> ::front() const
{
    if (empty())
        throw "ERROR: unable to access data from an empty list";
    else
        return pHead->data;
}

/*******************************************
* list :: back
*******************************************/
template <class T>
T &list <T> ::back() const
{
    if (empty())
        throw "ERROR: unable to access data from an empty list";
    else
        return pTail->data;
}

/******************************************
 * list :: find
 ******************************************/
template <class T>
typename list <T> ::iterator list <T> ::find(const T& t)
{
    for (iterator it = begin(); it != end(); ++it)
        if (*it == t)
            return it;
    return end();
}

/******************************************
* list :: remove
******************************************/
template <class T>
typename list <T> ::iterator list <T> ::erase(list <T> ::iterator it)
{
    list <T> ::iterator itNext = end();

    // invalid iterator case
    if (it == end())
        return it;

    // fixup everything after the current location
    if (it.p->pNext) // not the last element
    {
        it.p->pNext->pPrev = it.p->pPrev;
        itNext = it.p->pNext;
    }
    else // are the last element
        pTail = pTail->pPrev;

    // fixup everything before the current location
    if (it.p->pPrev) // not the first element
        it.p->pPrev->pNext = it.p->pNext;
    else
        pHead = pHead->pNext;

    // delete self and return
    delete it.p;
    numElements--;
    return itNext;
}

/******************************************
 * list :: insert
 ******************************************/
template <class T>
typename list <T> ::iterator list <T> ::insert(list <T> ::iterator& it,
    const T& data)
{
    // empty list case
    if (empty())
    {
        pHead = pTail = new list <T> ::Node(data);
        return begin();
    }

    try
    {
        list <T> ::Node* pNew = new list <T> ::Node(data);

        // end of list case
        if (it == end())
        {
            // update pTail as appropriate
            pTail->pNext = pNew;
            // update the iterator
            it = pNew;
        }
        // otherwise we have a valid iterator
        else
        {
            // set pNext and pPrev
            pNew->pPrev = it.p->pPrev;
            pNew->pNext = it.p;
            // update who pNext and pPrev point to
            pNew->pNext->pPrev = pNew;
            if (pNew->pPrev)
                pNew->pPrev->pNext = pNew;
            else
                pHead = pNew;
            if (pNew->pNext)
                pNew->pNext->pPrev = pNew;
            else
                pTail = pNew;

            it = pNew;
        }
        numElements++;
    }
    catch (...)
    {
        throw "ERROR: unable to allocate a new node for a list";
    }

    return it;
}


}; // namespace custom

#endif //list_H
