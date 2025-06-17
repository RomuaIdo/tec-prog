#ifndef TILE_H
#define TILE_H


#include "../entities/Ente.h"

class BackgroundElement : public Ente {
private:
  float parallaxFactor;
public:
    BackgroundElement(float x, float y, float Parallaxfactor, const string& texturePath);
    virtual ~BackgroundElement();
    virtual void execute() override;
    float getParallaxFactor() const;
};
#endif
