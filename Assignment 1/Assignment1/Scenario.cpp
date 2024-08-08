#include "Scenario.h"

//Initializing the size fN and fM of the node
Scenario::Scenario(int aN, int aM) : fN(aN), fM(aM)
{
    fNodes = new Node * [fN];

    //Defining the nodes
    for (int i = 0; i < fN; i++)
    {
        fNodes[i] = new Node[fM];
        for (int j = 0; j < fM; j++)
        {   
            //Set coordinate X; Y respectively for the node
            fNodes[i][j].fX = i;
            fNodes[i][j].fY = j;
        }
    }
}

//Separating the algorithms' output 
void Scenario::print() const { cout << "-------------------------------------------------------------------------------------\n"; }

//Validating Coordinate Position
bool Scenario::isValid(int aX, int aY) const
{
    if (aX < 0)
    {
        return false;
    }
    if (aX >= fN)
    {
        return false;
    }
    if (aY < 0)
    {
        return false;
    }
    if (aY >= fM)
    {
        return false;
    }
    if (fNodes[aX][aY].fColor == 'W')
    {
        return false;
    }
    if (fNodes[aX][aY].fVisited)
    {
        return false;
    }
    return true;
}

//Reseting the cost & all visted of the nodes
void Scenario::resetVisited() const
{
    for (int i = 0; i < fN; i++)
    {
        for (int j = 0; j < fM; j++)
        {
            fNodes[i][j].fVisited = false;
            fNodes[i][j].fCost = -1;
            fNodes[i][j].fDistance = -1;
            fNodes[i][j].fPrevious = NULL;
        }
    }
}

//Caculating the cost between aSources & aDestination 
int Scenario::cost(Node* aSource, Node* aDestination) const
{   
    //The cost rely on Manhattan distant between 2 node
    return abs(aSource->fX - aDestination->fX) +
        abs(aSource->fY - aDestination->fY);
}
   

//Print th path recursively from the start node by "fPrevious" pointer
void Scenario::printPath(Node* aTail, stringstream& S) const
{
    if (aTail->fPrevious == NULL)
    {
        return;
    }

    //Caculating movements, based on coordinates X;Y
    printPath(aTail->fPrevious, S);
    int dx = aTail->fPrevious->fX - aTail->fX;
    int dy = aTail->fPrevious->fY - aTail->fY;

    int startX = 0;
    int startY = 0;

    if (aTail->fPrevious->fColor == 'R')
    {
        startX = (aTail->fPrevious->fX);
        startY = (aTail->fPrevious->fY);
        S << "[";
    }

    //Determining the directions
    if (dx == -1)
        S << "'down'";
    else if (dx == 1)
        S << "'up'";
    else if (dy == 1)
        S << "'left'";
    else if (dy == -1)
        S << "'right'";

    if (aTail->fColor == 'G')
        S << "]\nGoal: <Node (" << aTail->fY << ", " << aTail->fX << ")>";
    else
        S << ", ";
}