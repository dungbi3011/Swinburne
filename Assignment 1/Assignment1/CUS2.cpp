#include "Scenario.h"

void Scenario::CUS2(Node* aSource, Node* aDestination) const
{   
    //Custom comparison function for sorting nodes based on the sum of their cost and distance
    auto comp = [](const Node* a, const Node* b)
    {
        return (a->fCost + a->fDistance) > (b->fCost + b->fDistance);
    };

    //Open list to store nodes that are yet to be explored
    std::vector<Node*> openList;

    //Start with the source node
    openList.push_back(aSource);

    // Continue until there are no nodes left to explore
    while (!openList.empty())
    {   
        //Index of the node with the minimum cost + distance
        int Minimum = 0;
        for (int i = 1; i < openList.size(); i++)
        {
            if ((openList[i]->fCost + openList[i]->fDistance) < (openList[Minimum]->fCost + openList[Minimum]->fDistance))
            {
                Minimum = i;
            }
        }

        //Node with the minimum cost + distance
        Node* temp = openList[Minimum];

        //Remove it from the open list
        openList.erase(openList.begin() + Minimum);

        //Mark the node as visited
        temp->fVisited = true;

        //Check if the current node is the destination node
        if (temp->fX == aDestination->fX && temp->fY == aDestination->fY)
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
            break;
        }

        int tx = temp->fX;
        int ty = temp->fY;

        //Lambda function to attempt pushing valid neighboring nodes onto the open list
        auto Push = [&](int dx, int dy)
        {
            if (isValid(tx + dx, ty + dy))
            {
                Node& neighbor = fNodes[tx + dx][ty + dy];
                if (!neighbor.fVisited)
                {   
                    //Set the current node as the predecessor of the neighbor
                    neighbor.fPrevious = temp;

                    //Increment the distance for the neighbor
                    neighbor.fDistance = temp->fDistance + 1;

                    //Calculate cost for the neighbor
                    neighbor.fCost = cost(&neighbor, aDestination);

                    //Add the neighbor to the open list
                    openList.push_back(&neighbor);
                }
            }
        };

        //Attempt to push all valid neighbors onto the open list
    
        //Up
        Push(-1, 0); 

        //Left
        Push(0, -1);

        //Down
        Push(1, 0); 

        //Right
        Push(0, 1); 
    }
}