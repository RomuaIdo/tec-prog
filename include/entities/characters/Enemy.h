#ifndef ENEMY_H
#define ENEMY_H
#include <list>
#include "Character.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <list>
#include <math.h>
using namespace sf;
using namespace std;

class Enemy : public Character {

    protected:
        /* ------- PLAYER -------- */
        vector<Player*> players_list;
        vector<Player*>::iterator it;

    public:

        Enemy(float x, float y, const float acel, int life = 5, float coef = 0.5, int s = 1);
        virtual ~Enemy();

        /* ---- OWN FUNCTIONS ---- */
        virtual void execute() = 0;
        virtual void move() = 0;
        virtual void collide(Entity* e) = 0;

        /* ------- PLAYER -------- */
        virtual void addPlayer(Player *p);
        virtual void removePlayer(Player *p);
        virtual void attack(Player *p) = 0;
};

#endif
