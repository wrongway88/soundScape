#ifndef SOUND_SCAPE_H
#define SOUND_SCAPE_H

#define _SILENCE_TR2_SYS_NAMESPACE_DEPRECATION_WARNING

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

class SoundScape : public App
{
public:
	void setup() override;
	void update() override;
	void mouseDrag(MouseEvent event) override;
	void keyDown(KeyEvent event) override;
	void draw() override;

private:
	std::vector<vec2> m_points;

	std::vector<float> m_currentSpectrum;
};

#endif // SOUND_SCAPE_H
