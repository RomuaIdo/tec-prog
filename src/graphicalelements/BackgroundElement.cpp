#include "../../include/graphicalelements/BackgroundElement.h"

BackgroundElement::BackgroundElement(float x, float y, float Parallaxfactor,
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
BackgroundElement::~BackgroundElement() {}
void BackgroundElement::execute() {
  update(pGM->getCameraCenter());
  draw();
}

void BackgroundElement::update(const Vector2f &camPosition) {
  // Calcula a posição relativa à câmera com fator de paralaxe
  float parallaxX =
      InitialPosition.x + (camPosition.x - InitialPosition.x) * parallaxFactor;
  float parallaxY =
      InitialPosition.y + (camPosition.y - InitialPosition.y) * parallaxFactor;

  sprite.setPosition(parallaxX, parallaxY);
}

float BackgroundElement::getParallaxFactor() const { return parallaxFactor; }
