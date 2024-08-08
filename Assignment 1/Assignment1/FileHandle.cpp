#include "FileHandle.h"
#include <stdio.h>


Scenario* readFile(char* aFileName) {

    FILE* fptr;

    // Attempt to open the file; fopen_s is safer than fopen, reducing the risk of buffer overflows
    errno_t err = fopen_s(&fptr, aFileName, "r");
    if (err != 0) {
        printf("Failed to open file %s. Exiting... \n", aFileName);
        return NULL;
    }

    int N, M;
    char line[32];
    char lineG[256];

    // Read and parse the first line for N and M values (line 1 - txt file)
    if (fgets(line, 32, fptr) == NULL) {
        printf("N and M values are missing. Exiting ...\n");
        return NULL;
    }
    vector<int> argV = readLine(line, 32);
    N = argV[0];
    M = argV[1];
    Scenario* scenario = new Scenario(N, M);


    // Read and set the initial state (line 2 - txt file)
    if (fgets(line, 32, fptr) == NULL) {
        printf("Initial state missing. Exiting ...\n");
        return NULL;
    }
    argV = readLine(line, 32);
    scenario->fStart = Node(argV[1], argV[0], 'R');
    scenario->fNodes[argV[1]][argV[0]].fColor = 'R';


    // Read and set goal states (line 3 - txt file)
    if (fgets(lineG, 256, fptr) == NULL) {
        printf("Goal state missing. Exiting ...\n");
        return NULL;
    }
    argV = readLine(lineG, 256);
    // Loop to process multiple goals, if present (line 3 - txt file)
    for (int i = 0; i < argV.size(); i += 2) {
        scenario->fGoal.push_back(Node(argV[i + 1], argV[i], 'G'));
        scenario->fNodes[argV[i + 1]][argV[i]].fColor = 'G';  
    }


    // Read and mark obstacles (line 4 -> end - txt file)
    while (fgets(line, 32, fptr) != NULL) {
        argV = readLine(line, 32);
        for (int i = 0; i < argV[3]; i++) {
            for (int j = 0; j < argV[2]; j++) {
                //Checking if the location of the goals and the wall are duplicated
                if (scenario->fNodes[argV[1] + i][argV[0] + j].fColor == 'G') {
                    printf("Goal: Node< (%d, %d)> is unreachable.\n\n-------------------------------------------------------------------------------------\n",
                        argV[0] + j, argV[1] + i);
                }
                //Process Wall
                scenario->fNodes[argV[1] + i][argV[0] + j].fColor = 'W';
            }
        }
    }

    fclose(fptr);

    return scenario;
}

// Helper function to parse a line of text into a vector of integers
vector<int> readLine(char* aLine, int aLength) {
    vector<int> args;
    int i = 0;
    int sum = 0;
    bool start = false;

    // Loop through each character in the line
    while (i < aLength) {

        // Check if the current character is a digit
        if (aLine[i] >= '0' && aLine[i] <= '9') {
            if (!start)
                start = true;
            sum *= 10;
            sum += aLine[i] - '0';
        }

        // Check if the current character is not a digit, indicating the end of the current integer
        if (!(aLine[i] >= '0' && aLine[i] <= '9') && start) {
            args.push_back(sum);
            start = false;
            sum = 0;
        }

        // Break the loop if the newline character is encountered
        if (aLine[i] == '\n') break;

        i++;
    }

    return args;
}


