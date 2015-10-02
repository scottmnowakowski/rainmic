#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "rainmic.h"
#include "csv.h"

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		printf("Wrong number of arguments\n");
		return;
	}
	time_t *t = NULL;
	uint16_t *mic = NULL;
	uint32_t n = 0;
	n = ReadCSV(argv[1], &t, &mic);
	WriteHeaders(argv[2]);
	rainmic(n, t, mic, argv[2]);
}
