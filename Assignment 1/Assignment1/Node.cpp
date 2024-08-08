#include "Node.h"

//Initializing the Node class
Node::Node(int aX, int aY, char aColor) : fX(aX), fY(aY), fCost(-1), fDistance(-1), fColor(aColor), fVisited(false), fPrevious(NULL) {};