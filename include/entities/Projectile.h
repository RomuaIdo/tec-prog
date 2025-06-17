#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "characters/Character.h"
using namespace sf;

class Projectile : public Entity{

    private:
        /* ------ STATUS ------- */
        Texture potion;
        Texture bullet;
        
        /* ------ FLAGS ------- */
        bool active;
    
    public:
        /* --- CONSTRUCTORS --- */
        Projectile();
        Projectile(float x, float y, Vector2f vel);
        ~Projectile();

        /* --- OWN FUNCTIONS --- */
        void collide(Entity* other);
        void execute();
        void move();
        bool getActive();
        void setActive(bool Active = false);
};  

#endif
