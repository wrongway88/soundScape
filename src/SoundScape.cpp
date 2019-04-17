#include "SoundScape.h"

#include "core/utility/logging/logging.h"
#include "core/utility/logging/ConsoleLogger.h"
#include "core/utility/logging/FileLogger.h"

#include <Windows.h>

#include "sound/WaveExtractor.h"

void prepareSettings(SoundScape::Settings* settings)
{
	FILE* f;
	AllocConsole();
	freopen_s(&f, "CON", "w", stdout);
}

void SoundScape::setup()
{
	std::shared_ptr<ConsoleLogger> consoleLogger = std::make_shared<ConsoleLogger>();
	// std::shared_ptr<FileLogger> fileLogger = std::make_shared<FileLogger>();
	consoleLogger->setLogLevel(Logger::LOG_WARNINGS | Logger::LOG_ERRORS);
	LogManager::getInstance()->addLogger(consoleLogger);
	// LogManager::getInstance()->addLogger(fileLogger);

	LOG_INFO_STREAM(<< "Logging initialized");

	WaveExtractor::setup(".\\data\\test.wav");
}

void SoundScape::update()
{
	WaveExtractor::update();

	m_currentSpectrum = WaveExtractor::getSpectrum();
}

void SoundScape::mouseDrag(MouseEvent event)
{
	m_points.push_back(event.getPos());
}

void SoundScape::keyDown(KeyEvent event)
{
	if (event.getChar() == 'f')
	{
		setFullScreen(!isFullScreen());
	}
	else if (event.getCode() == KeyEvent::KEY_SPACE)
	{
		m_points.clear();
	}
	else if (event.getCode() == KeyEvent::KEY_ESCAPE)
	{
		if (isFullScreen())
			setFullScreen(false);
		else
			quit();
	}
}

void SoundScape::draw()
{
	gl::clear(Color::gray(0.1f));

	gl::color(0.9f, 0.9f, 0.9f);

	int windowHeight = getWindow()->getHeight();

	int xPos = 0;
	for (int i = 0; i < m_currentSpectrum.size(); i++)
	{
		int lineLength = m_currentSpectrum[i] * windowHeight;

		gl::drawLine(ci::vec2(xPos, windowHeight), ci::vec2(xPos, windowHeight - lineLength));

		++xPos;
	}

	gl::color(1.0f, 0.5f, 0.25f);

	gl::begin(GL_LINE_STRIP);
	for (const vec2 &point : m_points)
	{
		gl::vertex(point);
	}
	gl::end();
}

CINDER_APP(SoundScape, RendererGl, prepareSettings)
