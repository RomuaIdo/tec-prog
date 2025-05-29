#include "../../include/managers/CollisionManager.h"

CollisionManager::CollisionManager():
    enemies_vector(), obstacles_list(){

}

CollisionManager::~CollisionManager(){



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