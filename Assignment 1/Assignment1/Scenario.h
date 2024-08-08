#pragma once

#include "Node.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Scenario
{
public:
	int fN;
	int fM;
	Node fStart;
	vector<Node> fGoal;
	Node** fNodes;

	Scenario(int aN, int aM);
	void print() const;
	bool isValid(int aX, int aY) const;
	int cost(Node* aSource, Node* aDestination) const;
	void printPath(Node* aTail, stringstream& S) const;
	void resetVisited() const;
	void DFS(Node* aSource) const;
	void BFS(Node* aSource) const;
	void GBFS(Node* aSource, Node* aDestination) const;
	void AStar(Node* aSource, Node* aDestination) const;
	void CUS1(Node* aSource) const;
	void CUS2(Node* aSource, Node* aDestination) const;
};
