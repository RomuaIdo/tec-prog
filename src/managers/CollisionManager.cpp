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
    enemies_vector(), obstacles_list(), projectiles_set(), players_vector(){
    enemies_vector.clear();
    obstacles_list.clear();
    projectiles_set.clear();
}

CollisionManager::~CollisionManager(){
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

void resolveCollisionCharacter(Character* a, Character* b) {
    Vector2f aPos = a->getPosition();
    Vector2f bPos = b->getPosition();
    Vector2f aSize = a->getSize();
    Vector2f bSize = b->getSize();

    float dx = (aPos.x - bPos.x);
    float dy = (aPos.y - bPos.y);
    // Vector2f variation = Vector2f(dx, dy);

    /* If dx > 0 -> a in b's right  */
    
    /* If dy > 0 -> a is below b    */

    /* The intersection between a and b ,
    *   if they collide, the vector will be
    *   negative in x and y                */

    Vector2f intersection = Vector2f( abs(dx) - (aSize.x + bSize.x), 
                                      abs(dy) - (aSize.y + bSize.y) );

    if (intersection.x < 0.0f && intersection.y < 0.0f) {

        /* If intersection in x is less then intersection in y
        /*  means that they are side by side                 */

        if (std::abs(intersection.x) < std::abs(intersection.y)) {
            
            /* To push the character the amount he is inside */                       
            float push = abs(intersection.x / 2.f);

            if (dx > 0) {
                aPos.x += push;
                bPos.x -= push;
                a->setSpeed({0.f + push, a->getSpeed().y});
                b->setSpeed({0.f - push, b->getSpeed().y});
            } else {
                aPos.x -= push;
                bPos.x += push;
                a->setSpeed({0.f - push, a->getSpeed().y});
                b->setSpeed({0.f + push, b->getSpeed().y});
            }

            

        /* If intersection in y is less then intersection in x
        /*  means that one is on top of the other             */

        } else {

            /* To push the character the amount he is inside */ 
            float push = abs(intersection.y / 2.f);

            /* a is below b */
            if (dy > 0) {

                /* b can jump */
                b->changeInAir();

                aPos.y += push;
                bPos.y -= push;
                // a->setSpeed({ a->getSpeed().x, 0.f });
                if(b->getSpeed().y > 0)
                    b->setSpeed({ b->getSpeed().x, 0.f });

            /* a is on top of b */
            } else {

                /* a can jump */
                a->changeInAir();

                aPos.y -= push;
                bPos.y += push;
                // b->setSpeed({ b->getSpeed().x, 0.f });
                if(a->getSpeed().y > 0)
                    a->setSpeed({ a->getSpeed().x, 0.f });

            }
        }
        a->setPosition(aPos);
        b->setPosition(bPos);
    }
}

void resolveCollisionObstacle(Character* c, Obstacle* o) {
    Vector2f cPos = c->getPosition();
    Vector2f oPos = o->getPosition();
    Vector2f cSize = c->getSize();
    Vector2f oSize = o->getSize();

    float dx = (cPos.x - oPos.x);
    float dy = (cPos.y - oPos.y);
    // Vector2f variation = Vector2f(dx, dy);

    /* If dx > 0 -> a in b's right  */
    
    /* If dy > 0 -> a is below b    */

    /* The intersection between a and b ,
    *   if they collide, the vector will be
    *   negative in x and y                */

    Vector2f intersection = Vector2f( abs(dx) - (cSize.x + oSize.x), 
                                      abs(dy) - (cSize.y + oSize.y) );

    if (intersection.x < 0.0f && intersection.y < 0.0f) {

        /* If intersection in x is less then intersection in y
        /*  means that they are side by side                 */

        if (std::abs(intersection.x) < std::abs(intersection.y)) {
            
            /* To push the character the amount he is inside */                       
            float push = abs(intersection.x / 2.f);

            if (dx > 0) {
                cPos.x += push;
                c->setSpeed({0.f + push, c->getSpeed().y});
            }
            else{
                cPos.x -= push;
                c->setSpeed({0.f - push, c->getSpeed().y});
            } 


        /* If intersection in y is less then intersection in x
        /*  means that character collided in y with obstacle */

        } else {

            /* To push the character the amount he is inside */ 
            float push = abs(intersection.y / 2.f);

            /* c is below o */
            if (dy > 0) {

                cPos.y += push;

            /* c is on top of o */
            } else {

                /* c can jump */
                c->changeInAir();
                cPos.y -= push;
                
                c->setSpeed({ c->getSpeed().x, 0.f });
            }
        }
        c->setPosition(cPos);
    }
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
    float window_width = 800.0f;  // example
    float window_height = 600.0f; // example

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
                p->changeInAir();
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
                e->changeInAir();
            }
            
            e->setPosition(pos);
            e->setSpeed(vel);
        }
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

/* ------------------------------------------- */
/*                   EXECUTE                   */
/* ------------------------------------------- */

void CollisionManager::execute(){
    treatEnemiesCollision();
    treatObstaclesCollision();
    treatProjectilesCollision();
    if(players_vector.size()>1) 
        treatPlayersCollision();
    treatWallCollision();
}