/* wave.c: tick functions for oscillators */
#include <wave.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

OSCIL* new_oscil(double srate)
{
    OSCIL* p_osc;
    p_osc = (OSCIL*) malloc(sizeof(OSCIL));
    if(p_osc == NULL) {
        return NULL;
    }
    p_osc->twopiovrsr = TWOPI / srate;
    p_osc->curfreq = 0.0;
    p_osc->curphase = 0.0;
    p_osc->incr = 0.0;

    return p_osc;
}

double sinetick(OSCIL* p_osc, double freq)
{
    double val;

    val = sin(p_osc->curphase);
    if(p_osc->curfreq != freq) {
        p_osc->curfreq = freq;
        p_osc->incr = p_osc->twopiovrsr * freq;
    }
    p_osc->curphase += p_osc->incr;
    if(p_osc->curphase >= TWOPI) {
        p_osc->curphase -= TWOPI;
    }
    if(p_osc->curphase < 0.0) {
        p_osc->curphase += TWOPI;
    }
    return val;
}

double sqtick(OSCIL* p_osc, double freq)
{
    double val;

    if(p_osc->curfreq != freq) {
        p_osc->curfreq = freq;
        p_osc->incr = p_osc->twopiovrsr * freq;
    }
    if(p_osc->curphase <= M_PI) {
        val = 1.0;
    } else {
        val = -1;
    }
    p_osc->curphase += p_osc->incr;    
    if(p_osc->curphase >= TWOPI) {
        p_osc->curphase -= TWOPI;
    }
    if(p_osc->curphase < 0.0) {
        p_osc->curphase += TWOPI;
    }
    return val;
}

double sawdtick(OSCIL* p_osc, double freq)
{
    double val;

    if(p_osc->curfreq != freq) {
        p_osc->curfreq = freq;
        p_osc->incr = p_osc->twopiovrsr * freq;
    }
    val = 1.0 - 2.0 * (p_osc->curphase * (1.0 / TWOPI));
    p_osc->curphase += p_osc->incr;
    if(p_osc->curphase >= TWOPI) {
        p_osc->curphase -= TWOPI;
    }
    if(p_osc->curphase < 0.0) {
        p_osc->curphase += TWOPI;
    }
    return val;    
}

double sawutick(OSCIL* p_osc, double freq)
{
    double val;
    
    val = (2.0 * (p_osc->curphase * (1.0 / TWOPI))) - 1.0;
    if(p_osc->curfreq != freq) {
        p_osc->curfreq = freq;
        p_osc->incr = p_osc->twopiovrsr * freq;
    }
    p_osc->curphase += p_osc->incr;
    if(p_osc->curphase >= TWOPI) {
        p_osc->curphase -= TWOPI;
    }
    if(p_osc->curphase < 0.0) {
        p_osc->curphase += TWOPI;
    }
    return val;
}

double tritick(OSCIL* p_osc, double freq)
{
    double val;

    if(p_osc->curfreq != freq) {
        p_osc->curfreq = freq;
        p_osc->incr = p_osc->twopiovrsr * freq;
    }
    val = (2.0 * (p_osc->curphase * (1.0 / TWOPI))) - 1.0;
    if(val < 0.0) {
        val = -val;
    }
    val = 2.0 * (val - 0.5);
    p_osc->curphase += p_osc->incr;
    if(p_osc->curphase >= TWOPI) {
        p_osc->curphase -= TWOPI;
    }
    if(p_osc->curphase < 0.0) {
        p_osc->curphase += TWOPI;
    }
    return val;
}

double pwmtick(OSCIL* p_osc, double freq, double pwmod)
{
    double val;

    if(p_osc->curfreq != freq) {
        p_osc->curfreq = freq;
        p_osc->incr = p_osc->twopiovrsr * freq;
    }
    if((p_osc->curphase / (2.0*pwmod)) <= M_PI) {
        val = 1.0;
    } else {
        val = -1;
    }
    p_osc->curphase += p_osc->incr;    
    if(p_osc->curphase >= TWOPI) {
        p_osc->curphase -= TWOPI;
    }
    if(p_osc->curphase < 0.0) {
        p_osc->curphase += TWOPI;
    }
    return val;
} 
