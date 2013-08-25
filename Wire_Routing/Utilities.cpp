//
//  Utilities.cpp
//  Wire_Routing
//
//  Created by Josh Jacobson on 10/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Utilities.h"

using namespace std;
extern stack pointStack;
extern queue pointQueue;

int checkPosition(int row, int column, int value, grid * theGrid) {
    // Return 99 for target found, 1 for 1, 0 for 0
    int positionValue = theGrid->getValue(row,column);
    if (positionValue == 1) { 
        theGrid->setValue(value+1,row,column);
        return 1;
    }
    else if (positionValue == 99) {
        theGrid->setValue(value+1,row,column);
        return 99; // Target found!
    }
    return 0;
}

bool checkNeighbors(point currentPoint, grid * theGrid) {
    int row = currentPoint.getRow();
    int column = currentPoint.getColumn();
    int currentValue = theGrid->getValue(row,column);
    int status;
    
    if (row != 0) { // Neighbor to the north (Canada)
        status = checkPosition(row-1, column, currentValue, theGrid);
        if (status == 99) return true;
        else if (status == 1) pointQueue.enqueue(point(row-1,column));
    }
    if (row < theGrid->getSize() -1) { // Neighbor to the south (Mexico)
        status = checkPosition(row+1, column, currentValue, theGrid);
        if (status == 99) return true;
        else if (status == 1) pointQueue.enqueue(point(row+1,column));
    }
    if (column != 0) { // Neighbor to the west (Pacific)
        status = checkPosition(row, column-1, currentValue, theGrid);
        if (status == 99) return true;
        else if (status == 1) pointQueue.enqueue(point(row,column-1));
    }
    if (column < theGrid->getSize() -1) { // Neighbor to the east (Atlantic)
        status = checkPosition(row, column+1, currentValue, theGrid);
        if (status == 99) return true;
        else if (status == 1) pointQueue.enqueue(point(row,column+1));
    }
    return false;
}

point checkNeighborsBackward(point currentPoint, grid * theGrid) {
    int row = currentPoint.getRow();
    int column = currentPoint.getColumn();
    int currentValue = theGrid->getValue(row,column);
    point nextPoint(row,column);
    
    if (row != 0) { // Neighbor to the north (Canada)
        if (theGrid->getValue(row-1,column) == currentValue-1) {
            nextPoint = point(row-1,column);
            pointStack.push(&nextPoint);
            return nextPoint;
        }
    }
    if (row < theGrid->getSize() -1) { // Neighbor to the south (Mexico)
        if (theGrid->getValue(row+1,column) == currentValue-1) {
            nextPoint = point(row+1,column);
            pointStack.push(&nextPoint);
            return nextPoint;
        }
    }
    if (column != 0) { // Neighbor to the west (Pacific)
        if (theGrid->getValue(row,column-1) == currentValue-1) {
            nextPoint = point(row,column-1);
            pointStack.push(&nextPoint);
            return nextPoint;
        }
    }
    if (column < theGrid->getSize() -1) { // Neighbor to the east (Atlantic)
        if (theGrid->getValue(row,column+1) == currentValue-1) {
            nextPoint = point(row,column+1);
            pointStack.push(&nextPoint);
            return nextPoint;
        }
    }
    return NULL;
}


 
// Grid class:

grid::grid(int mySize) {
    size = mySize;
    gridArray = new int[size*size];
}

grid::~grid() {
    delete gridArray;
}

int grid::getValue(int row, int column) {
    return gridArray[row*size + column];
}
void grid::setValue(int value, int row, int column) {
    gridArray[row*size + column] = value;
}

int grid::getSize() {
    return size;
}
void grid::print() {
    int value;
    for (int i = 0; i<size; i++) {
        for (int j = 0; j<size; j++) {
            value = gridArray[i*size + j];
            cout << value << " ";
            if (value <10) cout << " "; // Make spacing nice for single and double digit numbers
        }
        cout << "\n";
    }
}










// Point Class

point::point(int rowval, int columnval) {
    row = rowval;
    column = columnval;
}

int point::getRow() {
    return row;
}

int point::getColumn() {
    return column;
}

void point::setRow(int rowval) {
    row = rowval;
}

void point::setColumn(int columnval) {
    column = columnval;
}

bool point::operator ==(point & other) {
    if ((other.getRow() == row) && (other.getColumn() == column)) return true;
    else return false;
}

bool point::operator !=(point & other) {
    if ((other.getRow() == row) && (other.getColumn() == column)) return false;
    else return true;
}

point::point(point* other) { // Copy constructor
    row = other->getRow();
    column = other->getColumn();
}

void point::print() {
    cout << "(" << row << "," << column << ") ";
}


// Queue Class

queue::queue() {
    currentSize = 0;
    frontIndex = 0;
    backIndex = 0;
}
queue::~queue() {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (pointArray[i] == NULL) delete pointArray[i];
        pointArray[i] = NULL;
    }
}

bool queue::isEmpty() {
    if (currentSize == 0) return true;
    else return false;
}
int queue::size() {
    return currentSize;
}
point queue::front() {
    if (currentSize != 0) {
        return *(pointArray[frontIndex]);
    }
    else return NULL;
    // else THROW EMPTY QUEUE EXCEPTION
}
point queue::back() {
    if (currentSize != 0) {
        int index = backIndex - 1 + ARRAY_SIZE;
        index = index % ARRAY_SIZE;
        return *(pointArray[index]);
    }
    else return NULL;
    // else THROW EMPTY QUEUE EXCEPTION
}
void queue::dequeue() {
    if (currentSize != 0) {
        frontIndex += 1;
        frontIndex = frontIndex % ARRAY_SIZE;
        currentSize--;
    }
    // else THROW EMPTY QUEUE EXCEPTION
}
void queue::enqueue(const point & newPoint) {
    if (currentSize < ARRAY_SIZE) {
        point * a = new point(newPoint); // make a copy of newPoint that is not a const
        pointArray[backIndex] = a;
        
        backIndex += 1;
        backIndex = backIndex % ARRAY_SIZE;
        currentSize++;
    }
    // else THROW FULL QUEUE EXCEPTION
}


// Stack Class


stack::stack() {
    currentSize = 0;
    top = 0; // Stores index of top + 1
}
stack::~stack() {
    for (int i = 0; i < STACK_SIZE; i++) {
        if (pointArray[i] == NULL) delete pointArray[i];
        pointArray[i] = NULL;
    }
}
bool stack::isEmpty() {
    if (currentSize == 0) return true;
    else return false;
}
int stack::getSize() {
    return currentSize;
}

point * stack::pop() {
    if (currentSize!=0) {
        top--;
        currentSize--;
        return pointArray[top];
    }
    else return NULL;
}
bool stack::push(const point & theElement) {
    if (currentSize < STACK_SIZE) {
        point * a = new point(theElement); // make a copy of theElement that is not a const
        pointArray[top] = a;
        top++;
        currentSize++;
        return true;
    }
    else return false;
}
