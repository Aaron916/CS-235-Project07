/***********************************************************************
* Header:
*    list
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
    list() : data(NULL), numCapacity(0) { clear(); }
    list(int newCapacity);
    list(const list <T>& rhs);
    ~list() { if (numCapacity != 0) delete[] data; }
    list<T>& operator = (const list <T>& rhs);

    // standard container interfaces
    int size() const { return iBack - iFront + 1; }
    bool empty() const { return size() == 0; }
    void clear() { iFront = 0; iBack = -1; }

    // list-specific interfaces
    void push_front(const T& t);
    void push_back(const T& t);
    void pop_front();
    void pop_back();
    T front() const;
    T back() const;

    // declaring nested Node struct
    struct Node;

    // the various iterator interfaces
    class iterator;
    iterator begin() { return iterator(data); }
    iterator end();

    class const_iterator;
    const_iterator cbegin() const { return const_iterator(data); }
    const_iterator cend() const;

private:
    // utility functions
    int iNormalize(int i) const
    {
        return (i >= 0) ?
            (i % numCapacity) :
            (numCapacity - ((-1 - i) % numCapacity) - 1);
    }
    int iFrontNormalize() const { return iNormalize(iFront); }
    int iBackNormalize() const { return iNormalize(iBack); }
    void resize(int newCapacity = 0, int option = 0);

    // member variables
    T* data; // dynamically allocated data for the list
    int numCapacity; // the size of the data data
    int iFront; // the index of the first item in the data
    int iBack; // the index of the last item in the data
};

/**************************************************
* NODE
* Code for our Node struct
*************************************************/
template <class T>
struct Node {
public:
    T data;
    Node<T>* pNext;
    Node<T>* pPrev;

    Node() : pNext(NULL), pPrev(NULL), data() {}

    // non-default. Initialize data as we create the node
    Node(const T& data) : pNext(NULL), pPrev(NULL), data(data) {} // changed the format of the constructors to be in line with what the instructor has. -AG
};

template <class T>
Node <T>* copy(Node<T>* pSource) // removed the const before the argument to test a fix for an error.
{
    Node<T>* pDestination = new Node<T>(pSource->data);
    Node<T>* pSrc = pSource;
    Node<T>* pDes = pDestination;

    for (pSrc = pSrc->pNext; pSrc != NULL; pSrc = pSrc->pNext) // Had to change the loop. It wasn't copying correctly. It was throwing bad_alloc exceptions. -AG
    {
        pDes = insert(pDes, pSrc->data, true);
    }
    return pDestination;
}

template <class T>
Node <T>* insert(Node<T>* pCurrent, const T& t, bool after = false)
{
    Node<T>* pNew = new Node<T>(t);

    if (pCurrent && after == false)
    {
        pNew->pNext = pCurrent;
        pNew->pPrev = pCurrent->pPrev;
        pCurrent->pPrev = pNew;
        if (pNew->pPrev)
        {
            pNew->pPrev->pNext = pNew;
        }
    }

    if (pCurrent && after == true)
    {
        //THIS ORDER MATTERS. If out of order, it doesn't get inserted correctly.
        pNew->pNext = pCurrent->pNext;
        pCurrent->pNext = pNew;
        pNew->pPrev = pCurrent;
        if (pNew->pNext)
        {
            pNew->pNext->pPrev = pNew;
        }
    }

    return pNew;
}

template <class T>
Node <T>* find(Node<T>* pHead, const T& t)
{
    // Changed the contents of this function to what the instructor posted in the discussion board. -AG
    // loop through the linked list
    for (Node <T>* p = pHead; p != NULL; p = p->pNext)
        if (t == p->data)
            return p;

    return NULL;
}

template <class T>
void freeData(Node<T>*& pHead)
{
    // Changed the contents of this function to what the instructor posted in the discussion board. -AG
    Node <T>* pNext;
    for (Node <T>* p = pHead; p; p = pNext)
    {
        pNext = p->pNext;
        delete p;
    }
    pHead = NULL;
}

template <class T>
Node <T>* remove(const Node<T>* pRemove)
{
    Node<T>* pReturn;

    if (NULL == pRemove)
    {
        std::cout << "Empty";
    }

    if (pRemove->pPrev)
    {
        pRemove->pPrev->pNext = pRemove->pNext;
    }
    if (pRemove->pNext)
    {
        pRemove->pNext->pPrev = pRemove->pPrev;
    }
    if (pRemove->pPrev)
    {
        pReturn = pRemove->pPrev;
    }
    else
    {
        pReturn = pRemove->pNext;
    }

    delete pRemove;
    return pReturn;
}

//changed this operator overload method to what the instructor shared in the discussion board.
template <class T>
std::ostream& operator << (std::ostream& out, const Node <T>* pHead)
{
    // paranoia
    if (pHead == NULL)
        return out;

    // display the data
    out << pHead->data;

    // if there is something after us, display it
    if (pHead->pNext)
        return out << ", " << pHead->pNext;
    else
        return out;
}

/******************************************************
* FIND SORTED
* Find the spot in a given linked list where a given Node
* is to go. We will return a pointer to the node preceeding
* one where the new node will exist in the list
* INPUT : a pointer to the head of the linked list
* the value we are inserting
* OUTPUT : a pointer to the node we will be inserting after
* COST : O(n)
********************************************************/
template <class T> // Added this function from the instructor's post in the discussion board.
Node <T>* findSorted(Node <T>* pHead,
    const T& t)
{
    // trivial case
    if (NULL == pHead || t < pHead->data)
        return NULL;

    // search for the node
    while (pHead->pNext && pHead->pNext->data < t)
        pHead = pHead->pNext;

    return pHead;
}

 /**************************************************
 * ARRAY CONSTANT ITERATOR
 * An iterator through array
 *************************************************/
template <class T>
class list <T> ::const_iterator
{
public:
    // constructors, destructors, and assignment operator
    const_iterator() : p(NULL) {              }
    const_iterator(T* p) : p(p) {              }
    const_iterator(const iterator& rhs) { *this = rhs; }
    const_iterator& operator = (const iterator& rhs)
    {
        this->p = rhs.p;
        return *this;
    }

    // equals, not equals operator
    bool operator != (const const_iterator& rhs) const { return rhs.p != this->p; }
    bool operator == (const const_iterator& rhs) const { return rhs.p == this->p; }

    // dereference operator
    T& operator * () { return *p; }
    const T& operator * () const { return *p; }

    // prefix increment
    const_iterator& operator ++ ()
    {
        p++;
        return *this;
    }

    // postfix increment
    const_iterator operator ++ (int postfix)
    {
        const_iterator tmp(*this);
        p++;
        return tmp;
    }

    //prefix decrement
    const_iterator& operator -- ()
    {
        p--;
        return *this;
    }

    //postfix decrement
    const_iterator operator -- (int postfix)
    {
        iterator tmp(*this);
        p--;
        return tmp;
    }

private:
    T* p;
};


/**************************************************
* ARRAY ITERATOR
* An iterator through array
*************************************************/
template <class T>
class list <T> ::iterator
{
public:
    // constructors, destructors, and assignment operator
    iterator() : p(NULL) {              }
    iterator(T* p) : p(p) {              }
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
    T& operator * () { return *p; }
    const T& operator * () const { return *p; }

    // prefix increment
    iterator& operator ++ ()
    {
        p++;
        return *this;
    }

    // postfix increment
    iterator operator ++ (int postfix)
    {
        iterator tmp(*this);
        p++;
        return tmp;
    }

    //prefix decrement
    iterator& operator -- ()
    {
        p--;
        return *this;
    }

    //postfix decrement
    iterator operator -- (int postfix)
    {
        iterator tmp(*this);
        p--;
        return tmp;
    }

private:
    T* p;
};


/*******************************************
* list :: Assignment
*******************************************/
template <class T>
list <T>& list <T> :: operator = (const list <T>& rhs)
{
    if (this->size() < rhs.size())
    {
        this->resize(rhs.size());
    }

    if (rhs.numCapacity != 0)
    {
        for (int i = (rhs.iFront % rhs.numCapacity); i <= (rhs.iBack % rhs.numCapacity); i++)
        {
            data[i] = rhs.data[i];
        }

        this->numCapacity = rhs.size();
        this->iBack = rhs.iBack;
        this->iFront = rhs.iFront;

        return *this;
    }
    else
    {
        return *this;
    }
}

/*******************************************
* list :: COPY CONSTRUCTOR
*******************************************/
template <class T>
list <T> ::list(const list <T>& rhs)
{
    // do nothing if there is nothing to do
    if (rhs.numCapacity == 0)
    {
        clear();
        numCapacity = 0;
        data = NULL;
        return;
    }

    // attempt to allocate
    try
    {
        data = new T[rhs.numCapacity];
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate buffer";
    }

    // copy over the capacity
    iBack = rhs.iBack;
    iFront = rhs.iFront;
    numCapacity = rhs.numCapacity;

    // copy the items over one at a time using the assignment operator
    for (int i = 0; i < numCapacity; i++)
        data[i] = rhs.data[i];
}

/**********************************************
* list : NON-DEFAULT CONSTRUCTOR
* Preallocate the list to "capacity"
**********************************************/
template <class T>
list <T> ::list(int numCapacity)
{
    if (numCapacity == 0)
    {
        clear();
        this->numCapacity = 0;
        this->data = NULL;
        return;
    }

    // attempt to allocate
    try
    {
        data = new T[numCapacity];
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate buffer";
    }

    clear();
    this->numCapacity = numCapacity;
}

/*******************************************
* list :: RESIZE
* Resizes the data as needed.
*******************************************/
template <class T>
void list <T> ::resize(int newCapacity, int option)
{
    bool test;
    int count = 0;
    T* tempData = new T[newCapacity];
    int iFront = 0;
    int iBack = 0;

    for (int i = 0; i < this->size(); i++)
    {
        if (data[i] == front())
            test = true;
        if (data[i] != front() && test == false)
            count++;
    }
    //Because of the wrap-around concept, this for loop basically counts
    //the offset. The count is then implemented into the next for loop
    //which makes it so the new data accounts for the places in the
    //old data and is able to assign the values from the old spots
    //into new spots in the data. 
    for (int i = 0; i < this->size(); i++)
    {
        iBack++;
        //   if (i + count < size())
        //     tempData[i] = data[i + count];
        //   else
        tempData[i] = data[(i + count) % size()];
    }
    switch (option)
    {
    case 1:
        iBack--;
        break;
    case 2:
        //do nothing
        break;
    }
    data = tempData;


    this->iFront = iFront;
    this->iBack = iBack;
    this->numCapacity = newCapacity;
}

template <class T>
void list <T> ::push_front(const T& t)
{
    bool test = false;
    if (this->numCapacity == 0)
    {
        this->resize(1);
        test = true;
    }
    else if (this->size() == this->numCapacity)
    {
        this->resize(this->numCapacity * 2, 1);
    }
    if (test == false)
        iFront--;
    data[iFrontNormalize()] = t;
    test = false;
}

template <class T>
void list <T> ::push_back(const T& t)
{
    bool test = false;
    if (this->numCapacity == 0)
    {
        this->resize(1);
        test = true;
    }
    else if (this->size() == this->numCapacity)
    {
        this->resize(this->numCapacity * 2, 2);
        test = true;
    }
    if (test == false)
        iBack++;
    data[iBackNormalize()] = t;
    test = false;
}

template <class T>
void list <T> ::pop_front()
{
    if (!empty())
        iFront++;
    return;
}

template <class T>
void list <T> ::pop_back()
{
    if (!empty())
        iBack--;
    return;
}

template <class T>
T list <T> ::front() const
{
    if (empty())
        throw "ERROR: unable to access data from an empty list";
    else
        return data[iFrontNormalize()];
}

template <class T>
T list <T> ::back() const
{
    if (empty())
        throw "ERROR: unable to access data from an empty list";
    else
        return data[iBackNormalize()];
}

}; // namespace custom

#endif //list_H
