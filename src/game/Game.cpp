#include "../../include/game/Game.h"
#include "../../include/graphicalelements/Button.h"
#include "../../include/managers/CollisionManager.h"
#include "../../include/menu/Leaderboard.h"
#include "../../include/menu/MainMenu.h"
#include "../../include/menu/NewGameMenu.h"
#include <algorithm>

Game::Game()
    : pGM(nullptr), pCM(nullptr), number_of_players(1), player1(nullptr),
      player2(nullptr), mainMenu(nullptr), newGameMenu(nullptr), leaderboard(nullptr), mouseSubject(),
      phase_size(1600.f, 600.f), firstPhase(nullptr), secondPhase(nullptr),
      currentPhase(nullptr) {

  pCM = CollisionManager::getInstance();
  pGM = GraphicsManager::getInstance();
  Ente::setGraphicsManager(pGM);

  RenderWindow window(VideoMode(1920, 1080), "Good Game", Style::Fullscreen);
  window.setFramerateLimit(60);
  pGM->setWindow(&window);
  pGM->setCameraCenter(
      Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
  create_menus();
  game_state = GameState::MAIN_MENU;
  currentMenu = mainMenu;
  srand(time(nullptr));
  execute();
}

Game::~Game() {
  delete player1;
  player1 = nullptr;
  if (player2) {
    delete player2;
    player2 = nullptr;
  }

  if (firstPhase) {
    delete firstPhase;
    firstPhase = nullptr;
  }
  if (secondPhase) {
    delete secondPhase;
    secondPhase = nullptr;
  }
  currentPhase = nullptr;
  if (mainMenu) {
    delete mainMenu;
    mainMenu = nullptr;
  }
  if (newGameMenu) {
    delete newGameMenu;
    newGameMenu = nullptr;
  }
  if (leaderboard) {
    delete leaderboard;
    leaderboard = nullptr;
  }
  currentMenu = nullptr;
}

void Game::execute() {

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
      }
      if (event.type == Event::MouseMoved) {
        mouseSubject.notifyObservers(event.mouseMove);
      }
      if (event.type == Event::MouseButtonPressed) {
        mouseSubject.notifyObservers(event.mouseButton);
      }
    }

    pGM->clean();
    switch (game_state) {
    case GameState::MAIN_MENU:
      currentMenu = mainMenu;
      currentMenu->execute();
      break;
    case GameState::NEW_GAME_MENU:
      currentMenu = newGameMenu;
      currentMenu->execute();
      break;
    case GameState::PLAYING:
      running();
      break;
    case GameState::LEADERBOARD:
      currentMenu = leaderboard;
      currentMenu->execute();
      break;
    case GameState::PAUSED:
    case GameState::GAME_OVER:
      break;
    }

    pGM->show();
  }
}

void Game::running() {
  if (currentPhase) {
    currentPhase->execute();

    if (currentPhase->passed()) {
      if (dynamic_cast<FirstPhase *>(currentPhase)) {
        createSecondPhase();
      } else if (dynamic_cast<SecondPhase *>(currentPhase)) {
        setGameState(GameState::MAIN_MENU);
      }
    }
  }
  updateCamera();
  player1->execute();
  if (player2) {
    player2->execute();
  }
}

void Game::main_menu() {
  mainMenu->execute();
  map<string, Button *>::iterator it;
  for (it = mainMenu->getButtons().begin(); it != mainMenu->getButtons().end(); ++it) {
    if (it->second->wasClicked()) {
      game_state = GameState::PLAYING;
      createFirstPhase();
      break;
    }
  }
}

MouseSubject &Game::getMouseSubject() { return mouseSubject; }

void Game::setGameState(GameState state) { game_state = state; }

void Game::setNumberPlayers(int n) { number_of_players = n; }

void Game::create_menus() {
    mainMenu = new MainMenu(this);
    newGameMenu = new NewGameMenu(this);
    leaderboard = new Leaderboard(this);
}

void Game::updateCamera() {
  if (!currentPhase) {
    cerr << "Current phase is not set. Cannot update camera." << endl;
    return;
  }

  Vector2f phaseSize = currentPhase->getPhaseSize();
  float avgX = player1->getPosition().x;

  if (player2) {
    avgX = (player1->getPosition().x + player2->getPosition().x) / 2.0f;
  }

  float fixedY = 300.f;

  float cameraHalfWidth = pGM->getWindow()->getSize().x / 2.0f;
  avgX = max(cameraHalfWidth, min(avgX, phaseSize.x - cameraHalfWidth));
  cameraCenter = sf::Vector2f(avgX, fixedY);
  pGM->setCameraCenter(cameraCenter);
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

  player1->setPosition(Vector2f(200.f, 100.f));
  player1->setVelocity(Vector2f(0.f, 0.f));
  pCM->addPlayer(player1);
  if (player2) {
    player2->setPosition(Vector2f(100.f, 100.f));
    player2->setVelocity(Vector2f(0.f, 0.f));
    pCM->addPlayer(player2);
  }
}

void Game::createSecondPhase() {
  if (currentPhase) {
    delete currentPhase;
  }
  currentPhase =
      new SecondPhase(Vector2f(12000.f, 850), 11900.0, player1, player2);

  player1->setPosition(Vector2f(200.f, 100.f));
  player1->setVelocity(Vector2f(0.f, 0.f));
  pCM->addPlayer(player1);
  if (player2) {
    player2->setPosition(Vector2f(100.f, 100.f));
    player2->setVelocity(Vector2f(0.f, 0.f));
    pCM->addPlayer(player2);
  }
}

void Game::createPlayers() {
  if (!player1 && !player2) {
    player1 = new Player(200, 100, PLAYERACEL, PLAYERHEALTH, PLAYERSTRENGTH, 1);
    if (number_of_players == 2) {
      player2 =
          new Player(100, 100, PLAYERACEL, PLAYERHEALTH, PLAYERSTRENGTH, 2);
    }
  }
}
