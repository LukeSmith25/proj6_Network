/**
 * file: driver-proj6.cpp
 * author: Luke Smith
 * course: CSI 3334
 * assignment: project 6
 * due date: December 4, 2022
 *
 * Driver for implementing the network system.
 */

#include <iostream>
#include "graph-proj6.h"
#include "arrayheap-prof-proj6.h"
using namespace std;

int main() {
    /*
     * STORE NUMBER OF LINES
     * PROCESS DELAY TIMES
     * THEN INITIALIZE GRAPH
     * DONT END IF NON-VALID MACHINE IS FOUND
     */

    // Read in number of machines
    int numMachines;
    cin >> numMachines;
    int numServers;

    // Map is used like enum
    map<string, int> vertices;
    // Store Connections in 'graph'
    vector<list<pair<string,int>>> connection(numMachines);

    /*
     * ONLY READ IN VERTEX (DW AB CONNECTIONS)
     * 1. Once all vertices are in map, then you can connect location to location
     *    using integer values
     *
     * Driver is very simple don't overthink it
     */
    for (int i = 0; i < numMachines; i++) {
        string from, to;
        int cost = 0;

        // Read in vertex
        cin >> from;
        if (vertices.find(from) == vertices.end()) {
            if (from.find("_server")) {
                vertices.insert(pair<string,int>(from, i));
                numServers++;
            }
        }

        // Read in Connection
        cin >> to;
        cin >> cost;
        cout << vertices[from] << endl;
        connection.at(vertices[from]).push_back(pair<string,int>(to, cost));
    }

    // Graph to store path
    Graph network(numServers);




    return 0;
}
