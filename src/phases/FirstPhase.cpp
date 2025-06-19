#include "../../include/phases/FirstPhase.h"
#include "../../include/entities/characters/enemies/Cuca.h"
#include "../../include/entities/obstacles/Honey.h"
#include "../../include/graphicalelements/BackgroundElement.h"
#include <cmath>

FirstPhase::FirstPhase(Vector2f size, float limiarX, Player *p1, Player *p2)
    : Phase(size, limiarX, p1, p2) {
    createScenery();
    createEnemies();
    createObstacles();
    createPlatforms();
}

FirstPhase::~FirstPhase() { pCM->clearEntities(); }

void FirstPhase::execute() {
    vector<BackgroundElement *>::iterator it;
    for (it = BackgroundLayers.begin(); it != BackgroundLayers.end(); ++it) {
        (*it)->execute();
    }
    for (it = tiles.begin(); it != tiles.end(); ++it) {
        (*it)->execute();
    }
    entities_list.traverse();
    checkPhaseCompletion();
    pCM->execute();
}

void FirstPhase::createEnemies() { 
    createSaci();
    createCucas();
}

void FirstPhase::createObstacles() { 
    createHoney(); 
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
      if (fabs(x - (*it)) < tileWidth * 2) {
        positionValid = false;
        break;
      }
    }

    if (positionValid) {
      Honey *h = new Honey(x, groundY, false);
      Honey *h2 = new Honey(x+50.f, groundY, false);
      entities_list.add(h);
      entities_list.add(h2);
      pCM->addObstacle(h);
      pCM->addObstacle(h2);
      usedPositions.push_back(x);
      usedPositions.push_back(x + 50.f); // Add the second honey's position

      honeyCount++;
    }
  }
}

void FirstPhase::createCucas() {
    const float groundY = phaseSize.y ; 

    for (int i = 0; i < maxCucas; i++) {
        float x = 100.f + static_cast<float>(rand() %
                                            static_cast<int>(phaseSize.x - 200.f));

        // Calcular posição Y correta para ficar no chão
        Cuca *cuca = new Cuca(x, groundY, CUCAACEL, CUCAHEALTH, CUCASTRENGTH);
        if(cuca){
            cuca->setPosition(Vector2f(cuca->getPosition().x, cuca->getPosition().y - cuca->getSize().y));
            cuca->addPlayer(player1);
            if(player2)
                cuca->addPlayer(player2);
                
            entities_list.add(cuca);
            pCM->addEnemy(cuca);
        }
    }
}