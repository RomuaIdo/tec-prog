#ifndef ENEMY_H
#define ENEMY_H
#include <list>
#include "Entity.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Enemy : public Character{

    protected:

        list<Player*> players_list;
        list<Player*>::iterator it;
        
    public:

        Enemy(const float size, float x, float y, const float movSpeed, int life = 5, float coef = 0.5, int s = 1);
        ~Enemy();
        void addPlayer(Player *p);
        void attack(Player *p);
        void execute();
        void move();
};


#endif