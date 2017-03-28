#include <iostream>
#include <string.h>
#include <list>
#include <climits>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

//#define DEBUG			1

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
list<int> treeConfig;
list<int> bestConfig;
list<long> monkeyPrevPos;
int nb_fire;

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

void update_values(long * monkeyNextPos, long monkeyCurrPos)
{
    FOR(i, n)
        if((monkeyCurrPos & ((long)1 << i)) != 0)
            FOR(j, nodes[i]->nbEdges)
                *monkeyNextPos |= (long)1 << nodes[i]->edges[j];
}

void fire(int treeIdx, long monkeyPos)
{
#ifdef DEBUG
    cout << "=== treeIdx:" << treeIdx << " ===" << endl;
    cout << "monkeyPos:          ";
    FOR(i, n)
        cout << (((monkeyPos & ((long)1 << i)) != 0) ? '1' : '0') << " ";
    cout << endl;
#endif
    // attention, ne prend pas en compte l'ordre lexicographique
    if((int)treeConfig.size() >= nb_fire)
        return;
    long monkeySavePos = monkeyPos & ~((long)1 << treeIdx);
    monkeyPos = 0;
    treeConfig.push_back(treeIdx);
#ifdef DEBUG
    cout << "treeConfig: ";
    for(std::list<int>::iterator it = treeConfig.begin(); it != treeConfig.end(); it++)
        cout << *it << " ";
    cout << endl;
#endif
    update_values(&monkeyPos, monkeySavePos);
    int stop = 0;
    for(std::list<long>::iterator it = monkeyPrevPos.begin(); it != monkeyPrevPos.end(); it++)
        if(monkeyPos == *it)
            stop = 1;
    monkeyPrevPos.push_back(monkeyPos);
    #ifdef DEBUG
        cout << "monkeyPREVposADDED: ";
        FOR(i, n)
            cout << (((monkeyPos & ((long)1 << i)) != 0) ? '1' : '0') << " ";
        cout << endl;
    #endif
    // this solution doesn't end
    if(stop);
    // aucune position n'est possible pour le monkey
    else if(monkeyPos == 0)
    {
        // attention, ne prend pas en compte l'ordre lexicographique
        if((int)treeConfig.size() < nb_fire)
        {
            nb_fire = (int)treeConfig.size();
#ifdef DEBUG
            cout << "new nb_fire: " << nb_fire << endl;
#endif
            // copy treeConfig in bestConfig
            bestConfig.clear();
            for(std::list<int>::iterator it = treeConfig.begin(); it != treeConfig.end(); it++)
                bestConfig.push_back(*it);
        }
    }
    // toutes les positions sont envisageables pour la position du monkey
    else if(((long)1 << n) - 1 != monkeyPos)
    {
        int nbMonkeySavePrevPos = monkeyPrevPos.size();
        FOR(i, n)
            fire(i, monkeyPos);
        while((int)monkeyPrevPos.size() > nbMonkeySavePrevPos)
            monkeyPrevPos.pop_back();
    }
    treeConfig.pop_back();
    // charging
    monkeyPos = monkeySavePos;
}

/* Solve Jumping Monkey
** https://icpcarchive.ecs.baylor.edu/external/20/2036.pdf
*/
int main(void)
{
    while(1)
    {
#ifdef DEBUG
        cout << endl << "======================" << endl;
#endif
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
        nb_fire = INT_MAX;
        FOR(i, n)
            nodes[i]->value = 1;
        FOR(i, n)
            fire(i,((long)1 << n) - 1);
        cout << bestConfig.size() << ":";
        for(std::list<int>::iterator it = bestConfig.begin(); it != bestConfig.end(); it++)
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
