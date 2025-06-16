#include "../../include/phases/Phase.h"
#include "../../include/graphicalelements/Tile.h"
#include "../../include/entities/obstacles/Plataform.h"

Phase::Phase(Vector2f size, Player *p1, Player *p2,
             const string &backgroundPath)
    : pCM(CollisionManager::getInstance()), phaseSize(size), player1(p1),
      player2(p2) {
  entities_list.clear();
  tiles.clear();
  maxPlatforms = 10;
}

Phase::~Phase() {
  entities_list.clear();
  vector<Tile *>::iterator it;
  for (it = tiles.begin(); it != tiles.end(); it++) {
    delete *it; // Free memory allocated for each Tile
  }
  tiles.clear();
}

Vector2f Phase::getPhaseSize() const { return phaseSize; }

void Phase::createScenery() {
  const string texturePath = "assets/textures/Grass.png";
  const float tileWidth = 50.0f;
  const float tileHeight = 50.0f;

  const int numTilesX = static_cast<int>(phaseSize.x / tileWidth) + 1;
  const int numTilesY = 1;

  for (int y = 0; y < numTilesY; y++) {
    for (int x = 0; x < numTilesX; x++) {
      float posX = x * tileWidth + tileWidth / 2;
      float posY = phaseSize.y - (tileHeight / 2) - (y * tileHeight);

      tiles.push_back(new Tile(posX, posY, texturePath));
    }
  }
  Vector2f newphaseSize = getPhaseSize();
  newphaseSize.y = newphaseSize.y - (numTilesY * tileHeight);
  pCM->setPhaseSize(newphaseSize);
}

void Phase::createPlatforms() {
  const float minY = 100.0f; // Minimum Y position
  const float maxY =
      phaseSize.y - 150.0f; // Maximum Y position (50px above ground)

  for (int i = 0; i < maxPlatforms; i++) {
    // Generate random position
    float x =
        static_cast<float>(50 + rand() % static_cast<int>(phaseSize.x - 100));
    float y = minY + static_cast<float>(rand() % static_cast<int>(maxY - minY));

    Plataform *p = new Plataform(x, y, false);
    entities_list.add(p);
    pCM->addObstacle(p);
  }
}
