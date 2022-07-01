/*
 * lui_piezo.h
 *
 *  Created on: Jul 1, 2022
 *      Author: gopala4
 */

#ifndef LUI_PIEZO_H_
#define LUI_PIEZO_H_

float get_freq_from_note(char note[]);
void pause_pwm(int duration_in_ms);
void play_frequency(int note_beat_length, float frequency, float beats_per_sec);
void play_frequency_array(int beats[], float frequencies[], int tempo, int song_len);
void play_tune(int beats[], char *song_notes, int tempo);



#endif /* LUI_PIEZO_H_ */
