#include "../../include/managers/GraphicsManager.h"
#include "../../include/entities/Ente.h"

GraphicsManager  *GraphicsManager::instance(nullptr);

float GraphicsManager::clock_time(0.f);

GraphicsManager *GraphicsManager::getInstance() {
  if (instance == nullptr) {
    instance = new GraphicsManager();
  }
  return instance;
}

GraphicsManager::GraphicsManager():
  pWindow(nullptr),
  font(NULL)
{
  font = new Font();
  if (!font->loadFromFile("assets/fonts/arial.ttf")) {
    std::cerr << "Error when trying to load the font." << std::endl;
  }
}

GraphicsManager::~GraphicsManager() {
  map<string, Texture *>::iterator it;
  for (it = textures.begin(); it != textures.end(); it++) {
    delete it->second;
    it->second = nullptr;
  }
  delete font;
}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void GraphicsManager::draw(Ente* ente) {
  if (pWindow != nullptr) {
    pWindow->draw(ente->getDrawable());
  } else{
    std::cerr << "Window not initialized." << std::endl;
  } 
}

bool GraphicsManager::openWindow() const {
  return pWindow != nullptr && pWindow->isOpen();
}

void GraphicsManager::clean() {
  if (pWindow != nullptr) {
    pWindow->clear();
  } else {
    std::cerr << "Window not initialized." << std::endl;
  }
}

void GraphicsManager::show() {
  if (pWindow != nullptr) {
    pWindow->display();
  } else {
    std::cerr << "Window not initialized." << std::endl;
  }
}

void GraphicsManager::operator++(){
    clock_time += dt;
}

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

RenderWindow *GraphicsManager::getWindow() const {
  return pWindow;
}

void GraphicsManager::setWindow(RenderWindow *window) { 
    pWindow = window; 
}

Font *GraphicsManager::getFont() { 
    return font; 
}

void GraphicsManager::setClock(){ 
    dt = dt_clock.restart().asSeconds(); 
}

float GraphicsManager::getdt() const{ 
    return dt; 
}

const Clock GraphicsManager::getClockdt() const { 
    return dt_clock; 
}

float GraphicsManager::getClockTime() const { 
    return clock_time; 
}

void GraphicsManager::resetClock(){ 
    clock_time = 0;
}
