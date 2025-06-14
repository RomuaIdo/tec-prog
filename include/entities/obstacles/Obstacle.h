#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "../Entity.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Obstacle : public Entity{

    private:
        /* ------ STATUS ------- */
        bool harmful;

    public:
        Obstacle(bool harm, float x, float y);
        virtual ~Obstacle();

        // virtual void dealDamage() = 0;
        
        /* ---- OWN FUNCTIONS ---- */
        virtual void obstacleAction(Entity* e);
        virtual void execute();
        virtual void collide(Entity* e);
        // virtual void execute()        = 0;
        // virtual void collide()        = 0;
        // virtual void ObstacleAction() = 0;


};

#endif
