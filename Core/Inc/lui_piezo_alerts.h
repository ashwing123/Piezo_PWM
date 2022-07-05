/*
 * lui_piezo_alerts.h
 *
 *  Created on: Jul 5, 2022
 *      Author: gopala4
 */

#ifndef INC_LUI_PIEZO_ALERTS_H_
#define INC_LUI_PIEZO_ALERTS_H_

void play_frequency_repeat(int duration, float freq, int num_repeats, int pause_duration);
void play_ascending(float start_freq, float end_freq, int pulse_duration, int pause_duration, int num_steps);
void play_descending(float start_freq, float end_freq, int pulse_duration, int pause_duration, int num_steps);



#endif /* INC_LUI_PIEZO_ALERTS_H_ */
