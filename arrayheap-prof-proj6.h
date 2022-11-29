#ifndef ARRAY_HEAP_PROF_PROJ6_H
#define ARRAY_HEAP_PROF_PROJ6_H

/* CHANGES FROM PROJECT 5:
 *  - There is a new array called dataToHeap, which keeps track of where each
 *    data item lives in the heap ordering. Adding this array will require
 *    changes to every method in the class except for getMinItem() and
 *    getNumItems().
 *
 *  - The insert() method returns an integer "key", which is the index where the
 *    new item is inserted into the data array. This key can be used later to
 *    get back to that item, so that the item can be changed.
 *
 *  - The isOnHeap() method checks to see if a given key is on the heap.
 *
 *  - The changeItemAtKey() method takes a key and a new item, uses the new item
 *    to replace the old item at data[key], and performs bubble operations as
 *    necessary to maintain heap order.
 */
template <class Base>
class ArrayHeap {
    public:
        ArrayHeap();
        ArrayHeap(const ArrayHeap<Base> &h);
        ~ArrayHeap();

        const ArrayHeap<Base> &operator=(const ArrayHeap<Base> &ah);

        int insert(const Base &item);
        void removeMinItem();
        const Base &getMinItem() const;
        int getNumItems() const;

        bool isOnHeap(int key) const;
        void changeItemAtKey(int key, const Base &newItem);

    private:
        Base *data;
        int *dataToHeap;
        int *heapAndFreeStack;

        int numItems;
        int capacity;

        void doubleCapacity();
        void bubbleUp(int ndx);
        void bubbleDown(int ndx);
};

#endif

