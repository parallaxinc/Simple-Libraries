/**
 * @file wavplayer.h
 *
 * @author Andy Lindsay
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2012. All Rights MIT Licensed.
 *
 * @brief CONSTRUCTION ZONE: This is a preliminary library, 
 * revisions pending, not for release.  This library 
 * provides convenience functions for the Ping))) Ultrasonic 
 * Distance Sensor.
 */

/**
 * @brief Play a .wav file.
 *
 * @param filename pointer to character array with filename.
 */
void wav_play(const char* wavFilename);

/**
 * @brief Set wav play volume 0 to 10.
 *
 * @param vol wav playback volume.
 */
void wav_volume(int vol);

/**
 * @brief Stop wav playback.
 */
void wav_stop(void);

//void wav_start(void);
//void wav_volume(int vol);
void blink(void *par);
void spooler(void *par);
