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
    if (!this) {
        numItems = ah.numItems;
        capacity = ah.capacity;

        delete [] data;
        delete [] heapAndFreeStack;
        delete [] dataToHeap;
        data = new Base[capacity];
        heapAndFreeStack = new int[capacity];
        dataToHeap = new int[capacity];

        for (int i = 0; i < numItems; i++) {
            data[i] = ah.data[i];
            heapAndFreeStack[i] = ah.heapAndFreeStack[i];
            dataToHeap[i] = ah.dataToHeap;
        }
    }

    return *this;
}

template<class Base>
int ArrayHeap<Base>::insert(const Base &item) {
    if (numItems == capacity) {
        doubleCapacity();
    }
    data[heapAndFreeStack[numItems++]] = item;
    bubbleUp(numItems - 1);

    return numItems;
}

template<class Base>
void ArrayHeap<Base>::removeMinItem() {
    swap(heapAndFreeStack[0], heapAndFreeStack[numItems-1]);
    swap(dataToHeap[heapAndFreeStack[0]], dataToHeap[heapAndFreeStack[numItems-1]]);
    numItems--;
    bubbleDown(0);
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
    for (int i = 0; i < numItems; i++) {
        if (key == heapAndFreeStack[i]) {
            return true;
        }
    }
    return false;
}

template<class Base>
void ArrayHeap<Base>::changeItemAtKey(int key, const Base &newItem) {
    data[key] = newItem;
    bubbleUp(key);
}


template<class Base>
void ArrayHeap<Base>::doubleCapacity() {
    int newCapacity = capacity * 2;
    Base *newData = new Base[newCapacity];
    int *newHFS = new int[newCapacity];
    int *newDTH = new int[newCapacity];

    for (int i = 0; i < newCapacity; i++) {
        newHFS[i] = i;
        newDTH[i] = i;
    }
    for (int i = 0; i < numItems; i++) {
        newData[i] = data[i];
        newHFS[i] = heapAndFreeStack[i];
        newDTH[i] = dataToHeap[i];
    }

    delete [] data;
    data = newData;
    delete [] heapAndFreeStack;
    heapAndFreeStack = newHFS;
    delete [] dataToHeap;
    dataToHeap = newDTH;

    capacity = newCapacity;
}

template<class Base>
void ArrayHeap<Base>::bubbleUp(int ndx) {
    if (ndx == 0) {
        return;
    }
    int parent = (ndx - 1) / 2;

    if (data[heapAndFreeStack[ndx]] < data[heapAndFreeStack[parent]]) {
        // Swap HFS, then swap dataToHeap at HFS[index]
        swap(heapAndFreeStack[ndx], heapAndFreeStack[parent]);
        swap(dataToHeap[heapAndFreeStack[ndx]], dataToHeap[heapAndFreeStack[parent]]);
        bubbleUp(parent);
    }
}

template<class Base>
void ArrayHeap<Base>::bubbleDown(int ndx) {
    int child1 = 2 * ndx + 1;
    int child2 = 2 * ndx + 2;
    if (child1 < numItems) {
        int lesserChild = child1;
        if ((child2 < numItems) &&
            (data[heapAndFreeStack[child2]] < data[heapAndFreeStack[child1]])) {
            lesserChild = child2;
        }
        if (data[heapAndFreeStack[lesserChild]] < data[heapAndFreeStack[ndx]]){
            // Swap HFS, then swap dataToHeap at HFS[index]
            swap(heapAndFreeStack[lesserChild], heapAndFreeStack[ndx]);
            swap(dataToHeap[heapAndFreeStack[lesserChild]], dataToHeap[heapAndFreeStack[ndx]]);
            bubbleDown(lesserChild);
        }
    }
}


#endif

