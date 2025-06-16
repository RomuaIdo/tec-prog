#include "../../include/managers/CollisionManager.h"
#include "../../include/entities/Projectile.h"
#include "../../include/entities/characters/Enemy.h"
#include "../../include/entities/characters/Player.h"
#include "../../include/entities/obstacles/Obstacle.h"
#include "../../include/managers/GraphicsManager.h"

CollisionManager *CollisionManager::instance(nullptr);

CollisionManager *CollisionManager::getInstance() {
    if (instance == nullptr) {
        instance = new CollisionManager();
    }
    return instance;
}

CollisionManager::CollisionManager()
    : enemies_vector(), obstacles_list(), projectiles_set(), players_vector() {
    enemies_vector.clear();
    obstacles_list.clear();
    projectiles_set.clear();
    players_vector.clear();
    pGM = GraphicsManager::getInstance();
}

CollisionManager::~CollisionManager() {
    projectiles_set.clear();
    enemies_vector.clear();
    obstacles_list.clear();
    players_vector.clear();
}

/* ------------------------------------------- */
/*               LOCAL FUNCTIONS               */
/* ------------------------------------------- */

float vectorModule(Vector2f vector){  
    return sqrt(vector.x*vector.x + vector.y*vector.y);
}

/* ------------------------------------------- */
/*             COLLISION FUNCTIONS             */
/* ------------------------------------------- */

bool CollisionManager::verifyCollision(Entity* ent1, Entity* ent2) const{
    if(abs( vectorModule(ent1->getPosition() - ent2->getPosition()) ) < 
       abs( vectorModule(ent1->getSize()     + ent2->getSize()) )){
        return true;
    }
    return false;
}

void CollisionManager::treatWallCollision(){

    // float window_width  = Player::getGraphicsManager()->getWindow()->getSize().x;
    // float window_height = Player::getGraphicsManager()->getWindow()->getSize().y; 

    float window_height = pGM->getWindow()->getSize().y;
    float window_width  = pGM->getWindow()->getSize().x;

    // For each Player
    for(vector<Player*>::iterator it = players_vector.begin(); it != players_vector.end(); it++){
        if(*it){
            Player* p = (*it);
            Vector2f pos = p->getPosition();
            Vector2f vel = p->getSpeed();
            Vector2f size = p->getSize(); 
            // Left wall
            if (pos.x - size.x < 0){
                pos.x = size.x;
                vel.x = 0;
            }    
            // Right wall
            if (pos.x + size.x > window_width){
                pos.x = window_width - size.x;
                vel.x = 0;
            }   
            // Top wall
            if (pos.y - size.y < 0){
                pos.y = size.y;
                vel.y = 0;
            } 
            // Bottom wall
            if (pos.y + size.y > window_height){
                pos.y = window_height - size.y;
                vel.y = 0;
                p->setInAir(false);
            }

            p->setPosition(pos);
            p->setSpeed(vel);
        }
    }
    // For each Enemy
    for(vector<Enemy*>::iterator itEnemy = enemies_vector.begin(); itEnemy != enemies_vector.end(); itEnemy++){
        if(*itEnemy){
            Enemy* e = (*itEnemy);
            Vector2f pos = e->getPosition();
            Vector2f vel = e->getSpeed();
            Vector2f size = e->getSize();
            // Left wall
            if (pos.x - size.x < 0){
                pos.x = size.x;
                vel.x = 0;
            }    
            // Right wall
            if (pos.x + size.x > window_width){
                pos.x = window_width - size.x;
                vel.x = 0;
            }   
            // Top wall
            if (pos.y - size.y < 0){
                pos.y = size.y;
                vel.y = 0;
            } 
            // Bottom wall
            if (pos.y + size.y > window_height){
                pos.y = window_height - size.y;
                vel.y = 0;
                e->setInAir(false);
            }
            
            e->setPosition(pos);
            e->setSpeed(vel);
        }
    }
    
}

void CollisionManager::treatPlayersCollision(){
    if(verifyCollision(players_vector[0] , players_vector[1])){
        players_vector[0]->collide(players_vector[1]);
        players_vector[1]->collide(players_vector[0]);
    }
}

void CollisionManager::treatEnemiesCollision(){
    // Treat for each player
    for(vector<Player*>::iterator it = players_vector.begin(); it != players_vector.end(); it++){
        if((*it)){
            for(vector<Enemy*>::iterator itEnemy = enemies_vector.begin(); itEnemy != enemies_vector.end(); itEnemy++){
                if(*itEnemy){
                    if(verifyCollision( (*it) , (*itEnemy) ) ){
                        (*it)->collide(*itEnemy);
                        (*itEnemy)->collide(*it);
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
                        (*it)->collide(*itObstacle);
                        (*itObstacle)->collide(*it);
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
                        (*it)->collide(*itObstacle);
                        (*itObstacle)->collide(*it);
                    }
                }
            }
        }
    }
}

void CollisionManager::treatProjectilesCollision() {
    for (std::set<Projectile*>::iterator itProjectile = projectiles_set.begin(); itProjectile != projectiles_set.end(); ) {
        Projectile* proj = *itProjectile;
        bool collided = false;

        // Enemies collision
        for (std::vector<Enemy*>::iterator itEnemy = enemies_vector.begin(); itEnemy != enemies_vector.end(); ++itEnemy) {
            if (*itEnemy && verifyCollision(proj, *itEnemy)) {
                collided = true;
                break;
            }
        }

        // Obstacles collision
        if (!collided) {
            for (std::list<Obstacle*>::iterator itObstacle = obstacles_list.begin(); itObstacle != obstacles_list.end(); ++itObstacle) {
                if (*itObstacle && verifyCollision(proj, *itObstacle)) {
                    collided = true;
                    break;
                }
            }
        }

        if (collided) {
            proj->desactive();
        }
        
        ++itProjectile;
    }
}

/* ------------------------------------------- */
/*                   ENTITIES                  */
/* ------------------------------------------- */

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

void CollisionManager::removeProjectile(Projectile* p) {
    auto it = projectiles_set.find(p);
    if (it != projectiles_set.end()) {
        projectiles_set.erase(it);
    }
}

void CollisionManager::removeEnemy(Enemy *e) {
    auto it = std::find(enemies_vector.begin(), enemies_vector.end(), e);
    if (it != enemies_vector.end()) {
        enemies_vector.erase(it);
    }
}

void CollisionManager::removeObstacle(Obstacle *o) { 
    obstacles_list.remove(o); 
}

void CollisionManager::removePlayer(Player *p) {
    auto it = std::find(players_vector.begin(), players_vector.end(), p);
    if (it != players_vector.end()) {
        players_vector.erase(it);
    }
}

void CollisionManager::clearEntities() {
    enemies_vector.clear();
    obstacles_list.clear();
    projectiles_set.clear();
    players_vector.clear();
}

/* ------------------------------------------- */
/*                   EXECUTE                   */
/* ------------------------------------------- */

void CollisionManager::setPhaseSize(Vector2f size) {
    phaseSize = size;
}

void CollisionManager::execute(){
    treatEnemiesCollision();
    treatObstaclesCollision();
    treatProjectilesCollision();
    if(players_vector.size()>1) 
        treatPlayersCollision();
    treatWallCollision();
}