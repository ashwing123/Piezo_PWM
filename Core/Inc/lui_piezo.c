/*
 * lui_piezo.c
 *
 *  Created on: Jul 2, 2022
 *      Author: gopala4
 */
//include statements:
#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//definitions
#define CLOCKFREQ 1000000
#define NUM_NOTES 12




TIM_HandleTypeDef htim3;
//TIM3 initialization function
void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 64;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1000;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

void piezo_init(void) {
	MX_TIM3_Init();
	HAL_TIM_Base_Start(&htim3);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, GPIO_PIN_SET);
}
/*
 * function name: get_freq_from_note
 * purpose: convert a string representing a note & octave to its corresponding frequency
 * input: string representing a note (see NOTES array below for possible notes) followed by an octave (ex A#3).
 */
float get_freq_from_note(char note[]) {
	char NOTES[12][2] = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
	int octave;
	char curr_note[2];
	int note_len = strlen(note);
	if (note_len == 3) {
		octave = (int) note[2] - '0';
		strncpy(curr_note, note, 2);
	} else if (note_len == 2) {
		octave = (int) note[1] - '0';
		strncpy(curr_note, note, 1);
	} else {
		return 0;
	}
	int keyIndex = 0;
	for (int i = 0; i < NUM_NOTES; i++) {
		if (strncmp(curr_note, NOTES[i], 2) == 0) {
			keyIndex = i;
			break;
		}
	}
	//@source: https://gist.github.com/stuartmemo/3766449#file-note-to-frequency
	if (keyIndex < 3) {
		keyIndex = keyIndex + 12 + ((octave - 1) * 12) + 1;
	} else {
		keyIndex = keyIndex + ((octave - 1) * 12) + 1;
	}
	// Return frequency of note
	return 440 * pow(2, ((float) (keyIndex - 49)) / 12);
}

/*
 * function name: pause_pwm
 * purpose: make the duty cycle 0 so no output is provided for the specified duration
 * input: duration of pause in ms
 */
void pause_pwm(int duration_in_ms) {
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);
	HAL_Delay(duration_in_ms);
}
/*
 * function name: play_frequency
 * purpose: plays a frequency, for a duration that corresponds to the beat and the tempo
 * input: the beat length, the frequency, the beats per second (tempo)
 */
void play_frequency(float note_beat_length, float frequency, float beats_per_sec) {
	int note_duration_ms = (note_beat_length/beats_per_sec)*1000;
	if (frequency == 0) {
		pause_pwm(note_duration_ms);
	} else {
		int arr_val = (int) (CLOCKFREQ/frequency);
		//changing PWM frequency
		__HAL_TIM_SET_AUTORELOAD(&htim3, arr_val);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, arr_val / 2);
		//delaying so the note holds
		HAL_Delay(note_duration_ms);
	}
}
void play_frequency_array(float beats[], float frequencies[], int tempo, int song_len) {
	float beats_per_sec = tempo/60;
	for (int i = 0; i < song_len; i++) {
		play_frequency(beats[i], frequencies[i], beats_per_sec);
		pause_pwm((int) (50/(beats_per_sec)));
	}
}

void play_tune(float beats[], char *song_notes, int tempo) {
	int note_num = 0;
	float freq_arr[100];
	char *context = NULL;
	char *space_split = strtok_r(song_notes, " ", &context);
	while (space_split != NULL) {
		printf("%s", space_split);
		freq_arr[note_num] = get_freq_from_note(space_split);
		note_num += 1;
		space_split = strtok_r(NULL, " ", &context);
	}
	piezo_init();
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	play_frequency_array(beats, freq_arr, tempo, note_num);
}

void stop_pwm(void) {
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);
}
void play_freqs_no_pause(float beats[], float frequencies[], int tempo, int song_len) {
	piezo_init();
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	float beats_per_sec = tempo/60;
	for (int i = 0; i < song_len; i++) {
		play_frequency(beats[i], frequencies[i], beats_per_sec);
	}
	stop_pwm();

}

