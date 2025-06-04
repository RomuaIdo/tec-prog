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
class GraphicsManager;
class Character;

class CollisionManager{

    private:
        /* ------- VARIABLES ------ */
        vector<Enemy*> enemies_vector;
        list<Obstacle*> obstacles_list;
        set<Projectile*> projectiles_set;
        vector<Player*> players_vector;
        GraphicsManager* pGM;
        static CollisionManager* instance;
        
        CollisionManager();
    public:
        
        ~CollisionManager();
        static CollisionManager* getInstance();

        CollisionManager(const CollisionManager&) = delete;
        CollisionManager& operator=(const CollisionManager&) = delete;

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
        void removeProjectile(Projectile* p);
        
        void execute();
        void resolveCollisionObstacle(Character* c, Obstacle* o); 
};

#endif
