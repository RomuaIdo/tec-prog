#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H
#include <SFML/Graphics.hpp>
#include "CollisionManager.h"
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <set>
using namespace std;
using namespace sf;

class Enemy;
class Obstacle;
class Player;
class Projectile;
class Entity; 

class CollisionManager{

    private:
        /* ------- VARIABLES ------ */
        vector<Enemy*> enemies_vector;
        list<Obstacle*> obstacles_list;
        set<Projectile*> projectiles_set;
        vector<Player*> players_vector;

        static CollisionManager* instance;

        CollisionManager();
    public:
        
        ~CollisionManager();
        static CollisionManager* getInstance();

        /* ------- COLLISION ------- */
        bool verifyCollision(Entity* ent1, Entity* ent2) const;
        void treatEnemiesCollision();
        void treatObstaclesCollision();
        void treatProjectilesCollision();
        void treatPlayersCollision();
        void treatWallCollision();

        /* ------ ADD ENTITIES ------ */
        void addPlayer(Player* p);
        void addEnemy(Enemy* e);
        void addObstacle(Obstacle* o);
        void addProjectile(Projectile* p);

        
        void execute();

};

#endif