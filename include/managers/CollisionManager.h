#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H
#include <SFML/Graphics.hpp>
#include "../entities/Enemy.h"
#include "../entities/Obstacle.h"
#include "../entities/Player.h"
// #include "../entities/Projectile.h"
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <set>
using namespace std;
using namespace sf;

class CollisionManager{

    private:
        vector<Enemy*> enemys_vector;
        list<Obstacle*> obstacles_list;
        // set<Projectile*> projectiles_set;
        Player* player1;
        Player* player2;

    public:
        CollisionManager();
        ~CollisionManager();
        const bool verifyCollision(Entity* ent1, Entity* ent2) const;
        void treatObstaclesCollision();
        void treatEnemiesCollision();
        void treatProjectilesCollision();
        void addEnemy(Enemy* e);
        void addObstacle(Obstacle* o);
        // void addProjectile(Projectile* p);
        void execute();

};

#endif