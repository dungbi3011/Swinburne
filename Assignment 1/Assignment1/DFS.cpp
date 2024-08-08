#include "Scenario.h"

void Scenario::DFS(Node* aSource) const
{
    //Marking the source node as visited, preventing revisitation 
    aSource->fVisited = true;

    //If current node is the goal, print the path & stop the search
    if (aSource->fColor == 'G')
    {   
        //Initializing the path, with stringstream datatype
        stringstream path;

        //Tracking back, storing the path from the source to this goal node
        printPath(aSource, path); 

        // Counting number of steps (By converting "path" to istringstream)
        istringstream is(path.str());
        auto numOfSteps = distance(istream_iterator<string>(is), istream_iterator<string>());

        cout << "Number of steps: " << numOfSteps - 4 << endl;
        cout << path.str() << endl;
        cout << "\n";
        return;
    }

    //Explore four possible directions from the current node (up, down, left, right)

    if (isValid(aSource->fX - 1, aSource->fY))
    {
        fNodes[aSource->fX - 1][aSource->fY].fPrevious = aSource;
        DFS(&fNodes[aSource->fX - 1][aSource->fY]);
        fNodes[aSource->fX - 1][aSource->fY].fPrevious = NULL; //Reseting fPrevious
    }

    if (isValid(aSource->fX, aSource->fY - 1))
    {
        fNodes[aSource->fX][aSource->fY - 1].fPrevious = aSource;
        DFS(&fNodes[aSource->fX][aSource->fY - 1]);
        fNodes[aSource->fX][aSource->fY - 1].fPrevious = NULL; //Reseting fPrevious
    }

    if (isValid(aSource->fX + 1, aSource->fY))
    {
        fNodes[aSource->fX + 1][aSource->fY].fPrevious = aSource;
        DFS(&fNodes[aSource->fX + 1][aSource->fY]);
        fNodes[aSource->fX + 1][aSource->fY].fPrevious = NULL; //Reseting fPrevious
    }
    if (isValid(aSource->fX, aSource->fY + 1))
    {
        fNodes[aSource->fX][aSource->fY + 1].fPrevious = aSource;
        DFS(&fNodes[aSource->fX][aSource->fY + 1]);
        fNodes[aSource->fX][aSource->fY + 1].fPrevious = NULL; //Reseting fPrevious
    }
}