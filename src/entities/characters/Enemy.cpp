#include "../../../include/entities/characters/Enemy.h"
#include <SFML/Window.hpp>

Enemy::Enemy(float x, float y, const float acel, int life, float coef , int s):
    Character(x, y, acel, life, coef, s), players_list(), it(){

    if (!texture.loadFromFile("assets/textures/EnemySprite.png")) {
        std::cerr << "Failed to load EnemySprite.png!" << std::endl;
    }    

    configSprite(); 

    players_list.clear();
}

Enemy::~Enemy(){
    players_list.clear();
}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Enemy::move(){
    float closer = sqrt(800 * 800 + 600 * 600);
    Vector2f closer_direction = Vector2f(0.f,0.f);

    for(it = players_list.begin(); it != players_list.end(); it++){
        if(*it){
            // Get direction to player (feet to feet)
            Vector2f direction = ( ((*it)->getPosition() + (*it)->getSize()) - (position + size) );
            float module = sqrt(direction.x*direction.x + direction.y*direction.y);

            if(module < closer ){
                closer = module;
                closer_direction = direction;

                // Normalize vector
                closer_direction /= closer;

                closer_direction *= aceleration;
            } 
        }
    }

    if(closer_direction.y < 0 && speed.y == 0.f && !in_air){
        closer_direction.y = -10.f;
    }else closer_direction.y = 0.f;
    

    speed.x += closer_direction.x * pGM->getdt();
    speed.y += closer_direction.y;
    if ( abs(speed.x) > 10.f){
        speed.x = (speed.x/abs(speed.x)) * 10.f;
    }

    moveCharacter();
}

void Enemy::collide(){
    speed = Vector2f(0.f,0.f);
}

void Enemy::execute(){
    move();
    draw();
}

/* ------------------------------------------- */
/*              PLAYER FUNCTIONS               */
/* ------------------------------------------- */

void Enemy::removePlayer(Player *p){
    for(it = players_list.begin(); it != players_list.end(); it++){
        if(*it == p){
            players_list.erase(it);
            return;
        }
  }
}

void Enemy::addPlayer(Player *p){
    players_list.push_back(p);
}

void Enemy::attack(Player *p){
    /* If player has health and after 2 seconds, then he can attack */
    if(p->getHealth() > 0 && pGM->getClockTime() >= 2.f){
        p->loseHealth(strength);
        cout << "Player got hurt!" << endl;
        cout << "He now has:" << p->getHealth() << endl;
        pGM->resetClock();
    }

}