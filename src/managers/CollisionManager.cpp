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
  Vector2f pos1 = ent1->getPosition();
  Vector2f size1 = ent1->getSize();
  Vector2f pos2 = ent2->getPosition();
  Vector2f size2 = ent2->getSize();

  FloatRect rect1(pos1.x - size1.x / 2, pos1.y - size1.y / 2, size1.x, size1.y);

  FloatRect rect2(pos2.x - size2.x / 2, pos2.y - size2.y / 2, size2.x, size2.y);

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
      if (pos.x - p->getSize().x / 2.0 < 0) {
        pos.x = p->getSize().x / 2.0;
        vel.x = 0;
      }
      // Right wall
      if (pos.x + p->getSize().x / 2.0 > window_width) {
        pos.x = window_width - p->getSize().x / 2.0;
        vel.x = 0;
      }
      // Top wall
      if (pos.y - p->getSize().y / 2.0 < 0) {
        pos.y = p->getSize().y / 2.0;
        if (vel.y < 0) {
          vel.y = 0;         // Prevents jumping through the top wall
          p->setInAir(true); // Not on ground if jumping through top wall
        }
      }
      // Bottom wall
      if (pos.y + p->getSize().y / 2.0 > window_height) {
        pos.y = window_height - p->getSize().y / 2.0;
        vel.y = 0;
        p->setInAir(false);
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
      if (pos.x - e->getSize().x / 2.0 < 0) {
        pos.x = e->getSize().x / 2.0;
        vel.x = 0;
      }
      // Right wall
      if (pos.x + e->getSize().x / 2.0 > window_width) {
        pos.x = window_width - e->getSize().x / 2.0;
        vel.x = 0;
      }
      // Top wall
      if (pos.y - e->getSize().y / 2.0 < 0) {
        pos.y = e->getSize().y / 2.0;
        if (vel.y < 0) {
          vel.y = 0; // Prevents jumping through the top wall
        }
      }
      // Bottom wall
      if (pos.y + e->getSize().y / 2.0 > window_height) {
        pos.y = window_height - e->getSize().y / 2.0;
        vel.y = 0;
        e->setInAir(false);
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

  // Calculate the distance between the two centers
  Vector2f delta = aPos - bPos;
  float minDistanceX = (aSize.x + bSize.x) / 2;
  float minDistanceY = (aSize.y + bSize.y) / 2;

  // Calculate the overlap
  float overlapX = minDistanceX - std::abs(delta.x);
  float overlapY = minDistanceY - std::abs(delta.y);

  if (overlapX > 0 && overlapY > 0) {
    if (overlapX < overlapY) {
      // Resolve horizontal collision
      if (delta.x > 0) {
        aPos.x += overlapX / 2;
        bPos.x -= overlapX / 2;
      } else {
        aPos.x -= overlapX / 2;
        bPos.x += overlapX / 2;
      }
      a->setVelocity({0.f, a->getVelocity().y});
      b->setVelocity({0.f, b->getVelocity().y});
    } else {
      // Resolve vertical collision
      if (delta.y > 0) {
        aPos.y += overlapY / 2;
        bPos.y -= overlapY / 2;
        b->setInAir(false);
        b->setVelocity({b->getVelocity().x, 0.f});
      } else {
        aPos.y -= overlapY / 2;
        bPos.y += overlapY / 2;
        a->setInAir(false);
        a->setVelocity({a->getVelocity().x, 0.f});
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
  float cLeft = cPos.x - cSize.x / 2;
  float cRight = cPos.x + cSize.x / 2;
  float cTop = cPos.y - cSize.y / 2;
  float cBottom = cPos.y + cSize.y / 2;

  float oLeft = oPos.x - oSize.x / 2;
  float oRight = oPos.x + oSize.x / 2;
  float oTop = oPos.y - oSize.y / 2;
  float oBottom = oPos.y + oSize.y / 2;

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
      cPos.y -= minOverlap;
      c->setInAir(false);
      c->setVelocity(Vector2f(c->getVelocity().x, 0.f));
    } else if (minOverlap == bottomOverlap) {
      // Bottom collision (player is below the obstacle)
      cPos.y += minOverlap;
      c->setVelocity(Vector2f(c->getVelocity().x, 0.f));
    } else if (minOverlap == leftOverlap) {
      // Left collision
      cPos.x -= minOverlap;
      c->setVelocity(Vector2f(0.f, c->getVelocity().y));
    } else if (minOverlap == rightOverlap) {
      // Right collision
      cPos.x += minOverlap;
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
  for (std::set<Projectile *>::iterator itProjectile = projectiles_set.begin();
       itProjectile != projectiles_set.end();) {
    Projectile *proj = *itProjectile;
    bool collided = false;

    // Enemy collision
    for (std::vector<Enemy *>::iterator itEnemy = enemies_vector.begin();
         itEnemy != enemies_vector.end(); ++itEnemy) {
      if (*itEnemy && verifyCollision(proj, *itEnemy)) {
        collided = true;
        break;
      }
    }

    // Obstacle collision
    if (!collided) {
      for (std::list<Obstacle *>::iterator itObstacle = obstacles_list.begin();
           itObstacle != obstacles_list.end(); ++itObstacle) {
        if (*itObstacle && verifyCollision(proj, *itObstacle)) {
          collided = true;
          break;
        }
      }
    }
    /*
    // Player collision
    if (!collided) {
      for (std::vector<Player *>::iterator itPlayer = players_vector.begin();
           itPlayer != players_vector.end(); ++itPlayer) {
        if (*itPlayer && verifyCollision(proj, *itPlayer)) {
          collided = true;
          break;
        }
      }
    }
    */
    // Wall collision
    if (!collided) {
      if (proj->getPosition().x < proj->getSize().x / 2.0 ||
          proj->getPosition().x + proj->getSize().x / 2.0 >
              pGM->getWindow()->getSize().x) {
        collided = true;
      }
    }

    if (collided) {
      proj->setActive(false);
    }

    ++itProjectile;
  }
}

void CollisionManager::removeProjectile(Projectile *p) {
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
