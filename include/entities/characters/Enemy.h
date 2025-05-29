#ifndef ENEMY_H
#define ENEMY_H
#include <list>
#include "Character.h"
#include "Player.h"
#include <math.h>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Enemy : public Character{

    protected:

        list<Player*> players_list;
        list<Player*>::iterator it;

    public:

        Enemy(float x, float y, const float movSpeed, int life = 5, float coef = 0.5, int s = 1);
        virtual ~Enemy();
        virtual void addPlayer(Player *p);
        virtual void removePlayer(Player *p);
        virtual void attack(Player *p);
        virtual void execute();
        virtual void move();
};


#endif
