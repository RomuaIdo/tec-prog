#include "../../include/entities/Projectile.h"
#include <SFML/Window.hpp>

Projectile::Projectile() : Entity(), owner(nullptr), active(true) {}

Projectile::Projectile(float x, float y, Vector2f vel, Entity *creator)
    : Entity(x, y), owner(creator), active(true) {

  potion = pGM->loadTexture("assets/textures/Potion.png");
  Rock = pGM->loadTexture("assets/textures/Rock.png");

  setVelocity(vel);
  if (vel.x < 0) {
    sprite.setScale(-1.f, 1.f);
  } else {
    sprite.setScale(1.f, 1.f);
  }

  if (dynamic_cast<Player *>(owner)) {
    sprite.setTexture(Rock);
  } else if (dynamic_cast<Enemy *>(owner)) {
    sprite.setTexture(potion);
  } else {
    cerr << "Projectile owner is not a Player or Enemy!" << endl;
    return;
  }
  configSprite();
}

Projectile::~Projectile() {}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Projectile::collide(Entity *other) {
    // Não processar colisões se o projétil já está inativo
    if (!active)
        return;


    // Enemy's Projectile (ex: Cuca)
    if (dynamic_cast<Enemy *>(owner)) {
        
        // Player Collision
        if (Player *player = dynamic_cast<Player *>(other)) {
            int direction = static_cast<int>(player->getPosition().x - position.x);
            direction /= abs(direction);
            player->takeDamage(POTIONDAMAGE, direction);
            active = false;
        }
        // Colisão com outro inimigo - ignorar
        else if (dynamic_cast<Enemy *>(other)) {
        return;
        }
        // Colisão com qualquer outra entidade
        else {
        active = false;
        }
    }

    // Player Projectile
    else if (Player *playerOwner = dynamic_cast<Player *>(owner)) {

        // Enemy Collision
        if (Enemy *enemy = dynamic_cast<Enemy *>(other)) {

            int direction = static_cast<int>(enemy->getPosition().x - position.x);
            direction /= abs(direction);
            enemy->takeDamage(ROCKDAMAGE, direction);
            active = false;

            // Atualizar pontuação se inimigo morreu
            if (enemy->getHealth() <= 0) {
                playerOwner->increaseScore(SCOREMULTIPLIER * enemy->getEvilness());
                cout << "Player score increased to " << playerOwner->getScore() << endl;
            }
        }
        // Colisão com outro jogador - ignorar
        else if (dynamic_cast<Player *>(other)) {
            return;
        }
        // Colisão com qualquer outra entidade
        else {
            active = false;
        }
    }
    // Projétil sem dono válido (fallback)
    else {
        active = false;
        cerr << "Projectile owner is not a Player or Enemy!" << endl;
    }
}

void Projectile::move() {
    applyGravity();
    position += velocity;
}

void Projectile::execute() {
  draw();
  move();
}

/* ------------------------------------------- */
/*                 SAVE BUFFER                 */
/* ------------------------------------------- */

json Projectile::toJson() const {
    return {
        {"position_x", position.x},
        {"position_y", position.y},
        {"velocity_x", velocity.x},
        {"velocity_y", velocity.y},
        {"active", active}
    };
}

void Projectile::fromJson(const json& j) {
    position.x = j.at("position_x").get<float>();
    position.y = j.at("position_y").get<float>();
    velocity.x = j.at("velocity_x").get<float>();
    velocity.y = j.at("velocity_y").get<float>();
    active = j.at("active").get<bool>();
}

std::string Projectile::getType() const{
    return "Projectile";
}

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

bool Projectile::getActive() { return active; }

void Projectile::setActive(bool Active) { active = Active; }
