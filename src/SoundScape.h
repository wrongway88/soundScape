#ifndef SOUND_SCAPE_H
#define SOUND_SCAPE_H

#define _SILENCE_TR2_SYS_NAMESPACE_DEPRECATION_WARNING

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/CameraUi.h"

#include "terrain/terrain/Terrain.h"
#include "core/graphics/MeshBufferObject.h"
#include "core/graphics/Shader.h"

using namespace ci;
using namespace ci::app;

class SoundScape : public App
{
public:
	void setup() override;
	void update() override;

	void mouseDown(MouseEvent event) override;
	void mouseUp(MouseEvent event) override;
	void mouseWheel(MouseEvent event) override;
	void mouseMove(MouseEvent event) override;
	void mouseDrag(MouseEvent event) override;

	void keyDown(KeyEvent event) override;
	void keyUp(KeyEvent event) override;

	void draw() override;

private:
	void createTerrain();

	std::vector<vec2> m_points;

	std::vector<float> m_currentSpectrum;
	std::vector<std::vector<float>> m_spectrumOverTime;

	Terrain* m_terrain;
	MeshBufferObject m_terrainMeshBuffer;
	Shader m_phongShader;

	ci::vec3 m_lightPosition;

	ci::CameraPersp m_camera;
	ci::CameraUi m_cameraUI;
};

#endif // SOUND_SCAPE_H
