#include <iostream>
#include <string.h>
#include <climits>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

//#define DEBUG			1

using namespace std;

typedef struct city_s
{
    int x;
    int y;
    int val;
} city_t;

inline int sq(int x)
{
    return(x * x);
}

inline int dist(city_t * a, city_t * b)
{
	return(sq(a->x - b->x) + sq(a->y - b->y));
}

void setNetwork(city_t ** cities, int * network, int n)
{
    int val = cities[network[0]]->val;
    FOR3(1, i, n)
        cities[network[i]]->val = val;
}

int arbreCouvrantDePoidMin(city_t ** cities, int n, int cost)
{
    FOR(i, n - 1)
    {
        int min = 0;
        int d;
        int bestJ = 0;
        int bestK = 0;
        FOR(j, n)
            FOR(k, n)
                if(j != k)
                    if(cities[j]->val != cities[k]->val)
                        if((d = dist(cities[j], cities[k])) < min || min == 0)
                        {
                            min = d;
                            bestJ = j;
                            bestK = k;
                        }
        cities[bestK]->val = cities[bestJ]->val;
        cost += dist(cities[bestK], cities[bestJ]);
    }
    return cost;
}

/* Solve Buy or Build problem
** https://icpcarchive.ecs.baylor.edu/external/35/3505.pdf
*/
int main(void)
{
    // cities
    city_t ** cities;
    int nbCities;
    // networks
    int ** networks;
    int * netCosts;
    int * netSizes;

	int nbExos;
    cin >> nbExos;
	FOR(exo, nbExos)
	{
		int nbNetworks;
		cin >> nbCities >> nbNetworks;
        cities = new city_t*[nbCities];
        networks = new int*[nbNetworks];
        netCosts = new int[nbNetworks];
        netSizes = new int[nbNetworks];
		// init subnetworks
		FOR(i, nbNetworks)
        {
            cin >> netSizes[i];
            cin >> netCosts[i];
            networks[i] = new int[netSizes[i]];
            FOR(j, netSizes[i])
            {
                cin >> networks[i][j];
                networks[i][j]--;
            }
        }
        // init cities
        FOR(i, nbCities)
        {
            cities[i] = new city_t;
            cin >> cities[i]->x >> cities[i]->y;
            cities[i]->val = i;
        }
#ifdef DEBUG
		printf("nbCities: %d, nbNetworks: %d\n", nbCities, nbNetworks);
		FOR(i, nbNetworks)
        {
            cout << "cost:" << netCosts[i] << " [";
            FOR(j, netSizes[i])
                cout << networks[i][j] << ",";
            cout << "]" << endl;
        }
        FOR(i, nbCities)
            cout << cities[i]->x << " " << cities[i]->y << endl;
		printf("\n");
#endif
        int minCost = arbreCouvrantDePoidMin(cities, nbCities, 0);
        // use a network
        FOR(i, nbNetworks)
        {
            // reset cities values
            FOR(j, nbCities)
                cities[j]->val = j;
            setNetwork(cities, networks[i], netSizes[i]);
            int tmp;
            if((tmp = arbreCouvrantDePoidMin(cities, nbCities, netCosts[i])) < minCost)
                minCost = tmp;
        }
        cout << minCost << endl << endl;
		// clean
        FOR(i, nbCities)
            delete cities[i];
		delete[] cities;
        FOR(i, nbNetworks)
            delete[] networks[i];
        delete[] netCosts;
        delete[] netSizes;
		delete[] networks;
	}
    return 0;
}
