#include "../../../include/entities/obstacles/Plataform.h"
#include "../../../include/entities/characters/Enemy.h"
#include "../../../include/entities/characters/Player.h"
#include <SFML/Window.hpp>

Plataform::Plataform() : Obstacle(), width(0.f), height(0.f) {
  if (!texture.loadFromFile("assets/textures/Obstacle.png")) {
    std::cerr << "Failed to load Plataform.png!" << std::endl;
  }

  texture.setSmooth(true);
  sprite.setTexture(texture);
  centerOrigin();
  size.x = sprite.getLocalBounds().width;
  size.y = sprite.getLocalBounds().height;
  sprite.setScale(size.x / sprite.getLocalBounds().width,
                  size.y / sprite.getLocalBounds().height);
}

Plataform::Plataform(float x, float y, bool harm)
    : Obstacle(harm, x, y), width(0.f), height(0.f) {}

Plataform::~Plataform() {}

void Plataform::collide(Entity *other) {
  if (Player *player = dynamic_cast<Player *>(other)) {
    obstacleAction(player);
  }
  else if (Enemy *enemy = dynamic_cast<Enemy *>(other)) {
    obstacleAction(enemy);
  }
}

void Plataform::execute() { draw(); }

void Plataform::obstacleAction(Player *player) {
  Vector2f cPos = player->getPosition();
  Vector2f oPos = getPosition();
  Vector2f cSize = player->getSize();
  Vector2f oSize = getSize();

  float cLeft = cPos.x - cSize.x / 2;
  float cRight = cPos.x + cSize.x / 2;
  float cTop = cPos.y - cSize.y / 2;
  float cBottom = cPos.y + cSize.y / 2;

  float oLeft = oPos.x - oSize.x / 2;
  float oRight = oPos.x + oSize.x / 2;
  float oTop = oPos.y - oSize.y / 2;
  float oBottom = oPos.y + oSize.y / 2;

  float intersectX = min(cRight, oRight) - max(cLeft, oLeft);
  float intersectY = min(cBottom, oBottom) - max(cTop, oTop);

  if (intersectX > 0 && intersectY > 0) {
    // Calculate overlaps in each direction
    float topOverlap = cBottom - oTop;
    float bottomOverlap = oBottom - cTop;
    float leftOverlap = cRight - oLeft;
    float rightOverlap = oRight - cLeft;

    // Find the minimum overlap
    float minOverlap =
        min({topOverlap, bottomOverlap, leftOverlap, rightOverlap});

    // Resolve na direção da menor sobreposição
    if (minOverlap == topOverlap) {
      // Top collision (player is above the platform)
      cPos.y -= minOverlap;
      player->setInAir(false);
      player->setVelocity(Vector2f(player->getVelocity().x, 0.f));
    } else if (minOverlap == bottomOverlap) {
      // Bottom collision (player is below the platform)
      cPos.y += minOverlap;
      player->setVelocity(Vector2f(player->getVelocity().x, 0.f));
    } else if (minOverlap == leftOverlap) {
      // Left collision
      cPos.x -= minOverlap;
      player->setVelocity(Vector2f(0.f, player->getVelocity().y));
    } else if (minOverlap == rightOverlap) {
      // Right collision
      cPos.x += minOverlap;
      player->setVelocity(Vector2f(0.f, player->getVelocity().y));
    }

    player->setPosition(cPos);
  }
}

void Plataform::obstacleAction(Enemy *enemy) {
  Vector2f cPos = enemy->getPosition();
  Vector2f oPos = getPosition();
  Vector2f cSize = enemy->getSize();
  Vector2f oSize = getSize();

  // Define the limits of the collision box
  float cLeft = cPos.x - cSize.x / 2;
  float cRight = cPos.x + cSize.x / 2;
  float cTop = cPos.y - cSize.y / 2;
  float cBottom = cPos.y + cSize.y / 2;

  float oLeft = oPos.x - oSize.x / 2;
  float oRight = oPos.x + oSize.x / 2;
  float oTop = oPos.y - oSize.y / 2;
  float oBottom = oPos.y + oSize.y / 2;

  // Calculate the intersection area
  float intersectX = min(cRight, oRight) - max(cLeft, oLeft);
  float intersectY = min(cBottom, oBottom) - max(cTop, oTop);

  if (intersectX > 0 && intersectY > 0) {
    // Calculate overlaps in each direction
    float topOverlap = cBottom - oTop;
    float bottomOverlap = oBottom - cTop;
    float leftOverlap = cRight - oLeft;
    float rightOverlap = oRight - cLeft;

    // Find the minimum overlap
    float minOverlap =
        std::min({topOverlap, bottomOverlap, leftOverlap, rightOverlap});

    // Resolve in the direction of the smallest overlap
    if (minOverlap == topOverlap) {
      // Top collision (enemy is above the platform)
      cPos.y -= minOverlap;
      enemy->setInAir(false);
      enemy->setVelocity(Vector2f(enemy->getVelocity().x, 0.f));
    } else if (minOverlap == bottomOverlap) {
      // Bottom collision (enemy is below the platform)
      cPos.y += minOverlap;
      enemy->setVelocity(Vector2f(enemy->getVelocity().x, 0.f));
    } else if (minOverlap == leftOverlap) {
      // Left collision
      cPos.x -= minOverlap;
      enemy->setVelocity(Vector2f(0.f, enemy->getVelocity().y));
    } else if (minOverlap == rightOverlap) {
      // Right collision
      cPos.x += minOverlap;
      enemy->setVelocity(Vector2f(0.f, enemy->getVelocity().y));
    }

    enemy->setPosition(cPos);
  }
}

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

void Plataform::setHeight(float h) { height = h; }

void Plataform::setWidth(float w) { width = w; }

float Plataform::getHeight() const { return height; }

float Plataform::getWidth() const { return width; }
