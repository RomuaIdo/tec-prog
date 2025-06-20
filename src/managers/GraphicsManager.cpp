#include "../../include/managers/GraphicsManager.h"
#include "../../include/entities/Ente.h"
#include "../../include/managers/CollisionManager.h"

GraphicsManager *GraphicsManager::instance(nullptr);

float GraphicsManager::clock_time(0.f);

GraphicsManager *GraphicsManager::getInstance() {
  if (instance == nullptr) {
    instance = new GraphicsManager();
  }
  return instance;
}

GraphicsManager::~GraphicsManager() {
  map<string, Texture *>::iterator it;
  for (it = textures.begin(); it != textures.end(); it++) {
    delete it->second;
    it->second = nullptr;
  }
}

GraphicsManager::GraphicsManager() : pWindow(nullptr), view(nullptr) { setClock(); }

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void GraphicsManager::draw(Ente *ente) {
  if (pWindow != nullptr) {
    pWindow->draw(ente->getDrawable());
  } else {
    std::cerr << "Window not initialized." << std::endl;
  }
}

void GraphicsManager::draw(Text *text) {
  if (pWindow != nullptr) {
    pWindow->draw(*text);
  } else {
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

void GraphicsManager::operator++() { clock_time += dt; }

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

RenderWindow *GraphicsManager::getWindow() const { return pWindow; }

void GraphicsManager::setWindow(RenderWindow *window) { pWindow = window; }

void GraphicsManager::setCameraCenter(Vector2f center) {
  if (pWindow != nullptr) {
    if (view == nullptr) {
      view = new View();
      view->setSize(pWindow->getSize().x, pWindow->getSize().y);
    }
    
    // Mantém Y fixo (300.f) e só ajusta X
    Vector2f newCenter(center.x, 300.f); 
    view->setCenter(newCenter);
    pWindow->setView(*view);
  } else {
    cerr << "Window not initialized." << endl;
  }
}

void GraphicsManager::setCamera(View *view) {
  if (pWindow != nullptr) {
    pWindow->setView(*view);
  } else {
    cerr << "Window not initialized." << endl;
  }
}

void GraphicsManager::setClock() { dt = dt_clock.restart().asSeconds(); }

float GraphicsManager::getdt() const { return dt; }

const Clock GraphicsManager::getClockdt() const { return dt_clock; }

float GraphicsManager::getClockTime() const { return clock_time; }

void GraphicsManager::resetClock() { clock_time = 0; }

Vector2f GraphicsManager::getCameraCenter() const {
  if (pWindow != nullptr && view != nullptr) {
    return view->getCenter();
  } else {
    cerr << "Window or view not initialized." << endl;
    return Vector2f(0.f, 0.f);
  }
}

Texture GraphicsManager::loadTexture(const string &path) {
  if (textures.find(path) != textures.end()) {
    return *textures[path];
  } else {
    Texture *texture = new Texture();
    if (texture->loadFromFile(path)) {
      textures[path] = texture;
      return *texture;
    } else {
      cerr << "Failed to load texture from: " << path << endl;
      delete texture; // Clean up if loading fails
      return Texture(); // Return an empty texture
    }
  }
}
