#include "../../../include/entities/characters/Enemy.h"
#include <SFML/Window.hpp>


Enemy::Enemy(float x, float y, const float movSpeed, int life, float coef , int s):
    Character(x, y, movSpeed, life, coef, s), players_list(), it(){

    if (!texture.loadFromFile("assets/textures/EnemySprite.png")) {
        std::cerr << "Failed to load EnemySprite.png!" << std::endl;
    }    

    texture.setSmooth(true);
    sprite.setTexture(texture);
    size.x = sprite.getLocalBounds().width;
    size.y = sprite.getLocalBounds().height;
    sprite.setScale(    
    size.x / sprite.getLocalBounds().width,
    size.y / sprite.getLocalBounds().height
    );

    players_list.clear();
}

Enemy::~Enemy(){
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
    float closer = sqrt(800 * 800 + 600 * 600);
    Vector2f closer_direction;

    for(it = players_list.begin(); it != players_list.end(); it++){
        if(*it){
            // Get direction to player
            Vector2f direction = ((*it)->getPosition() - position);
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

            
            
        }
    }

    if(velocity.y > 0){
        closer_direction.y = 0.f;
    }
    velocity += closer_direction  * pGM->getdt();
    
    moveCharacter();
}

void Enemy::removePlayer(Player *p){
    for(it = players_list.begin(); it != players_list.end(); it++){
        if(*it == p){
            players_list.erase(it);
            return;
        }
  }
}
