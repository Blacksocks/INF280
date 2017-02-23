#include <iostream>

#define FOR(i,n)        for(int i = 0; i < n; i++)

#define K				5

int val[K];
int nb[K];

inline void check_input(const int input)
{
	if(!input)
	{
		printf("[ERROR] Reading input error\n");
		exit(1);
	}
}

/* Solve No Change problem
** https://icpcarchive.ecs.baylor.edu/external/24/2433.pdf
*/
int main(void)
{
	int nbInputs;
	int amount;

	int scan;
	int tmpVal;
	check_input(scanf("%d\n\n%d", &nbInputs, &scan));
	FOR(i, nbInputs)
	{
		amount = scan;
		FOR(k, K)
		{
			if(!scanf(" %d", &scan))
				break;
			val[k] = scan;
			// init nb array to 1,1,...,1,X,...,X
			tmpVal = 0;
			FOR(j, k)
			{
				nb[j] = 1;
				tmpVal += val[j];
			}
			FOR(j, k)
			{
				if(tmpVal > amount)
					break;
				if(tmpVal == amount)
				{
					printf("YES\n\n");
					goto success;
				}
				FOR(i, K)
					printf("%d ", nb[i]);
				printf("\n");
				nb[j]++;
				tmpVal += val[j];
			}
		}
		printf("NO\n\n");
success:;
	}
    return 0;
}
