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
    int visited; // is this edge visited?
} edge_t;

typedef struct node_s
{
    int * linked; // linked nodes index
    int nbEdges; // number of linked edges
    int value;
} node_t;

edge_t ** edges;
node_t ** nodes;
int n; // number of colors
int m; // number of beads

void getNodes()
{
    n = 0;
    // set n, nodes[n]->nbEdges and nodes[n]->value
    FOR(i, m)
    {
        // node1
        int newNode = 1;
        FOR(j, n)
            if(edges[i]->node1 == nodes[j]->value)
            {
                newNode = 0;
                break;
            }
        if(newNode)
        {
            nodes[n] = new node_t;
            nodes[n]->nbEdges = 1;
            nodes[n++]->value = edges[i]->node1;
        }
        // node2
        newNode = 1;
        FOR(j, n)
            if(edges[i]->node2 == nodes[j]->value)
            {
                newNode = 0;
                break;
            }
        if(newNode)
        {
            nodes[n] = new node_t;
            nodes[n]->nbEdges = 1;
            nodes[n++]->value = edges[i]->node2;
        }
    }
    // set nodes[i]->linked
    FOR(i, n)
        nodes[i]->linked = new int[nodes[i]->nbEdges];
    FOR(i, n)
        nodes[i]->nbEdges = 0;
    FOR(i, m)
        FOR(j, n)
            //if(edges[i]->node1 == edges[i]->node2 && nodes[j]->value == edges[i]->node1)
            //    nodes[j]->linked[nodes[j]->nbEdges++] = edges[i]->node2;
            //else
            if(edges[i]->node1 != edges[i]->node2)
            {
                if(nodes[j]->value == edges[i]->node1)
                    nodes[j]->linked[nodes[j]->nbEdges++] = edges[i]->node2;
                if(nodes[j]->value == edges[i]->node2)
                    nodes[j]->linked[nodes[j]->nbEdges++] = edges[i]->node1;
            }
}

/* return number of odds
 */
int getOdd(int * odd)
{
    int nbOdds = 0;
    FOR(i, n)
    {
        if(nodes[i]->nbEdges < 2)
            return -1;
        if(nodes[i]->nbEdges % 2 == 1)
        {
            if(nbOdds > 2)
                return 3;
            else if(nbOdds++ == 0)
                *odd = i;
        }
    }
    return nbOdds;
}

/* Find a loop in graph using backtracking algorithm
 */
void loopBacktracking(list<int> loop, int start)
{
    loop.push_back(start);
}

/* Solve The Necklace
** https://icpcarchive.ecs.baylor.edu/external/20/2036.pdf
*/
int main(void)
{
    int nbTests;
    cin >> nbTests;
    FOR(t, nbTests)
    {
        // input
        cin >> m;
        edges = new edge_t*[m];
        FOR(i, m)
            edges[i] = new edge_t;
        FOR(i, m)
        {
            cin >> edges[i]->node1;
            cin >> edges[i]->node2;
            edges[i]->visited = 0;
        }
        nodes = new node_t*[m * 2];
        getNodes();
#ifdef DEBUG
        cout << "nbRings: " << n << endl;
        FOR(i, m)
            cout << "edge" << i << ": [" << edges[i]->node1 << "," << edges[i]->node2 << "]" << endl;
        FOR(i, n)
        {
            cout << "node " << i << ": value: " << nodes[i]->value << ", [";
            FOR(j, nodes[i]->nbEdges)
                cout << nodes[i]->linked[j] << ",";
            cout << "]" << endl;
        }
#endif
        // algorithm
        int odd = 0;
        int nbOdds = getOdd(&odd);
        cout << "Case #" << t << endl;
        if(nbOdds != 0 && nbOdds != 2)
            cout << "some beads may be lost" << endl;
        else
        {
            list<int> loop;
            loopBacktracking(loop, odd);
            cout << "Don't forget to link [x,x] edges at the end !" << endl;
        }
        cout << endl;
        // free
        FOR(i, n)
            delete[] nodes[i]->linked;
        FOR(i, n)
            delete nodes[i];
        FOR(i, m)
            delete edges[i];
        delete[] nodes;
        delete[] edges;
    }
    return 0;
}
