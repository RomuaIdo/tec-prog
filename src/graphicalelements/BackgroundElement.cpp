#include "../../include/graphicalelements/BackgroundElement.h"

BackgroundElement::BackgroundElement(float x, float y, float Parallaxfactor, const string &texturePath) {
  if (texture.loadFromFile(texturePath)) {
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    size = Vector2f(sprite.getGlobalBounds().width,
                    sprite.getGlobalBounds().height);
    centerOrigin();
  }
  parallaxFactor = Parallaxfactor;
}
BackgroundElement::~BackgroundElement() {
}
void BackgroundElement::execute() { draw(); }

float BackgroundElement::getParallaxFactor() const { return parallaxFactor; }
