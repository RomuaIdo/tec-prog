#ifndef ENTITY_H
#define ENTITY_H
#include "Ente.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class Entity : public Ente {
    
    protected:
        /* ------ STATUS ------- */
        Vector2f position;

    public:
        Entity();
        Entity(float x, float y);
        virtual ~Entity() = default;

        virtual void execute() = 0;

        /* ---- OWN FUNCTIONS ---- */
        void draw();
        Drawable& getDrawable();

        /* ----- GETS & SETS ----- */
        Vector2f getPosition() const;
        void setPosition(Vector2f pos);

};

#endif
