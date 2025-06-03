#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <SFML/Graphics.hpp>
#include "Entity.h"
using namespace sf;

class Projectile : public Entity{

    private:
        bool active;
        float velocity;
    
    public:
        Projectile(float x, float y, float vel = 10.f);
        ~Projectile();
        void collide();
        void draw();
        Drawable& getDrawable();
        void execute();
        void move();
        bool getActive();

};  

#endif