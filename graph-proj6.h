#ifndef GRAPH_PROJ6_H
#define GRAPH_PROJ6_H

#include <vector>
#include <map>
#include <list>
#include <cassert>
#include "arrayheap-student-proj6.h"

using namespace std;

/* The Edge class represents an edge in a sparse (adjacency list) Graph. It
 * tells the vertex that the edge leads to, and the cost of the edge.
 */
struct Edge {
    public:
        Edge(int aTo = 0, int aCost = 0) : to(aTo), cost(aCost) {}
        int to;
        int cost;
};

/* The Graph class represents a set of vertices and directed, weighted edges
 * between those vertices. The cost of each edge is given by an integer value,
 * and the special value INFINITE_COST is a large number which represents an
 * impossible cost. We assume that no real path in the graph has a total cost of
 * INFINITE_COST or more.
 *
 * This Graph class uses an edge list format, meaning that there is a vector of
 * lists of Edge objects, and if an edge exists between two vertices, then it
 * will be listed in the inner list of the vertex the edge leaves from. If there
 * is NO connection from vertex A to vertex B, then this is represented by the
 * absence of an edge from A to B (and NOT by the inclusion of an edge of cost
 * INFINITE_COST). Remember that the adjacency list representation does not keep
 * track of non-existent edges.
 *
 * The constructor makes a graph with enough space for the given number of
 * vertices. No edges are present in the graph at this point.
 *
 * The addEdge method adds an edge connecting (from -> to) with the given cost.
 *
 * The dijkstra method is the classical Dijkstra's shortest path algorithm,
 * which starts at the given source vertex and finds the shortest paths to all
 * other vertices in the graph. The method will return a vector that lists the
 * shortest path cost of going from the source vertex to each vertex in the
 * graph. The cost of going from a vertex to itself is always 0. If a vertex is
 * not reachable, then the distance to it should be >= INFINITE_COST.
 *
 * The inVertexRange method checks that the given index is within the
 * appropriate range for accessing vertices.
 *
 * The adjacencyList data member is a sparse representation of the edges in the
 * graph. It is a vector of lists of Edge objects. If an edge exists between
 * vertex i to vertex j, then edgeList[i] will have an Edge object that points
 * to vertex j, with an associated cost. If there is no edge between them,
 * then edgeList[i] will not have an Edge object that points to j.
 *
 * The copy constructor and operator= methods are off limits for this data
 * structure.
 */
class Graph {
    public:
        enum { INFINITE_COST = 1000000000 };

        Graph(unsigned int numVertices) : adjacencyList(numVertices) {}

        void addEdge(int from, int to, int cost);

        vector<int> dijkstra(int source) const;

        bool inVertexRange(unsigned int ndx) const {
            return (0 <= ndx) && (ndx < adjacencyList.size());
        }

    private:
        Graph(const Graph &) { assert(false); }
        const Graph &operator=(const Graph &) { assert(false); return *this; }

        vector<list<Edge>> adjacencyList;
};

void Graph::addEdge(int from, int to, int cost) {
    Edge newEdge(to, cost);
    adjacencyList.at(from).push_back(newEdge);
}

vector<int> Graph::dijkstra(int source) const {
    // Distance store final distance
    vector<int> distance;
    vector<bool> visited;
    // Distance, vertex
    pair<int,int> path;
    // Heap of different paths
    ArrayHeap<pair<int,int>> heap;
    // Map holds (vertex, location in data)
    map<int,int> storedAt;

    // Set all vertices to INF_COST and false
    for (int i = 0; i < adjacencyList.size(); i++) {
        distance.push_back(INFINITE_COST);
        visited.push_back(false);
    }

    // Distance from source to itself = 0
    distance.at(source) = 0; //
    path.first = source;         // FIRST = VERTEX
    path.second = 0;            // SECOND = DISTANCE

    // Push first vertex and store index in data
    storedAt.insert(pair<int,int>(0, heap.insert(path)));

    // Push first to stack then pop stack, then check all of popped nodes neighbors.
    // If new shortest path is found update shortest path and put back in heap.

    // Find shortest path FROM A VERTEX
    while (heap.getNumItems() != 0) {
        // Pop item from heap
        path = heap.getMinItem();
        heap.removeMinItem();

        // Update distance because you know it is the shortest distance
        distance.at(path.first) = path.second;
        visited.at(path.first) = true;

        // From vertex, check all other paths
        for (list<Edge>::const_iterator it = adjacencyList.at(path.first).begin();
        it != adjacencyList.at(path.first).end(); it++) {

            // If not on heap put on heap
            // IsOnHeap()
            if (!heap.isOnHeap(storedAt[path.first])) {
                storedAt.insert(pair<int,int>(path.first, heap.insert(path)));
            }

            // Calculate current distance + distance to next vertex
            int newDistance = path.second + it->cost;

            // If shorter length update
            // ChangeKey()
            if (newDistance < distance.at(path.first)) {
                path.second = newDistance;
                heap.changeItemAtKey(storedAt[path.first], path);
                distance.at(path.first) = newDistance;
            }
        }
    }

    return distance;
}

#endif

