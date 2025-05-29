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

float vectorModule(Vector2f vector){
    
    return sqrt(vector.x*vector.x + vector.y*vector.y);
}

float module(float val){
    if(val < 0) return -val;
    return val;
}

bool CollisionManager::verifyCollision(Entity* ent1, Entity* ent2) const{

    Vector2f ent1center = ent1->getPosition() + (ent1->getSize() / static_cast<float> (2));    
    Vector2f ent2center = ent2->getPosition() + (ent2->getSize() / static_cast<float> (2));

    if(module(vectorModule(ent1center - ent2center)) < module(vectorModule(ent1->getSize() / static_cast<float>(2) + ent2->getSize() / static_cast<float>(2) ))){
        return true;
    }
    return false;
}

void CollisionManager::treatEnemiesCollision(){
    // Treat for each player
    for(list<Player*>::iterator it = players_list.begin(); it != players_list.end(); it++){
        if((*it)){
            for(vector<Enemy*>::iterator itEnemy = enemies_vector.begin(); itEnemy != enemies_vector.end(); itEnemy++){
                if(*itEnemy){
                    if(verifyCollision( (*it) , (*itEnemy) ) ){
                        cout << "Player collided!" <<endl;
                        (*it)->setVelocity( (*it)->getVelocity() - (*it)->getVelocity() * static_cast<float>(1.1));
                        (*it)->moveCharacter();

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
                        cout << "Player collided!" <<endl;
                        (*it)->setVelocity( (*it)->getVelocity() - (*it)->getVelocity() * static_cast<float>(1.1));
                        (*it)->moveCharacter();
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
                        cout << "Player collided!" <<endl;
                        (*it)->setPosition( (*it)->getVelocity() - (*it)->getVelocity() * static_cast<float>(0.3));
                        (*it)->setVelocity( (*it)->getVelocity() - (*it)->getVelocity() * static_cast<float>(0.3));
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

void CollisionManager::addPlayer(Player* p){
    players_list.push_back(p);
}

void CollisionManager::execute(){
    treatEnemiesCollision();
    treatObstaclesCollision();
    treatProjectilesCollision();
}