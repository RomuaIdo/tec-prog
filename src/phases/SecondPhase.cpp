#include "../../include/phases/SecondPhase.h"
#include "../../include/entities/characters/enemies/Cuca.h"
#include "../../include/entities/obstacles/ThornyBush.h"
#include "../../include/graphicalelements/BackgroundElement.h"

SecondPhase::SecondPhase(Vector2f size, float limiarX, Player *p1, Player *p2)
    : Phase(size, limiarX, p1, p2) {
  createScenery();
  createEnemies();
  createObstacles();
  createPlatforms();
}

SecondPhase::~SecondPhase() { pCM->clearEntities(); }

void SecondPhase::execute() {
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

void SecondPhase::createEnemies() {
    createCucas();
    createSaci();
}

void SecondPhase::createObstacles() { createSpikes(); }

void SecondPhase::createSpikes() {
    const float groundY = phaseSize.y - 50.0f; // Altura do chão
    std::vector<float> availablePositions;

    // Gerar posições X disponíveis (evitando bordas)
    for (float x = 100.f; x < phaseSize.x - 100.f; x += 50.f) {
        availablePositions.push_back(x);
    }

    // Embaralhar posições (Fisher-Yates shuffle)
    for (int i = availablePositions.size() - 1; i > 0; --i) {
        int j = std::rand() % (i + 1);
        float temp = availablePositions[i];
        availablePositions[i] = availablePositions[j];
        availablePositions[j] = temp;
    }

    // Criar spikes sem sobreposição
    vector<float> usedPositions;
    int createdSpikes = 0;

    for (size_t i = 0; i < availablePositions.size() && createdSpikes < maxSpikes; i++) {
        float x = availablePositions[i];
        bool positionValid = true;

        // Verificar distância mínima (100 pixels)
        for (vector<float>::iterator it = usedPositions.begin();
                it != usedPositions.end(); ++it) {
            if (fabs(x - *it) < 100.f) {
                positionValid = false;
                break;
            }
        }

        if (positionValid) {
            ThornyBush *tb = new ThornyBush(x, groundY, true);
            entities_list.add(tb);
            pCM->addObstacle(tb);
            usedPositions.push_back(x);
            createdSpikes++;
        }
    }
}

void SecondPhase::createCucas() {
    const float groundY = phaseSize.y ; 

    for (int i = 0; i < maxCucas; i++) {
        float x = 100.f + static_cast<float>(rand() %
                                            static_cast<int>(phaseSize.x - 200.f));

        // Calcular posição Y correta para ficar no chão
        Cuca *cuca = new Cuca(x, groundY, CUCAACEL, CUCAHEALTH, CUCASTRENGTH);
        if(cuca){
            cuca->setPosition(Vector2f(cuca->getPosition().x, cuca->getPosition().y - cuca->getSize().y));
            cuca->addPlayer(player1);
            cuca->addPlayer(player2);
            entities_list.add(cuca);
            pCM->addEnemy(cuca);
        }
    }
}
