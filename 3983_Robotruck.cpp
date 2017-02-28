#include <iostream>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

#define DEBUG			1

int * weight;
int * backHome;
int minDist;
int nbPoints;
int * pos;
int capacity;

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

void nextStep(int idx, int currDist, int w)
{
#ifdef DEBUG
	FOR(i, nbPoints-1)
		printf("%d ", backHome[i]);
	printf("<> idx:%d, dist:%d, minDist:%d, w:%d\n", idx, currDist, minDist, w);
#endif
	if(w > capacity)
		return;
	if(idx >= nbPoints - 1)
	{
		currDist += distHome(pos + 2*idx);
		if(minDist != -1 && currDist >= minDist)
			return;
		minDist = currDist;
#ifdef DEBUG
		printf(">minDist changed: %d\n", minDist);
#endif
		return;
	}
	// on ne retourne pas a la maison
	backHome[idx] = 0;
	nextStep(idx + 1, currDist + dist(pos + 2*idx, pos + 2*(idx+1)), w + weight[idx+1]);
	// on retourne a la maison
	backHome[idx] = 1;
	nextStep(idx + 1, currDist + distHome(pos + 2*idx) + distHome(pos + 2*(idx+1)), weight[idx+1]);
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
		backHome = new int[nbPoints - 1];
		FOR(j, nbPoints)
			check_input(scanf("%d%d%d", &pos[j*2], &pos[j*2+1], &weight[j]));
#ifdef DEBUG
		printf("capacity: %d\nnbPoints: %d\nlist: [", capacity, nbPoints);
		FOR(j, nbPoints)
			printf("(%d,%d,%d) ", pos[j*2], pos[j*2+1], weight[j]);
		printf("\b]\n\n");
#endif
		minDist = -1;
		nextStep(0, distHome(pos), weight[0]);
		delete[] pos;
		printf("%d\n\n", minDist);
	}
    return 0;
}
