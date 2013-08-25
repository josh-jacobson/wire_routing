//
//  main.cpp
//  Wire Routing
//
//  EECS 311 Programming Assignment #1
//  Josh Jacobson
//  netID: jdj560
//

#include <iostream>
#include <fstream>
#include "Utilities.h"
using namespace std;

// Global variables:
queue pointQueue;
stack pointStack;

int main (int argc, const char * argv[])
{
    
    ifstream infile;
    infile.open("sample_grid",ios::in); // Read input file
    char nextCharacter;
    
    int i = 0;
    int j = 0;
    int value;
    point start(0,0);
    point target(0,0);
    int gridSize;
    
    
    // Determine grid size:
    if (infile.is_open()) { // file successfully opened
        while ((infile.good()) && (nextCharacter != '\n')) {
            nextCharacter = infile.get();
            if ((nextCharacter == '0') || (nextCharacter == '1')|| (nextCharacter == 'S') || (nextCharacter == 'T')) {
                gridSize++;
            }
        }
        infile.close(); // Done reading, close the file.
    }
     else cout << "Error reading file.\n";
    
    grid myGrid(gridSize);
    myGrid.setValue(10,1,1);
    myGrid.setValue(99,8,8);
    myGrid.print();
    
    infile.open("sample_grid",ios::in); // Read input file
    if (infile.is_open()) { // file successfully opened
        while ((infile.good()) && (i < gridSize)) {
            // Loop to read successive lines from input file
            while (j < gridSize) {
                // Loop to read one horizontal line
                nextCharacter = infile.get();
                if ((nextCharacter == '0') || (nextCharacter == '1')) {
                    value = (int) nextCharacter - 48;
                    myGrid.setValue(value,i,j);
                    j++;
                }
                else if (nextCharacter == 'S') { // Start location
                    start.setRow(i);
                    start.setColumn(j);
                    myGrid.setValue(10,i,j);
                    j++;
                }
                else if (nextCharacter == 'T') { // Target location
                    target.setRow(i);
                    target.setColumn(j);
                    myGrid.setValue(99,i,j);
                    j++;
                }
            }
            // Line has been read. Increment i and reset j, then move onto the next line:
            i++;
            j = 0;
        }
        infile.close(); // Done reading, close the file.
    }
    else cout << "Error reading file.\n";
    
    myGrid.print();
    
    bool targetFound = false;
    int row, column;
    point a = point(5,5);

    // Check the neighbors of the first position:
    targetFound = checkNeighbors(start, &myGrid);
    
    // Loop to travel through the array and look for the finish position
    while ((!pointQueue.isEmpty()) && (!targetFound)) {
        if (checkNeighbors(pointQueue.front(),&myGrid)) {
            targetFound = true;
        }
        else pointQueue.dequeue();
    }
    
    if (targetFound) {
        // Travel back to the start and push points onto the stack in order to print in forward order
        point currentPoint(&target);
        while (currentPoint != start) {
            currentPoint = checkNeighborsBackward(currentPoint, &myGrid);
            
        }
        
        cout << "A path was found from the start to the target.\n";
        cout << "Integer \'Path length\': " << pointStack.getSize()+1 << "\nArray Path: ";
        // Print path:
        while (!pointStack.isEmpty()) {
            currentPoint = pointStack.pop();
            currentPoint.print();
        }
        target.print(); // Print the last point
        
    }
    else cout << "No path was found from the start to the target.\n";

    return 0;
}

