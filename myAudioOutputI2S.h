/*
  AudioOutputI2S
  Base class for an I2S output port
  
  Copyright (C) 2017  Earle F. Philhower, III

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _MYAUDIOOUTPUTI2S_H
#define _MYAUDIOOUTPUTI2S_H

#include "AudioOutputI2S.h"

class myAudioOutputI2S : public AudioOutputI2S
{
  public:
    // myAudioOutputI2S(int port=0, int output_mode=EXTERNAL_I2S, int dma_buf_count = 8, int use_apll=APLL_DISABLE)
  	//  : AudioOutputI2S(port, output_mode, dma_buf_count, use_apll){};
    virtual bool SetGain(float f) { gainF2P6 = (uint8_t)(f);Serial.printf("Mygain [%d]\n",gainF2P6); return true; }


};

#endif

