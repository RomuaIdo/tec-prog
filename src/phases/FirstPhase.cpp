#include "../../include/phases/FirstPhase.h"
#include "../../include/entities/characters/Enemy.h"
#include "../../include/entities/obstacles/Obstacle.h"
#include "../../include/entities/obstacles/Plataform.h"

FirstPhase::FirstPhase(Vector2f size, Player* p1, Player* p2) : 
    Phase(size, p1, p2) {
    createEnemies();
    createObstacles();
    createPlatforms();
    createScenery();
}

FirstPhase::~FirstPhase() {
  pCM->clearEntities();
}

void FirstPhase::execute() {
    entities_list.traverse();
    pCM->execute();
}

void FirstPhase::createEnemies() {
    createMediumEnemies();
}

void FirstPhase::createObstacles() {
    createMediumObstacles();
}

void FirstPhase::createPlatforms() {
    // Exemplo: criar 3 plataformas
    for (int i = 0; i < 3; i++) {
        Plataform* p = new Plataform(i * 300.f, 500.f, false);
        entities_list.add(p);
        pCM->addObstacle(p);
    }
}

void FirstPhase::createScenery() {
}

void FirstPhase::createMediumEnemies() {
    for (int i = 0; i < maxMediumEnemies; i++) {
        Enemy* e = new Enemy(i * 200.f, 100.f, 15.f, 5, 1.f, 2);
        e->addPlayer(player1);
        e->addPlayer(player2);
        entities_list.add(e);
        pCM->addEnemy(e);
    }
}

void FirstPhase::createMediumObstacles() {
    for (int i = 0; i < 2; i++) {
        Plataform* o = new Plataform(i*400.f, (i + 2) * 150.f, false);
        entities_list.add(o);
        pCM->addObstacle(o);
    }
}
