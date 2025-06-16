#include "../../include/phases/SecondPhase.h"
#include "../../include/entities/characters/Enemy.h"
#include "../../include/entities/obstacles/Obstacle.h"
#include "../../include/entities/obstacles/Plataform.h"

SecondPhase::SecondPhase(Vector2f size, Player* p1, Player* p2, const string &backgroundPath) : 
    Phase(size, p1, p2, backgroundPath) {
    createEnemies();
    createObstacles();
    createPlatforms();
    createScenery();
}

SecondPhase::~SecondPhase() {}

void SecondPhase::execute() {
  entities_list.clear();
  pCM->execute();
}

void SecondPhase::createEnemies() {
}

void SecondPhase::createObstacles() {
}

