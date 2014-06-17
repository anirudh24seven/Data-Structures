// Program to show segment tree operations like construction, query and update
#include <stdio.h>
#include <math.h>

// Utility function to get the middle index from corner vertices
int getMiddleIndex (int startIndex, int endIndex) {
    return startIndex + (endIndex - startIndex)/2;
}

// A recursive function to get the sum of values in given range of the array.
int getSumUtil(int *segmentTree, int startIndexOfSegmentTree, int endIndexOfSegmentTree, int startIndexOfQuery, int endIndexOfQuery, int currentNodeIndex) {
    // If segment of this node is part of a given range, return the sum of the segment
    if (startIndexOfQuery <= startIndexOfSegmentTree && endIndexOfQuery >= endIndexOfSegmentTree) {
        return segmentTree[currentNodeIndex];
    }

    // If segment of this node is outside the given range
    if (endIndexOfSegmentTree < startIndexOfQuery || startIndexOfSegmentTree > endIndexOfQuery) {
        return 0;
    }

    // If a part of this segment overlaps with the given range
    int middleIndex = getMiddleIndex(startIndexOfSegmentTree, endIndexOfSegmentTree);

    return getSumUtil(segmentTree, startIndexOfSegmentTree, middleIndex, startIndexOfQuery, endIndexOfQuery, 2*currentNodeIndex + 1) +
        getSumUtil(segmentTree, middleIndex + 1, endIndexOfSegmentTree, startIndexOfQuery, endIndexOfQuery, 2*currentNodeIndex + 2);
}

// A recursive function to update the nodes which have the given index in their range
void updateValueUtil(int *segmentTree, int startIndexOfSegmentTree, int endIndexOfSegmentTree, int indexOfElementToBeUpdated, int valueToBeAdded, int currentNodeIndex) {

    // Base case: If the input index lies outside the range of this segment
    if (indexOfElementToBeUpdated < startIndexOfSegmentTree || indexOfElementToBeUpdated > endIndexOfSegmentTree) {
        return;
    }

    // If the input index is in range, update the value of the node and its children
    segmentTree[currentNodeIndex] += valueToBeAdded;
    if (endIndexOfSegmentTree != startIndexOfSegmentTree) {
        int middleIndex = getMiddleIndex(startIndexOfSegmentTree, endIndexOfSegmentTree);
        updateValueUtil(segmentTree, startIndexOfSegmentTree, middleIndex, indexOfElementToBeUpdated, valueToBeAdded, 2*currentNodeIndex + 1);
        updateValueUtil(segmentTree, middleIndex + 1, endIndexOfSegmentTree, indexOfElementToBeUpdated, valueToBeAdded, 2*currentNodeIndex + 2);
    }
}

int constructSegmentTreeUtil(int array[], int startIndexOfSegmentTree, int endIndexOfSegmentTree, int *segmentTree, int currentNodeIndex) {
    // If there is one element in the array, store it in th current node of the segment tree and return
    if (startIndexOfSegmentTree == endIndexOfSegmentTree) {
        segmentTree[currentNodeIndex] = array[startIndexOfSegmentTree];
        return array[startIndexOfSegmentTree];
    }

    int middleIndex = getMiddleIndex(startIndexOfSegmentTree, endIndexOfSegmentTree);
    segmentTree[currentNodeIndex] = constructSegmentTreeUtil(array, startIndexOfSegmentTree, middleIndex, segmentTree, currentNodeIndex*2 + 1) +
        constructSegmentTreeUtil(array, middleIndex + 1, endIndexOfSegmentTree, segmentTree, currentNodeIndex*2 + 2);

    return segmentTree[currentNodeIndex];
}

int getSum(int *segmentTree, int numberOfElements, int startIndexOfQuery, int endIndexOfQuery) {
    // Check for erroneous input values
    if (startIndexOfQuery < 0 || endIndexOfQuery >= numberOfElements || startIndexOfQuery > endIndexOfQuery) {
        printf("Invalid input");
        return -1;
    }

    return getSumUtil(segmentTree, 0, numberOfElements - 1, startIndexOfQuery, endIndexOfQuery, 0);
}

void updateValue(int array[], int *segmentTree, int numberOfElements, int index, int newValue) {
    if (index < 0 || index >= numberOfElements) {
        printf("Invalid input");
        return;
    }

    int difference = newValue - array[index];
    array[index] = newValue;

    updateValueUtil(segmentTree, 0, numberOfElements - 1, index, difference, 0);
}

int *constructSegmentTree(int array[], int numberOfElements) {
    // Allocate memory for segment tree
    int height = (int)(ceil(log2(numberOfElements)));
    int maxSize = 2*(int)pow(2, height) - 1;
    int *segmentTree = new int[maxSize];

    constructSegmentTreeUtil(array, 0, numberOfElements - 1, segmentTree, 0);

    return segmentTree;
}

int main() {
    int array[] = {1, 3, 5, 7, 9, 11};
    int numberOfElements = sizeof(array)/sizeof(array[0]);

    int *segmentTree = constructSegmentTree(array, numberOfElements);

    printf("Sum of values in given range = %d\n", getSum(segmentTree, numberOfElements, 1, 3));

    updateValue(array, segmentTree, numberOfElements, 1, 10);

    printf("Updated sum of values in given range = %d\n", getSum(segmentTree, numberOfElements, 1, 3));

    return 0;
}
