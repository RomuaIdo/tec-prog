#include "../../../include/entities/characters/Enemy.h"
#include <SFML/Window.hpp>

Enemy::Enemy(float x, float y, const float acel, int life, float coef , int s):
    Character(x, y, acel, life, coef, s), players_list(), it(){

    if (!texture.loadFromFile("assets/textures/EnemySprite.png")) {
        std::cerr << "Failed to load EnemySprite.png!" << std::endl;
    }    

    sprite.setTexture(texture);
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

    // if(closer_direction.y < 0 && speed.y == 0.f && !in_air){
    //     closer_direction.y = -10.f;
    // }else closer_direction.y = 0.f;
    closer_direction.y = 0.f;

    speed.x += closer_direction.x * pGM->getdt();
    speed.y += closer_direction.y;
    if ( abs(speed.x) > 10.f){
        speed.x = (speed.x/abs(speed.x)) * 10.f;
    }

    moveCharacter();
}

void Enemy::collide(Entity* e){
    Vector2f ePos = e->getPosition();
    Vector2f eSize = e->getSize();

    float dx = (position.x - ePos.x);
    float dy = (position.y - ePos.y);
    // Vector2f variation = Vector2f(dx, dy);

    /* If dx > 0 -> a in b's right  */
    
    /* If dy > 0 -> a is below b    */

    /* The intersection between a and b ,
    *   if they collide, the vector will be
    *   negative in x and y                */

    Vector2f intersection = Vector2f( abs(dx) - (size.x + eSize.x), 
                                      abs(dy) - (size.y + eSize.y) );

    if (intersection.x < 0.0f && intersection.y < 0.0f) {

        /* If intersection in x is less then intersection in y
        /*  means that they are side by side                 */

        if (std::abs(intersection.x) < std::abs(intersection.y)) {
            
            /* To push the character the amount he is inside */                       
            float push = abs(intersection.x / 2.f);

            if (dx > 0) {
                position.x += push;
                setSpeed({0.f + push, getSpeed().y});
            }
            else{
                position.x -= push;
                setSpeed({0.f - push, getSpeed().y});
            } 


        /* If intersection in y is less then intersection in x
        /*  means that character collided in y with obstacle */

        } else {

            /* To push the character the amount he is inside */ 
            float push = abs(intersection.y / 2.f);

            /* c is below o */
            if (dy > 0) {

                position.y += push;

            /* c is on top of o */
            } else {

                /* c can jump */
                changeInAir();
                position.y -= push;
                
                setSpeed({ getSpeed().x, 0.f });
            }
        }
        setPosition(position);
    }
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
        p->takeDamage(strength);
        pGM->resetClock();
    }

}