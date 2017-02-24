#include <iostream>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

#define MAX_NB_PIECES	5
//#define DEBUG			1

int val[MAX_NB_PIECES];
int nb[MAX_NB_PIECES];
int amount;
int founded;
int tmpAmount;
int nbPieces;

inline void check_input(const int input)
{
	if(!input)
	{
		printf("[ERROR] Reading input error\n");
		exit(1);
	}
}

void addCoin(int idx)
{
	if(founded)
		return;
	tmpAmount = 0;
	FOR(i, nbPieces)
		tmpAmount += nb[i] * val[i];
#ifdef DEBUG
	FOR(i, nbPieces)
		printf("%d ", nb[i]);
	printf("sum: %d\n", tmpAmount);
#endif
	if(tmpAmount == amount)
		founded = 1;
	if(tmpAmount >= amount)
		return;
	FOR3(idx, i, nbPieces)
	{
		if(i != 0)
		{
			if(nb[i-1] < nb[i])
				break;
			if(nb[i-1] == nb[i])
				continue;
		}
		nb[i]++;
		addCoin(i);
		nb[i]--;
	}
}

/* Solve No Change problem
** https://icpcarchive.ecs.baylor.edu/external/24/2433.pdf
*/
int main(void)
{
	int nbInputs;
	nbPieces = MAX_NB_PIECES;
	check_input(scanf("%d", &nbInputs));
	FOR(i, nbInputs)
	{
		FOR(i, nbPieces)
			nb[i] = 0;
		check_input(scanf("%d%d", &amount, &nbPieces));
		founded = 0;
		FOR(k, nbPieces)
			check_input(scanf("%d", &val[k]));
#ifdef DEBUG
		printf("Input: Amount:%d, coins: [", amount);
		FOR(i, nbPieces)
			printf("%d,", val[i]);
		printf("]\n");
#endif
		addCoin(0);
		if(founded) printf("YES\n");
		else printf("NO\n");
		if(i < nbInputs - 1)
			printf("\n");
	}
    return 0;
}
