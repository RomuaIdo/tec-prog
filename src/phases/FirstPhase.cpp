#include "../../include/phases/FirstPhase.h"
#include "../../include/entities/characters/Enemy.h"
#include "../../include/entities/obstacles/Honey.h"
#include "../../include/graphicalelements/Tile.h"

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

void FirstPhase::createEnemies() { createMediumEnemies(); }

void FirstPhase::createObstacles() { createMediumObstacles(); }

void FirstPhase::createMediumEnemies() {
  for (int i = 0; i < maxMediumEnemies; i++) {
    Enemy *e = new Enemy(i * 200.f, 100.f, 15.f, 5, 1.f, 2);
    e->addPlayer(player1);
    e->addPlayer(player2);
    entities_list.add(e);
    pCM->addEnemy(e);
  }
}

void FirstPhase::createMediumObstacles() {
  const float tileWidth = 50.0f;
  const float groundY = phaseSize.y - 250.0f;
  vector<float> availablePositions;

  // Gerar posições no centro dos tiles (25, 75, 125...)
  for (float x = tileWidth / 2; x <= phaseSize.x - tileWidth / 2;
       x += tileWidth) {
    availablePositions.push_back(x);
  }

  // Embaralhar posições
  for (int i = availablePositions.size() - 1; i > 0; --i) {
    int j = rand() % (i + 1);
    float temp = availablePositions[i];
    availablePositions[i] = availablePositions[j];
    availablePositions[j] = temp;
  }

  // Criar honeys
  int honeyCount = 0;
  vector<float> usedPositions;

  for (int i = 0;
       i < maxHoneys && i < static_cast<int>(availablePositions.size()); i++) {
    float x = availablePositions[i];
    bool positionValid = true;

    // Verificar proximidade com outros honeys
    for (size_t k = 0; k < usedPositions.size(); ++k) {
      if (std::abs(x - usedPositions[k]) < tileWidth * 2) {
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

      // Calcular índice do tile (fórmula: (x - 25) / 50)
      int tileIndex = static_cast<int>((x - tileWidth / 2) / tileWidth);

      // Verificar se o índice é válido
      if (tileIndex >= 0 && tileIndex < static_cast<int>(tiles.size())) {
        // Remover e deletar o tile
        delete tiles[tileIndex];
        tiles[tileIndex] = NULL;
      }
    }
  }

  // Remover tiles nulos do vetor
  for (int i = tiles.size() - 1; i >= 0; --i) {
    if (tiles[i] == NULL) {
      tiles.erase(tiles.begin() + i);
    }
  }
}
