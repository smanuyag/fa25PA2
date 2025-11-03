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
        //can't push into a full heap
        if (size >= 64) {
            cout<<"Heap is full.";
            return;
        }
        data[size] = weightArr[idx];
        int pushed = size;
        size++;
        upheap(pushed, weightArr);
    }
    //uses an int var that contains the smallest index for returning, and another with the same
    //value to get replaced by the last element, then downheaps to maintain minheap structure
    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        if (size == 0) {
            cout << "Heap is empty." << endl;
            return -1;
        }
        int smallest = data[0];
        int replace = data[size-1]; //size-1 is last element

        // Replace root with last element, then call downheap()
        //^ need to dec size
        replace = data[size-1];
        //dec size here
        size--;
        downheap(replace, weightArr);
        return smallest;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        int child = pos;
        while (child > 0) { //no child means no parent, so the loop condition should rely on the child
            int parent = (child - 1) / 2;
            //maybe add condition check for if it's still a min heap after push
            if (weightArr[data[parent]] <= weightArr[data[child]]) {
                break;
            }

        //make parent dependent on child instead
            int temp = data[parent]; //save parent spot since it will be replaced in the line below
            data[parent] = data[child]; //swap child with parent
            data[child] = temp; //child gets parent value
            child = parent; //update child
            parent = (child - 1) / 2; //update parent
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        //need to check that both children exist somehow
        //might have to change the loop condition because it will keep going even if there's no children
        //^probably dependent on left child since it has to come before a right child
        //^if there is a left child, compare it to the right child, and make sure both are
        //within the size range(?), whichever is smaller (if both exist) will get swapped with the parent

        int parent = pos;

        while (((2 * parent) + 1) <  size) { //ensures that the left child exists
            int leftChild = (2 * parent) + 1;
            int rightChild = (2 * parent) + 2;
            //if less than both children already, it's a minheap
            int smallest = leftChild; //set smaller child to leftChild first
            if ((rightChild < size) && (weightArr[data[rightChild]] < weightArr[data[leftChild]])) { //check that the rightChild index is within range and if the weight is less than the left child
                smallest = rightChild; //right child is smaller
            }
            if (weightArr[data[parent]] <= weightArr[data[smallest]]) { //condition for already in minheap order
                return;
            }
            int temp = data[parent];
            //no need to compare parent with left and right child since the smallest between them was already found
                //swaps and update parent node
                data[parent] = data[smallest];
                data[smallest] = temp;
                parent = smallest;
                //leftChild = (2 * parent) + 1;
                //rightChild = (2 * parent) + 2;
                //^the beginning of the loop should do this already
        }
    }


};

#endif