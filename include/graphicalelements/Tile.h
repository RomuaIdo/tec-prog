#ifndef TILE_H
#define TILE_H


#include "../entities/Ente.h"

class Tile : public Ente {
public:
    Tile(float x, float y, const string& texturePath);
    virtual ~Tile() = default;
    virtual void execute() override;
};

#endif
