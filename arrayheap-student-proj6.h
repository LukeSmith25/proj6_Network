/**
 * file: arrayheap-student-proj6.h
 * author: Luke Smith
 * course: CSI 3334
 * assignment: project 6
 * due date: December 4, 2022
 *
 * Function definitions for the arrayheap class.
 */
#ifndef ARRAY_HEAP_STUDENT_PROJ6_H
#define ARRAY_HEAP_STUDENT_PROJ6_H

#include "arrayheap-prof-proj6.h"
#include <algorithm>
#include <iostream>

using namespace std;

/**
 * Default Constructor
 *
 * This function is the default constructor for arrayheap.
 *
 * Parameters: none
 *
 * Return value: none
 */
template<class Base>
ArrayHeap<Base>::ArrayHeap() {
    numItems = 0;
    capacity = 1;
    data = new Base[capacity];
    heapAndFreeStack = new int[capacity];
    dataToHeap = new int[capacity];
    heapAndFreeStack[0] = 0;
    dataToHeap[0] = 0;
}

/**
 * Copy Constructor
 *
 * This function creates and copies an arrayheap object.
 *
 * Parameters:
 *      ArrayHeap<Base> &h: process to be copied
 *
 * Return value: none
 */
template<class Base>
ArrayHeap<Base>::ArrayHeap(const ArrayHeap<Base> &h) {
    data = new Base[h.capacity];
    heapAndFreeStack = new int[h.capacity];
    dataToHeap = new int[h.capacity];
    numItems = h.numItems;
    capacity = h.capacity;

    for (int i = 0; i < numItems; i++) {
        data[i] = h.data[i];
        heapAndFreeStack[i] = h.heapAndFreeStack[i];
        dataToHeap[i] = h.dataToHeap;
    }
}

template<class Base>
ArrayHeap<Base>::~ArrayHeap() {
    delete [] data;
    delete [] heapAndFreeStack;
    delete [] dataToHeap;
    data = nullptr;
    heapAndFreeStack = nullptr;
    dataToHeap = nullptr;
    numItems = 0;
    capacity = 0;
}

template<class Base>
const ArrayHeap<Base> &ArrayHeap<Base>::operator=(const ArrayHeap<Base> &ah) {
    return <#initializer#>;
}

template<class Base>
int ArrayHeap<Base>::insert(const Base &item) {
    return 0;
}

template<class Base>
void ArrayHeap<Base>::removeMinItem() {

}

/**
 * getMinItem
 *
 * This function returns the minimum item in an array heap.
 *
 * Parameters: none
 *
 * Return value: minimum array heap object
 */
template<class Base>
const Base &ArrayHeap<Base>::getMinItem() const {
    return data[heapAndFreeStack[0]];
}

/**
 * getNumItems
 *
 * This function returns the number of items in an array heap
 *
 * Parameters: none
 *
 * Return value: integer representing number of items
 */
template<class Base>
int ArrayHeap<Base>::getNumItems() const {
    return numItems;
}

template<class Base>
bool ArrayHeap<Base>::isOnHeap(int key) const {
    return false;
}

template<class Base>
void ArrayHeap<Base>::changeItemAtKey(int key, const Base &newItem) {

}

template<class Base>
void ArrayHeap<Base>::doubleCapacity() {

}

template<class Base>
void ArrayHeap<Base>::bubbleUp(int ndx) {

}

template<class Base>
void ArrayHeap<Base>::bubbleDown(int ndx) {

}


#endif

