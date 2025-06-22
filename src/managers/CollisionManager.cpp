#include "../../include/managers/CollisionManager.h"
#include "../../include/entities/Projectile.h"
#include "../../include/entities/characters/Enemy.h"
#include "../../include/entities/characters/Player.h"
#include "../../include/entities/obstacles/Obstacle.h"
#include "../../include/entities/obstacles/ThornyBush.h"
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
  if (!ent1 || !ent2) {
    return false; // Verifica se as entidades são válidas
  }

  Vector2f pos1 = ent1->getPosition();
  Vector2f pos2 = ent2->getPosition();
  Vector2f size1 = ent1->getSize();
  Vector2f size2 = ent2->getSize();

  // Verifica se há sobreposição entre os retângulos delimitadores
  return (pos1.x - size1.x < pos2.x + size2.x &&
          pos1.x + size1.x > pos2.x - size2.x &&
          pos1.y - size1.y < pos2.y + size2.y &&
          pos1.y + size1.y > pos2.y - size2.y);
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

      if (pos.x < cameraLeft + p->getSize().x) {
        pos.x = cameraLeft + p->getSize().x;
        vel.x = 0;
      } else if (pos.x > cameraRight - p->getSize().x) {
        pos.x = cameraRight - p->getSize().x;
        vel.x = 0;
      }

      // Left wall
      if (pos.x - p->getSize().x < 0) {
        pos.x = p->getSize().x;
        vel.x = 0;
      }

      // Right wall
      if (pos.x + p->getSize().x > phase_width) {
        pos.x = phase_width - p->getSize().x;
        vel.x = 0;
      }

      // Top wall

      if (pos.y - p->getSize().y < -205) {
        pos.y = p->getSize().y;

        if (vel.y < 0) {
          vel.y = 0; // Prevents jumping through the top wall
          p->setInAir(true); // Not on ground if jumping through top wall
        }
      }

      // Bottom wall

      if (pos.y + p->getSize().y > phase_height) {
        pos.y = phase_height - p->getSize().y;
        p->setJumpForce();
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
      if (pos.x - e->getSize().x < 0) {
        pos.x = e->getSize().x;
        vel.x = 0;
      }

      // Right wall
      if (pos.x + e->getSize().x > phase_width) {
        pos.x = phase_width - e->getSize().x;
        vel.x = 0;
      }

      // Top wall

      if (pos.y - e->getSize().y < -205) {
        pos.y = e->getSize().y;
        if (vel.y < 0) {
          vel.y = 0; // Prevents jumping through the top wall
        }
      }

      // Bottom wall

      if (pos.y + e->getSize().y > phase_height) {
        pos.y = phase_height - e->getSize().y;
        vel.y = 0;
        e->setInAir(false);
      }
      e->setPosition(pos);
      e->setVelocity(vel);
    }
  }

}

void CollisionManager::treatPlayersCollision() {

  if (verifyCollision(players_vector[0], players_vector[1])) {
    players_vector[0]->collide(players_vector[1]);
    players_vector[1]->collide(players_vector[0]);
  }
}

void CollisionManager::treatEnemiesCollision() {
    // Colisões entre jogadores e inimigos
    for (vector<Player *>::iterator it = players_vector.begin();
        it != players_vector.end(); it++) {
        if ((*it) && (*it)->getAlive()) { // Só verifica se vivo
            for (vector<Enemy *>::iterator itEnemy = enemies_vector.begin();
                itEnemy != enemies_vector.end(); itEnemy++) {
                if (*itEnemy && (*itEnemy)->getAlive()) { // Só verifica se vivo
                    if (verifyCollision((*it), (*itEnemy))) {
                        (*itEnemy)->collide(*it);
                        (*it)->collide(*itEnemy);
                    }
                }
            }
        }
    }

    for (vector<Enemy *>::iterator it = enemies_vector.begin();
        it != enemies_vector.end(); it++) {
        if ((*it) && (*it)->getAlive()) { // Só verifica se vivo
            for (vector<Enemy *>::iterator itEnemy = enemies_vector.begin();
                itEnemy != enemies_vector.end(); itEnemy++) {
                if (*itEnemy && (*itEnemy)->getAlive()) { // Só verifica se vivo
                    if ((*it) != (*itEnemy)) {
                        if (verifyCollision((*it), (*itEnemy))) {
                            (*itEnemy)->collide(*it);
                            (*it)->collide(*itEnemy);
                        }
                    }
                }
            }
        }
    }
}
void CollisionManager::treatObstaclesCollision() {


  for (vector<Enemy *>::iterator it = enemies_vector.begin();
       it != enemies_vector.end(); it++) {
    if ((*it) && (*it)->getAlive()) {
      for (list<Obstacle *>::iterator itObstacle = obstacles_list.begin();
           itObstacle != obstacles_list.end(); itObstacle++) {
        if (*itObstacle) {
          if (verifyCollision((*it), (*itObstacle))) {
            if (!(dynamic_cast<ThornyBush *>(*itObstacle)))
              (*it)->collide(*itObstacle);
            (*itObstacle)->collide(*it);
          }
        }
      }
    }
  }

  for (vector<Player *>::iterator it = players_vector.begin();
       it != players_vector.end(); it++) {

    if ((*it) && (*it)->getAlive()) {
      for (list<Obstacle *>::iterator itObstacle = obstacles_list.begin();
           itObstacle != obstacles_list.end(); itObstacle++) {
        if (*itObstacle) {
          if (verifyCollision((*it), (*itObstacle))) {
            if (!(dynamic_cast<ThornyBush *>(*itObstacle)))
              (*it)->collide(*itObstacle);
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

      if (*itEnemy && (*itEnemy)->getAlive())
        if (verifyCollision(proj, *itEnemy)) {
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

        if (*itPlayer && (*itPlayer)->getAlive() && verifyCollision(proj, *itPlayer)) {
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
        collidedEntity = nullptr;
        cout << "Projectile collided with wall at position: "
             << pos.x << ", " << pos.y << endl;
      }
    }
    if (collided) {
      proj->collide(collidedEntity);
    }
    ++itProjectile;
  }
}

/* ------------------------------------------- */
/*                   ENTITIES                  */
/* ------------------------------------------- */

void CollisionManager::clearEntities() {
  enemies_vector.clear();
  obstacles_list.clear();
  projectiles_set.clear();
  players_vector.clear();
}

void CollisionManager::addObstacle(Obstacle *o) { obstacles_list.push_back(o); }

void CollisionManager::addProjectile(Projectile *p) { projectiles_set.insert(p); }

void CollisionManager::addEnemy(Enemy *e) { enemies_vector.push_back(e); }

void CollisionManager::addPlayer(Player *p) { players_vector.push_back(p); }

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

void CollisionManager::removeObstacle(Obstacle *o) { 
    obstacles_list.remove(o); 
}

void CollisionManager::removePlayer(Player *p) {
  auto it = std::find(players_vector.begin(), players_vector.end(), p);
  if (it != players_vector.end()) {
    players_vector.erase(it);
  }
}

/* ------------------------------------------- */
/*                   EXECUTE                   */
/* ------------------------------------------- */

void CollisionManager::setPhaseSize(Vector2f size) { phaseSize = size; }

void CollisionManager::execute() {
  treatEnemiesCollision();
  treatObstaclesCollision();
  treatProjectilesCollision();
  if (players_vector.size() > 1)
    treatPlayersCollision();
  treatWallCollision();
}



