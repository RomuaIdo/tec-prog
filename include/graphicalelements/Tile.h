#ifndef TILE_H
#define TILE_H


#include "../entities/Ente.h"

class Tile : public Ente {
private:
  float parallaxFactor;
public:
    Tile(float x, float y, float Parallaxfactor, const string& texturePath);
    virtual ~Tile();
    virtual void execute() override;
    float getParallaxFactor() const;
};
#endif
