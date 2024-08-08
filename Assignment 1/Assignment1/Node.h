#pragma once

#ifndef NULL
#define NULL nullptr
#endif

class Node {
public:
	int fX;
	int fY;
	unsigned int fCost;
	unsigned int fDistance;
	char fColor;
	bool fVisited;
	Node* fPrevious;

	Node(int aX = -1, int aY = -1, char aColor = '0');
};
