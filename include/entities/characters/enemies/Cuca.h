#ifndef CUCA_H
#define CUCA_H
#include <list>
#include "../Enemy.h"
#include <SFML/Graphics.hpp>
#include <list>
#include <math.h>
using namespace sf;
using namespace std;

class Cuca : public Enemy {

    protected:

    public:

        Cuca(float x, float y, const float acel = 10.f, int life = 5, float coef = 0.5, int s = 1);
        virtual ~Cuca();

        /* ---- OWN FUNCTIONS ---- */
        void execute();
        void move();
        void collide(Entity* e);
        void trowPotion(Vector2f *direction);

        /* ------- PLAYER -------- */

        void attack(Player *p);
};

#endif
