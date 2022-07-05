/*
 * lui_piezo_alerts.c
 *
 *  Created on: Jul 5, 2022
 *      Author: gopala4
 */
//includes
#include "lui_piezo_music.h"
/*
 * function name: play_frequency
 * purpose: plays a frequency on the piezo for the specified duration and frequency
 * input: duration of buzz (in ms), frequency (in Hz)
 */

void play_frequency_repeat(int duration, float freq, int num_repeats, int pause_duration) {
	pause_pwm(100);
	for (int i = 0; i < num_repeats; i++) {
		play_frequency(duration, freq);
		if (pause_duration != 0) {
			pause_pwm(pause_duration);
		}
	}
}
/*
void play_freqs_no_pause(float beats[], float frequencies[], int tempo, int song_len) {
	float beats_per_sec = tempo/60;
	for (int i = 0; i < song_len; i++) {
		play_frequency(beats[i], frequencies[i], beats_per_sec);
	}
	stop_piezo();
}*/
/*
 * function name: play_ascending
 * purpose: plays an ascending series of frequencies with a specified start and end frequency and a number of frequency changes
 * input: start & end freq, duration of pulses, pause between frequencies, number of frequency changes
 */
void play_ascending(float start_freq, float end_freq, int pulse_duration, int pause_duration, int num_steps) {
	float init_freq = start_freq;
	float step = (end_freq - start_freq) / num_steps;
	pause_pwm(100);
	for (int i = 0; i < num_steps; i++) {
		play_frequency(pulse_duration, init_freq);
		if (pause_duration != 0) {
			pause_pwm(pause_duration);
		}
		init_freq = init_freq + step;
	}
	stop_pwm();
}
/*
 * function name: play_descending
 * purpose: like play_ascending, but plays it from a higher starting to a lower ending
 * input: start & end freq, duration of pulses, pause between frequencies, number of frequency changes.
 */
void play_descending(float start_freq, float end_freq, int pulse_duration, int pause_duration, int num_steps) {
	float init_freq = start_freq;
	float step = (start_freq - end_freq) / num_steps;
	pause_pwm(100);
	for (int i = 0; i < num_steps; i++) {
		play_frequency(pulse_duration, init_freq);
		if (pause_duration != 0) {
			pause_pwm(pause_duration);
		}
		init_freq = init_freq - step;
	}
	stop_pwm();
}

