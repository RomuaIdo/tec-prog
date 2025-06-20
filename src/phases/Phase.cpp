#include "../../include/phases/Phase.h"
#include "../../include/entities/characters/enemies/Saci.h"
#include "../../include/entities/obstacles/Plataform.h"
#include "../../include/graphicalelements/BackgroundElement.h"

Phase::Phase(Vector2f size, float limiarX, Player *p1, Player *p2)
    : pCM(CollisionManager::getInstance()), phaseSize(size), player1(p1),
      player2(p2), passingX(limiarX), passedPhase(false) {
  entities_list.clear();
  tiles.clear();
  BackgroundLayers.clear();
}

Phase::~Phase() {
  entities_list.clear();
  vector<BackgroundElement *>::iterator it;
  for (it = tiles.begin(); it != tiles.end(); it++) {
    delete *it; // Free memory allocated for each BackgroundElement
  }
  tiles.clear();
  for (it = BackgroundLayers.begin(); it != BackgroundLayers.end(); it++) {
    delete *it; // Free memory allocated for each BackgroundLayer
  }
  BackgroundLayers.clear();
  pCM->clearEntities();
}

Vector2f Phase::getPhaseSize() const { 
    return phaseSize; 
}

void Phase::createScenery() {
  const string texturePath = "assets/textures/Grass.png";
  const float tileWidth = 50.0f;
  const float tileHeight = 50.0f;

  const int numBackgroundElementsX =
      static_cast<int>(phaseSize.x / tileWidth) + 1;
  const int numBackgroundElementsY = 1;

  for (int y = 0; y < numBackgroundElementsY; y++) {
    for (int x = 0; x < numBackgroundElementsX; x++) {
      float posX = x * tileWidth + tileWidth / 2;
      float posY = phaseSize.y - (tileHeight / 2) - (y * tileHeight);
      tiles.push_back(new BackgroundElement(posX, posY, 0.0f, texturePath));
    }
  }

  Vector2f newphaseSize = getPhaseSize();
  newphaseSize.y = newphaseSize.y - (numBackgroundElementsY * tileHeight);

  BackgroundLayers.push_back(new BackgroundElement(
      newphaseSize.x/2.f, newphaseSize.y/2.f, 1.0f, "assets/textures/1_TreesBackground.png"));
  BackgroundLayers.push_back(new BackgroundElement(
      newphaseSize.x/2.f, newphaseSize.y/2.f, 0.98f, "assets/textures/2_Trees.png"));
   BackgroundLayers.push_back(new BackgroundElement(
      newphaseSize.x/2.f, newphaseSize.y/2.f, 0.9f, "assets/textures/3_Trees.png"));
   BackgroundLayers.push_back(new BackgroundElement(
      newphaseSize.x/2.f, newphaseSize.y/2.f, 0.85f, "assets/textures/4_Trees.png"));
 

  pCM->setPhaseSize(newphaseSize);
}

void Phase::createPlatforms() {
  const float minY = 100.0f; // Minimum Y position
  const float maxY =
      phaseSize.y - 150.0f; // Maximum Y position (50px above ground)

  for (int i = 0; i < maxPlatforms; i++) {
    int numPlataform = rand() % 2;
    // Generate random position
    float x =
        static_cast<float>(50 + rand() % static_cast<int>(phaseSize.x - 500));
    float y = minY + static_cast<float>(rand() % static_cast<int>(maxY - minY));
    
    Plataform *p = new Plataform(x, y, false);
    Plataform *p2 = new Plataform(x + 50.f, y, false);


    entities_list.add(p);
    entities_list.add(p2);
    pCM->addObstacle(p);
    pCM->addObstacle(p2);
  }
}

void Phase::createSaci() {
  const float tileHeight = 50.0f;
  const float groundY =
      phaseSize.y - (tileHeight / 2); // Centro do tile do chão
  const float saciHeight = 64.0f;     // Altura do sprite do Saci
  const float saciY = groundY - (tileHeight / 2) -
                      (saciHeight / 2); // Ajuste para ficar no chão

  for (int i = 0; i < maxSaci; i++) {
    // Gera posição X aleatória (evitando bordas)
    float x = 100.f + static_cast<float>(rand() %
                                         static_cast<int>(phaseSize.x - 200.f));

    Saci *saci = new Saci(x, saciY, SACIACEL, SACIHEALTH, SACISTRENGTH);
    saci->addPlayer(player1);
    if(player2)
        saci->addPlayer(player2);
    
    entities_list.add(saci);
    pCM->addEnemy(saci);
  }
}

bool Phase::passed() const { return passedPhase; }

void Phase::checkPhaseCompletion() {
    if (player1) {
        if(player2){
            if (player1->getPosition().x > passingX &&
            player2->getPosition().x > passingX) {
                passedPhase = true;
            }
        }else{
            if (player1->getPosition().x > passingX) {
                passedPhase = true;
            }
        }
    }
}
