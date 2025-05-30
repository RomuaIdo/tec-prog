#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H
#include <SFML/Graphics.hpp>
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
        vector<Enemy*> enemies_vector;
        list<Obstacle*> obstacles_list;
        set<Projectile*> projectiles_set;
        list<Player*> players_list;

        static CollisionManager* instance;

        CollisionManager();
    public:
        
        ~CollisionManager();
        static CollisionManager* getInstance();
        bool verifyCollision(Entity* ent1, Entity* ent2) const;
        void treatEnemiesCollision();
        void treatObstaclesCollision();
        void treatProjectilesCollision();
        void treatWallCollision();
        void addPlayer(Player* p);
        void addEnemy(Enemy* e);
        void addObstacle(Obstacle* o);
        void addProjectile(Projectile* p);
        void execute();

};

#endif