#include "../../include/phases/Phase.h"



Phase::Phase(Vector2f size, float limiarX, Player *p1, Player *p2)
    : pCM(CollisionManager::getInstance()), phaseSize(size), player1(p1),
      player2(p2), passingX(limiarX), passedPhase(false) {
  entities_list.clear();
  tiles.clear();
  BackgroundLayers.clear();
  pCM->addPlayer(player1);
  if (player2) {
    pCM->addPlayer(player2);
  }
}

Phase::~Phase() {
  entities_list.clear();
  vector<ge::BackgroundElement *>::iterator it;
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

Vector2f Phase::getPhaseSize() const { return phaseSize; }

void Phase::createScenery() {
  const string texturePath = "assets/textures/Grass.png";
  const float tileWidth = 50.0f;
  const float tileHeight = 50.0f;

  const int numTilesX =
      static_cast<int>(phaseSize.x / tileWidth) + 1;
  const int numTilesY = 1;

  for (int y = 0; y < numTilesY; y++) {
    for (int x = 0; x < numTilesX; x++) {
      float posX = x * tileWidth + tileWidth / 2;
      float posY = phaseSize.y - (tileHeight / 2) - (y * tileHeight);
      tiles.push_back(new ge::BackgroundElement(posX, posY, 0.0f, texturePath));
    }
  }

  Vector2f newphaseSize = getPhaseSize();
  newphaseSize.y = newphaseSize.y - (numTilesY * tileHeight);

  BackgroundLayers.push_back(
      new ge::BackgroundElement(newphaseSize.x / 2.f, newphaseSize.y / 2.f, 1.0f,
                            "assets/textures/1_TreesBackground.png"));
  BackgroundLayers.push_back(
      new ge::BackgroundElement(newphaseSize.x / 2.f, newphaseSize.y / 2.f, 0.98f,
                            "assets/textures/2_Trees.png"));
  BackgroundLayers.push_back(
      new ge::BackgroundElement(newphaseSize.x / 2.f, newphaseSize.y / 2.f, 0.9f,
                            "assets/textures/3_Trees.png"));
  BackgroundLayers.push_back(
      new ge::BackgroundElement(newphaseSize.x / 2.f, newphaseSize.y / 2.f, 0.85f,
                            "assets/textures/4_Trees.png"));

  pCM->setPhaseSize(newphaseSize);
}

void Phase::createPlatforms() {
  const float minY = 100.0f; // Minimum Y position
  const float maxY =
      phaseSize.y - 150.0f; // Maximum Y position (50px above ground)
  int numPlatforms =
      minPlatforms + rand() % (maxPlatforms - minPlatforms + 1);
  for (int i = 0; i < numPlatforms; i++) {
    int numPlataform = rand() % 2;
    // Generate random position
    float x =
        static_cast<float>(50 + rand() % static_cast<int>(phaseSize.x - 500));
    float y = minY + static_cast<float>(rand() % static_cast<int>(maxY - minY));

    Plataform *p = new Plataform(x, y, false, numPlataform);
    Plataform *p2 =
        new Plataform(x + p->getSize().x * 1.7f, y, false, numPlataform);

    p->configSprite();
    p2->configSprite();
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

  int numSaci = minSaci + rand() % (maxSaci - minSaci + 1);
  for (int i = 0; i < numSaci; i++) {
    // Gera posição X aleatória (evitando bordas)
    float x = 100.f + static_cast<float>(rand() %
                                         static_cast<int>(phaseSize.x - 200.f));

    Saci *saci = new Saci(x, saciY, SACIACEL, SACIHEALTH, SACISTRENGTH);
    saci->addPlayer(player1);
    if (player2)
      saci->addPlayer(player2);

    entities_list.add(saci);
    pCM->addEnemy(saci);
  }
}

bool Phase::passed() const { return passedPhase; }

void Phase::checkPhaseCompletion() {
    bool player1Alive = player1 && player1->getAlive();
    bool player2Alive = player2 && player2->getAlive();

    if (player1Alive && player2Alive) {
        // Ambos vivos: precisam passar juntos
        if (player1->getPosition().x > passingX && 
            player2->getPosition().x > passingX) {
            passedPhase = true;
        }
    } else if (player1Alive) {
        // Apenas player1 vivo
        if (player1->getPosition().x > passingX) {
            passedPhase = true;
        }
    } else if (player2Alive) {
        // Apenas player2 vivo
        if (player2->getPosition().x > passingX) {
            passedPhase = true;
        }
    }
}

/* ------------------------------------------- */
/*                 SAVE BUFFER                 */
/* ------------------------------------------- */

json Phase::toJson() {
  json j;
  j["phaseType"] = getType();
  j["type"] = getType();
  j["phaseSize_x"] = phaseSize.x;
  j["phaseSize_y"] = phaseSize.y;
  j["passingX"] = passingX;
  j["passedPhase"] = passedPhase;

  
  j["entities"] = entities_list.toJson();

  return j;
}

void Phase::fromJson(const json &j) { 

  // Carrega dados básicos da fase
  if (j.contains("phaseSize_x") && !j["phaseSize_x"].is_null()) {
    phaseSize.x = j["phaseSize_x"];
  }
  if (j.contains("phaseSize_y") && !j["phaseSize_y"].is_null()) {
    phaseSize.y = j["phaseSize_y"];
  }
  if (j.contains("passingX") && !j["passingX"].is_null()) {
    passingX = j["passingX"];
  }
  if (j.contains("passedPhase") && !j["passedPhase"].is_null()) {
    passedPhase = j["passedPhase"];
  }

  createScenery();
  // Limpa entidades existentes
  entities_list.clear();

  // Carrega entidades
  if (j.contains("entities") && j["entities"].is_array()) {
    for (const auto &entityJson : j["entities"]) {
      // Verifica se o tipo existe
      if (!entityJson.contains("type") || !entityJson["type"].is_string()) {
        cerr << "Entity JSON missing type field" << endl;
        continue;
      }

      string type = entityJson["type"];
      Entity *e = nullptr;

      // Cria a entidade com base no tipo
      if (type == "Cuca") {
        e = new Cuca();
      } else if (type == "Honey") {
        e = new Honey();
      } else if (type == "Plataform") {
        e = new Plataform();
      } else if (type == "Player") {
        e = new Player();
      } else if (type == "MulaSemCabeca") {
        e = new MulaSemCabeca();
      } else if (type == "ThornyBush") {
        e = new ThornyBush();
      } else if (type == "Saci") {
        e = new Saci();
     }else if(type == "Mula"){
        e = new MulaSemCabeca();
      }
      // Adicione outros tipos conforme necessário

      if (e) {
        try {
          e->fromJson(entityJson);
          entities_list.add(e);

          // Adiciona aos managers específicos se necessário
          if (dynamic_cast<Enemy *>(e)) {
            pCM->addEnemy(static_cast<Enemy *>(e));
          } else if (dynamic_cast<Obstacle *>(e)) {
            pCM->addObstacle(static_cast<Obstacle *>(e));
          } else if (dynamic_cast<Player *>(e)) {
            pCM->addPlayer(static_cast<Player *>(e));
          } else if (dynamic_cast<Projectile *>(e)) {
            pCM->addProjectile(static_cast<Projectile *>(e));
          }
        } catch (const exception &ex) {
          cerr << "Error loading entity: " << ex.what() << endl;
          delete e;
        }
      } else {
        cerr << "Unknown entity type: " << type << endl;
      }
    }
  }
  entities_list.addPlayerToEnemiesList(player1, player2);
}


void Phase::setPlayers(Player *p1, Player *p2) {
  player1 = p1;
  player2 = p2;
  pCM->addPlayer(player1);
  if (player2) {
    pCM->addPlayer(player2);
  }
}

