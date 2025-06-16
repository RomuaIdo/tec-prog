#include "../../include/phases/FirstPhase.h"
#include "../../include/entities/characters/Enemy.h"
#include "../../include/entities/obstacles/Honey.h"
#include "../../include/graphicalelements/Tile.h"
#include <cmath>

FirstPhase::FirstPhase(Vector2f size, Player *p1, Player *p2,
                       const string &backgroundPath)
    : Phase(size, p1, p2, backgroundPath) {
  createScenery();
  createEnemies();
  createObstacles();
  createPlatforms();
}

FirstPhase::~FirstPhase() { pCM->clearEntities(); }

void FirstPhase::execute() {
  vector<Tile *>::iterator it;
  for (it = tiles.begin(); it != tiles.end(); ++it) {
    (*it)->execute();
  }
  entities_list.traverse();

  pCM->execute();
}

void FirstPhase::createEnemies() { 
  createSaci();
  createMediumEnemies(); 
}

void FirstPhase::createObstacles() { createHoney(); }

void FirstPhase::createMediumEnemies() {
}

void FirstPhase::createHoney() {
  const float tileWidth = 50.0f;
  const float groundY = phaseSize.y - 25.0f; // Ground level (tile center)
  vector<float> availablePositions;

  // Generate all possible x positions (multiples of 50)
  for (float x = tileWidth; x < phaseSize.x - tileWidth; x += tileWidth) {
    availablePositions.push_back(x);
  }

  // Simple Fisher-Yates shuffle using rand()
  for (int i = availablePositions.size() - 1; i > 0; --i) {
    int j = rand() % (i + 1);
    float temp = availablePositions[i];
    availablePositions[i] = availablePositions[j];
    availablePositions[j] = temp;
  }

  // Create honeys without overlapping
  int honeyCount = 0;
  vector<float> usedPositions;

  for (int i = 0;
       i < maxHoneys && i < static_cast<int>(availablePositions.size()); i++) {
    float x = availablePositions[i];
    bool positionValid = true;

    // Check if position is too close to existing honeys
    for (vector<float>::iterator it = usedPositions.begin();
         it != usedPositions.end(); ++it) {
      if (fabs(x - *it) < tileWidth * 2) {
        positionValid = false;
        break;
      }
    }

    if (positionValid) {
      Honey *h = new Honey(x, groundY, false, "assets/textures/Honey.png");
      entities_list.add(h);
      pCM->addObstacle(h);
      usedPositions.push_back(x);
      honeyCount++;
    }
  }
}
