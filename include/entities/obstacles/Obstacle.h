#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "../Entity.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Player;
class Enemy;

class Obstacle : public Entity {

    protected:
        /* ------ STATUS ------- */
        bool harmful;

    public:
        Obstacle();
        Obstacle(float x, float y, bool harm);
        virtual ~Obstacle();

        /* ---- OWN FUNCTIONS ---- */
        virtual void collide(Entity *e) = 0;
        virtual void execute() = 0;
        virtual void obstacleAction(Entity* e) = 0;
};

#endif
