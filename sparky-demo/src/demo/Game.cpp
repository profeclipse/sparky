#include <format>
#include <json/json.h>
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
	loadAtlas();

	loadLayers();

#if PLAY_SOUNDS
	SoundManager::add(new Sound("start","res/sounds/start-music.ogg"));
	SoundManager::get("start")->play();
#endif
}

void Game::tick() {
	static uint16_t ticks = 0;
	m_fpsLabel->setText(fmt::format("{:4d} fps {:2d} ups {:.2f} ms",getFPS(),getUPS(),getFrameTime()));
	//SP_TRACE("[tick] {}",m_fpsLabel->getText().c_str());

#if FIXED_RUN_TIME
	if (++ticks >= 5) {
		m_window->close();
	}
#endif
}

void Game::update(const TimeStep& ts) {
	static float xdir = 1.0f;
	static float ydir = 1.0f;
	static float speed = 120.0f;	// pixels per second
	float elapsed = ts.getSeconds();

	const vec2& size = m_sprite->getSize();
	vec3 pos = m_sprite->getPosition();

	pos.x += xdir * speed * elapsed;
	pos.y += ydir * speed * elapsed;
	if (((pos.x+size.x) > 960) || (pos.x < 0)) {
		xdir = -xdir;
		pos.x += xdir * speed * elapsed;
	}
	if (((pos.y+size.y) > 540) || (pos.y < 0)) {
		ydir = -ydir;
		pos.y += ydir * speed * elapsed;
	}

	m_sprite->setPosition(pos);
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
	TextureManager::add(new Texture("pacman","res/images/pac-man-all.png"));
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
	m_backgroundLayer->add(new Sprite(50.0f,50.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV(0)));
	m_backgroundLayer->add(new Sprite(120.f,50.0f,64.0f,64.0f,m_textureAtlas->getTexture(),
				m_textureAtlas->getUV(1)));

	m_sprite = new Sprite(200.0f,150.0f,16.0f,16.0f,TextureManager::get("sprite"));
	m_backgroundLayer->add(m_sprite);
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

void Game::loadAtlas() {
	std::string fileName = "res/atlas/pacman.json";
	std::string str = read_file(fileName.c_str());

	if (str.length() == 0) {
		SP_TRACE("[loadAtlas] - no data or file not found '{}'",fileName);
		return;
	}

	Json::Value atlas;
	Json::Reader reader;
    reader.parse(str,atlas);

	std::string name = atlas["atlas"]["name"].asString();
	SP_TRACE("[loadAtlas] - Loading texture atlas '{}'",name);

	Texture* texture = TextureManager::get(name);
	vec2 tsize = vec2(texture->getWidth(),texture->getHeight());

	std::vector<std::vector<vec2>> allUVs;

	float px = 1.0f / tsize.x;		// one pixel width in texture space
	float half_px = px * 0.5f;		// 1/2 pixel width in texture space
	float py = 1.0f / tsize.y;		// one pixel height in texture space
	float half_py = py * 0.5;		// 1/2 pixel height in texture space

	Json::Value frames = atlas["atlas"]["frames"];
	for (auto &frame : frames) {
		int x = frame["x"].asInt();
		int y = frame["y"].asInt();
		int w = frame["w"].asInt();
		int h = frame["h"].asInt();
		std::vector<vec2> uvs;
		vec2 uv;

		float tx = x * px - half_px;
		float ty = (tsize.y - y) * py - half_py;
		float tw = float(w) * px + px;
		float th = float(h) * py + py;

		uv.x = tx;
		uv.y = ty;
		uvs.push_back(uv);
		uv.y = ty + th;
		uvs.push_back(uv);
		uv.x = tx + tw;
		uvs.push_back(uv);
		uv.y = ty;
		uvs.push_back(uv);

		SP_TRACE("[loadAtlas] - Coords {},{} {},{} {},{} {},{}",
				uvs[0].x,uvs[0].y,uvs[1].x,uvs[1].y,uvs[2].x,uvs[2].y,uvs[3].x,uvs[3].y);

		allUVs.push_back(uvs);
	}

	m_textureAtlas = new TextureAtlas(texture,allUVs);
}
