#ifndef ENEMY_H
#define ENEMY_H
#include <list>
#include "Character.h"
#include <SFML/Graphics.hpp>
#include <list>
#include <math.h>
using namespace sf;
using namespace std;

class Player;

class Enemy : public Character {

    protected:
        /* ------- PLAYER -------- */
        list<Player*> players_list;

    public:
        Enemy();
        Enemy(float x, float y, const float acel, int life = 5, float coef = 0.5, int s = 1);
        virtual ~Enemy();

        /* ---- OWN FUNCTIONS ---- */
        virtual void collide(Entity *other);
        virtual void execute();
        virtual void move();

        /* ------- PLAYER -------- */
        virtual void addPlayer(Player *p);
        virtual void removePlayer(Player *p);
        virtual void attack(Player *p);
};

#endif
