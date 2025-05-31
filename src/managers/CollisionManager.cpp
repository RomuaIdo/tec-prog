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

    if(module(vectorModule(ent1center - ent2center)) < 
       module(vectorModule(ent1->getSize() / static_cast<float>(2) + ent2->getSize() / static_cast<float>(2) ))){
        return true;
    }
    return false;
}

void CollisionManager::treatWallCollision(){
    float window_width = 800.0f;  // example
    float window_height = 600.0f; // example

    // For each Player
    for(vector<Player*>::iterator it = players_vector.begin(); it != players_vector.end(); it++){
        if(*it){
            Player* p = (*it);
            Vector2f pos = p->getPosition();
            Vector2f vel = p->getVelocity();
            // Left wall
            if (pos.x < 0){
                pos.x = 0;
                vel.x = 0;
            }    
            // Right wall
            if (pos.x + p->getSize().x > window_width){
                pos.x = window_width - p->getSize().x;
                vel.x = 0;
            }   
            // Top wall
            if (pos.y < 0){
                pos.y = 0;
                vel.y = 0;
            } 
            // Bottom wall
            if (pos.y + p->getSize().y > window_height){
                pos.y = window_height - p->getSize().y;
                vel.y = 0;
            }
            p->setPosition(pos);
            p->setVelocity(vel);
        }
    }
    // For each Enemy
    for(vector<Enemy*>::iterator itEnemy = enemies_vector.begin(); itEnemy != enemies_vector.end(); itEnemy++){
        if(*itEnemy){
            Enemy* e = (*itEnemy);
            Vector2f pos = e->getPosition();
            Vector2f vel = e->getVelocity();
            // Left wall
            if (pos.x < 0){
                pos.x = 0;
                vel.x = 0;
            }    
            // Right wall
            if (pos.x + e->getSize().x > window_width){
                pos.x = window_width - e->getSize().x;
                vel.x = 0;
            }   
            // Top wall
            if (pos.y < 0){
                pos.y = 0;
                vel.y = 0;
            } 
            // Bottom wall
            if (pos.y + e->getSize().y > window_height){
                pos.y = window_height - e->getSize().y;
                vel.y = 0;
            }
            e->setPosition(pos);
            e->setVelocity(vel);
        }
    }
    
}

void resolveCollisionCharacter(Character* a, Character* b) {
    Vector2f aPos = a->getPosition();
    Vector2f bPos = b->getPosition();
    Vector2f aSize = a->getSize();
    Vector2f bSize = b->getSize();

    float deltaX = (aPos.x + aSize.x / 2) - (bPos.x + bSize.x / 2);
    float deltaY = (aPos.y + aSize.y / 2) - (bPos.y + bSize.y / 2);

    float intersectX = std::abs(deltaX) - (aSize.x + bSize.x) / 2;
    float intersectY = std::abs(deltaY) - (aSize.y + bSize.y) / 2;

    if (intersectX < 0.0f && intersectY < 0.0f) {
        if (std::abs(intersectX) < std::abs(intersectY)) {
            float push = intersectX / 2.f;
            if (deltaX > 0) {
                aPos.x -= push;
                bPos.x += push;
            } else {
                aPos.x += push;
                bPos.x -= push;
            }
            a->setVelocity({0.f, a->getVelocity().y});
            b->setVelocity({0.f, b->getVelocity().y});
        } else {
            float push = intersectY / 2.f;
            if (deltaY > 0) {
                // a is above b
                aPos.y -= push;
                bPos.y += push;
                if (a->getVelocity().y > 0)  // only cancel downward movement
                    a->setVelocity({a->getVelocity().x, 0.f});
                if (b->getVelocity().y > 0)
                    b->setVelocity({b->getVelocity().x, 0.f});
            } else {
                // a is below b (jumping up)
                aPos.y += push;
                bPos.y -= push;
                // don't cancel a's velocity — it's jumping
                if (a->getVelocity().y > 0)  // only cancel downward movement
                    a->setVelocity({a->getVelocity().x, 0.f});
                if (b->getVelocity().y > 0)
                    b->setVelocity({b->getVelocity().x, 0.f});
            }
        }

        a->setPosition(aPos);
        b->setPosition(bPos);
    }
}

void resolveCollisionObstacle(Character* c, Obstacle* o) {
    Vector2f cPos =  c->getPosition();
    Vector2f oPos =  o->getPosition();
    Vector2f cSize = c->getSize();
    Vector2f oSize = o->getSize();

    float deltaX = (cPos.x + cSize.x / 2) - (oPos.x + oSize.x / 2);
    float deltaY = (cPos.y + cSize.y / 2) - (oPos.y + oSize.y / 2);

    float intersectX = std::abs(deltaX) - (cSize.x + oSize.x) / 2;
    float intersectY = std::abs(deltaY) - (cSize.y + oSize.y) / 2;

    if (intersectX < 0.0f && intersectY < 0.0f) {
        if (std::abs(intersectX) < std::abs(intersectY)) {
            float push = intersectX;
            if (deltaX > 0) {
                cPos.x -= push;
            } else {
                cPos.x += push;
            }
            c->setVelocity({0.f, c->getVelocity().y});
        } else {
            float push = intersectY;
            if (deltaY > 0) {
                // a is above b
                cPos.y -= push;
                if (c->getVelocity().y > 0)  // only cancel downward movement
                    c->setVelocity({c->getVelocity().x, 0.f});
                } else {
                // a is below b (jumping up)
                cPos.y += push;
                // don't cancel a's velocity — it's jumping
                if (c->getVelocity().y > 0)  // only cancel downward movement
                    c->setVelocity({c->getVelocity().x, 0.f});
            }
        }

        c->setPosition(cPos);
    }
}

void CollisionManager::treatPlayersCollision(){
    
    if(verifyCollision(players_vector[0] , players_vector[1])){
        resolveCollisionCharacter(players_vector[0], players_vector[1]);
    }
}

void CollisionManager::treatEnemiesCollision(){
    // Treat for each player
    for(vector<Player*>::iterator it = players_vector.begin(); it != players_vector.end(); it++){
        if((*it)){
            for(vector<Enemy*>::iterator itEnemy = enemies_vector.begin(); itEnemy != enemies_vector.end(); itEnemy++){
                if(*itEnemy){
                    if(verifyCollision( (*it) , (*itEnemy) ) ){
                        resolveCollisionCharacter((*it), (*itEnemy));
                        (*itEnemy)->attack(*it);
                    }
                }
            }
        }
    }

}

void CollisionManager::treatObstaclesCollision(){
    // Treat for each player
    for(vector<Player*>::iterator it = players_vector.begin(); it != players_vector.end(); it++){
        if((*it)){
            for(list<Obstacle*>::iterator itObstacle = obstacles_list.begin(); itObstacle != obstacles_list.end(); itObstacle++){
                if(*itObstacle){
                    if(verifyCollision( (*it) , (*itObstacle) ) ){
                        resolveCollisionObstacle((*it), (*itObstacle));
                    }
                }
            }
        }
    }
    // Treat for each Enemy
    for(vector<Enemy*>::iterator it = enemies_vector.begin(); it != enemies_vector.end(); it++){
        if((*it)){
            for(list<Obstacle*>::iterator itObstacle = obstacles_list.begin(); itObstacle != obstacles_list.end(); itObstacle++){
                if(*itObstacle){
                    if(verifyCollision( (*it) , (*itObstacle) ) ){
                        resolveCollisionObstacle((*it), (*itObstacle));
                    }
                }
            }
        }
    }
}

void CollisionManager::treatProjectilesCollision(){
    // Treat for each player
    for(vector<Player*>::iterator it = players_vector.begin(); it != players_vector.end(); it++){
        if((*it)){
            for(set<Projectile*>::iterator itProjectile = projectiles_set.begin(); itProjectile != projectiles_set.end(); itProjectile++){
                if(*itProjectile){
                    if(verifyCollision( (*it) , (*itProjectile) ) ){
                        (*it)->collide();
                        (*itProjectile)->collide();
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
    players_vector.push_back(p);
}

void CollisionManager::execute(){
    treatEnemiesCollision();
    treatObstaclesCollision();
    treatProjectilesCollision();
    treatWallCollision();
    if(players_vector.size()>1) 
        treatPlayersCollision();
}