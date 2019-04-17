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
		_dsp->setParameterInt(FMOD_DSP_FFT_WINDOWSIZE, 1024);

		// 
		r = _system->createSound(soundFile.c_str(), FMOD_LOOP_NORMAL /*FMOD_OPENMEMORY | FMOD_LOOP_NORMAL | FMOD_CREATESAMPLE*/, nullptr, &_sound);
		FMOD_ERROR_CHECK(r);

		r = _system->playSound(_sound, 0, false, &_channel);
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
}
