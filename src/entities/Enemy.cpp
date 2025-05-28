#include "../../include/entities/Enemy.h"
#include "../../include/managers/GraphicsManager.h"
#include <SFML/Window.hpp>


Enemy::Enemy(const float size, float x, float y, const float movSpeed, int life, float coef , int s):
    Character(size, x, y, movSpeed, life, coef, s), players_list(), it(){

    if (!texture.loadFromFile("sprites/EnemySprite.png")) {
        std::cerr << "Failed to load EnemySprite.png!" << std::endl;
    }    

    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setScale(    
    shape.getSize().x / sprite.getLocalBounds().width,
    shape.getSize().y / sprite.getLocalBounds().height
    );

    players_list.clear();
}

Enemy::~Enemy(){
    for( it = players_list.begin(); it != players_list.end(); it++){
        if(*it){
            delete (*it);
            (*it) = NULL;
        }
    }
    players_list.clear();
}

void Enemy::addPlayer(Player *p){
    players_list.push_back(p);
}

void Enemy::attack(Player *p){
    // If player has health and after 2 seconds, it can attack 
    if(p->getHealth() > 0 && pGM->getClockTime() >= 2.f){
        p->loseHealth(strength);
        cout << "Player got hurt!" << endl;
        cout << "He now has:" << p->getHealth() << endl;
        pGM->resetClock();
    }

}

void Enemy::execute(){
    move();
    draw();
    collide();
}

void Enemy::move(){
    const float vel_max = 30.f;
    float closer = sqrt(800 * 800 + 600 * 600);
    Vector2f closer_direction;
    closer_direction.x = 800.f;
    closer_direction.y = 600.f;
    for(it = players_list.begin(); it != players_list.end(); it++){
        if(*it){
            // Get direction to player
            Vector2f direction = ((*it)->getShape().getPosition() - shape.getPosition());
            float module = sqrt(direction.x*direction.x + direction.y*direction.y);


            // To improve
            if(module == 0) {
                attack((*it));
                continue;
            }    

            if(module < closer ){
                closer = module;
                closer_direction = direction;
                closer_direction /= closer;
                closer_direction *= movimentSpeed;
            } 

            
                

            
            // if ((*it)->getShape().getPosition().x > shape.getPosition().x )
            //     velocity.x += movimentSpeed * pGM->getdt();
            // else if ((*it)->getShape().getPosition().x < shape.getPosition().x )
            //     velocity.x += -movimentSpeed * pGM->getdt();
            // else attack(*it);

            if((*it)->getShape().getPosition().x == shape.getPosition().x || 
               (*it)->getShape().getPosition().y == shape.getPosition().y)
                attack(*it);
            else{
                velocity = closer_direction  * pGM->getdt();
            }
        }
    }
    velocity.y *= 20;
    moveCharacter();
}