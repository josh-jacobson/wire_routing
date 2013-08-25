//
//  Utilities.h
//  Wire_Routing
//
//  Created by Josh Jacobson on 10/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Wire_Routing_Utilities_h
#define Wire_Routing_Utilities_h

#define ARRAY_SIZE 100
#define STACK_SIZE 100

class grid {
private:
    int size;
    int * gridArray;
public:
    grid(int mySize);
    ~grid();
    int getValue(int row, int column);
    void setValue(int value, int row, int column);
    int getSize();
    void print();
};


class point {
private:
    int row;
    int column;
public:
    point(int rowval, int columnval);
    point(point* other);
    int getRow();
    int getColumn();
    bool operator ==(point & other);
    bool operator !=(point & other);
    void setRow(int rowval);
    void setColumn(int columnval);
    void print();
};

int checkPosition(int row, int column, int value, grid * theGrid);
bool checkNeighbors(point currentPoint, grid * theGrid);
point checkNeighborsBackward(point currentPoint, grid * theGrid);

class queue {
private:
    point * pointArray[ARRAY_SIZE];
    int currentSize;
    int frontIndex;
    int backIndex;
public:
    queue();
    ~queue();
    bool isEmpty();
    int size();
    point front();
    point back();
    void dequeue();
    void enqueue(const point & theElement);
};

class stack {
private:
    point * pointArray[STACK_SIZE];
    int currentSize;
    int top; // Stores value of top index + 1
public:
    stack();
    ~stack();
    bool isEmpty();
    int getSize();
    point * pop();
    bool push(const point & theElement);
};


#endif
