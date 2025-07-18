#include "../../../../include/entities/characters/enemies/Saci.h"

Saci::Saci()
    :Enemy(), jumpClock(0.f), lastPositionClock(0.f), 
    teleportClock(0.f), lastPosition(Vector2f(0.f,0.f)){
    texture = pGM->loadTexture("assets/textures/Saci.png");

    evilness = SACIEVILNESS;
    sprite.setTexture(texture);
    configSprite();
}

Saci::Saci(float x, float y, const float acel, int life, int s)
    : Enemy(x, y, acel, life, s), jumpClock(0.f), lastPositionClock(0.f),
      teleportClock(0.f), lastPosition(Vector2f(x, y)) {

  texture = pGM->loadTexture("assets/textures/Saci.png");

  evilness = SACIEVILNESS;
  sprite.setTexture(texture);
  configSprite();
}

Saci::~Saci() {}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Saci::execute() {
    if (alive) {
        move();
        draw();
        teleport(getPlayerLastPosition());
        verifyDeadPlayers();
        updateClocks();
        updateDamageBlink();
    }
}

void Saci::move() {

    float closer = 100000.f;
    float right = 1.f;

    for (list<Player *>::iterator it = players_list.begin();
        it != players_list.end(); it++) {
        if (*it) {

        // Get direction to player (feet to feet)
        Vector2f direction =
            (((*it)->getPosition() + Vector2f(0.f, (*it)->getSize().y)) -
            (position + Vector2f(0.f, size.y)));

        float module =
            sqrt(direction.x * direction.x + direction.y * direction.y);

        if (module < closer) {

            // See if closer is in right or left
            right = direction.x;

            closer = module;

            if (lastPositionClock >= 1.f) {
            lastPosition = Vector2f((*it)->getPosition().x,
                                    pGM->getWindow()->getSize().y - size.y);
            lastPositionClock = 0.f;
            }
        }
        }
    }

    // if it is 600 pixels far, the enemy dont move
    if (abs(right) < SACIFAR) {
        far = false;
    } else {
        far = true;
    }

    faced_right = (int)(right / abs(right));

    if (!far) {
        if (!getInAir() && jumpClock >= JUMPCOOLDOWN) {
        setInAir(true);
        velocity = (Vector2f(faced_right * aceleration, -SACIJUMPFORCE));
        jumpClock = 0.f;
        }
    }

    // Stop after jumping
    if (!getInAir() && !isBlinking) {
        velocity = Vector2f(0.f, 0.f);
    }

    applyGravity();
    moveCharacter();
}


void Saci::updateClocks() {
    float dt = pGM->getdt();
    jumpClock += dt;
    lastPositionClock += dt;
    teleportClock += dt;
}

/* ------------------------------------------- */
/*                 SAVE BUFFER                 */
/* ------------------------------------------- */

json Saci::toJson() const {
    return {
        {"type", getType()},
        {"position_x", position.x},
        {"position_y", position.y},
        {"aceleration", aceleration},
        {"health", health},
        {"jumpClock", jumpClock},
        {"lastPosition_x", lastPosition.x},
        {"lastPosition_y", lastPosition.y},
        {"lastPositionClock", lastPositionClock},
        {"teleportClock", teleportClock},
        {"faced_right", faced_right},
        {"alive", alive},
        {"evilness", evilness},
        {"strength", strength},
        {"far", far},
        {"isBlinking", isBlinking},
        {"damageBlinkClock", damageBlinkClock},
        {"takeDamageClock", takeDamageClock}
    };
}

void Saci::fromJson(const json& j) {
    position.x = j.at("position_x");
    position.y = j.at("position_y");
    health = j.at("health");
    jumpClock = j.at("jumpClock");
    lastPositionClock = j.at("lastPositionClock");
    teleportClock = j.at("teleportClock");
    lastPosition.x = j.at("lastPosition_x");
    lastPosition.y = j.at("lastPosition_y");
    aceleration = j.at("aceleration");
    faced_right = j.at("faced_right");
    alive = j.at("alive");
    evilness = j.at("evilness");
    strength = j.at("strength");
    far = j.at("far");
    isBlinking = j.at("isBlinking");
    damageBlinkClock = j.at("damageBlinkClock");
    takeDamageClock = j.at("takeDamageClock");
}

std::string Saci::getType() const {
    return "Saci";
}

/* ------------------------------------------- */
/*              TELEPORT FUNCTIONS             */
/* ------------------------------------------- */

Vector2f Saci::getPlayerLastPosition() { return lastPosition; }

void Saci::teleport(Vector2f pos) {
    if (!far && teleportClock >= TELEPORTCOOLDOWN) {
        teleportClock = 0;
        setPosition(pos);
    }
}

/* ------------------------------------------- */
/*              PLAYER FUNCTIONS               */
/* ------------------------------------------- */

void Saci::attack(Player *p) {
    if (p) {
        int direction = static_cast<int>(p->getPosition().x - position.x);
        direction /= abs(direction);
        p->takeDamage(strength, direction);
    }
}
