#include <iostream>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

#define K				5
//#define DEBUG			1

int val[K];
int amount;
int founded;

inline void check_input(const int input)
{
	if(!input)
	{
		printf("[ERROR] Reading input error\n");
		exit(1);
	}
}

void addCoin(int * nb, int idx)
{
	if(founded)
		return;
	int tmpAmount = 0;
	int currNb[K]; // copie of nb
	FOR(i, K)
	{
#ifdef DEBUG
		printf("%d ", nb[i]);
#endif
		currNb[i] = nb[i];
		tmpAmount += nb[i] * val[i];
	}
#ifdef DEBUG
	printf("\n");
#endif
	tmpAmount += nb[idx];
	currNb[idx]++;
	if(tmpAmount == amount)
		founded = 1;
	if(tmpAmount >= amount)
		return;
	FOR3(idx, i, K)
	{
		if(i != 0 && nb[i-1] <= nb[i])
			break;
		addCoin(currNb, i);
	}
}

/* Solve No Change problem
** https://icpcarchive.ecs.baylor.edu/external/24/2433.pdf
*/
int main(void)
{
	int nbInputs;
	int scan;
	int nb[K];
	FOR(i, K)
		nb[i] = 0;
	check_input(scanf("%d\n\n%d", &nbInputs, &scan));
	FOR(i, nbInputs)
	{
		founded = 0;
		amount = scan;
		FOR(k, K)
		{
			if(!scanf(" %d", &scan))
				break;
			val[k] = scan;
		}
		addCoin(nb, 0);
		if(founded) printf("YES\n");
		else printf("NO\n");
		if(i < nbInputs - 1)
			printf("\n");
	}
    return 0;
}
