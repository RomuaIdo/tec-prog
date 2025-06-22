#include "../../include/graphicalelements/BackgroundElement.h"

ge::BackgroundElement::BackgroundElement(float x, float y, float Parallaxfactor,
                                     const string &texturePath)
    : InitialPosition(x, y) {
  texture = pGM->loadTexture(texturePath);
  sprite.setTexture(texture);
  sprite.setPosition(x, y);
  size =
      Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
  centerOrigin();
  parallaxFactor = Parallaxfactor;
}
ge::BackgroundElement::~BackgroundElement() {}
void ge::BackgroundElement::execute() {
  update(pGM->getCameraCenter());
  draw();
}

void ge::BackgroundElement::update(const Vector2f &camPosition) {
  float parallaxX =
      InitialPosition.x + (camPosition.x - InitialPosition.x) * parallaxFactor;
  float parallaxY =
      InitialPosition.y + (camPosition.y - InitialPosition.y) * parallaxFactor;

  sprite.setPosition(parallaxX, parallaxY);
}

float ge::BackgroundElement::getParallaxFactor() const { return parallaxFactor; }
