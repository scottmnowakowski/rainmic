#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "rainmic.h"
#include "csv.h"

int main(int argc, char * argv[])
{
	time_t t[10000];
	uint16_t mic[10000];
	int i,x;
	for (i = 0; i < 10000; i++)
	{
		t[i] = i;
		mic[i] = i;
	}
	printf("\"Num data points\",\"Time (ms)\"\n");
	for (i = 50; i <= 10000; i += 50)
	{
		double avg = 0;
		double n = 10;
		for (x = 0; x < (int)n; x++)
		{
			clock_t begin = clock();
			rainmic(i, t, mic, argv[2]);
			clock_t end = clock();
			avg += (double)(end - begin)*1000.0/CLOCKS_PER_SEC;
		}
		printf("%d,%f\n", i, avg/n);
	}
}
