#include "../../../include/entities/obstacles/ThornyBush.h"
#include <SFML/Window.hpp>

ThornyBush::ThornyBush() : Obstacle(), regenClock(0.f), active(false) {

  texture_hide = pGM->loadTexture("assets/textures/ThornyBushHide.png");
  texture_spikes = pGM->loadTexture("assets/textures/ThornyBushSpikes.png");

  texture = texture_hide;
  sprite.setTexture(texture_hide); // Start hidden
  configSprite();
}

ThornyBush::ThornyBush(float x, float y, bool harm)
    : Obstacle(x, y, harm), regenClock(0.f), active(false) {

  texture_hide = pGM->loadTexture("assets/textures/ThornyBushHide.png");
  texture_spikes = pGM->loadTexture("assets/textures/ThornyBushSpikes.png");

  texture = texture_hide;
  sprite.setTexture(texture_hide); // Start hidden
  configSprite();
}

ThornyBush::~ThornyBush() {}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void ThornyBush::execute() {
  update();
  draw();
}

void ThornyBush::update() {

  // If the bush is active, and has passed its cooldown,
  // it will hide again
  if (active && regenClock >= THORNYBUSHCOOLDOWN) {
    active = false; // Deactivate after dealing damage
    regenClock = 0.0f;
    setState(); // Update the texture to show Hide
  }

  regenClock += pGM->getdt();
}

void ThornyBush::obstacleAction(Entity *e) {
  if (Player *p = dynamic_cast<Player *>(e)) {
    if (!active) {
      active = true; // Activate the spikes when a character collides
      if (harmful) {
        dealDamage(p); // Deal damage to the player
      }
      setState(); // Update the texture to show Spikes
    }
  }
}

void ThornyBush::setState() {
  if (active) {
    sprite.setTexture(texture_spikes);
  } else {
    sprite.setTexture(texture_hide);
  }

  configSprite();
  sprite.setPosition(position);
}

void ThornyBush::collide(Entity *e) {
  obstacleAction(e);
  setState();
}

void ThornyBush::dealDamage(Player *p) {
  if (p) {
    p->takeDamage(THORNYBUSHSPIKES, 0);
  }
}

/* ------------------------------------------- */
/*                 SAVE BUFFER                 */
/* ------------------------------------------- */

json ThornyBush::toJson() const {
  return {{"type", getType()},
          {"position_x", position.x},
          {"position_y", position.y},
          {"regenClock", regenClock},
          {"active", active}};
}

void ThornyBush::fromJson(const json &j) {
  position.x = j.at("position_x");
  position.y = j.at("position_y");
  regenClock = j.at("regenClock");
  active = j.at("active");
}

std::string ThornyBush::getType() const { return "ThornyBush"; }
