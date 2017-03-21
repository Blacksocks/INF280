#include <iostream>
#include <list>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

//#define DEBUG			1

typedef struct pos_s {
	int x;
	int y;
} pos_t;

using namespace std;

int * weight;
int * backHome;
int nbPoints;
pos_t * pos;
int capacity;

inline void check_input(const int input)
{
	if(!input)
	{
		printf("[ERROR] Reading input error\n");
		exit(1);
	}
}

inline int dist(pos_t * a, pos_t * b)
{
	return(abs(b->x - a->x) + abs(b->y - a->y));
}

inline int distHome(pos_t * a)
{
	return(a->x + a->y);
}

int initIdx()
{
	int i = 0;
	int w = 0;
	for(i = 0; (w += weight[i]) <= capacity && i < nbPoints; i++);
	return(i - 1);
}

int initIdxBack(int i)
{
	i--;
	for(; backHome[i] == 0 && i > 0; i--);
	return(i);
}

int optimize(int idx, int maxIdx, int currDist, int w)
{
#ifdef DEBUG
	FOR(i, nbPoints-1)
		printf("%d ", backHome[i]);
	printf("<> idx:%d, dist:%d, maxIdx:%d, w:%d\n", idx, currDist, maxIdx, w);
#endif
	if(w > capacity)
		return -1;
	if(idx == maxIdx)
		return currDist;
	// on ne retourne pas a la maison
	backHome[idx] = 0;
	int notGoBackHomeDist = optimize(idx + 1, maxIdx, currDist + dist(&pos[idx], &pos[idx+1]), w + weight[idx+1]);
	// on retourne a la maison
	backHome[idx] = 1;
	int goBackHomeDist = optimize(idx + 1, maxIdx, currDist + distHome(&pos[idx]) + distHome(&pos[idx+1]), weight[idx+1]);
#ifdef DEBUG
	printf("idx: %d, notGoBackHomeDist / goBackHomeDist : %d / %d\n", idx, notGoBackHomeDist, goBackHomeDist);
#endif
	if(notGoBackHomeDist == -1)
		return goBackHomeDist;
	if(goBackHomeDist == -1)
	{
		backHome[idx] = 1;
		return goBackHomeDist;
	}
	if(notGoBackHomeDist < goBackHomeDist)
	{
#ifdef DEBUG
		printf("backHome[%d] = %d\n", idx, 0);
#endif
		backHome[idx] = 0;
		return notGoBackHomeDist;
	}
#ifdef DEBUG
	printf("backHome[%d] = %d\n", idx, 1);
#endif
	return goBackHomeDist;
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
		pos = new pos_t[nbPoints];
		weight = new int[nbPoints];
		backHome = new int[nbPoints - 1];
		FOR(j, nbPoints)
			check_input(scanf("%d%d%d", &pos[j].x, &pos[j].y, &weight[j]));
#ifdef DEBUG
		printf("capacity: %d\nnbPoints: %d\nlist: [", capacity, nbPoints);
		FOR(j, nbPoints)
			printf("(%d,%d,%d) ", pos[j].x, pos[j].y, weight[j]);
		printf("\b]\n\n");
#endif

		int idx = initIdx();
		optimize(0, idx, 0, 0);
		FOR3(idx+1, j, nbPoints)
		{
#ifdef DEBUG
			printf("======================\n\n");
#endif
			optimize(initIdxBack(j), j, 0, 0);
		}

		int minDist = distHome(&pos[0]) + distHome(&pos[nbPoints-1]);
#ifdef DEBUG
		printf("backHome: ");
		FOR(j, nbPoints-1)
			printf("%d ", backHome[j]);
		printf("\n");
#endif
		FOR(j, nbPoints-1)
			minDist += backHome[j] ? distHome(&pos[j]) + distHome(&pos[j+1]) : dist(&pos[j], &pos[j+1]);
		printf("%d\n\n", minDist);
		delete[] pos;
		delete[] weight;
		delete[] backHome;
	}
    return 0;
}
