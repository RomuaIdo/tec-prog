#include "../../include/graphicalelements/Tile.h"

Tile::Tile(float x, float y, const string &texturePath) {
  if (texture.loadFromFile(texturePath)) {
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    size = Vector2f(sprite.getGlobalBounds().width,
                    sprite.getGlobalBounds().height);
    centerOrigin();
  }
}

void Tile::execute() { draw(); }
