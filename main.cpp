#include <iostream>
#include <fstream>
#include "Node.h"
#include "StateTree.h"
#include "Menu.h"

using namespace std;


void accessData(int count, StateTree _treeData[]) {
    string state;
    string previousState;
    string confirmed;
    string deaths;
    string incidentRate;
    string fatalityRate;

    TreeNode *treeNode;

    // Loop through data folder
    for (int i = 0; i < count; i++) {
        // Read each .csv file within
        ifstream myFile("./Data/" + to_string(i + 1) + ".csv");
        // File is valid
        if (myFile.is_open()) {
            // Trash the title line
            string firstLine;
            getline(myFile, firstLine);

            // Read the 5 columns from each line
            while(getline(myFile, state, ',')) {
                getline(myFile, confirmed, ',');
                getline(myFile, deaths, ',');
                getline(myFile, incidentRate, ',');
                getline(myFile, fatalityRate);

                // If the state from previous line is equal to current state
                if (previousState != state) {
                    // If the state from previous like is not empty
                    if (!previousState.empty()) {
                        // Insert the treeNode into correct tree
                        _treeData[i].insert(treeNode);
                    }
                    // And construct a new Node for new state
                    treeNode = new TreeNode(state, confirmed, deaths, incidentRate);
                }
                // If the state from previous line is the same as current state
                else {
                    // Add the value to the Node
                    treeNode->add(confirmed, deaths, incidentRate);
                }

                // After finishing current line, make the current line previous line
                // And move 1 line down
                previousState = state;
            }
            // Reach this point after finishing the entire csv file
            // Insert the treeNode into correct tree
            _treeData[i].insert(treeNode);
        }
        // Close the file and reset the previousState
        previousState.clear();
        myFile.close();
    }
}

int main() {
    // Array of 30 trees
    StateTree treeData[30] = {};
    // Read the data and store them into Tree and Map
    accessData(30, treeData);

    Menu::mainMenu(treeData);

    return 0;
}
