#include "../../../../include/entities/characters/enemies/MulaSemCabeca.h"

MulaSemCabeca::MulaSemCabeca(float x, float y, const float acel, int life, int s)
    : Enemy(x, y, acel, life, s), chargeClock(0.f), isCharging(false), chargingClock(0.f) {

  texture = pGM->loadTexture("assets/textures/Mula.png");
  runTexture = texture;

  chargeTexture = pGM->loadTexture("assets/textures/MulaCharging.png");

  sprite.setTexture(texture);
  configSprite();
}

MulaSemCabeca::~MulaSemCabeca() {}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void MulaSemCabeca::execute() {
  if (alive) {
    move();
    draw();
    verifyDeadPlayers();
    updateClocks();
    updateDamageBlink();
    updateChargingClock();
  }
}

void MulaSemCabeca::move() {

    float closer = 100000.f;
    float right = 1.f;

    // Get the closest player direction
    for (list<Player *>::iterator it = players_list.begin(); it != players_list.end(); it++) {
        if (*it) {
            // Get direction to player (feet to feet)
            Vector2f direction =
                (((*it)->getPosition() + Vector2f(0.f, (*it)->getSize().y)) - (position + Vector2f(0.f, size.y)));
            float module =
                sqrt(direction.x * direction.x + direction.y * direction.y);
            if (module < closer) {
                // See if closer is in right or left
                right = direction.x;

                closer = module;
            }
        }
    }

    if (abs(right) < MULAFAR) {
        far = false;
    } else {
        far = true;
    }

    faced_right = right / abs(right);
    Vector2f positionBeforeCharge(position);
    if (!far) {
        charge();
    } else {
        velocity = Vector2f(0.f, 0.f);
    }

    if ( abs(position.x - positionBeforeCharge.x) > 800.f)
        velocity.x = faced_right * aceleration;

    applyGravity();
    moveCharacter();
}

void MulaSemCabeca::updateClocks() {
    float dt = pGM->getdt();

    clock += dt;
    chargeClock += dt;
}

void MulaSemCabeca::updateChargingClock() {
    if (isCharging) {
        chargingClock += pGM->getdt();

        // Para de carregar após 1 segundo
        if (chargingClock >= 1.0f) {
            isCharging = false;
            chargingClock = 0.f;
            velocity = Vector2f(MULAACEL * faced_right, 0.f);
        }
    }
}

void MulaSemCabeca::charge() {
    if (chargeClock >= CHARGECOOLDOWN) {
        // stay active for 2 seconds (showing that will charge)

        texture = chargeTexture;
        sprite.setTexture(texture);
        configSprite();
        setVelocity(Vector2f(0.f, 0.f));

        // after 2 seconds, the enemy will charge
        if (chargeClock >= CHARGECOOLDOWN + CHARGEPREPARATIONCOOLDOWN) {
            setVelocity(Vector2f(faced_right * CHARGEFORCE, 0.f));
            chargeClock = 0.f;

            texture = runTexture;
            sprite.setTexture(texture);
            configSprite();
        }
    }
}

/* ------------------------------------------- */
/*              PLAYER FUNCTIONS               */
/* ------------------------------------------- */

void MulaSemCabeca::attack(Player *p) {
  if (p) {
    int direction = static_cast<int>(p->getPosition().x - position.x);
    direction /= abs(direction);
    p->takeDamage(strength, direction);
  }
}
