#include "WaveExtractor.h"

#include "core/utility/logging/logging.h"

namespace WaveExtractor
{
	bool errorCheck(FMOD_RESULT result)
	{
		if (result != FMOD_OK)
		{
			LOG_ERROR_STREAM(<< "Fmod Error: " << result);

			return false;
		}

		return true;
	}

#define FMOD_ERROR_CHECK(_result)\
if (errorCheck(_result) == false)\
{\
	return;\
}

#define FMOD_ERROR_CHECK_RET(_result, _retVal)\
if(errorCheck(_result) == false)\
{\
	return _retVal;\
}

	void setup(const std::string& soundFile)
	{
		FMOD_RESULT r;

		_system = nullptr;

		r = FMOD::System_Create(&_system);
		FMOD_ERROR_CHECK(r);

		unsigned int version = 0;
		r = _system->getVersion(&version);
		FMOD_ERROR_CHECK(r);

		if (version != FMOD_VERSION)
		{
			LOG_ERROR_STREAM(<< "FMOD lib version " << version << " does not match header version " << FMOD_VERSION);
			return;
		}

		void* extraDriverData = nullptr;
		r = _system->init(32, FMOD_INIT_NORMAL, extraDriverData);
		FMOD_ERROR_CHECK(r);

		_system->createDSPByType(FMOD_DSP_TYPE_FFT, &_dsp);
		_dsp->setParameterInt(FMOD_DSP_FFT_WINDOWTYPE, FMOD_DSP_FFT_WINDOW_TRIANGLE);
		_windowSize = 1024;
		_dsp->setParameterInt(FMOD_DSP_FFT_WINDOWSIZE, _windowSize);

		// 
		r = _system->createSound(soundFile.c_str(), FMOD_LOOP_NORMAL /*FMOD_OPENMEMORY | FMOD_LOOP_NORMAL | FMOD_CREATESAMPLE*/, nullptr, &_sound);
		FMOD_ERROR_CHECK(r);

		r = _system->playSound(_sound, 0, false, &_channel);
		FMOD_ERROR_CHECK(r);

		r = _channel->getFrequency(&_samplingFrequency);
		FMOD_ERROR_CHECK(r);

		r = _channel->addDSP(0, _dsp);
		FMOD_ERROR_CHECK(r);

		r = _dsp->setActive(true);
		FMOD_ERROR_CHECK(r);

		// _system->close();
	}

	void update()
	{
		FMOD_RESULT r = _system->update();
		FMOD_ERROR_CHECK(r);
	}

	std::vector<float> getSpectrum()
	{
		std::vector<float> result;

		FMOD_DSP_PARAMETER_FFT* dspFFT = nullptr;

		FMOD_RESULT r;

		r = _dsp->getParameterData(FMOD_DSP_FFT_SPECTRUMDATA, (void**)&dspFFT, 0, 0, 0);
		FMOD_ERROR_CHECK_RET(r, result);

		if (dspFFT != nullptr)
		{
			int length = dspFFT->length / 2;
			int numChannels = dspFFT->numchannels;

			if (length > 0)
			{
				int indexFFT = 0;
				for (int i = 0; i < numChannels; i++)
				{
					for (int j = 0; j < length; j++)
					{
						result.push_back(dspFFT->spectrum[i][j]);
					}
				}
			}
		}

		return result;
	}

	bool detectBeat(const std::vector<float>& spectrum)
	{
		if (spectrum.size() <= 0)
		{
			return false;
		}

		int bandSize = _samplingFrequency / _windowSize;

		int kickDrumLower = 60 / bandSize;
		int kickDrumUpper = 130 / bandSize;

		int snareDrumLower = 301 / bandSize;
		int snareDrumUpper = 750 / bandSize;

		float kickDrumEnergy = 0.0f;
		for (int i = kickDrumLower; i < kickDrumUpper; i++)
		{
			kickDrumEnergy += (float)spectrum[i] / float(kickDrumUpper - kickDrumLower);
		}

		_kickDrumHistory.push_back(kickDrumEnergy);

		float snareDrumEnergy = 0.0f;
		for (int i = snareDrumLower; i < snareDrumUpper; i++)
		{
			snareDrumEnergy += (float)spectrum[i] / float(snareDrumUpper - snareDrumLower);
		}

		_snareDrumHistory.push_back(snareDrumEnergy);

		if (_kickDrumHistory.size() > 42 && _snareDrumHistory.size() > 42)
		{
			float kickDrumAvg = 0.0f;
			float kickDrumVar = 0.0f;
			float kickDrumThreshold = 0.0f;
			float snareDrumAvg = 0.0f;
			float snareDrumVar = 0.0f;
			float snareDrumThreshold = 0.0f;

			for (int i = _kickDrumHistory.size() - 42; i < _kickDrumHistory.size(); i++)
			{
				kickDrumAvg += _kickDrumHistory[i] / 42.0f;
			}

			for (int i = _kickDrumHistory.size() - 42; i < _kickDrumHistory.size(); i++)
			{
				kickDrumVar += (_kickDrumHistory[i] - kickDrumAvg) / 42.0f;
			}

			kickDrumThreshold = -15.0f * kickDrumVar + 1.55f;

			for (int i = _snareDrumHistory.size() - 42; i < _snareDrumHistory.size(); i++)
			{
				snareDrumAvg += _snareDrumHistory[i] / 42.0f;
			}

			for (int i = _snareDrumHistory.size() - 42; i < _snareDrumHistory.size(); i++)
			{
				snareDrumVar += (_snareDrumHistory[i] - snareDrumAvg) / 42.0f;
			}

			snareDrumThreshold = -15.0f * snareDrumVar + 1.55f;

			return (kickDrumEnergy > kickDrumThreshold * kickDrumAvg); // | (snareDrumEnergy > snareDrumAvg * snareDrumThreshold);
		}

		return false;
	}
}
