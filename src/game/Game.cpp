#include "../../include/game/Game.h"
#include "../../include/graphicalelements/eventshandler/KeyboardEventHandler.h"
#include "../../include/graphicalelements/eventshandler/MouseEventHandler.h"
#include "../../include/graphicalelements/eventshandler/TextInputEventHandler.h"
#include "../../include/managers/CollisionManager.h"
#include "../../include/menu/GameOverMenu.h"
#include "../../include/menu/Leaderboard.h"
#include "../../include/menu/MainMenu.h"
#include "../../include/menu/NewGameMenu.h"
#include "../../include/menu/PauseMenu.h"
#include <algorithm>

Game::Game()
    : pGM(nullptr), player1(nullptr), player2(nullptr), mouseSubject(),
      textInputSubject(), currentPhase(nullptr) {

  pGM = GraphicsManager::getInstance();
  Ente::setGraphicsManager(pGM);

  RenderWindow window(VideoMode(1920, 1080), "Brasilore v1.0",
                      Style::Fullscreen);
  window.setFramerateLimit(60);
  pGM->setWindow(&window);
  pGM->setCameraCenter(
      Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
  create_menus();
  game_state = GameState::MAIN_MENU;
  currentMenu = menus[GameState::MAIN_MENU];
  currentMenu->activate();
  srand(time(nullptr));
  seed = rand();
  srand(seed);
  execute();
}

Game::~Game() {
  delete player1;
  player1 = nullptr;
  if (player2) {
    delete player2;
    player2 = nullptr;
  }
  if (currentPhase) {
    delete currentPhase;
  }
  currentPhase = nullptr;
  for (map<GameState, Menu *>::iterator it = menus.begin(); it != menus.end();
       ++it) {
    delete it->second;
  }
  menus.clear();
}

void Game::execute() {

  MouseEventHandler mouseHandler(mouseSubject);
  TextInputEventHandler textInputHandler(textInputSubject);
  mouseHandler.setNextHandler(&textInputHandler);
  KeyboardEventHandler keyboardHandler(this);
  keyboardHandler.setNextHandler(&mouseHandler);
  EventHandler *eventChain = &keyboardHandler;
  RenderWindow *pWindow = pGM->getWindow();
  while (pGM->openWindow()) {
    Event event;
    pGM->setClock();
    pGM->operator++();

    while (pWindow->pollEvent(event)) {
      if (event.type == Event::Closed ||
          (event.type == Event::KeyPressed &&
           event.key.code == sf::Keyboard::Escape)) {
        pWindow->close();
      } else {
        eventChain->handleEvent(event); // Usa a nova cadeia
      }
    }
    Menu *previousMenu = currentMenu;

    pGM->clean();

    if (game_state == GameState::PLAYING) {
      running();
    } else {
      currentMenu = menus[game_state];
      currentMenu->execute();
    }

    if (previousMenu != currentMenu) {
      if (previousMenu)
        previousMenu->deactivate();
      if (currentMenu)
        currentMenu->activate();
    }
    pGM->show();
  }
}

void Game::running() {
  updateCamera();
  if (currentPhase) {
    currentPhase->execute();
    bool player1Dead = (player1 == nullptr || !player1->getAlive());
    bool player2Dead = (player2 == nullptr || (!player2->getAlive()));
    if (player1Dead && player2Dead) {
      cleanupAfterGame();
      resetCamera();
      setGameState(GameState::GAME_OVER);
      return;
    }
    if (currentPhase->passed()) {
      if (dynamic_cast<FirstPhase *>(currentPhase)) {
        createSecondPhase();
      } else if (dynamic_cast<SecondPhase *>(currentPhase)) {
        saveScoretoLeaderboard();
        cleanupAfterGame();
        resetCamera();
        setGameState(GameState::LEADERBOARD);
      }
    }
  }
}

MouseSubject &Game::getMouseSubject() { return mouseSubject; }

void Game::setGameState(GameState state) { game_state = state; }

void Game::create_menus() {
  menus[GameState::MAIN_MENU] = new MainMenu(this);
  menus[GameState::NEW_GAME_MENU] = new NewGameMenu(this);
  menus[GameState::PAUSED] = new PauseMenu(this);
  menus[GameState::LEADERBOARD] = new Leaderboard(this);
  menus[GameState::GAME_OVER] = new GameOverMenu(this);
}

void Game::updateCamera() {
  if (!currentPhase || !player1)
    return;

  float avgX = 0.f;
  int count = 0;

  if (player1->getAlive()) {
    avgX += player1->getPosition().x;
    count++;
  }
  if (player2 && player2->getAlive()) {
    avgX += player2->getPosition().x;
    count++;
  }

  if (count == 0)
    return; // No players alive, do not update camera

  avgX /= count;
  const Vector2f &phaseSize = currentPhase->getPhaseSize();
  const float cameraHalfWidth = pGM->getWindow()->getSize().x / 2.0f;
  avgX = max(cameraHalfWidth, std::min(avgX, phaseSize.x - cameraHalfWidth));

  pGM->setCameraCenter(Vector2f(avgX, 540.f));
}

void Game::createPhase(short int phaseNumber) {
  if (phaseNumber == 1) {
    createFirstPhase();
  } else if (phaseNumber == 2) {
    createSecondPhase();
  } else {
    cerr << "Invalid phase number: " << phaseNumber << endl;
  }
}

void Game::createFirstPhase() {
  if (currentPhase) {
    delete currentPhase;
  }
  currentPhase =
      new FirstPhase(Vector2f(12000.f, 850.f), 11900.0, player1, player2);

  player1->setPosition(Vector2f(200.f, 800.f));
  player1->setVelocity(Vector2f(0.f, 0.f));
  if (player2) {
    player2->setPosition(Vector2f(100.f, 800.f));
    player2->setVelocity(Vector2f(0.f, 0.f));
  }
}

void Game::createSecondPhase() {
  if (currentPhase) {
    delete currentPhase;
  }
  currentPhase =
      new SecondPhase(Vector2f(12000.f, 850.f), 11900.0, player1, player2);

  player1->setPosition(Vector2f(200.f, 800.f));
  player1->setVelocity(Vector2f(0.f, 0.f));
  if (player2) {
    player2->setPosition(Vector2f(100.f, 800.f));
    player2->setVelocity(Vector2f(0.f, 0.f));
  }
}

void Game::createPlayers(const vector<string> &playerNames) {
  if (!player1 && !player2) {
    player1 = new Player(200, 100, PLAYERACEL, playerNames[0], PLAYERHEALTH,
                         PLAYERSTRENGTH, 1);

    if (playerNames.size() > 1) {
      player2 = new Player(100, 100, PLAYERACEL, playerNames[1], PLAYERHEALTH,
                           PLAYERSTRENGTH, 2);
    }
  }
}

void Game::setPlayerNames(const vector<string> &names) { player_names = names; }

TextInputSubject &Game::getTextInputSubject() { return textInputSubject; }

void Game::saveScoretoLeaderboard() {
  if (!player1)
    return;

  int totalScore = player1->getScore();
  string player1Name = player_names.size() > 0 ? player_names[0] : "___";
  string player2Name = "___";

  if (player2) {
    totalScore += player2->getScore();
    if (player_names.size() > 1) {
      player2Name = player_names[1];
    }
  }

  string filename = (player2 == nullptr || player2Name.empty())
                        ? "leaderboards/leaderboard_single.txt"
                        : "leaderboards/leaderboard_multi.txt";

  vector<Leaderboard::ScoreEntry> entries;
  ifstream inFile(filename.c_str());
  string line;
  while (getline(inFile, line)) {
    if (line.empty())
      continue;

    if (player2 == nullptr || player2Name.empty()) {
      istringstream iss(line);
      string name;
      int score;
      if (iss >> name >> score) {
        entries.push_back(Leaderboard::ScoreEntry(0, name, "", score, true));
      }
    } else {
      istringstream iss(line);
      string name1, name2;
      int score;
      if (iss >> name1 >> name2 >> score) {
        entries.push_back(
            Leaderboard::ScoreEntry(0, name1, name2, score, false));
      }
    }
  }
  inFile.close();

  // Adiciona novo score
  if (player2 == nullptr || player2Name.empty()) {
    entries.push_back(
        Leaderboard::ScoreEntry(0, player1Name, "", totalScore, true));
  } else {
    entries.push_back(Leaderboard::ScoreEntry(0, player1Name, player2Name,
                                              totalScore, false));
  }

  // Ordena decrescente
  sort(entries.begin(), entries.end(),
       [](const Leaderboard::ScoreEntry &a, const Leaderboard::ScoreEntry &b) {
         return a.score > b.score;
       });

  // Mantém apenas top 10
  if (entries.size() > 10) {
    // Cria um novo vetor com os primeiros 10 elementos
    vector<Leaderboard::ScoreEntry> topEntries;
    for (size_t i = 0; i < 10; ++i) {
      topEntries.push_back(entries[i]);
    }
    entries = topEntries;
  }

  // Reescreve arquivo
  ofstream outFile(filename.c_str());
  for (size_t i = 0; i < entries.size(); ++i) {
    if (entries[i].isSinglePlayer) {
      outFile << entries[i].player1 << " " << entries[i].score << "\n";
    } else {
      outFile << entries[i].player1 << " " << entries[i].player2 << " "
              << entries[i].score << "\n";
    }
  }
  outFile.close();

  // Forçar recarregamento no próximo acesso
  Leaderboard *lb = dynamic_cast<Leaderboard *>(menus[GameState::LEADERBOARD]);
  lb->reloadScores();
}

void Game::cleanupAfterGame() {
  delete player1;
  player1 = nullptr;

  if (player2) {
    delete player2;
    player2 = nullptr;
  }

  if (currentPhase) {
    delete currentPhase;
    currentPhase = nullptr;
  }

  player_names.clear();
}

void Game::resetCamera() {
  RenderWindow *window = pGM->getWindow();
  if (window) {
    Vector2u windowSize = window->getSize();
    pGM->setCameraCenter(Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f));
  }
}

/*=====================================================*/
/*                     SAVE GAME                       */
/*=====================================================*/

json Game::toJson() const {
  json j;

  j["game_state"] = static_cast<int>(game_state);

  if (player1)
    j["player1"] = player1->toJson();
  if (player2)
    j["player2"] = player2->toJson();
  if (currentPhase)
    j["phase"] = currentPhase->toJson();

  return j;
}

void Game::fromJson(const json &j) {
  game_state = static_cast<GameState>(j["game_state"]);
  if (currentPhase)
    currentPhase->fromJson(j["phase"]);
  if (player1)
    player1->fromJson(j["player1"]);
  if (player2)
    player2->fromJson(j["player2"]);
}

void Game::saveGame(const std::string &filename) const {
  std::ofstream file(filename);
  if (file.is_open()) {
    json gameState = {
        {"players",
         {player1 ? player1->toJson() : json(nullptr),
          player2 ? player2->toJson() : json(nullptr)}},
        {"player_names", player_names},
        {"state", static_cast<int>(game_state)},
        {"phase", currentPhase ? currentPhase->toJson() : json(nullptr)},
        {"seed", seed}
    };
    file << gameState.dump(4);
    file.close();
  }
}

void Game::loadGame(const std::string &filename) {
  std::ifstream file(filename);
  if (file.is_open()) {
    json j;
    file >> j;

    cleanupAfterGame();

    if (j.find("seed") != j.end() && !j["seed"].is_null()) {
      seed = j["seed"].get<unsigned int>();
      srand(seed);    
    }

    if (j.find("state") != j.end() && !j["state"].is_null()) {
      game_state = static_cast<GameState>(j["state"].get<int>());
    }

    if (j.find("players") != j.end() && j["players"].is_array()) {
      const json &players = j["players"];
      if (players.size() > 0 && !players[0].is_null()) {
        player1 = new Player();
        player1->fromJson(players[0]);
      }
      if (players.size() > 1 && !players[1].is_null()) {
        player2 = new Player();
        player2->fromJson(players[1]);
      }
    }

    if (j.find("player_names") != j.end() && j["player_names"].is_array()) {
      player_names.clear();
      const json &namesArray = j["player_names"];
      for (json::const_iterator it = namesArray.begin(); 
           it != namesArray.end(); 
           ++it) {
        player_names.push_back(it->get<std::string>());
      }
    }

    if (j.find("phase") != j.end() && !j["phase"].is_null()) {
      if (j["phase"].find("type") != j["phase"].end() && j["phase"]["type"].is_string()) {
        std::string phaseType = j["phase"]["type"];
        if (phaseType == "FirstPhase") {
          currentPhase = new FirstPhase();
        } else if (phaseType == "SecondPhase") {
          currentPhase = new SecondPhase();
        }
        if (currentPhase) {
          currentPhase->setPlayers(player1, player2);
          currentPhase->fromJson(j["phase"]);
        }
      }
    }

    file.close();
    updateCamera();
    game_state = GameState::PLAYING;
  }
}

GameState Game::getGameState() const { return game_state; }
