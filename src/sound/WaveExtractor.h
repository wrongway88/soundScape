#ifndef WAVE_EXTRACTOR_H
#define WAVE_EXTRACTOR_H

#include <string>
#include<vector>

#include "core/inc/fmod.hpp"

namespace WaveExtractor
{
	static FMOD::System* _system;
	static FMOD::Channel* _channel;
	static FMOD::Sound* _sound;
	static FMOD::DSP* _dsp;

	void setup(const std::string& soundFile);

	void update();

	std::vector<float> getSpectrum();
}

#endif // WAVE_EXTRACTOR_H
