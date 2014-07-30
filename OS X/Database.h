//
//  Header.h
//  Cpp_Revision
//

/*

Copyright (c) 2014 Luke Marcus Biagio Testa
All rights reserved.

Redistribution and use in source and binary forms are permitted
provided that the above copyright notice and this paragraph are
duplicated in all such forms and that any documentation,
advertising materials, and other materials related to such
distribution and use acknowledge that the software was developed
by the Luke Marcus Biagio Testa. The name of the
Luke Marcus Biagio Testa may not be used to endorse or promote products derived
from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * 
 */

#include <iostream>

#ifndef Cpp_Revision_Header_h
#define Cpp_Revision_Header_h

#ifndef DATABASE_H
#define DATABASE_H

    namespace Database
    {
        
    // Default Definition of Queue Template
    template <class DataC> class Queue
    {
        public:
                    // Constructors
                    Queue();
                    Queue(const DataC& Element);
        
                    // Destructor
                    virtual ~Queue();
        
                    // Queue Operations
                    void push(const DataC& Element);
                    bool inList(const DataC& Element);
                    DataC* pop();
        
                    // Debug Operations
                    void printList();

        private:
                    // Override Copy Semantics as Uninheritable Abstract Functions
                    Queue(const Queue& Q);
                    Queue& operator=(const Queue& Q);
        
                    // Queue Operations
                    Queue* lastElement();
        
                    // Members
                    DataC* ptrData;
                    Queue* ptrNext;
    };
        
    };

#endif

#endif





//---------------- Definition of Queue Members ----------------------


// ----------------------- Constructors --------------------

// Create empty list
template <class DataC> Database::Queue<DataC>::Queue() : ptrData(NULL), ptrNext(NULL) {};


// Create list with single element
template <class DataC> Database::Queue<DataC>::Queue(const DataC& Element) : ptrNext(NULL)
{ ptrData = new DataC(Element); };



// ----------------------- Destructors --------------------

template <class DataC> Database::Queue<DataC>::~Queue() { delete ptrData, delete ptrNext; };



// ----------------------- Public Members ----------------------

// Append to Last Element using Call-by-Reference
template <class DataC> void Database::Queue<DataC>::push(const DataC& Element)
{
    
    // Get last Live Element in Queue
    Queue* ptr = lastElement();
    
    // empty list
    if(!ptr)
        ptrData = new DataC(Element);
    // append to existing list
    else
        ptr->ptrNext = new Queue(Element);
    
};


// Recursively Search List Contents.
template <class DataC> bool Database::Queue<DataC>::inList(const DataC& Element)
{
    // Base Case
    if (*ptrData == Element)
        return true;
    
    // Search Conditions
    else if (ptrNext == NULL)
        return false;
    else
        return ptrNext->inList(Element);
};


// Recursively finds last element in list. Cannot use template function as o/p type different to i/p type
template <class DataC> void Database::Queue<DataC>::printList()
{
    // Base Case
    if (ptrData == NULL)
        return;
    
    std::cerr << *ptrData << std::endl;
    
    // Search Conditions.
    if(ptrNext == NULL)
        return;
    else
        ptrNext->printList();
};


// --------------------- Private Members ---------------------

// Returns and deletes first element of queue and shifts queue list
template <class DataC> DataC* Database::Queue<DataC>::pop()
{
    // Assumes safe deep copy
    DataC* tempData = ptrData;
    
    // List size > 1
    if(ptrNext)
    {
        ptrData = ptrNext->ptrData;
        ptrNext = ptrNext->ptrNext;
    }
    // List size = 1
    else
    {
        ptrData = NULL;
        ptrNext = NULL;
    }
    
    return tempData;
};


// Recursively finds last element in list. Cannot use template function as o/p type different to i/p type
// Returns pointer to last empty element in list. If list empty, return null
template <class DataC> Database::Queue<DataC>* Database::Queue<DataC>::lastElement()
{
    // Base Case
    if (ptrData == NULL)
        return NULL;
    
    // Search Conditions.
    if(ptrNext == NULL)
        return this;
    else
        return ptrNext->lastElement();
};











// -------------- Test Code Main ---------------------


/*Queue<int> interface;
 
 std::cout << "Printing List" << std::endl;
 interface.printList();
 
 std::cout << "Printing List" << std::endl;
 interface.push(1);
 interface.printList();
 
 std::cout << "Printing List" << std::endl;
 interface.pop();
 interface.printList();
 
 std::cout << "Printing List" << std::endl;
 for(int i = 0; i < 20; i++)
 interface.push(i);
 interface.printList();
 
 std::cout << "is -2 in list? " << interface.inList(-2) << std::endl;
 std::cout << "is 0 in list? " << interface.inList(0) << std::endl;
 std::cout << "is 19 in list? " << interface.inList(19) << std::endl;
 std::cout << "is 8 in list? " << interface.inList(8) << std::endl;
 std::cout << "is 40 in list? " << interface.inList(40) << std::endl;
 
 for (int i = 0; i < 14; i++)
 std::cout << "popping: " << *interface.pop() << std::endl;
 
 std::cout << "Printing List " << std::endl;
 interface.printList();
 */
