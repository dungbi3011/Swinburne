#include "Scenario.h"

void Scenario::BFS(Node* aSource) const
{
    queue<Node*> Search;

    //Marking the source node as visited, preventing revisitation 
    aSource->fVisited = true;

    //Enqueue the source node
    Search.push(aSource);


    // Continue until there are no more nodes to explore
    while (!Search.empty())
    {
        //Get the next node to explore
        Node* temp = Search.front();

        //Remove this node from the queue
        Search.pop();


        //If the current node is the goal, print the path and exit
        if (temp->fColor == 'G')
        {
            //Initializing the path, with stringstream datatype
            stringstream path;

            //Tracking back, storing the path details from the source to this goal node
            printPath(temp, path);

            // Counting number of steps (By converting "path" to istringstream)
            istringstream is(path.str());
            auto numOfSteps = distance(istream_iterator<string>(is), istream_iterator<string>());

            cout << "Number of steps: " << numOfSteps - 4 << endl;
            cout << path.str() << endl;
            cout << "\n";
        }

        //Explore each neighbor of the current node and enqueue if valid (i.e., within bounds and not visited)
        //Set the current node as the predecessor of each valid neighbor to trace the path later

        if (isValid(temp->fX - 1, temp->fY))
        {
            fNodes[temp->fX - 1][temp->fY].fPrevious = temp;
            fNodes[temp->fX - 1][temp->fY].fVisited = true;
            Search.push(&fNodes[temp->fX - 1][temp->fY]);
        }
        if (isValid(temp->fX, temp->fY - 1))
        {
            fNodes[temp->fX][temp->fY - 1].fPrevious = temp;
            fNodes[temp->fX][temp->fY - 1].fVisited = true;
            Search.push(&fNodes[temp->fX][temp->fY - 1]);
        }
        if (isValid(temp->fX + 1, temp->fY))
        {
            fNodes[temp->fX + 1][temp->fY].fPrevious = temp;
            fNodes[temp->fX + 1][temp->fY].fVisited = true;
            Search.push(&fNodes[temp->fX + 1][temp->fY]);
        }
        if (isValid(temp->fX, temp->fY + 1))
        {
            fNodes[temp->fX][temp->fY + 1].fPrevious = temp;
            fNodes[temp->fX][temp->fY + 1].fVisited = true;
            Search.push(&fNodes[temp->fX][temp->fY + 1]);
        }
    }
}