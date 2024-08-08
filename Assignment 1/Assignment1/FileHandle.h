#pragma once
#include "Scenario.h"

#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

vector<int> readLine(char* aLine, int aLength);
Scenario* readFile(char* aFileName);

