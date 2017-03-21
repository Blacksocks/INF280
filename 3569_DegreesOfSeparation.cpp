#include <iostream>
#include <string.h>
#include <climits>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

#define DEBUG			1
#define MAX				INT_MAX / 2

using namespace std;

int * links;
int nbPersons;

inline int get(int x, int y)
{
	return links[y * nbPersons + x];
}

inline void set(int x, int y, int value)
{
	links[y * nbPersons + x] = value;
}

/* Floyed Warshall Algoruthm describe into:
**	https://a3nm.net/work/teaching/2016-2017/inf280/3/graph.pdf
*/
void FloydWarshall()
{
	FOR(k, nbPersons)
		FOR(i, nbPersons)
			FOR(j, nbPersons)
				set(i, j, min(get(i, j), get(i, k) + get(k, j)));
}

/* Solve Degrees of Separation
** https://icpcarchive.ecs.baylor.edu/external/35/3569.pdf
*/
int main(void)
{
	int networkNb = 1;
	while(1)
	{
		int nbLinks;
		cin >> nbPersons >> nbLinks;
		if(nbPersons == 0)
			return 0;
		links = new int[nbPersons * nbPersons];
		string * names = new string [nbPersons];
		int idx1 = 0;
		int idx2 = 0;
		int currentIdx = 0;
		string name1;
		string name2;
		// init links matrix
		FOR(i, nbPersons)
			FOR(j, nbPersons)
				set(i, j, MAX);
		// get links
		FOR(i, nbLinks)
		{
			cin >> name1 >> name2;
			// does the names list already contains the name
			int count = 0;
			idx1 = currentIdx;
			idx2 = currentIdx;
			FOR(j, currentIdx)
			{
				if(names[j] == name1)
				{
					idx1 = j;
					if(count == 1) break;
					else count++;
				}
				if(names[j] == name2)
				{
					idx2 = j;
					if(count == 1) break;
					else count++;
				}
			}
			// the name is new
			if(idx1 == currentIdx)
			{
				if(idx2 == currentIdx++)
					idx2 = currentIdx;
				names[idx1] = name1;
			}
			if(idx2 >= currentIdx)
			{
				names[idx2] = name2;
				currentIdx++;
			}
			// set link
			set(idx1, idx2, 1);
			set(idx2, idx1, 1);
		}
#ifdef DEBUG
		printf("nbPersons: %d, nbLinks: %d\n", nbPersons, nbLinks);
		FOR(i, nbPersons)
			FOR(j, nbPersons)
				if(get(i, j) < MAX)
					cout << i << "," << j << " " << names[i] << "->" << names[j] << endl;
		printf("\n");
#endif
		FloydWarshall();
#ifdef DEBUG
		printf("Links:\n");
		FOR(i, nbPersons)
			FOR(j, nbPersons)
				
#endif
		int max = 0;
		int disconnected = 0;
		FOR(i, nbPersons * nbPersons)
		{
			if(links[i] == MAX)
			{
				printf("Network %d: DISCONNECTED\n\n", networkNb);
				disconnected = 1;
				break;
			}
			if(max < links[i])
				max = links[i];
		}
		if(!disconnected)
			printf("Network %d: %d\n\n", networkNb, max);
		networkNb++;
		// clean
		delete[] names;
		delete[] links;
	}
    return 0;
}
