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

    //insert new element at the end of the heap, and increase the size by 1 to get the next
    //available index, then upheap
    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        data[size] = weightArr[idx];
        int pushed = size;
        size++;
        //upheap - need something in push() to pass to upheap, what is it?
        //upheap(size) - maybe
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
        //downheap(); - need something to pass to this
        return smallest;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        int child = pos;
        while (child > 0) {
            int parent = (child - 1) / 2;
            //maybe add condition check for if it's still a min heap after push
            if (weightArr[data[parent]] <= weightArr[data[child]]) {
                break;
            }

        //make parent dependent on child instead
            int temp = data[parent];
            data[parent] = data[child];
            data[child] = temp;
            child = parent;
            parent = (child - 1) / 2;
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        //need to check that both children exist somehow
        //^maybe like !data[leftChild]? or !weightArr[data[rightChild]] (?)
        int parent = 0;
        while (parent != size) { //not sure if this is the right condition, maybe < size works better
            int leftChild = (2 * parent) + 1;
            int rightChild = (2 * parent) + 2;
            //if less than both children already, it's a minheap
            if (weightArr[data[parent]] <= weightArr[data[rightChild]] && weightArr[data[parent]] < weightArr[data[leftChild]]) {
            }
            int temp = data[parent];
            if (data[leftChild] < data[parent]) {
                data[parent] = data[leftChild];
                data[leftChild] = temp;
                parent = leftChild;
                //leftChild = (2 * parent) + 1;
                //rightChild = (2 * parent) + 2;
                //^the beginning of the loop should do this already
            }
            else if (data[rightChild] < data[parent]) {
                data[parent] = data[rightChild];
                data[rightChild] = temp;
                parent = rightChild;
                //again the left and right child updates should happen on the next loop iteration
            }
        }
    }


};

#endif