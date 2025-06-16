#include "../../../include/entities/obstacles/ThornyBush.h"

ThornyBush::ThornyBush(float x, float y, bool harm)
    : Obstacle(x, y, harm), spikes(2), time_between_attacks(2.0f),
      own_clock(0.0f) {
  if (!texture_hide.loadFromFile("assets/textures/ThornyBushHide.png")) {
    std::cerr << "Failed to load ThornyBushHide.png!" << std::endl;
  }
  if (!texture_spikes.loadFromFile("assets/textures/ThornyBushSpikes.png")) {
    std::cerr << "Failed to load ThornyBushSpikes.png!" << std::endl;
  }
  is_active = false; // Initially not active
  harmful = true;
  texture = texture_hide;
  sprite.setTexture(texture_hide); // Start hidden
  centerOrigin();
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
  own_clock += pGM->getdt();

  // If the bush is active, it can deal damage periodically
  if (is_active && own_clock >= time_between_attacks) {
    is_active = false; // Deactivate after dealing damage
    own_clock = 0.0f;  // Reset the clock
    setState();        // Update the texture to show Hide
  }
}

void ThornyBush::obstacleAction(Player *p) {
  if (p) {
    if (!is_active) {
      is_active = true; // Activate the spikes when a character collides
      dealDamage(p);
      setState(); // Update the texture to show Spikes
    }
  }
}

void ThornyBush::obstacleAction(Enemy *e) {
  if (e) {
    if (!is_active) {
      is_active = true; // Activate the spikes when a character collides
      e->loseHealth(spikes);
      setState(); // Update the texture to show Spikes
    }
  }
}

void ThornyBush::setState() {
  if (is_active) {
    sprite.setTexture(texture_spikes);
  } else {
    sprite.setTexture(texture_hide);
  }
  centerOrigin();
  sprite.setPosition(position);
}

void ThornyBush::collide(Entity *e) {
  if(Player *p = dynamic_cast<Player *>(e)) {
    obstacleAction(p);
  } else if (Enemy *en = dynamic_cast<Enemy *>(e)) {
    obstacleAction(en);
  }
  setState();
}

void ThornyBush::dealDamage(Player *p) {
  if (p) {
    p->loseHealth(spikes);
  }
}

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

void ThornyBush::setSpikes(int s) { spikes = s; }

int ThornyBush::getSpikes() const { return spikes; }
