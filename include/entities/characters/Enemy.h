#ifndef ENEMY_H
#define ENEMY_H
#include "Character.h"
#include "Player.h"
#include <list>
#include <math.h>

class Enemy : public Character {

    protected:
        /* ------- PLAYER -------- */
        bool far;
        list<Player*> players_list;

        int evilness;

    public:
        Enemy();
        Enemy(float x, float y, const float acel, int life = 5, int s = 1);
        virtual ~Enemy();

        /* ---- OWN FUNCTIONS ---- */
        virtual void execute() = 0;
        virtual void move() = 0;
        virtual void collide(Entity *e) = 0;
        virtual void updateClocks() = 0;

        /* ------- PLAYER -------- */
        virtual void addPlayer(Player *p);
        virtual void removePlayer(Player *p);
        virtual void attack(Player *p) = 0;

        int getEvilness();
};

#endif
