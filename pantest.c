/* pantest.c: test simplepan and constpower panning functions */

#import <math.h>
#import <stdio.h>

typedef struct panpos {
	double left;
	double right;
} PANPOS;

double maxsamp(float* buf, unsigned long blocksize);
PANPOS simplepan(double position);
PANPOS constpower(double position);

PANPOS simplepan(double position) {
	PANPOS pos;

	position *= 0.5;
	pos.left = position - 0.5;
	pos.right = position + 0.5;

	return pos;
}

PANPOS constpower(double position) {
	PANPOS pos;
	const double root2ovr2 = sqrt(2.0) * 0.5;
	double angle = position * atan(1.0);
	double cosVal = cos(angle);
	double sinVal = sin(angle);

	pos.left = root2ovr2 * (cosVal - sinVal);
	pos.right = root2ovr2 * (cosVal + sinVal);
	return pos;
}

int main(int argc, char* argv[]) {
	int i;
	double step = 2.0/128.0;
	double pos = -1.0;
	PANPOS position;
	double total = 0.0;
	double left, right;

	for (i = 0; i < 128; i++) {
		position = simplepan(pos);
		left = (double)(1.0*position.left);
		right = (double)(1.0*position.right);
		total += sqrt(pow(left,2) + pow(right,2));
		pos += step;
	}

	total = total / 128.0;
	printf("Simplepan total: %f\n", total);

	total = 0.0;
	pos = -1.0;

	for (i = 0; i < 128; i++) {
		position = constpower(pos);
		left = (double)(1.0*position.left);
		right = (double)(1.0*position.right);
		total += sqrt(pow(left,2) + pow(right,2));
		pos += step;
	}

	total = total / 128.0;
	printf("Constpower total: %f\n", total);
}
