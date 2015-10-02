#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include "rainmic.h"
#include "csv.h"

static int32_t micBuf[DATA_POINTS_PER_SECOND];
static int32_t tmpBuf[DATA_POINTS_PER_SECOND/2];
static int32_t W1Buf[DATA_POINTS_PER_SECOND/2];
static int32_t W2Buf[DATA_POINTS_PER_SECOND/4];
static int32_t W3Buf[DATA_POINTS_PER_SECOND/8];
static int32_t W4Buf[DATA_POINTS_PER_SECOND/16];

void rainmic(int32_t n, time_t *t, uint16_t *mic, char *filename)
{
	if (!t || !mic || !filename)
		return;
	int32_t count = 0, i, x;	// count: number of data points processed in total so far, x: number of data points to process this cycle
	struct strRain zrain;
	while (n - count >= 32)
	{
		x = n-count >= DATA_POINTS_PER_SECOND ? DATA_POINTS_PER_SECOND : n-count;
		for (i = 0; i < x; i++)
		{
			micBuf[i] = SCALE((int32_t)mic[i+count]);
		}
		dwt(x, micBuf, tmpBuf, W1Buf, W2Buf, W3Buf, W4Buf);
		zrain.time = t[count];
		zrain.totV1 = var(x/2, W1Buf);
		zrain.totV2 = var(x/4, W2Buf);
		zrain.totV3 = var(x/8, W3Buf);
		zrain.totV4 = var(x/16, W4Buf);
		//AppendZrain(filename, zrain.time, zrain.totV1, zrain.totV2, zrain.totV3, zrain.totV4);
		count += x;
	}
}

void dwt(int32_t n, int32_t *mic, int32_t *tmpBuf, int32_t *W1, int32_t *W2, int32_t *W3, int32_t *W4)
{
	dwt_forward(n, mic, W1, tmpBuf);

	n = (n/2)%2 == 0 ? n/2 : n/2-1;
	dwt_forward(n, tmpBuf, W2, mic);

	n = (n/2)%2 == 0 ? n/2 : n/2-1;
	dwt_forward(n, mic, W3, tmpBuf);

	n = (n/2)%2 == 0 ? n/2 : n/2-1;
	dwt_forward(n, tmpBuf, W4, mic);
}

void dwt_forward(int n, int32_t *V, int32_t *Wj, int32_t *Vj)
{
	int t, u;
	for (t = 0; t < n/2; t++)
	{
		u = 2*t + 1;
		Wj[t] = S_MULT(G_0, V[u]);
		Vj[t] = S_MULT(H_0, V[u]);
		
		u--;
		if (u < 0)
			u = n-1;
		Wj[t] += S_MULT(G_1, V[u]);
		Vj[t] += S_MULT(H_1, V[u]);

		u--;
		if (u < 0)
			u = n-1;
		Wj[t] += S_MULT(G_2, V[u]);
		Vj[t] += S_MULT(H_2, V[u]);

		u--;
		if (u < 0)
			u = n-1;
		Wj[t] += S_MULT(G_3, V[u]);
		Vj[t] += S_MULT(H_3, V[u]);

		Wj[t] = UNSCALE(Wj[t]);
	}
}

int32_t var(int n, int32_t *buf)
{
	int i, mean = 0, var = 0, tmp;
	for (i=0; i < n; i++)
		mean += buf[i];
	mean /= n;
	for (i=0; i < n; i++)
	{
		tmp = buf[i] - mean;
		var += tmp*tmp;
	}
	return (var/n);
}
