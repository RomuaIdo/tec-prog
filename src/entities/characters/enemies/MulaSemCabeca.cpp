#include "../../../../include/entities/characters/enemies/MulaSemCabeca.h"

MulaSemCabeca::MulaSemCabeca()
    :Enemy(), chargeClock(0.f), isCharging(false), chargingClock(0.f){

    texture = pGM->loadTexture("assets/textures/mula.png");
    runTexture = texture;

    chargeTexture = pGM->loadTexture("assets/textures/MulaCharging.png");
    evilness = MULAEVILNESS;
    sprite.setTexture(texture);
    configSprite();
}

MulaSemCabeca::MulaSemCabeca(float x, float y, const float acel, int life, int s)
    : Enemy(x, y, acel, life, s), chargeClock(0.f), isCharging(false), chargingClock(0.f) {

    texture = pGM->loadTexture("assets/textures/mula.png");
    runTexture = texture;

    chargeTexture = pGM->loadTexture("assets/textures/MulaCharging.png");
    evilness = MULAEVILNESS;

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
        if(!isCharging) {
            velocity = Vector2f(MULAACEL * faced_right, 0.f);
        }
    } else {
        velocity = Vector2f(0.f, 0.f);
    }


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

        if (chargingClock >= 0.4f) {
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
            isCharging = true;
            chargingClock = 0.f;
            texture = runTexture;
            sprite.setTexture(texture);
            configSprite();
        }
    }
}

/* ------------------------------------------- */
/*                 SAVE BUFFER                 */
/* ------------------------------------------- */

json MulaSemCabeca::toJson() const {
    return {
        {"type", getType()},
        {"position_x", position.x},
        {"position_y", position.y},
        {"health", health},
        {"chargeClock", chargeClock},
        {"isCharging", isCharging},
        {"chargingClock", chargingClock},
        {"faced_right", faced_right},
        {"evilness", evilness},
        {"alive", alive},
        {"velocity_x", velocity.x},
        {"velocity_y", velocity.y},
        {"faced_right", faced_right},
        {"takeDamageClock", takeDamageClock},
        {"clock", clock},
        {"isBlinking", isBlinking},
        {"damageBlinkClock", damageBlinkClock}
    };
}

void MulaSemCabeca::fromJson(const json& j) {
    position.x = j.at("position_x");
    position.y = j.at("position_y");
    health = j.at("health");
    chargeClock = j.at("chargeClock");
    isCharging = j.at("isCharging");
    chargingClock = j.at("chargingClock");
    faced_right = j.at("faced_right");
    evilness = j.at("evilness");
    alive = j.at("alive");
    velocity.x = j.at("velocity_x");
    velocity.y = j.at("velocity_y");
    takeDamageClock = j.at("takeDamageClock");
    clock = j.at("clock");
    isBlinking = j.at("isBlinking");
    damageBlinkClock = j.at("damageBlinkClock");
}

std::string MulaSemCabeca::getType() const {
    return "Mula";
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
