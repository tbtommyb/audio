/* p77 Ex 1.2.6: Find MIDI note of given frequency, including pitchbend */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]) {
	double semitone_ratio;
	double c0; /* for frequency of MIDI 0 */
	double c5; /* for frequency of middle C */
	double fracmidi;
	double frequency;
	int midinote;
	double lower_freq;
	double upper_freq;
	int lower_midinote;
	int upper_midinote;
	double pitchbend;
	double freq_diff;
	char message[256];

	/* calculate numbers required */

	semitone_ratio = pow(2, 1/12.0);
	/* find middle C, three semitones above low A = 220 */
	c5 = 220.0 * pow(semitone_ratio, 3);
	/* MIDI 0 is C 5 octaves below middle C, so halve five times */
	c0 = c5 * pow(0.5, 5);

	if (argc < 2) {
		printf("%s error: Provide frequency as argument\n", argv[0]);
		return 1;
	}

	frequency = atof(argv[1]);

	fracmidi = log(frequency / c0) / log(semitone_ratio);
	lower_midinote = (int) fracmidi;
	upper_midinote = (int) (fracmidi + 1);
	lower_freq = c0 * pow(semitone_ratio, lower_midinote);
	upper_freq = c0 * pow(semitone_ratio, upper_midinote);
	freq_diff = upper_freq - lower_freq;

	if (upper_freq - frequency < frequency - lower_freq) {
		/* nearest note is above, -ve pitchbend */
		pitchbend = ((upper_freq - frequency) / freq_diff) * 100;
		printf("Nearest note: %d\n", upper_midinote);
		printf("Pitchbend: -%.f%%\n", pitchbend);
	} else {
		pitchbend = ((frequency - lower_freq) / freq_diff) * 100;
		printf("Nearest note: %d\n", lower_midinote);
		printf("Pitchbend: +%.f%%\n", pitchbend);
	}

	return 0;
}