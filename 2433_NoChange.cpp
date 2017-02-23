#include <iostream>

#define FOR(i,n)        for(int i = 0; i < n; i++)

#define K				5

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

void addCoin(int * nb)
{
	if(founded)
		return;
	int tmpAmount = 0;
	int currNb[K]; // copie of nb
	FOR(i, K)
	{
		currNb[i] = nb[i];
		tmpAmount += nb[i] * val[i];
	}
	if(tmpAmount == amount)
		founded = 1;
	if(tmpAmount >= amount)
		return;
	FOR(i, K)
	{
		if(i != 0 && nb[i-1] <= nb[i])
			break;
		currNb[i]++;
		addCoin(currNb);
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
		addCoin(nb);
		if(founded) printf("YES");
		else printf("NO");
		if(i < nbInputs - 1)
			printf("\n\n");
	}
    return 0;
}
