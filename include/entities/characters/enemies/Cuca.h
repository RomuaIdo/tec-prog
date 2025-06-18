#ifndef CUCA_H
#define CUCA_H
#include "../../Projectile.h"
#include "../Enemy.h"
#include <SFML/Graphics.hpp>
#include <list>
#include <math.h>

class Cuca : public Enemy {

    protected:
        list<Projectile *> potions;
        float potionClock;

    public:
        Cuca(float x, float y, const float acel = 10.f, int life = 5, int s = 1);
        ~Cuca();

        /* ---- OWN FUNCTIONS ---- */
        void execute();
        void move();
        void collide(Entity *e);
        void updateClocks();

        /* ---- POTIONS ---- */
        void makePotion();
        void throwPotion();
        void addPotion(Projectile *pot);

        /* ------- PLAYER -------- */
        void attack(Player *p);
};

#endif
