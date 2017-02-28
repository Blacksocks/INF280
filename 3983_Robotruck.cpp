#include <iostream>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

//#define DEBUG			1
#define HOME			(-1)

int * path;
int * minPath;
int minDist;
int nbPath;
int nbPoints;
int capacity;
int * weight;
int * pos;
int * reached;
int nbReached;
int currWeight;
int currDist;
int idxPath;

inline void check_input(const int input)
{
	if(!input)
	{
		printf("[ERROR] Reading input error\n");
		exit(1);
	}
}

inline int dist(int * a, int * b)
{
	return(abs(b[0] - a[0]) + abs(b[1] - a[1]));
}

inline int distHome(int * a)
{
	return(a[0] + a[1]);
}

inline void printList(int * l, int n)
{
	printf("[");
	FOR(i, n)
		printf("%d ", l[i]);
	printf("\b]\n");
}

void printPath(int * p)
{
	int w = 0;
	printf("path: [HOME] ");
	FOR(i, nbPoints)
	{
		w += weight[i];
		if(w > capacity)
		{
			printf("[HOME] ");
			w = weight[i];
		}
		printf("%d ", p[i]);
	}
	printf("[HOME]\n");
}

void nextPoint()
{
	if(nbReached == nbPoints)
	{
		currDist += distHome(pos + 2*path[idxPath-1]);
		if(minDist != -1 && currDist >= minDist)
			return;
		minDist = currDist;
		FOR(i, nbPoints)
			minPath[i] = path[i];
		return;
	}
	FOR(i, nbPoints)
	{
		if(reached[i])
			continue;
		int prevWeight = currWeight;
		int prevDist = currDist;
		currWeight += weight[i];
		if(nbReached == 0)
		{
#ifdef DEBUG
			printf(" <dist add 1: +%d> ", distHome(pos + 2*i));
#endif
			currDist += distHome(pos + 2*i);
		}
		else if(currWeight > capacity)
		{
			currWeight = weight[i];
#ifdef DEBUG
			printf(" <dist add 2: +%d> ", distHome(pos + 2*path[idxPath-1]) + distHome(pos + i));
#endif
			currDist += distHome(pos + 2*path[idxPath-1]) + distHome(pos + 2*i);
		}
		else
		{
#ifdef DEBUG
			printf(" <dist add 3: +%d (%d/%d)> ", dist(pos + 2*path[idxPath-1], pos + 2*i), path[idxPath-1],i);
#endif
			currDist += dist(pos + 2*path[idxPath-1], pos + 2*i);
		}
		if(minDist != -1 && currDist >= minDist)
			continue;
		path[idxPath++] = i;
		reached[i] = 1;
		nbReached++;
#ifdef DEBUG
		printf("tmpPath: ");
		FOR(i, idxPath)
			printf("%d ", path[i]);
		printf("[%d]\n", currDist);
#endif
		nextPoint();
		nbReached--;
		idxPath--;
		currDist = prevDist;
		currWeight = prevWeight;
		reached[i] = 0;
	}
}

/* Solve Robotruck
** https://icpcarchive.ecs.baylor.edu/external/39/3983.pdf
*/
int main(void)
{
	int nbTests;
	check_input(scanf("%d", &nbTests));
	FOR(i, nbTests)
	{
		check_input(scanf("%d%d", &capacity, &nbPoints));
		pos = new int[nbPoints * 2];
		weight = new int[nbPoints];
		FOR(j, nbPoints)
			check_input(scanf("%d%d%d", &pos[j*2], &pos[j*2+1], &weight[j]));
#ifdef DEBUG
		printf("capacity: %d\nnbPoints: %d\nlist: [", capacity, nbPoints);
		FOR(j, nbPoints)
			printf("(%d,%d,%d) ", pos[j*2], pos[j*2+1], weight[j]);
		printf("\b]\n\n");
#endif
		minDist = -1;
		// on ne servira pas forcement de tout ces paths
		path = new int[nbPoints];
		minPath = new int[nbPoints];
		reached = new int[nbPoints];
		nbPath = 0;
		FOR(i, nbPoints)
			reached[i] = 0;
		idxPath = 0;
		nbReached = 0;
		nextPoint();
		printf("%d\n", minDist);
#ifdef DEBUG
		printPath(minPath);
#endif
	}
    return 0;
}
