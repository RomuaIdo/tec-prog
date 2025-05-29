#include "../../include/managers/CollisionManager.h"


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

}

void CollisionManager::treatEnemiesCollision(){
    
}

void CollisionManager::treatObstaclesCollision(){

}

void CollisionManager::treatProjectilesCollision(){
    
}

void CollisionManager::addEnemy(Enemy *e){

}

void CollisionManager::addObstacle(Obstacle *o){

}

void CollisionManager::addProjectile(Projectile *p){

}