//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()


    }
    //uses an int var that contains the smallest index for returning, and another with the same
    //value to get replaced by the last element, then downheaps to maintain minheap structure
    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        if (size == 0) {
            cout << "Heap is empty." << endl;
            return -1;
        }
        int smallest = weightArr[0];
        int replace = weightArr[0];

        // Replace root with last element, then call downheap()
        replace = weightArr[size - 1];
        //downheap();
        return smallest;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
    }
};

#endif