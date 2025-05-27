#ifndef ENTE_H
#define ENTE_H
#include <SFML/Graphics.hpp>
#include "../managers/Graphical_Manager.h"
using namespace sf;


class Ente {
protected:
  static Graphical_Manager* pGG;
  Sprite sprite;
  Texture texture;

public:
  Ente();
  virtual ~Ente();
  virtual void draw() = 0;
  virtual Drawable& getDrawable() = 0;
};

#endif
