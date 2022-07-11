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
void play_frequency(int duration_ms, float frequency);
void play_frequency_array(float beats[], float frequencies[], float tempo, int song_len);
void play_tune(float beats[], char *song_notes, float tempo);
void stop_pwm(void);

//solely notification purposes



#endif /* LUI_PIEZO_H_ */
