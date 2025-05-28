#include "../../include/entities/Enemy.h"
#include "../../include/managers/GraphicsManager.h"
#include <SFML/Window.hpp>

Enemy::Enemy(const float size, float x, float y, const float movSpeed, int life, float coef , int s):
    Character(size, x, y, movSpeed, life, coef, s), players_list(), it(){
    shape.setSize(sf::Vector2f(grid_size, grid_size));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Red);
    players_list.clear();
}

Enemy::~Enemy(){
    list<Player*>::iterator it;
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
    p->loseHealth(strength);
}

void Enemy::execute(){
    move();
}

void Enemy::move(){
    const float vel_max = 30.f;
    for(it = players_list.begin(); it != players_list.end(); it++){
        if(*it){
            if ((*it)->getShape().getPosition().x > shape.getPosition().x ){
                velocity.x += movimentSpeed * pGM->getdt();
            }else if ((*it)->getShape().getPosition().x < shape.getPosition().x ){
                velocity.x += -movimentSpeed * pGM->getdt();
            }           
            if (velocity.x > vel_max){
                if(velocity.y > vel_max)
                    velocity.y = vel_max;
                velocity.x = vel_max;
            }else if( velocity.y > vel_max){
                if(velocity.x > vel_max)
                    velocity.x = vel_max;
                velocity.y = vel_max;
            }
            if (velocity.x < -vel_max){
                if(velocity.y < -vel_max)
                    velocity.y = -vel_max;
                velocity.x = -vel_max;
            }else if( velocity.y < -vel_max){
                if(velocity.x < -vel_max)
                    velocity.x = -vel_max;
                velocity.y = -vel_max;
            }

            
            if(velocity.x > 0){
                friction.x = -gravity.y * friction_coef;
                if(velocity.x + friction.x * pGM->getdt() < 0) {
                velocity.x = 0;
                    friction.x = 0;
                }
            }
            else if(velocity.x <0){
                friction.x = gravity.y * friction_coef;
                if(velocity.x + friction.x * pGM->getdt() > 0) {
                    velocity.x = 0;
                    friction.x = 0;
                }
            }
            else
                friction.x = 0;
            
            velocity += gravity * pGM->getdt();
            velocity += friction * pGM->getdt();
            shape.move(velocity);
        }
    }
}