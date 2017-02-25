#include <iostream>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

#define DEBUG			1
#define HOME			(-1)

typedef struct path_s {
	int * p; // points
	int n; // number of points
	int d; // distance
} path_t;

int minPathsDist;
path_t * paths;
int nbPath;
int nbPoints;
int capacity;
int * weight;
int * pos;
int * reached;

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

inline void printList(int * l, int n)
{
	printf("[");
	FOR(i, n)
		printf("%d ", l[i]);
	printf("\b]\n");
}

int getMinPathLen(int pointIdx, int curDist, int curWeight, int * len, int * reached)
{
	int idx = (pointIdx == 0);
	int minDist = dist(pos+idx, pos+pointIdx);
	// get nearest point from pointIdx
	FOR(i, nbPoints)
	{
		if(i == pointIdx || reached[i])
			continue;
		if(dist(pos+i, pos+idx) < minDist || reached[idx])
		{
			minDist = dist(pos+i, pos+idx);
			idx = i;
		}
	}
	// minPathsDist is shorter, this paths are not optimized -> stop
	if(minPathsDist != -1 && curDist + minDist > minPathsDist)
		return 1;
	// out of capacity -> got back home
	if(curWeight + weight[idx] > capacity)
		return 0;
	// all points joined -> got back home
	if(reached[idx])
		return 2;
	(*len)++;
	reached[idx] = 1;
	return getMinPathLen(idx, curDist+minDist, curWeight+weight[idx], len, reached);
}

int getMinPath(int pathIdx, int pointIdx, int curWeight, int pathPointIdx)
{
	int idx = (pointIdx == 0);
	int minDist = dist(pos+idx, pos+pointIdx);
	int curDist = paths[pathIdx].d;
	// get nearest point from pointIdx
	FOR3(2, i, nbPoints)
	{
		if(i == pointIdx || reached[i])
			continue;
		if(dist(pos+i, pos+idx) < minDist || reached[idx])
		{
			minDist = dist(pos+i, pos+idx);
			//printf("  %d to %d - minDist: %d\n", i, idx, minDist);
			idx = i;
		}
	}
	// minPathsDist is shorter, this paths are not optimized -> stop
	if(minPathsDist != -1 && curDist + minDist > minPathsDist)
		return 1;
	// out of capacity -> got back home
	if(curWeight + weight[idx] > capacity)
		return 0;
	paths[pathIdx].p[pathPointIdx++] = idx;
	// all points joined -> got back home
	if(reached[idx])
		return 2;
	reached[idx] = 1;
	paths[pathIdx].d += minDist;
#ifdef DEBUG
	printf("%d to %d, minDist: %d\n", pointIdx, idx, minDist);
#endif
	return getMinPath(pathIdx, idx, curWeight+weight[idx], pathPointIdx);
}

void getMinPaths()
{
	int pathLen;
	int * tmpReached = new int[nbPoints];
	int res;
	FOR(i, nbPoints)
		tmpReached[i] = reached[i];
	do{
		pathLen = 0;
		if(getMinPathLen(0, 0, 0, &pathLen, tmpReached) == 1)
		{
			printf("[INFO] Unoptimized paths\n");
			return;
		}
		paths[nbPath].p = new int[pathLen];
		paths[nbPath].n = pathLen;
		paths[nbPath].d = 0;
		res = getMinPath(nbPath, 0, 0, 0);
		int p0 = paths[nbPath].p[0];
		int pN = paths[nbPath].p[pathLen-1];
		paths[nbPath++].d += pos[p0] + pos[p0+1] + pos[pN] + pos[pN+1];
	}
	while(res != 2);
	delete(tmpReached);
}

void printPath()
{
	FOR(i, nbPath)
	{
		printf("[HOME] ");
		FOR(j, paths[i].n)
			printf("%d ", paths[i].p[j]);
		printf("[HOME]\n");
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
		minPathsDist = -1;
		paths = new path_t[nbPoints];
		reached = new int[nbPoints];
		nbPath = 0;
		FOR(i, nbPoints)
			reached[i] = 0;
		getMinPaths();
		minPathsDist = 0;
		FOR(j, nbPath)
			minPathsDist += paths[j].d;
		printf("%d\n\n", minPathsDist);
#ifdef DEBUG
		printPath();
#endif
	}
    return 0;
}
