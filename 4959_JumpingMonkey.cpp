#include <iostream>
#include <string.h>
#include <list>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

#define DEBUG			1

using namespace std;

typedef struct edge_s
{
    int node1; // start node
    int node2; // node pointed
} edge_t;

typedef struct node_s
{
    int * edges; // linked edges index
    int nbEdges; // number of linked edges
    int value;
} node_t;

int n; // number of nodes
int m; // number of edges
edge_t ** edges; // graph edges
node_t ** nodes; // graph nodes

/* Solve Jumping Monkey
** https://icpcarchive.ecs.baylor.edu/external/20/2036.pdf
*/
int main(void)
{
    while(1)
    {
        // input
        cin >> n >> m;
        if(n == 0)
            return 0;
        nodes = new node_t*[n];
        edges = new edge_t*[m];
        FOR(i, n)
        {
            nodes[i] = new node_t;
            nodes[i]->value = 0;
        }
        FOR(i, m)
            edges[i] = new edge_t;
        FOR(i, m)
            cin >> edges[i]->node1 >> edges[i]->node2;
        // set node nbEdges
        FOR(i, n)
            nodes[i]->nbEdges = 0;
        FOR(i, m)
            nodes[edges[i]->node1]->nbEdges++;
        FOR(i, m)
            nodes[edges[i]->node2]->nbEdges++;
        // set node edges
        FOR(i, n)
            nodes[i]->edges = new int[nodes[i]->nbEdges];
        FOR(i, n)
            nodes[i]->nbEdges = 0;
        FOR(i, m)
        {
            node_t * node = nodes[edges[i]->node1];
            node->edges[node->nbEdges++] = edges[i]->node2;
            node = nodes[edges[i]->node2];
            node->edges[node->nbEdges++] = edges[i]->node1;
        }
#ifdef DEBUG
        cout << "nbNodes: " << n << endl << "nbEdges: " << m << endl;
        FOR(i, m)
            cout << "edge " << i << ": [" << edges[i]->node1 << "," << edges[i]->node2 << "] size: " << endl;
        FOR(i, n)
        {
            cout << "node " << i << ": value: " << nodes[i]->value << ", [";
            FOR(j, nodes[i]->nbEdges)
                cout << nodes[i]->edges[j] << ",";
            cout << "]" << endl;
        }
        cout << endl;
#endif
        // algorithm

        // free
        FOR(i, n)
            delete[] nodes[i]->edges;
        FOR(i, n)
            delete nodes[i];
        FOR(i, m)
            delete edges[i];
        delete[] nodes;
        delete[] edges;
    }
    return 0;
}
