#include <iostream>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

#define K				5
//#define DEBUG			1

int val[K];
int nb[K];
int amount;
int founded;
int tmpAmount;

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
	FOR(i, K)
		tmpAmount += nb[i] * val[i];
#ifdef DEBUG
	FOR(i, K)
		printf("%d ", nb[i]);
	printf("sum: %d\n", tmpAmount);
#endif
	if(tmpAmount == amount)
		founded = 1;
	if(tmpAmount >= amount)
		return;
	FOR3(idx, i, K)
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
	int scan;
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
		addCoin(0);
		if(founded) printf("YES\n");
		else printf("NO\n");
		if(i < nbInputs - 1)
			printf("\n");
	}
    return 0;
}
