
#ifndef AudioManager_h
#define AudioManager_h

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif

#include <BaseManager.h>
#include "AudioFileSourceSD.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioFileSourceICYStream.h"
#include "AudioFileSourceBuffer.h"
//#include "AudioGeneratorWAV.h"
//#include "AudioGeneratorFLAC.h"
#include "AudioOutputI2SNoDAC.h"
#include "AudioOutputI2S.h"
#include "myAudioOutputI2S.h"

class AudioManager : public BaseManager
{
  public:
	AudioManager(uint8_t pinLed) : BaseManager (pinLed){
		/*if (out == NULL) {
			out = new myAudioOutputI2S();//AudioOutputI2S();
			out->SetOutputModeMono(true);
		}*/

		//if (mp3 == NULL) mp3 = new AudioGeneratorMP3(/*space, 29200*/);
     } ;
    //~DurationManager();

	void stopSound();

	void startNewSound(String link, uint8_t InputType, int8_t volume);

	void setVolume(int8_t volume) {
		if (out) out->SetGain(volume) ;
	}
	void handle();

	boolean isRunning() {
		if (mp3!=NULL)
			return mp3->isRunning();
		return false;
	}

  protected:
	AudioGeneratorMP3 *mp3 = NULL;
	AudioFileSource *file = NULL;
	AudioOutputI2S *out = NULL;
	AudioFileSourceBuffer *buff = NULL;
	boolean stopHandle = true;
};

#endif
