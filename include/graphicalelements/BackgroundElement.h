#ifndef TILE_H
#define TILE_H

#include "../entities/Ente.h"

class BackgroundElement : public Ente {
private:
  float parallaxFactor;
  Vector2f InitialPosition;
public:
  BackgroundElement(float x, float y, float Parallaxfactor,
                    const string &texturePath);
  virtual ~BackgroundElement();
  virtual void execute() override;
  void update(const Vector2f &camPosition);
  float getParallaxFactor() const;
};
#endif
