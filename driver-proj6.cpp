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
#include "arrayheap-student-proj6.h"
using namespace std;

int main() {
    /*
     * STORE NUMBER OF LINES
     * PROCESS DELAY TIMES
     * THEN INITIALIZE GRAPH
     * DONT END IF NON-VALID MACHINE IS FOUND
     */

    // Read in number of machines
    int numMachines = 0;
    cin >> numMachines;
    int numServers = 0;

    // Map is used like enum
    map<string, int> vertices;
    // Store Connections in 'graph'
    vector<list<pair<string,int>>> connection(numMachines);

    /*
     * ONLY READ IN VERTEX (DW AB CONNECTIONS)
     * 1. Once all vertices are in map, then you can connect location to location
     *    using integer values
     * 2. NON-SYSTEM CAN ONLY RECEIVE CONNECTION
     * 3. USE FIND TO
     *
     * Driver is very simple don't overthink it
     */
    cout << "ESTABLISHING VERTICES:" << endl;
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
        cout << from << " " << vertices[from] << endl;
        connection.at(vertices[from]).push_back(pair<string,int>(to, cost));
    }
    cout << endl;

    // Graph to store path
    Graph network(numServers);

    int sumPath = 0;

    // Process each vertex
    cout << "PROCESS IN ALPHABETICAL ORDER:" << endl;
    for (map<string,int>::const_iterator it = vertices.begin(); it != vertices.end(); it++) {
        cout << it->first << " " << it->second << endl;

        // Add each edge to vertices
        for (list<pair<string,int>>::const_iterator con = connection.at(it->second).begin();
             con != connection.at(it->second).end(); con++) {
            network.addEdge(it->second, vertices[con->first], con->second);
        }

        vector<int> shortestPath = network.dijkstra(it->second);
        for (int i = 0; i < shortestPath.size(); i++) {
            sumPath += shortestPath.at(i);
        }
        cout << "SUM OF PATH: " << sumPath << endl;
    }
    cout << endl;

    //



    return 0;
}
