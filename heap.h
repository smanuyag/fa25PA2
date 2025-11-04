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

    //Push inserts new index (idx) at the end of the heap, and increase the size by 1 to get the next
    //available index, then upheaps.
    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        //can't push into a full heap
        if (size >= 64) {
            cout<<"Heap is full.";
            return;
        }
        data[size] = idx;
        int pushed = size; //preserve size before it's incremented
        size++;
        upheap(pushed, weightArr);
    }
    //Pop uses an int variable that contains the smallest index for returning, sets the beginning of heap to
    //last element, updates size, then downheaps starting with root since that element was just replaced and needs
    //to be checked to see if it has to be downheaped.
    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        if (size == 0) {
            cout << "Heap is empty." << endl;
            return -1;
        }
        int smallest = data[0];

        // Replace root with last element, then call downheap()
        data[0] = data[size - 1];

        size--; //dec size after removal
        downheap(0, weightArr);
        return smallest;
    }

    //Upheap first checks to make sure the child node exists, find its parent, compare their weights,
    //break if it's still in minheap order, and swap otherwise, and update child
    //and parent nodes to keep going/see if more upheaps are needed.
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
            //parent updated in the beginning of while loop
        }
    }

    //Downheap first checks that the parent is in range, check that the left child exists, so the parent has at least one child node,
    //then the indexes for the left and right child are created, the left and right child weights are compared to see
    //which one (the smaller weight) will be compared to the parent node's weight and swapped if needed, then the parent, and
    //left and right child indexes are updated.
    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        //might have to change the loop condition because it will keep going even if there's no children
        //^probably dependent on left child since it has to come before a right child
        //^if there is a left child, compare it to the right child, and make sure both are
        //whichever is smaller (if both exist) will get swapped with the parent

        if (pos < 0 || pos >= size) { //check if parent is within range/out of range
            return;
        }

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
                break;
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