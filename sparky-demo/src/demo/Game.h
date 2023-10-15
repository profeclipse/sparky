#pragma once

#include <string>
#include "sparky-core.h"

class Game : public sparky::Application {
	public:
		sparky::Layer*	m_backgroundLayer;
		sparky::Layer*	m_guiLayer;
		sparky::Label*	m_fpsLabel;
		sparky::TextureAtlas* m_textureAtlas;
		sparky::Animation2D* m_blinkyAnimation;
		sparky::AnimatedSprite* m_blinky;

		static const std::string SHADER_DIR;

	public:
		Game();
		~Game();

		void init() override;
		void tick() override;
		void update(const sparky::TimeStep& ts) override;
		void render() override;

		void initWindow();
		void initFonts();
		void loadTextures();
		void loadAnimations();
		void loadLayers();
		void loadBackgroundLayer();
		void loadGUILayer();
		sparky::Animation2D* loadAnimation(const std::string& file);
};
