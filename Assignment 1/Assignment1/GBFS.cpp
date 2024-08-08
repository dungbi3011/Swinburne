#include "Scenario.h"


//This constructor compare node based on the cost
struct compare {

    //Define priority node with a cost
    bool operator()(const Node* a, const Node* b) { return a->fCost > b->fCost; }
};

void Scenario::GBFS(Node* aSource, Node* aDestination) const {

    //Priority queue for node which prioritized with a cost
    priority_queue<Node*, vector<Node*>, compare> pq; 

    //Initialized the cost for the sources node 
    aSource->fCost = cost(aSource, aDestination);
    pq.push(aSource);

    //Marked the sources node as visited
    aSource->fVisited = true;


    //Continues until no nodes left has been visited
    while (!pq.empty()) {

        //Get the nodes with the lowest cost
        Node* temp = pq.top();
        //Remove this node form queue
        pq.pop();


        //Check if the current node is the destination node 
        if (temp->fX == aDestination->fX && temp->fY == aDestination->fY) {

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

        //Check neighboring nodes in all four directions if they are not visited and within bounds
        int tx = temp->fX;
        int ty = temp->fY;

        //Each if condition checks a direction, updates the node's previous pointer, cost, visited status,
        //and adds it to the priority queue for further exploration.

        if (isValid(tx - 1, ty)) {
            fNodes[tx - 1][ty].fPrevious = temp;
            fNodes[tx - 1][ty].fCost = cost(&fNodes[tx - 1][ty], aDestination);
            fNodes[tx - 1][ty].fVisited = true;
            pq.push(&fNodes[tx - 1][ty]);
        }
        if (isValid(tx, ty - 1)) {
            fNodes[tx][ty - 1].fPrevious = temp;
            fNodes[tx][ty - 1].fCost = cost(&fNodes[tx][ty - 1], aDestination);
            fNodes[tx][ty - 1].fVisited = true;
            pq.push(&fNodes[tx][ty - 1]);
        }
        if (isValid(tx + 1, ty)) {
            fNodes[tx + 1][ty].fPrevious = temp;
            fNodes[tx + 1][ty].fCost = cost(&fNodes[tx + 1][ty], aDestination);
            fNodes[tx + 1][ty].fVisited = true;
            pq.push(&fNodes[tx + 1][ty]);
        }
        if (isValid(tx, ty + 1)) {
            fNodes[tx][ty + 1].fPrevious = temp;
            fNodes[tx][ty + 1].fCost = cost(&fNodes[tx][ty + 1], aDestination);
            fNodes[tx][ty + 1].fVisited = true;
            pq.push(&fNodes[tx][ty + 1]);
        }
    }
}