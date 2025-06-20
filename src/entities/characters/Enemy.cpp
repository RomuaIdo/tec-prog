#include "../../../include/entities/characters/Enemy.h"
#include <SFML/Window.hpp>

Enemy::Enemy(float x, float y, const float acel, int life, int s):
    Character(x, y, acel, life, s), far(false), players_list(), evilness(0){
}

Enemy::~Enemy(){
    players_list.clear();
}

/* ------------------------------------------- */
/*              PLAYER FUNCTIONS               */
/* ------------------------------------------- */
void Enemy::removePlayer(Player *p){
    list<Player*>::iterator it;
    for(it = players_list.begin(); it != players_list.end(); it++){
        if((*it) == p){
            players_list.erase(it);
            return;
        }
    }
}

void Enemy::addPlayer(Player *p){
    players_list.push_back(p);
}

void Enemy::verifyDeadPlayers(){
  list<Player*>::iterator it;

    // Remove players that are dead or not alive
  for(it = players_list.begin(); it != players_list.end(); ) {
        // Verifica se o jogador existe e se está morto
        if(*it && ((*it)->getHealth() <= 0 || !(*it)->getAlive())) {
            it = players_list.erase(it);
        } else {
            ++it;
        }
    }
}

/* ------------------------------------------- */
/*                GETS AND SETS                */
/* ------------------------------------------- */

int Enemy::getEvilness() {
    return evilness;
}
