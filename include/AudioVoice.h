#ifndef _AUDIO_VOICE_H_
#define _AUDIO_VOICE_H_

template<typename T>
class AudioVoice
{
public:
    AudioVoice();
    ~AudioVoice();
protected:
    T* audioUnit;
};

#endif