/* wave.h - definition of OSCIL type */

#define M_PI 3.14159265358979323846
#define TWOPI (M_PI * 2)

typedef struct t_oscil {
	double twopiovrsr;
	double curfreq;
	double curphase;
	double incr;
} OSCIL;

OSCIL* new_oscil(unsigned long srate);
double sinetick(OSCIL* p_osc, double freq);
