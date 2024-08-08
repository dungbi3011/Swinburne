#include "Scenario.h"

//Custom comparator for prioritizing nodes in the priority queue based on their cost and heuristic distance
struct compare
{

    bool operator()(const Node* a, const Node* b)
    {   
        //Prioritize by the sum of actual cost from the start and the heuristic estimate to the goal
        return (a->fCost + a->fDistance) > (b->fCost + b->fDistance);
    }
};

void Scenario::AStar(Node* aSource, Node* aDestination) const
{   
    //Priority queue to manage nodes during search
    priority_queue<Node*, vector<Node*>, compare> pq;

    //Initialize the source node with the heuristic cost to the destination, set its distance to 0, and mark as visited
    aSource->fCost = cost(aSource, aDestination);
    aSource->fDistance = 0;
    aSource->fVisited = true;

    //Add the source node to the priority queue
    pq.push(aSource);

    //Direction vectors for exploring orthogonal neighbors (up, down, left, right)
    int dx[] = { -1, 0, 1, 0 };
    int dy[] = { 0, -1, 0, 1 };


    //Continue until there are no more nodes to explore
    while (!pq.empty())
    {
        //Current node being explored
        Node* temp = pq.top();

        //Remove it from the priority queue
        pq.pop();

        //Check if the current node is the destination
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
            return;
        }

        // Explore all valid orthogonal neighbors, update their cost, distance, and visited status, and add them to the queue
  
        for (int i = 0; i < 4; i++)
        {
            int tx = temp->fX + dx[i];
            int ty = temp->fY + dy[i];

            if (isValid(tx, ty) && !fNodes[tx][ty].fVisited)
            {
                fNodes[tx][ty].fPrevious = temp;
                fNodes[tx][ty].fDistance = temp->fDistance + 1;
                fNodes[tx][ty].fCost = cost(&fNodes[tx][ty], aDestination);
                fNodes[tx][ty].fVisited = true;
                pq.push(&fNodes[tx][ty]);
            }
        }
    }
}