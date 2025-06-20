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

  // Projétil lançado por inimigo (ex: Cuca)
  if (dynamic_cast<Enemy *>(owner)) {
    // Colisão com jogador
    if (Player *player = dynamic_cast<Player *>(other)) {
      player->takeDamage(POTIONDAMAGE);
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
  // Projétil lançado por jogador
  else if (Player *playerOwner = dynamic_cast<Player *>(owner)) {

    // Colisão com inimigo
    if (Enemy *enemy = dynamic_cast<Enemy *>(other)) {
      cout << "Projectile hit enemy " << endl;
      enemy->takeDamage(10);
      active = false;

      // Atualizar pontuação se inimigo morreu
      if (enemy->getHealth() <= 0) {
        playerOwner->increaseScore(SCOREMULTIPLIER * enemy->getEvilness());
        cout << "Player score increased to " << endl;
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
/*                 GETS & SETS                 */
/* ------------------------------------------- */

bool Projectile::getActive() { return active; }

void Projectile::setActive(bool Active) { active = Active; }
