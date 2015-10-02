#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <stdio.h>

int32_t ReadCSV(char * filename, time_t **t, uint16_t **mic)
{
	int numLines = 0;
	FILE *file = fopen(filename, "r");
	while (!feof(file))
	{
		if (fgetc(file) == '\n')
			numLines++;
	}
	numLines--;
	fclose(file);

	*t = malloc(numLines*sizeof(time_t));
	*mic = malloc(numLines*sizeof(uint16_t));

	file = fopen(filename, "r");
	while (fgetc(file) != '\n') {}	// Skip first line in file (column headers)
	uint32_t x = 0, y;
	for (x; x < numLines; x++)
	{
		double tmpTime;
		while (fgetc(file) != ',') {} // Skip until after first commma on each line
		fscanf(file, "%lf,%lu", &tmpTime, (long unsigned *)(*mic + x));
		*(*t + x)= (time_t)(tmpTime + 0.5);
	}
	fclose(file);
	return numLines;
}

void WriteHeaders(char * filename)
{
	FILE *file = fopen(filename, "w");
	fprintf(file, "\"totT\",\"totV1\",\"totV2\",\"totV3\",\"totV4\"\n");
	fclose(file);
}

void AppendZrain(char * filename, int32_t time, int32_t v1, int32_t v2, int32_t v3, int32_t v4)
{
	FILE *file = fopen(filename, "a");
	fprintf(file, "%d,%d,%d,%d,%d\n", time, v1, v2, v3, v4);
	fclose(file);
}
