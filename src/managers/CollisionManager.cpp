#include "../../include/managers/CollisionManager.h"
#include "../../include/entities/characters/Player.h"
#include "../../include/entities/characters/Enemy.h"
#include "../../include/entities/obstacles/Obstacle.h"
#include "../../include/entities/Projectile.h"

CollisionManager* CollisionManager::instance(nullptr);

CollisionManager* CollisionManager::getInstance(){
    if (instance == nullptr) {
        instance = new CollisionManager();
    }
    return instance;
}

CollisionManager::CollisionManager():
    enemies_vector(), obstacles_list(), projectiles_set(){
    enemies_vector.clear();
    obstacles_list.clear();
    projectiles_set.clear();
}

CollisionManager::~CollisionManager(){
    projectiles_set.clear();
    enemies_vector.clear();
    obstacles_list.clear();
}

const bool CollisionManager::verifyCollision(Entity* ent1, Entity* ent2) const{
    if( ent2->getPosition().x + ent2->getSize().x > ent1->getPosition().x )
        return true;
    if( ent2->getPosition().y + ent2->getSize().y > ent1->getPosition().y )
        return true;
    if( ent1->getPosition().x + ent1->getSize().x > ent2->getPosition().x )
        return true;
    if( ent1->getPosition().y + ent1->getSize().y > ent2->getPosition().y )
        return true;
    return false;
}

void CollisionManager::treatEnemiesCollision(){
    // Treat for each player
    for(list<Player*>::iterator it = players_list.begin(); it != players_list.end(); it++){
        if((*it)){
            for(vector<Enemy*>::iterator itEnemy = enemies_vector.begin(); itEnemy != enemies_vector.end(); itEnemy++){
                if(*itEnemy){
                    if(verifyCollision( (*it) , (*itEnemy) ) ){
                        (*it)->moveCharacter((*it)->getVelocity() * static_cast<float>(-1.5));
                        (*itEnemy)->attack((*it));
                    }
                }
            }
        }
    }
}

void CollisionManager::treatObstaclesCollision(){
    // Treat for each player
    for(list<Player*>::iterator it = players_list.begin(); it != players_list.end(); it++){
        if((*it)){
            for(list<Obstacle*>::iterator itObstacle = obstacles_list.begin(); itObstacle != obstacles_list.end(); itObstacle++){
                if(*itObstacle){
                    if(verifyCollision( (*it) , (*itObstacle) ) ){
                        (*it)->moveCharacter((*it)->getVelocity() * static_cast<float>(-1.2));
                    }
                }
            }
        }
    }
}

void CollisionManager::treatProjectilesCollision(){
    // Treat for each player
    for(list<Player*>::iterator it = players_list.begin(); it != players_list.end(); it++){
        if((*it)){
            for(set<Projectile*>::iterator itProjectile = projectiles_set.begin(); itProjectile != projectiles_set.end(); itProjectile++){
                if(*itProjectile){
                    if(verifyCollision( (*it) , (*itProjectile) ) ){
                        (*it)->moveCharacter((*it)->getVelocity()* static_cast<float>(-0.3));
                    }
                }
            }
        }
    }
}

void CollisionManager::addEnemy(Enemy *e){
    enemies_vector.push_back(e);
}

void CollisionManager::addObstacle(Obstacle *o){
    obstacles_list.push_back(o);
}

void CollisionManager::addProjectile(Projectile *p){
    projectiles_set.insert(p);
}

void CollisionManager::execute(){
    treatEnemiesCollision();
    treatObstaclesCollision();
    treatProjectilesCollision();
}