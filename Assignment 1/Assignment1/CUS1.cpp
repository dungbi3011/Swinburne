#include "Scenario.h"


//Custom comparator for the priority queue to prioritize nodes with lower cost
struct compare
{
    bool operator()(const Node* a, const Node* b) { return a->fCost > b->fCost; }
};


//Cost function determining the cost between two nodes based on their color
int cost(Node* a, Node* b)
{
    return (a->fColor == b->fColor) ? 1 : 2;
}

void Scenario::CUS1(Node* aSource) const
{   
    //Priority queue for nodes to explore
    priority_queue<Node*, vector<Node*>, compare> Search;

    //Mark the source node as visited
    aSource->fVisited = true;

    //Set initial cost to 0
    aSource->fCost = 0;

    //Start with the source node
    Search.push(aSource);

    //Continue until there are no nodes left to explore
    while (!Search.empty())
    {
        //Get the node with the lowest cost
        Node* temp = Search.top();

        //Remove it from the priority queue
        Search.pop();


        //Check if the current node is the goal
        if (temp->fColor == 'G')
        {
            //Initializing the path, with stringstream datatype
            stringstream path;

            //Tracking back, storing the path from the source to this goal node
            printPath(temp, path);

            // Counting number of steps (By converting "path" to istringstream)
            istringstream is(path.str());
            auto numOfSteps = distance(istream_iterator<string>(is), istream_iterator<string>());

            cout << "Number of steps: " << numOfSteps - 4 << endl;
            cout << path.str() << endl;
            cout << "\n";
        }
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (abs(i) + abs(j) != 1)  continue;
                  
                //Check if the neighbor is valid (within bounds and not previously visited)
                if (isValid(temp->fX + i, temp->fY + j))
                {
                    //Mark as visited
                    fNodes[temp->fX + i][temp->fY + j].fVisited = true;

                    //Mark as visited
                    fNodes[temp->fX + i][temp->fY + j].fPrevious = temp;

                    //Update the cost to reach this neighbor
                    fNodes[temp->fX + i][temp->fY + j].fCost = temp->fCost + cost(temp, &fNodes[temp->fX + i][temp->fY + j]);

                    //Add to the priority queue for exploration
                    Search.push(&fNodes[temp->fX + i][temp->fY + j]);
                }
            }
        }
    }
}