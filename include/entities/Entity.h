#ifndef ENTITY_H
#define ENTITY_H
#include "Ente.h"
#include <SFML/Graphics.hpp>
#include "../managers/GraphicsManager.h"
using namespace sf;

class Entity : public Ente {
    
    protected:
        RectangleShape shape;
        const float grid_size;

    public:
        Entity(const float size, float x, float y);
        virtual ~Entity();

        virtual void execute() = 0;
        virtual void draw();
        virtual void collide() = 0;
        virtual Drawable& getDrawable();
        sf::RectangleShape getShape();

};
#endif
