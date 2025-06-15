#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "../Entity.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Obstacle : public Entity{

    protected:
        /* ------ STATUS ------- */
        bool harmful;
        bool is_active;

    public:
        Obstacle(float x, float y,bool harm = false);
        virtual ~Obstacle();

        // virtual void dealDamage() = 0;
        
        /* ---- OWN FUNCTIONS ---- */
        virtual void execute()                 = 0;
        virtual void collide(Entity* e)        = 0;
        virtual void obstacleAction(Entity* e) = 0;

        /* ----- GETS & SETS ----- */

        void setActive(bool active);
        bool isActive() const;



};

#endif
