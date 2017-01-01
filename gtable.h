#include <wave.h>

typedef struct t_gtable
{
  double* table; /* pointer to array containing the waveform */
  unsigned long length; /* excluding guardpoint */
} GTABLE;

typedef struct t_tab_oscil
{
  OSCIL osc;
  const GTABLE* gtable;
  double dtablen;
  double sizeovrsr;
} OSCILT;

typedef double (*oscilt_tickfunc)(OSCILT* osc, double freq);

enum { SAW_DOWN, SAW_UP };

GTABLE* new_sine(unsigned long length);
GTABLE* new_gtable(unsigned long length);
void gtable_free(GTABLE** gtable);

OSCILT* new_oscilt(double srate, const GTABLE* gtable, double phase);

double tabtick(OSCILT* p_osc, double freq);
double tabitick(OSCILT* p_osc, double freq);

GTABLE* new_saw(unsigned long length, unsigned long nharms, int up);
GTABLE* new_triangle(unsigned long length, unsigned long nharms);
GTABLE* new_square(unsigned long length, unsigned long nharms);