#include <iostream>
#include <string.h>
#include <list>
#include <climits>

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
list<int> treeFired;
list<int> bestFired;
int nb_fire = INT_MAX;

/* value must be equal to node->value */
void networkChangeValue(node_t * node, int newValue, int value)
{
    if(node->value == -1 || node->value != value)
        return;
    node->value = newValue;
    FOR(i, node->nbEdges)
        networkChangeValue(nodes[node->edges[i]], newValue, value);
}

int loopExists()
{
    int networkValue = 0;
    // init graph
    FOR(i, n)
        nodes[i]->value = -1;
    FOR(i, m)
    {
        int tmp1 = nodes[edges[i]->node1]->value;
        int tmp2 = nodes[edges[i]->node2]->value;
        if(tmp1 != -1 && tmp1 == tmp2)
            return 1;
        if(tmp1 == -1 && tmp2 == -1)
        {
            nodes[edges[i]->node1]->value = networkValue;
            nodes[edges[i]->node2]->value = networkValue++;
            continue;
        }
        if(tmp1 == -1)
        {
            nodes[edges[i]->node1]->value = nodes[edges[i]->node2]->value;
            continue;
        }
        if(tmp2 == -1)
        {
            nodes[edges[i]->node2]->value = nodes[edges[i]->node1]->value;
            continue;
        }
        networkChangeValue(nodes[edges[i]->node1], nodes[edges[i]->node2]->value, nodes[edges[i]->node1]->value);
    }
    return 0;
}

int update_values(int * nodes_val_save)
{
    int nbPos = 0;
    FOR(i, n)
        if(nodes_val_save[i] == 0)
            FOR(j, nodes[i]->nbEdges)
            {
                nodes[nodes[i]->edges[j]]->value = 1;
                nbPos++;
            }
    return nbPos;
}

void fire(int treeIdx)
{
#ifdef DEBUG
    cout << "[";
    for(std::list<int>::iterator it = treeFired.begin(); it != treeFired.end(); it++)
        cout << *it << ",";
    cout << "]" << endl;
#endif
    // attention, ne prend pas en compte l'ordre lexicographique
    if((int)treeFired.size() >= nb_fire)
        return;
    int * nodes_val_save = new int[n];
    // saving
    FOR(i, n)
        nodes_val_save[i] = nodes[i]->value;
    FOR(i, n)
        nodes[i]->value = 0;
    treeFired.push_back(treeIdx);
    nodes_val_save[treeIdx] = 0;
    int nbPos = update_values(nodes_val_save);
    cout << nbPos << endl;
    // aucune position n'est possible pour le monkey
    if(nbPos == 0)
    {
        // attention, ne prend pas en compte l'ordre lexicographique
        if(nbPos < nb_fire)
        {
            nb_fire = nbPos;
            // copy treeFired in bestFired
            bestFired.clear();
            for(std::list<int>::iterator it = treeFired.begin(); it != treeFired.end(); it++)
                bestFired.push_back(*it);
        }
    }
    else if(nbPos != n)
    {
        FOR(i, n)
            fire(i);
    }
    treeFired.pop_back();
    // charging
    FOR(i, n)
        nodes[i]->value = nodes_val_save[i];
    delete[] nodes_val_save;
}

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
            nodes[i] = new node_t;
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
        cout << endl << "nbNodes: " << n << endl << "nbEdges: " << m << endl;
        FOR(i, m)
            cout << "edge " << i << ": [" << edges[i]->node1 << "," << edges[i]->node2 << "] size: " << endl;
        FOR(i, n)
        {
            cout << "node " << i << ": value: " << nodes[i]->value << ", [";
            FOR(j, nodes[i]->nbEdges)
                cout << nodes[i]->edges[j] << ",";
            cout << "]" << endl;
        }
#endif
        // algorithm
        if(loopExists())
        {
            cout << "Impossible" << endl;
            continue;
        }
        // Brute force
        FOR(i, n)
            nodes[i]->value = 1;
        FOR(i, n)
            fire(i);
        cout << bestFired.size() << ":";
        for(std::list<int>::iterator it = bestFired.begin(); it != bestFired.end(); it++)
            cout << " " << *it;
        cout << endl;
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
