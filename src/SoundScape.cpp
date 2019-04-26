#include "SoundScape.h"

#include "core/utility/logging/logging.h"
#include "core/utility/logging/ConsoleLogger.h"
#include "core/utility/logging/FileLogger.h"

#include <Windows.h>

#include "sound/WaveExtractor.h"

#include "terrain/terrain/TerrainGenerator.h"
#include "terrain/densityFunction/DensityFunctionSinCosComplex.h"
#include "terrain/densityFunction/DensityFunctionSpectrumSimple.h"

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

	m_terrain = nullptr;

	m_phongShader.load("data/shader/phongShader.vert", "data/shader/phongShader.frag");
	m_phongShader.bindAttribute(0, "vPosition");
	m_phongShader.bindAttribute(1, "vNormal");
	m_phongShader.bindAttribute(2, "vTexcoord");
	m_phongShader.linkShaders();

	createTerrain();

	m_camera.setEyePoint(ci::vec3(0.0f, 0.0f, 0.0f));
	m_camera.setPerspective(45.0f, ci::app::getWindowAspectRatio(), 0.1f, 10000.0f);

	m_cameraUI = ci::CameraUi(&m_camera, ci::app::getWindow());

	m_lightPosition = ci::vec3(0.0f, 100.0f, 0.0f);
}

void SoundScape::update()
{
	WaveExtractor::update();

	m_currentSpectrum = WaveExtractor::getSpectrum();

	m_spectrumOverTime.push_back(m_currentSpectrum);
}

void SoundScape::mouseDown(MouseEvent event)
{
	m_cameraUI.mouseDown(event);
}

void SoundScape::mouseUp(MouseEvent event)
{
	m_cameraUI.mouseUp(event);
}

void SoundScape::mouseWheel(MouseEvent event)
{
	m_cameraUI.mouseWheel(event);
}

void SoundScape::mouseMove(MouseEvent event)
{
	
}

void SoundScape::mouseDrag(MouseEvent event)
{
	// m_points.push_back(event.getPos());

	m_cameraUI.mouseDrag(event);
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
	else if (event.getChar() == 'r')
	{
		createTerrain();
	}
}

void SoundScape::keyUp(KeyEvent event)
{

}

void SoundScape::draw()
{
	gl::clear(Color(0.3f, 0.3f, 0.7f));

	ci::mat4 matView = m_cameraUI.getCamera().getViewMatrix();
	ci::mat4 matViewProj = m_cameraUI.getCamera().getProjectionMatrix() * matView;

	ci::vec4 lightPos4(m_lightPosition.x, m_lightPosition.y, m_lightPosition.z, 1.0f);
	ci::vec3 lightPos = matView * lightPos4;

	ci::gl::pushMatrices();

		ci::gl::enableDepthWrite();
		ci::gl::enableDepthRead();
		ci::gl::setMatrices(m_cameraUI.getCamera());

		m_phongShader.bind();
		m_phongShader.setUniform("modelviewMatrix", matView, false);
		m_phongShader.setUniform("modelviewProjectionMatrix", matViewProj, false);
		m_phongShader.setUniform("vCameraPos", m_cameraUI.getCamera().getEyePoint());

		m_phongShader.setUniform("fLightAmbient", ci::vec4(0.8f, 0.9f, 1.0f, 1.0f));
		m_phongShader.setUniform("fLightDiffuse", ci::vec4(0.8f, 0.9f, 1.0f, 1.0f));
		m_phongShader.setUniform("fLightSpecular", ci::vec4(0.8f, 0.9f, 1.0f, 1.0f));
		m_phongShader.setUniform("fShinyness", 20.0f);

		m_phongShader.setUniform("fMaterialSpecular", ci::vec4(0.1f, 0.3f, 0.12f, 1.0f));
		m_phongShader.setUniform("vLightPosition", lightPos);

		m_terrainMeshBuffer.bindVertexArray();
		m_terrainMeshBuffer.draw();

		m_phongShader.unbind();
	ci::gl::popMatrices();

	/*if (WaveExtractor::detectBeat(m_currentSpectrum))
	{
		gl::color(0.8f, 0.2f, 0.2f);
	}
	else
	{
		gl::color(0.9f, 0.9f, 0.9f);
	}

	int windowHeight = getWindow()->getHeight();

	int xPos = 0;
	for (int i = 0; i < m_currentSpectrum.size(); i++)
	{
		int lineLength = m_currentSpectrum[i] * windowHeight;

		gl::drawLine(ci::vec2(xPos, windowHeight), ci::vec2(xPos, windowHeight - lineLength));

		++xPos;
	}*/
}

void SoundScape::createTerrain()
{
	const float terrainSize = 128.0f;
	const float cellSize = 1.0f;
	const float altScale = 100.0f;

	TerrainGenerator terrainGenerator;

	if (m_spectrumOverTime.size() > 0)
	{
		DensityFunctionSpectrumSimple densityFunction;

		densityFunction.setAltitudeScale(altScale);
		densityFunction.setTerrainSize(terrainSize);
		densityFunction.setSpectrum(m_spectrumOverTime);

		m_terrain = terrainGenerator.generateTerrain(densityFunction, terrainSize, cellSize);
	}
	else
	{
		DensityFunctionSinCosComplex densityFunction;

		m_terrain = terrainGenerator.generateTerrain(densityFunction, terrainSize, cellSize);
	}

	m_terrainMeshBuffer.generateBuffers();
	m_terrainMeshBuffer.bindVertices(m_terrain->getVertices());
	m_terrainMeshBuffer.bindIndices(m_terrain->getIndices());
	m_terrainMeshBuffer.bindNormals(m_terrain->getNormals());
	m_terrainMeshBuffer.bindTexCoords(m_terrain->getTextureCoordinates());
}

CINDER_APP(SoundScape, RendererGl, prepareSettings)
