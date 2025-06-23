#include "../../../include/entities/obstacles/Cloud.h"
#include <SFML/Window.hpp>

Cloud::Cloud()
    : Obstacle(), isActive(false), plataformType(1), regenClock(0.0f),
      originalPosition(0, 0) {
}

Cloud::Cloud(float x, float y, bool harm, int n)
    : Obstacle(x, y, harm), isActive(false), plataformType(n), regenClock(0.0f),
      originalPosition(x, y) {

  cloud1 = pGM->loadTexture("assets/textures/Cloud1.png");
  cloud1active = pGM->loadTexture("assets/textures/Cloud1active.png");
  cloud2 = pGM->loadTexture("assets/textures/Cloud2.png");
  cloud2active = pGM->loadTexture("assets/textures/Cloud2active.png");

  if (plataformType) {
    texture = cloud2;
  } else {
    texture = cloud1;
  }

  sprite.setTexture(texture);
  configSprite();
}

Cloud::~Cloud() {}

void Cloud::collide(Entity *other) {
  if (dynamic_cast<Cloud *>(other)) {
    return; // Avoid self-collision
  }
  obstacleAction(other);
}

void Cloud::execute() {
  draw();
  move();
  setState();
  sprite.setTexture(texture);
  configSprite();
  regenClock += pGM->getdt();
  if (regenClock >= PLATAFORMMOVECLOCK && isActive) {
    isActive = false;
  }
}

void Cloud::obstacleAction(Entity *e) {
  isActive = false;
  float dx = (position.x - e->getPosition().x);
  float dy = (position.y - e->getPosition().y);

  Vector2f intersection = Vector2f(abs(dx) - (size.x + e->getSize().x),
                                   abs(dy) - (size.y + e->getSize().y));

  if (intersection.x < 0.0f && intersection.y < 0.0f) {
    // Collision in y
    if (std::abs(intersection.x) >= std::abs(intersection.y)) {
      if (dy > 0) {
        isActive = true;   // Player is on top of the platform
        regenClock = 0.0f; // Reset regen clock
      } else
        isActive = false;
    } else {
      isActive = false;
    }
  }
}

void Cloud::setState() {
  if (isActive) {
    if (plataformType) {
      texture = cloud2active;
    } else {
      texture = cloud1active;
    }
  } else {
    if (plataformType) {
      texture = cloud2;
    } else {
      texture = cloud1;
    }
  }
}

void Cloud::move() {
  if (isActive) {
    if (position.y < originalPosition.y + PLATAFORMMAXPOSITION) {
      position.y += PLATAFORMMOVE;
    }
    if (position.y > originalPosition.y + PLATAFORMMAXPOSITION)
      position.y = originalPosition.y + PLATAFORMMAXPOSITION;
  } else {
    if (position.y > originalPosition.y) {
      position.y -= PLATAFORMMOVE;
    }
    if (position.y < originalPosition.y)
      position.y = originalPosition.y;
  }
}

/* ------------------------------------------- */
/*                 SAVE BUFFER                 */
/* ------------------------------------------- */

json Cloud::toJson() const {
  return {{"type", getType()},
          {"position_x", position.x},
          {"position_y", position.y},
          {"velocity_x", velocity.x},
          {"velocity_y", velocity.y},
          {"clock", clock},
          {"size_x", size.x},
          {"size_y", size.y},
          {"plataformSize_x", originalPosition.x},
          {"plataformSize_y", originalPosition.y},
          {"regenClock", regenClock},
          {"isActive", isActive},
          {"plataformType", plataformType},
          {"regenClock", regenClock},
          {"originalPosition_x", originalPosition.x},
          {"originalPosition_y", originalPosition.y}
        };
}

void Cloud::fromJson(const json &j) {
  position.x = j.at("position_x");
  position.y = j.at("position_y");
  isActive = j.at("isActive").get<bool>();
  plataformType = j.at("plataformType").get<int>();
  regenClock = j.at("regenClock").get<float>();
  originalPosition.x = j.at("plataformSize_x").get<float>();
  originalPosition.y = j.at("plataformSize_y").get<float>();
  size.x = j.at("size_x").get<float>();
  size.y = j.at("size_y").get<float>();
  velocity.x = j.at("velocity_x").get<float>();
  velocity.y = j.at("velocity_y").get<float>();
  clock = j.at("clock").get<float>();

  cloud1 = pGM->loadTexture("assets/textures/Cloud1.png");
  cloud1active = pGM->loadTexture("assets/textures/Cloud1active.png");
  cloud2 = pGM->loadTexture("assets/textures/Cloud2.png");
  cloud2active = pGM->loadTexture("assets/textures/Cloud2active.png");

  if (plataformType) {
    texture = cloud2;
  } else {
    texture = cloud1;
  }
}

std::string Cloud::getType() const { return "Cloud"; }

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

bool Cloud::getIsActive() const { return isActive; }

void Cloud::setIsActive(bool active) { isActive = active; }
