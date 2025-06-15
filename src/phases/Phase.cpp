#include "../../include/phases/Phase.h"

Phase::Phase(Vector2f size, Player *p1, Player *p2)
    : pCM(CollisionManager::getInstance()), phaseSize(size), player1(p1),
      player2(p2) {
  entities_list.clear();
}

Phase::~Phase() {
  entities_list.clear();
}

Vector2f Phase::getPhaseSize() const { return phaseSize; }
