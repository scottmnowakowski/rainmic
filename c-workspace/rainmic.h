#define SHIFT 7		// The biggest scaler we can use without overflowing int32_t
#define SCALE(x) (x<<SHIFT)
#define UNSCALE(x) (x>>SHIFT)
#define S_MULT(x, y) ((x*y)>>SHIFT)	// Multiply then scaleback

#define H_0 (int32_t)((1+sqrt(3))/(4*sqrt(2))*(1<<SHIFT)+0.5)
#define H_1 (int32_t)((3+sqrt(3))/(4*sqrt(2))*(1<<SHIFT)+0.5)
#define H_2 (int32_t)((3-sqrt(3))/(4*sqrt(2))*(1<<SHIFT)+0.5)
#define H_3 (int32_t)((1-sqrt(3))/(4*sqrt(2))*(1<<SHIFT)+0.5)
#define G_0 (H_3)
#define G_1 (-H_2)
#define G_2 (H_1)
#define G_3 (-H_0)

#define DATA_POINTS_PER_SECOND 3334

struct strRain {
	time_t time;
	int32_t totV1;
	int32_t totV2;
	int32_t totV3;
	int32_t totV4;
};

void rainmic(int32_t n, time_t *t, uint16_t *mic, char *filename);
void dwt(int32_t n, int32_t *mic, int32_t *tmp, int32_t *W1, int32_t *W2, int32_t *W3, int32_t *W4);
void dwt_forward(int n, int32_t *V, int32_t *Wj, int32_t *Vj);
int32_t var(int n, int32_t *buf);
