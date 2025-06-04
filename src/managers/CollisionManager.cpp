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

float vectorModule(Vector2f vector) {
  return sqrt(vector.x * vector.x + vector.y * vector.y);
}


/* ------------------------------------------- */
/*             COLLISION FUNCTIONS             */
/* ------------------------------------------- */

bool CollisionManager::verifyCollision(Entity *ent1, Entity *ent2) const {
  FloatRect rect1(ent1->getPosition(), ent1->getSize());
  FloatRect rect2(ent2->getPosition(), ent2->getSize());
  return rect1.intersects(rect2);
}

void CollisionManager::treatWallCollision() {
  float window_width = pGM->getWindow()->getSize().x;
  float window_height = pGM->getWindow()->getSize().y;

  // For each Player
  for (vector<Player *>::iterator it = players_vector.begin();
       it != players_vector.end(); it++) {
    if (*it) {
      Player *p = (*it);
      Vector2f pos = p->getPosition();
      Vector2f vel = p->getVelocity();
      // Left wall
      if (pos.x < 0) {
        pos.x = 0;
        vel.x = 0;
      }
      // Right wall
      if (pos.x + p->getSize().x > window_width) {
        pos.x = window_width - p->getSize().x;
        vel.x = 0;
      }
      // Top wall
      if (pos.y < 0) {
        pos.y = 0;
        if (vel.y < 0) {
          vel.y = 0; // Prevents jumping through the top wall
          p->setOnGround(false); // Not on ground if jumping through top wall
        }
      }
      // Bottom wall
      if (pos.y + p->getSize().y > window_height) {
        pos.y = window_height - p->getSize().y;
        vel.y = 0;
        p->setOnGround(true);
      }
      p->setPosition(pos);
      p->setVelocity(vel);
    }
  }
  // For each Enemy
  for (vector<Enemy *>::iterator itEnemy = enemies_vector.begin();
       itEnemy != enemies_vector.end(); itEnemy++) {
    if (*itEnemy) {
      Enemy *e = (*itEnemy);
      Vector2f pos = e->getPosition();
      Vector2f vel = e->getVelocity();
      // Left wall
      if (pos.x < 0) {
        pos.x = 0;
        vel.x = 0;
      }
      // Right wall
      if (pos.x + e->getSize().x > window_width) {
        pos.x = window_width - e->getSize().x;
        vel.x = 0;
      }
      // Top wall
      if (pos.y < 0) {
        pos.y = 0;
        if (vel.y < 0) {
          vel.y = 0; // Prevents jumping through the top wall
        }
      }
      // Bottom wall
      if (pos.y + e->getSize().y > window_height) {
        pos.y = window_height - e->getSize().y;
        vel.y = 0;
        e->setOnGround(true);
      }
      e->setPosition(pos);
      e->setVelocity(vel);
    }
  }
}

void resolveCollisionCharacter(Character *a, Character *b) {
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
      // Horizontal collision
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
      // Vertical collision
      float push = intersectY / 2.f;
      if (deltaY > 0) {
        // 'a' is below 'b'
        aPos.y -= push;
        bPos.y += push;

        // Set 'b' (character below) as on ground
        if (b->getVelocity().y > 0) {
          b->setVelocity({b->getVelocity().x, 0.f});
          b->setOnGround(true);
        }

      } else {
        // 'a' is above 'b'
        aPos.y += push;
        bPos.y -= push;

        // Set 'a' (character above) as on ground
        if (a->getVelocity().y > 0) {
          a->setVelocity({a->getVelocity().x, 0.f});
          a->setOnGround(true);
        }
      }
    }

    a->setPosition(aPos);
    b->setPosition(bPos);
  }
}

void CollisionManager::resolveCollisionObstacle(Character *c, Obstacle *o) {
  Vector2f cPos = c->getPosition();
  Vector2f oPos = o->getPosition();
  Vector2f cSize = c->getSize();
  Vector2f oSize = o->getSize();

  // Define the limits of the character and obstacle
  float cTop = cPos.y;
  float cBottom = cPos.y + cSize.y;
  float cLeft = cPos.x;
  float cRight = cPos.x + cSize.x;

  float oTop = oPos.y;
  float oBottom = oPos.y + oSize.y;
  float oLeft = oPos.x;
  float oRight = oPos.x + oSize.x;

  // Calculate the intersection area
  float intersectX = std::min(cRight, oRight) - std::max(cLeft, oLeft);
  float intersectY = std::min(cBottom, oBottom) - std::max(cTop, oTop);

  if (intersectX > 0 && intersectY > 0) {
    // Calculate the distance between each side
    float topOverlap = cBottom - oTop;
    float bottomOverlap = oBottom - cTop;
    float leftOverlap = cRight - oLeft;
    float rightOverlap = oRight - cLeft;

    // Find the smallest overlap
    float minOverlap =
        std::min({topOverlap, bottomOverlap, leftOverlap, rightOverlap});

    // Resolve in the direction of the smallest overlap
    if (minOverlap == topOverlap) {
      // Top collision (player is above the obstacle)
      cPos.y = oTop - cSize.y;
      c->setOnGround(true);
      c->setVelocity(Vector2f(c->getVelocity().x, 0.f));
    } else if (minOverlap == bottomOverlap) {
      // Bottom collision (player is below the obstacle)
      cPos.y = oBottom;
      c->setVelocity(Vector2f(c->getVelocity().x, 0.f));
    } else if (minOverlap == leftOverlap) {
      // Left collision
      cPos.x = oLeft - cSize.x;
      c->setVelocity(Vector2f(0.f, c->getVelocity().y));
    } else if (minOverlap == rightOverlap) {
      // Right collision
      cPos.x = oRight;
      c->setVelocity(Vector2f(0.f, c->getVelocity().y));
    }

    c->setPosition(cPos);
  }
}





void CollisionManager::treatPlayersCollision() {

  if (verifyCollision(players_vector[0], players_vector[1])) {
    resolveCollisionCharacter(players_vector[0], players_vector[1]);
  }
}

void CollisionManager::treatEnemiesCollision() {
  // Treat for each player
  for (vector<Player *>::iterator it = players_vector.begin();
       it != players_vector.end(); it++) {
    if ((*it)) {
      for (vector<Enemy *>::iterator itEnemy = enemies_vector.begin();
           itEnemy != enemies_vector.end(); itEnemy++) {
        if (*itEnemy) {
          if (verifyCollision((*it), (*itEnemy))) {
            resolveCollisionCharacter((*it), (*itEnemy));
            (*itEnemy)->attack(*it);
          }
        }
      }
    }
  }
}

void CollisionManager::treatObstaclesCollision() {
  // Treat for each player
  for (vector<Player *>::iterator it = players_vector.begin();
       it != players_vector.end(); it++) {
    if ((*it)) {
      for (list<Obstacle *>::iterator itObstacle = obstacles_list.begin();
           itObstacle != obstacles_list.end(); itObstacle++) {
        if (*itObstacle) {
          if (verifyCollision((*it), (*itObstacle))) {
            resolveCollisionObstacle((*it), (*itObstacle));
          }
        }
      }
    }
  }
  // Treat for each Enemy
  for (vector<Enemy *>::iterator it = enemies_vector.begin();
       it != enemies_vector.end(); it++) {
    if ((*it)) {
      for (list<Obstacle *>::iterator itObstacle = obstacles_list.begin();
           itObstacle != obstacles_list.end(); itObstacle++) {
        if (*itObstacle) {
          if (verifyCollision((*it), (*itObstacle))) {
            resolveCollisionObstacle((*it), (*itObstacle));
          }
        }
      }
    }
  }
}


void CollisionManager::treatProjectilesCollision() {
    for (std::set<Projectile*>::iterator itProjectile = projectiles_set.begin(); 
         itProjectile != projectiles_set.end(); ) {
        Projectile* proj = *itProjectile;
        bool collided = false;

        // Colisão com inimigos
        for (std::vector<Enemy*>::iterator itEnemy = enemies_vector.begin(); 
             itEnemy != enemies_vector.end(); ++itEnemy) {
            if (*itEnemy && verifyCollision(proj, *itEnemy)) {
                collided = true;
                break;
            }
        }

        // Colisão com obstáculos
        if (!collided) {
            for (std::list<Obstacle*>::iterator itObstacle = obstacles_list.begin(); 
                 itObstacle != obstacles_list.end(); ++itObstacle) {
                if (*itObstacle && verifyCollision(proj, *itObstacle)) {
                    collided = true;
                    break;
                }
            }
        }

        if (collided) {
            proj->setActive(false);
        }
        
        ++itProjectile;
    }
}

void CollisionManager::removeProjectile(Projectile* p) {
    auto it = projectiles_set.find(p);
    if (it != projectiles_set.end()) {
        projectiles_set.erase(it);
    }
}


/* ------------------------------------------- */
/*                ADD ENTITIES                 */
/* ------------------------------------------- */
void CollisionManager::addObstacle(Obstacle *o) { obstacles_list.push_back(o); }

void CollisionManager::addProjectile(Projectile *p) {
  projectiles_set.insert(p);
}
void CollisionManager::addEnemy(Enemy *e) { enemies_vector.push_back(e); }

void CollisionManager::addPlayer(Player *p) { players_vector.push_back(p); }

/* ------------------------------------------- */
/*                   EXECUTE                   */
/* ------------------------------------------- */

void CollisionManager::execute() {
  treatEnemiesCollision();
  treatObstaclesCollision();
  treatProjectilesCollision();
  if (players_vector.size() > 1)
    treatPlayersCollision();
  treatWallCollision();
}
