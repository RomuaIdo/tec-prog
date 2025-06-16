#include "../../include/graphicalelements/Tile.h"

Tile::Tile(float x, float y, float Parallaxfactor, const string &texturePath) {
  if (texture.loadFromFile(texturePath)) {
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    size = Vector2f(sprite.getGlobalBounds().width,
                    sprite.getGlobalBounds().height);
    centerOrigin();
  }
  parallaxFactor = Parallaxfactor;
}
Tile::~Tile() {
}
void Tile::execute() { draw(); }

float Tile::getParallaxFactor() const { return parallaxFactor; }
