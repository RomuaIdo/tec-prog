#include "../../../include/entities/characters/Enemy.h"
#include <SFML/Window.hpp>

Enemy::Enemy(float x, float y, const float acel, int life, int s):
    Character(x, y, acel, life, s), far(false), players_list(){
}

Enemy::~Enemy(){
    players_list.clear();
}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */


/* ------------------------------------------- */
/*              PLAYER FUNCTIONS               */
/* ------------------------------------------- */

void Enemy::removePlayer(Player *p){
    for(auto it = players_list.begin(); it != players_list.end(); it++){
        if((*it) == p){
            players_list.erase(it);
            return;
        }
  }
}

void Enemy::addPlayer(Player *p){
    players_list.push_back(p);
}
