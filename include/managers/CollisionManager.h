#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;
using namespace sf;

class Enemy;
class Obstacle;
class Player;
class Projectile;
class Entity;
class GraphicsManager;
class Character;

class CollisionManager {

private:
  /* ------- VARIABLES ------ */
  vector<Enemy *> enemies_vector;
  list<Obstacle *> obstacles_list;
  set<Projectile *> projectiles_set;
  vector<Player *> players_vector;
  GraphicsManager *pGM;
  Vector2f phaseSize;
  /* ------- SINGLETON ------- */
  static CollisionManager *instance;

  CollisionManager();

public:
  ~CollisionManager();
  static CollisionManager *getInstance();

  CollisionManager(const CollisionManager &) = delete;
  CollisionManager &operator=(const CollisionManager &) = delete;

  /* ------- COLLISION ------- */
  bool verifyCollision(Entity *ent1, Entity *ent2) const;
  void treatEnemiesCollision();
  void treatObstaclesCollision();
  void treatProjectilesCollision();
  void treatPlayersCollision();
  void treatWallCollision();
  void resolveCollisionObstacle(Character *c, Obstacle *o);
  void resolveCollisionCharacter(Character *c1, Character *c2);
  void removeProjectile(Projectile *p);
  void removeEnemy(Enemy *e);
  void removeObstacle(Obstacle *o);
  void removePlayer(Player *p);
  /* ------ ADD ENTITIES ------ */
  void addPlayer(Player *p);
  void addEnemy(Enemy *e);
  void addObstacle(Obstacle *o);
  void addProjectile(Projectile *p);
  void clearEntities();
  /* ------ GETTERS/SETTERS ------ */
  void setPhaseSize(Vector2f size);
  void execute();
};

#endif
