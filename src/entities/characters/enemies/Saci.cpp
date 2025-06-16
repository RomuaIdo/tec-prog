#include "../../../../include/entities/characters/enemies/Saci.h"
#include "../../../../include/entities/characters/Player.h"
#include <cmath>
#include <limits>


Saci::Saci(float x, float y, const float acel, int life, float coef, int s)
    : Enemy(x, y, acel, life, coef, s), teleportTime(0.f),
      lastPositionTime(0.f), far(false), clock(0.f),
      minDistance(50.f), tooClose(false) { // Adicionado minDistance e tooClose

    lastPosition = Vector2f(x, y);
    
    if (!texture.loadFromFile("assets/textures/Saci.png")) {
        std::cerr << "Failed to load Saci.png!" << std::endl;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    centerOrigin();
    
    // Ajustar altura real do Saci
    const float actualHeight = sprite.getLocalBounds().height;
    position.y = y - actualHeight/2;
    sprite.setPosition(position);
    
    teleportTime = 5.f; // Tempo entre teleportes
    lastPositionTime = 0.f;
}

Saci::~Saci() {}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Saci::execute() {
  move();
  draw();
  teleport();
}

void Saci::move() {
  Player *closestPlayer = nullptr;
  float closestDistance = numeric_limits<float>::max();

  // Encontrar jogador mais próximo
  for (auto player : players_list) {
    if (!player)
      continue;

    Vector2f direction = player->getPosition() - position;
    float distance =
        sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < closestDistance) {
      closestDistance = distance;
      closestPlayer = player;
    }
  }

  if (closestPlayer) {
    // Atualizar última posição conhecida periodicamente (aumentar intervalo)
    lastPositionTime += pGM->getdt();
    if (lastPositionTime >= 4.f) { // Aumentado de 2s para 4s
      lastPosition = closestPlayer->getPosition();
      lastPositionTime = 0.f;
    }

    // Determinar se está longe (aumentar distância)
    far = (closestDistance > 500.f); // Aumentado de 300 para 500

    // Determinar se está muito perto (nova verificação)
    tooClose = (closestDistance < minDistance); // <-- Adicionado

    // Determinar direção do jogador
    faced_right = (closestPlayer->getPosition().x > position.x) ? 1 : -1;

    // Se estiver muito perto, parar o movimento
    if (tooClose) {
      speed.x = 0; // <-- Para de se mover
    } else if (!far) {
      // Movimento suavizado com aceleração reduzida
      speed.x =
          faced_right * (aceleration * 0.6f); // Reduzido para 60% da aceleração

      // Pular menos frequentemente
      if (!isInAir() && clock > 2.f) {
        speed.y = -aceleration * 0.7f; // Reduzir altura do pulo
        setInAir(true);
        clock = 0.f;
      }
    } else {
      // Movimento mais lento quando longe
      speed.x = faced_right * (aceleration * 0.4f);
    }
    clock += pGM->getdt();
  }

  moveCharacter();
}

void Saci::collide(Entity *e) {
  if (Player *p = dynamic_cast<Player *>(e)) {
    attack(p);
  }
}

Vector2f Saci::getPlayerLastPosition() { return lastPosition; }

void Saci::teleport() {
    // Não teleporta se estiver longe OU muito perto
    if (far || tooClose) return; // <-- Adicionado tooClose
    
    clock += pGM->getdt();
    if (clock >= teleportTime) {
        Vector2f pos = getPlayerLastPosition();
        
        // Limitar teleporte à área jogável
        Vector2f windowSize = Vector2f(
            static_cast<float>(pGM->getWindow()->getSize().x),
            static_cast<float>(pGM->getWindow()->getSize().y)
        );
        const float margin = 100.f;
        
        // Garantir que não teleporte para fora da tela
        if (pos.x < margin) pos.x = margin;
        if (pos.x > windowSize.x - margin) pos.x = windowSize.x - margin;
        if (pos.y < margin) pos.y = margin;
        if (pos.y > windowSize.y - margin) pos.y = windowSize.y - margin;
        
        setPosition(pos);
        clock = 0.f;
    }
}

/* ------------------------------------------- */
/*              PLAYER FUNCTIONS               */
/* ------------------------------------------- */

void Saci::attack(Player *p) {
  if (p->getHealth() > 0 && pGM->getClockTime() >= 2.f) {
    p->loseHealth(strength);
    pGM->resetClock();
  }
}
