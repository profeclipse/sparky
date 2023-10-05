#include "Game.h"
#include "TileLayer.h"

#define DEMO_LIGHTING 0
#define PLAY_SOUNDS 0

using namespace sparky;

#ifdef __EMSCRIPTEN__
const std::string Game::SHADER_DIR = "res/shaders/es3/";
#else
const std::string Game::SHADER_DIR = "res/shaders/gl33/";
#endif

Game::Game() {
}

Game::~Game() {
	SP_TRACE("[Game] dtor");
	delete m_backgroundLayer;
	SP_TRACE("[Game] dtor - deleted m_backgroundLayer");
	delete m_guiLayer;
	SP_TRACE("[Game] dtor - deleted m_guiLayer");
}

void Game::init() {
	initWindow();
	initFonts();
	loadTextures();
	loadLayers();

#if PLAY_SOUNDS
	SoundManager::add(new Sound("start","res/sounds/start-music.ogg"));
	SoundManager::get("start")->play();
#endif
}

void Game::tick() {
	static uint16_t ticks = 0;
	m_fpsLabel->setText(std::to_string(getFPS()) + " fps");
	SP_TRACE("[tick] {}",m_fpsLabel->getText().c_str());

	if (++ticks >= 5) {
		m_window->close();
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
	TextureManager::add(new Texture("girl2","res/images/meisa.jpg"));
	TextureManager::add(new Texture("sprite","res/images/tb.png"));
}

void Game::loadLayers() {

	loadBackgroundLayer();
	loadGUILayer();
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
	m_backgroundLayer->add(new Sprite(100.0f,100.0f,m_window->getWidth()-200,m_window->getHeight()-200,
				TextureManager::get("girl2")));
	m_backgroundLayer->add(new Sprite(200.0f,200.0f,16.0f,16.0f,
				TextureManager::get("sprite")));
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
	guiGroup->add(new Sprite(0.0f,0.0f,150.0f,32.0f,0x42FFFFFF));
	m_fpsLabel = new Label("",5.0f,8.0f,"Consola",0x7000FF00);
	guiGroup->add(m_fpsLabel);
	m_guiLayer->add(guiGroup);
}