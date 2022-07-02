/*
 * lui_piezo.h
 *
 *  Created on: Jul 1, 2022
 *      Author: gopala4
 */

#ifndef LUI_PIEZO_H_
#define LUI_PIEZO_H_

//music playing purposes
void piezo_init(void);
float get_freq_from_note(char note[]);
void pause_pwm(int duration_in_ms);
void play_frequency(float note_beat_length, float frequency, float beats_per_sec);
void play_frequency_array(float beats[], float frequencies[], int tempo, int song_len);
void play_tune(float beats[], char *song_notes, int tempo);

//solely notification purposes
void play_freqs_no_pause(float beats[], float frequencies[], int tempo, int song_len);


#endif /* LUI_PIEZO_H_ */
