#include "FileHandle.h"
#include "Node.h"
#include "Scenario.h"
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    // Check for the correct number of command-line arguments
    if (argc < 2)
    {
        // Inform the user of the correct usage if the filename is missing
        printf("Usage : %s <filename>\n", argv[0]);
        return 0;
    }

    // Load the scenario from the provided file
    Scenario* scenario = readFile(argv[1]);

    if (scenario == nullptr) {
        // Check if the scenario was successfully loaded
        return 1;
    }

    // Set up and perform various searches on the loaded scenario
    scenario->fNodes[scenario->fStart.fX][scenario->fStart.fY].fDistance = 0;
    scenario->fNodes[scenario->fStart.fX][scenario->fStart.fY].fVisited = true;

    // Displaying Depth First Search results
    cout << "Depth First Search\n\n";
    scenario->DFS(&(scenario->fStart));
    scenario->resetVisited();
    //

    scenario->print();

    //Displaying Breadth First Search results
    cout << "Breadth First Search\n\n";
    scenario->BFS(&(scenario->fStart));
    scenario->resetVisited();
    //

    scenario->print();

    //Displaying Greedy Best First Search results
    cout << "Greedy Best First Search\n\n";
    for (int i = 0; i < scenario->fGoal.size(); i++)
    {
        scenario->GBFS(&(scenario->fStart), &(scenario->fGoal[i]));
        scenario->resetVisited();
    }
    //

    scenario->print();


    // Execute A* Search for each goal
    cout << "A* Search\n\n";
    for (int i = 0; i < scenario->fGoal.size(); i++)
    {
        scenario->AStar(&(scenario->fStart), &(scenario->fGoal[i]));
        scenario->resetVisited();
    }
    //

    scenario->print();


    // Execute Custom Search 1
    cout << "CUS1 Search\n\n";
    scenario->CUS1(&(scenario->fStart));
    scenario->resetVisited();
    //

    scenario->print();


    // Execute Custom Search 2 for each goal
    cout << "CUS2 Search\n\n";
    for (int i = 0; i < scenario->fGoal.size(); i++)
    {
        scenario->CUS2(&(scenario->fStart), &(scenario->fGoal[i]));
        scenario->resetVisited();
    }
    //

    return 0;
}