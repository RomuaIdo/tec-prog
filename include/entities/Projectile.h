#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <SFML/Graphics.hpp>
#include "Entity.h"
using namespace sf;

class Projectile : public Entity{

    private:
        /* ------ STATUS ------- */
        float velocity;
        
        /* ------ FLAGS ------- */
        bool active;
    
    public:
        Projectile(float x, float y, float vel = 10.f);
        ~Projectile() override = default;

        /* --- OWN FUNCTIONS --- */
        void collide();

        void execute();
        void move();
        bool getActive();
        void setActive(bool Active);
};  

#endif
