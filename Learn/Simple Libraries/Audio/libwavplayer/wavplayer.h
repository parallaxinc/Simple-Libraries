/**
 * @file wavplayer.h
 *
 * @author Andy Lindsay
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2012. All Rights MIT Licensed.
 *
 * @brief Plays 16-bit, 32ksps, mono .wav files in the root directory of a 
 * microSD card.
 * @n @n <b><i>CONSTRUCTION ZONE:</i></b> This library is preliminary, major revisions 
 * pending, not for release.
 * @n @n Currently supports LMM and CMM memory models.  
 * @n @n Make sure to set optimization to -02 Speed.
 */
#ifndef WAVPLAYER_H
#define WAVPLAYER_H

#if defined(__cplusplus)
extern "C" {
#endif

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

void blink(void *par);
void spooler(void *par);

#if defined(__cplusplus)
}
#endif
/* __cplusplus */  
#endif
/* WAVPLAYER_H */  


/**
 * TERMS OF USE: MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

