#include "../../../include/entities/characters/Enemy.h"
#include <SFML/Window.hpp>

Enemy::Enemy()
    :Character(), far(false), players_list(), evilness(){}

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

void Enemy::collide(Entity* e){
        Vector2f ePos = e->getPosition();
    Vector2f eSize = e->getSize();

    float dx = (position.x - ePos.x);
    float dy = (position.y - ePos.y);

    Vector2f intersection =
        Vector2f(abs(dx) - (size.x + eSize.x), abs(dy) - (size.y + eSize.y));

    if (intersection.x < 0.0f && intersection.y < 0.0f) {

        /* If intersection in x is less then intersection in y */
        /*  means that they are side by side                 */

        float push = 0.f;
        if (std::abs(intersection.x) < std::abs(intersection.y)) {
            /* To push the character the amount he is inside */
            if (dynamic_cast<Cloud *>(e)) {
                push = abs(intersection.x);
            } else
                push = abs(intersection.x / 2.f);

            if (dx > 0) {
                position.x += push;
                setVelocity({0.f + push, getVelocity().y});
            } else {
                position.x -= push;
                setVelocity({0.f - push, getVelocity().y});
        }
        /* If intersection in y is less then intersection in x */
        /*  means that character collided in y with obstacle */
        } else {

            /* To push the character the amount he is inside */
            if (dynamic_cast<Cloud *>(e)) {
                push = abs(intersection.y);
            } else
                push = abs(intersection.y / 2.f);

            /* c is below o */
            if (dy > 0) {

                position.y += push;
                velocity.y = 0.f;
                
                /* c is on top of o */
            } else {

                /* c can jump */
                setInAir(false);
                position.y -= push;
                setVelocity({getVelocity().x, 0.f});
            }
        }
        setPosition(position);
        // If the entity is a Player, attack it
        if (dynamic_cast<Player *>(e)) {
            Player *p = static_cast<Player *>(e);
            if (p) {
                attack(p);
            }
        }
    }
}

/* ------------------------------------------- */
/*                GETS AND SETS                */
/* ------------------------------------------- */

int Enemy::getEvilness() {
    return evilness;
}
