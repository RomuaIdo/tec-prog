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
  float phase_width = phaseSize.x;
  float phase_height = phaseSize.y;
  // For each Player
  for (vector<Player *>::iterator it = players_vector.begin();
       it != players_vector.end(); it++) {
    if (*it) {
      Player *p = (*it);
      Vector2f pos = p->getPosition();
      Vector2f vel = p->getVelocity();

      float cameraLeft = pGM->getWindow()->getView().getCenter().x -
                         pGM->getWindow()->getSize().x / 2;
      float cameraRight = pGM->getWindow()->getView().getCenter().x +
                          pGM->getWindow()->getSize().x / 2;

      // Check if player is outside camera bounds
      if (pos.x < cameraLeft + p->getSize().x / 2.0) {
        pos.x = cameraLeft + p->getSize().x / 2.0;
        vel.x = 0;
      } else if (pos.x > cameraRight - p->getSize().x / 2.0) {
        pos.x = cameraRight - p->getSize().x / 2.0;
        vel.x = 0;
      }

      // Left wall
      if (pos.x - p->getSize().x / 2.0 < 0) {
        pos.x = p->getSize().x / 2.0;
        vel.x = 0;
      }
      // Right wall
      if (pos.x + p->getSize().x / 2.0 > phase_width) {
        pos.x = phase_width - p->getSize().x / 2.0;
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
      if (pos.y + p->getSize().y / 2.0 > phase_height) {
        pos.y = phase_height - p->getSize().y / 2.0;
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
      if (pos.x + e->getSize().x / 2.0 > phase_width) {
        pos.x = phase_width - e->getSize().x / 2.0;
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
      if (pos.y + e->getSize().y / 2.0 > phase_height) {
        pos.y = phase_height - e->getSize().y / 2.0;
        vel.y = 0;
        e->setInAir(false);
      }
      e->setPosition(pos);
      e->setVelocity(vel);
    }
  }
}

void CollisionManager::resolveCollisionCharacter(Character *a, Character *b) {
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

void CollisionManager::treatPlayersCollision() {
  if (players_vector.size() > 1 &&
      verifyCollision(players_vector[0], players_vector[1])) {
    resolveCollisionCharacter(players_vector[0], players_vector[1]);
    players_vector[0]->collide(players_vector[1]);
    players_vector[1]->collide(players_vector[0]);
  }
}

void CollisionManager::treatEnemiesCollision() {
  for (vector<Player *>::iterator it = players_vector.begin();
       it != players_vector.end(); it++) {
    if (*it) {
      for (vector<Enemy *>::iterator itEnemy = enemies_vector.begin();
           itEnemy != enemies_vector.end(); itEnemy++) {
        if (*itEnemy) {
          if (verifyCollision(*it, *itEnemy)) {
            resolveCollisionCharacter(*it, *itEnemy);
            (*it)->collide(*itEnemy);
            (*itEnemy)->collide(*it);
          }
        }
      }
    }
  }
}

void CollisionManager::treatObstaclesCollision() {
  // Tratamento de colisão para inimigos
  for (vector<Enemy *>::iterator it = enemies_vector.begin();
       it != enemies_vector.end(); it++) {
    if ((*it)) {
      for (list<Obstacle *>::iterator itObstacle = obstacles_list.begin();
           itObstacle != obstacles_list.end(); itObstacle++) {
        if (*itObstacle) {
          if (verifyCollision((*it), (*itObstacle))) {
            (*itObstacle)->collide(*it);
          }
        }
      }
    }
  }

  for (vector<Player *>::iterator it = players_vector.begin();
       it != players_vector.end(); it++) {
    if ((*it)) {
      for (list<Obstacle *>::iterator itObstacle = obstacles_list.begin();
           itObstacle != obstacles_list.end(); itObstacle++) {
        if (*itObstacle) {
          if (verifyCollision((*it), (*itObstacle))) {
            (*itObstacle)->collide(*it);
          }
        }
      }
    }
  }
}

void CollisionManager::treatProjectilesCollision() {
  for (set<Projectile *>::iterator itProjectile = projectiles_set.begin();
       itProjectile != projectiles_set.end();) {
    Projectile *proj = *itProjectile;
    bool collided = false;
    Entity *collidedEntity = nullptr;

    // Enemy collision
    for (vector<Enemy *>::iterator itEnemy = enemies_vector.begin();
         itEnemy != enemies_vector.end(); ++itEnemy) {
      if (*itEnemy && verifyCollision(proj, *itEnemy)) {
        collided = true;
        collidedEntity = *itEnemy;
        break;
      }
    }

    // Obstacle collision
    if (!collided) {
      for (list<Obstacle *>::iterator itObstacle = obstacles_list.begin();
           itObstacle != obstacles_list.end(); ++itObstacle) {
        if (*itObstacle && verifyCollision(proj, *itObstacle)) {
          collided = true;
          collidedEntity = *itObstacle;
          break;
        }
      }
    }

    // Player collision (opcional)
    if (!collided) {
      for (vector<Player *>::iterator itPlayer = players_vector.begin();
           itPlayer != players_vector.end(); ++itPlayer) {
        if (*itPlayer && verifyCollision(proj, *itPlayer)) {
          collided = true;
          collidedEntity = *itPlayer;
          break;
        }
      }
    }

    // Wall collision
    if (!collided) {
      Vector2f pos = proj->getPosition();
      Vector2f size = proj->getSize();
      if (pos.x - size.x / 2 < 0 || pos.x + size.x / 2 > phaseSize.x ||
          pos.y - size.y / 2 < 0 || pos.y + size.y / 2 > phaseSize.y) {
        collided = true;
      }
    }

    if (collided) {
      proj->collide(collidedEntity);
      if (collidedEntity) {
        collidedEntity->collide(proj);
      }
      proj->setActive(false);
    }

    ++itProjectile;
  }
}

void CollisionManager::removeProjectile(Projectile *p) {
  set<Projectile *>::iterator it = projectiles_set.find(p);
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

void CollisionManager::removeObstacle(Obstacle *o) { obstacles_list.remove(o); }

void CollisionManager::removePlayer(Player *p) {
  auto it = std::find(players_vector.begin(), players_vector.end(), p);
  if (it != players_vector.end()) {
    players_vector.erase(it);
  }
}

/* ------------------------------------------- */
/*                ADD ENTITIES                 */
/* ------------------------------------------- */

void CollisionManager::clearEntities() {
  enemies_vector.clear();
  obstacles_list.clear();
  projectiles_set.clear();
  players_vector.clear();
}

void CollisionManager::addObstacle(Obstacle *o) { obstacles_list.push_back(o); }

void CollisionManager::addProjectile(Projectile *p) {
  projectiles_set.insert(p);
}
void CollisionManager::addEnemy(Enemy *e) { enemies_vector.push_back(e); }

void CollisionManager::addPlayer(Player *p) { players_vector.push_back(p); }

/* ------------------------------------------- */
/*                   EXECUTE                   */
/* ------------------------------------------- */

void CollisionManager::setPhaseSize(Vector2f size) {
  phaseSize = size;
}

void CollisionManager::execute() {
  treatEnemiesCollision();
  treatObstaclesCollision();
  treatProjectilesCollision();
  if (players_vector.size() > 1)
    treatPlayersCollision();
  treatWallCollision();
}
