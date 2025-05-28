#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "Entity.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Obstacle : public Entity{

    private:
        bool harmful;

    public:
        Obstacle(bool harm, float x, float y);
        virtual ~Obstacle();
        virtual void execute();
        virtual void ObstacleAction();
        virtual void collide();
        virtual void dealDamage();

};

#endif