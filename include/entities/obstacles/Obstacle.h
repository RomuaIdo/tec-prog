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
        virtual void execute();
        virtual void ObstacleAction();

};

#endif
