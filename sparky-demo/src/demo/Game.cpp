#include <format>
#include "Game.h"
#include "TileLayer.h"

#define DEMO_LIGHTING 0
#define PLAY_SOUNDS 0
#define FIXED_RUN_TIME 0

using namespace sparky;

#ifdef __EMSCRIPTEN__
const std::string Game::SHADER_DIR = "res/shaders/es3/";
#else
const std::string Game::SHADER_DIR = "res/shaders/gl33/";
#endif

Game::Game() {
	Log::setLogLevel(LogLevel::TRACE);
}

Game::~Game() {
	delete m_backgroundLayer;
	delete m_guiLayer;
}

void Game::init() {
	initWindow();
	initFonts();
	loadTextures();
	loadAnimations();
	loadLayers();

#if PLAY_SOUNDS
	SoundManager::add(new Sound("start","res/sounds/start-music.ogg"));
	SoundManager::get("start")->play();
#endif
}

void Game::tick() {
	static uint16_t ticks = 0;
	m_fpsLabel->setText(fmt::format("{:4d} fps {:2d} ups {:.2f} ms",getFPS(),getUPS(),getFrameTime()));
#	ifndef __EMSCRIPTEN__
		SP_TRACE("[tick] - {}",m_fpsLabel->getText());
#	endif

#if FIXED_RUN_TIME
	if (++ticks >= 5) {
		m_window->close();
	}
#endif
}

void Game::update(const TimeStep& ts) {
	m_blinky->update();

	vec3 position = m_blinky->getPosition();
	const vec2& size = m_blinky->getSize();

	if (position.x > 960) {
		position.x = -size.x;
		m_blinky->setPosition(position);
	}
}

void Game::render() {
	m_backgroundLayer->render();
	m_guiLayer->render();
}

void Game::initWindow() {
	createWindow("Sparky Demo",960,960/16*9);

	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
}

void Game::initFonts() {
	FontManager::setScale(960.0f/(float)m_window->getWidth(),540.0f/(float)m_window->getHeight());

	FontManager::add(new Font("SourceSansPro","res/fonts/SourceSansPro-Light.ttf",36));
	FontManager::add(new Font("Consola","res/fonts/consola.ttf",28));
	FontManager::add(new Font("SpaceGrotesk","res/fonts/SpaceGrotesk-Light.ttf",28));
}

void Game::loadTextures() {
	TextureManager::add(new Texture("girl1","res/images/test.jpg"));
	TextureManager::add(new Texture("sprite","res/images/tb.png"));
	TextureAtlasManager::add(new TextureAtlas("res/atlas/pacman-atlas.json"));

	m_textureAtlas = TextureAtlasManager::get("pacman");
	if (m_textureAtlas == nullptr) {
		SP_ERROR("[Game::loadTextures] - failed to retrieve texture atlas 'pacman'");
	}
}

void Game::loadAnimations() {
	m_blinkyAnimation = loadAnimation("res/animations/blinky-anim.json");
}

void Game::loadLayers() {
	loadBackgroundLayer();
	loadGUILayer();
}

Animation2D* Game::loadAnimation(const std::string& file) {
	return new Animation2D(file);
}

void Game::loadBackgroundLayer() {
	std::string vertShaderPath = SHADER_DIR + "basic.vert";
#if DEMO_LIGHTING
	std::string fragShaderPath = SHADER_DIR + "basic.frag";
#else
	std::string fragShaderPath = SHADER_DIR + "basicnl.frag";
#endif

	Shader* shader = new Shader(vertShaderPath.c_str(),fragShaderPath.c_str());
#ifdef __EMSCRIPTEN__
	shader->enable();
	shader->setUniformMat4("vw_matrix",mat4::identity());
	shader->setUniformMat4("ml_matrix",mat4::identity());
	shader->disable();
#endif

	m_backgroundLayer = new TileLayer(shader);
	m_backgroundLayer->add(new Sprite(0.0f,0.0f,m_window->getWidth(),m_window->getHeight(),
				TextureManager::get("girl1")));
	m_backgroundLayer->add(new Sprite(50.0f,440.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("blinkyl1")));
	m_backgroundLayer->add(new Sprite(120.0f,440.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("blinkyl2")));
	m_backgroundLayer->add(new Sprite(190.0f,440.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("blinkyr1")));
	m_backgroundLayer->add(new Sprite(260.0f,440.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("blinkyr2")));
	m_backgroundLayer->add(new Sprite(330.0f,440.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("blinkyu1")));
	m_backgroundLayer->add(new Sprite(400.0f,440.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("blinkyu2")));
	m_backgroundLayer->add(new Sprite(470.0f,440.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("blinkyd1")));
	m_backgroundLayer->add(new Sprite(540.0f,440.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("blinkyd2")));
	m_backgroundLayer->add(new Sprite(50.0f,370.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("inkyl1")));
	m_backgroundLayer->add(new Sprite(120.0f,370.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("inkyl2")));
	m_backgroundLayer->add(new Sprite(190.0f,370.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("inkyr1")));
	m_backgroundLayer->add(new Sprite(260.0f,370.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("inkyr2")));
	m_backgroundLayer->add(new Sprite(330.0f,370.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("inkyu1")));
	m_backgroundLayer->add(new Sprite(400.0f,370.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("inkyu2")));
	m_backgroundLayer->add(new Sprite(470.0f,370.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("inkyd1")));
	m_backgroundLayer->add(new Sprite(540.0f,370.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("inkyd2")));
	m_backgroundLayer->add(new Sprite(50.0f,300.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("pinkyl1")));
	m_backgroundLayer->add(new Sprite(120.0f,300.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("pinkyl2")));
	m_backgroundLayer->add(new Sprite(190.0f,300.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("pinkyr1")));
	m_backgroundLayer->add(new Sprite(260.0f,300.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("pinkyr2")));
	m_backgroundLayer->add(new Sprite(330.0f,300.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("pinkyu1")));
	m_backgroundLayer->add(new Sprite(400.0f,300.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("pinkyu2")));
	m_backgroundLayer->add(new Sprite(470.0f,300.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("pinkyd1")));
	m_backgroundLayer->add(new Sprite(540.0f,300.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("pinkyd2")));
	m_backgroundLayer->add(new Sprite(50.0f,230.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("clydel1")));
	m_backgroundLayer->add(new Sprite(120.0f,230.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("clydel2")));
	m_backgroundLayer->add(new Sprite(190.0f,230.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("clyder1")));
	m_backgroundLayer->add(new Sprite(260.0f,230.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("clyder2")));
	m_backgroundLayer->add(new Sprite(330.0f,230.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("clydeu1")));
	m_backgroundLayer->add(new Sprite(400.0f,230.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("clydeu2")));
	m_backgroundLayer->add(new Sprite(470.0f,230.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("clyded1")));
	m_backgroundLayer->add(new Sprite(540.0f,230.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV("clyded2")));

	m_blinky = new AnimatedSprite(50.0f,140.0f,64.0f,64.0f,m_blinkyAnimation);
	m_blinky->setSequence("blinky-right");
	m_blinky->setAnimating(true);
	m_blinky->setDirection(vec2(1.0f,0.0f));
	m_blinky->setSpeed(1.0f);
	m_backgroundLayer->add(m_blinky);
}

void Game::loadGUILayer() {
	std::string vertShaderPath = SHADER_DIR + "basic.vert";
	std::string fragShaderPath = SHADER_DIR + "basicnl.frag";

	Shader* shader = new Shader(vertShaderPath.c_str(),fragShaderPath.c_str());
#ifdef __EMSCRIPTEN__
	shader->enable();
	shader->setUniformMat4("vw_matrix",mat4::identity());
	shader->setUniformMat4("ml_matrix",mat4::identity());
	shader->disable();
#endif
	m_guiLayer = new TileLayer(shader);

	Group *guiGroup = new Group(mat4::translate(vec3(5.0f,500.0f,0.0f)));
	guiGroup->add(new Sprite(0.0f,0.0f,375.0f,32.0f,0x42FFFFFF));
	m_fpsLabel = new Label("",5.0f,8.0f,"Consola",0x7000FF00);
	guiGroup->add(m_fpsLabel);
	m_guiLayer->add(guiGroup);
}
