#pragma once

#include <string>
#include "sparky-core.h"

class Game : public sparky::Application {
	public:
		sparky::Layer*	m_backgroundLayer;
		sparky::Layer*	m_guiLayer;
		sparky::Label*	m_fpsLabel;
		sparky::Sprite* m_sprite;
		sparky::TextureAtlas* m_textureAtlas;

		static const std::string SHADER_DIR;

	public:
		Game();
		~Game();

		void init() override;
		void tick() override;
		void update() override;
		void render() override;

		void initWindow();
		void initFonts();
		void loadTextures();
		void loadLayers();
		void loadBackgroundLayer();
		void loadGUILayer();
};
