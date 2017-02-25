#include <iostream>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

#define DEBUG			1
#define HOME			(-1)

typedef struct lnk_s {
	int i1; // index 1
	int i2; // index 2
	int d; // distance
	int l; // is linked ?
} lnk_t;

void sort(lnk_t * l, int n)
{
	int minIdx;
	int minVal;
	int tmpI1, tmpI2, tmpD;
	FOR(i, n)
	{
		minIdx = i;
		minVal = l[i].d;
		FOR3(i+1, j, n)
			if(l[j].d < minVal)
			{
				minIdx = j;
				minVal = l[j].d;
				tmpI1 = l[i].i1;
				tmpI2 = l[i].i2;
				tmpD = l[i].d;
				l[i].i1 = l[minIdx].i1;
				l[i].i2 = l[minIdx].i2;
				l[i].d = l[minIdx].d;
				l[minIdx].i1 = tmpI1;
				l[minIdx].i2 = tmpI2;
				l[minIdx].d = tmpD;
			}
	}
}

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

inline void printLnk(lnk_t * l, int n)
{
	printf("LINKS:\n");
	FOR(i, n)
		printf("  (%d, %d, %d, %d)\n", l[i].i1, l[i].i2, l[i].d, l[i].l);
	printf("\n");
}

inline void printList(int * l, int n)
{
	printf("LIST:\n");
	FOR(i, n)
		printf("%d ", l[n]);
	printf("\n");
}

/* Solve Robotruck
** https://icpcarchive.ecs.baylor.edu/external/39/3983.pdf
*/
int main(void)
{
	int nbTests;
	int capacity;
	int nbPackages;
	check_input(scanf("%d", &nbTests));
	FOR(i, nbTests)
	{
		check_input(scanf("%d%d", &capacity, &nbPackages));
		int * pos = new int[nbPackages * 2];
		int * weigth = new int[nbPackages];
		FOR(j, nbPackages)
			check_input(scanf("%d%d%d", &pos[j*2], &pos[j*2+1], &weigth[j]));
		// ([@A]..[@Z][AB]..[AZ]..[YZ])
		int nbLnk = nbPackages * (nbPackages+1) / 2;
		lnk_t * lnk = new lnk_t[nbLnk];
		FOR(j, nbPackages)
		{
			lnk_t * link = lnk + j;
			link->i1 = HOME;
			link->i2 = j;
			link->d = pos[2*j] + pos[2*j+1];
			link->l = 0;
		}

		int idx = nbPackages;
		FOR(j, nbPackages)
			FOR3(j+1, k, nbPackages)
			{
				lnk_t * link = lnk + idx++;
				link->i1 = j;
				link->i2 = k;
				link->d = dist(pos+j, pos+k);
				link->l = 0;
			}
#ifdef DEBUG
		printLnk(lnk, nbLnk);
#endif
		// tri des dist
		sort(lnk, nbLnk);
#ifdef DEBUG
		printLnk(lnk, nbLnk);
#endif
		int * isLinked = new int[nbPackages];
		FOR(j, nbPackages)
			isLinked[j] = 0;

		FOR(j, nbLnk)
		{
			// si A et B ne sont pas liés, si A(resp. B)=HOME, A(resp. B) est considéré non lié
			int i1 = lnk[j].i1;
			int i2 = lnk[j].i2;
			if((isLinked[i1] < 2 || i1 == HOME) && (isLinked[i2] < 2 || i2 == HOME))
			{
				isLinked[i1]++;
				isLinked[i2]++;
				lnk[j].l = 1;
			}
		}
#ifdef DEBUG
		printLnk(lnk, nbLnk);
		printList(isLinked, nbPackages);
#endif
	}
    return 0;
}
