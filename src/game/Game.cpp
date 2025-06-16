#include "../../include/game/Game.h"
#include "../../include/graphicalelements/Button.h"
#include "../../include/managers/CollisionManager.h"
#include "../../include/menu/MainMenu.h"
#include <algorithm>

Game::Game()
    : pGM(nullptr), pCM(nullptr), player1(nullptr),
      player2(nullptr), mouseSubject(), phase_size(1600.f, 600.f),
      firstPhase(nullptr), secondPhase(nullptr), currentPhase(nullptr) {
  pCM = CollisionManager::getInstance();
  pGM = GraphicsManager::getInstance();
  Ente::setGraphicsManager(pGM);
  player1 = new Player(200, 100, 50.f, 10, 1, 4, 1, 60.f);
  player2 = new Player(100, 100, 50.f, 10, 1, 4, 2, 60.f);
  create_menu();

  game_state = GameState::MAIN_MENU;
  srand(time(nullptr));
  execute();
}

Game::~Game() {
  delete player1;
  player1 = nullptr;
  delete player2;
  player2 = nullptr;
  delete menu;
  menu = nullptr;

  if(firstPhase) {
    delete firstPhase;
    firstPhase = nullptr;
  }
  if(secondPhase) {
    delete secondPhase;
    secondPhase = nullptr;
  }
  currentPhase = nullptr;
}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Game::execute() {
  RenderWindow window(VideoMode(800, 600), "Good Game");
  window.setFramerateLimit(60);
  pGM->setWindow(&window);
  RenderWindow *pWindow = pGM->getWindow();
  while (pGM->openWindow()) {
    Event event;
    pGM->setClock();
    pGM->operator++();
    while (pWindow->pollEvent(event)) {
      if (event.type == Event::Closed ||
          (event.type == Event::KeyPressed &&
           event.key.code == sf::Keyboard::Escape)) {
        window.close();
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
      main_menu();
      break;
    case GameState::PLAYING:
      running();
      break;
    }
    pGM->show();
  }
}

void Game::running() {
  if (currentPhase) {
    currentPhase->execute();
  } else {
    cerr << "Current phase is not set." << endl;
  }
  updateCamera();
  player1->execute();
  player2->execute();
}

void Game::main_menu() {
  menu->execute();
  map<string, Button *>::iterator it;
  for (it = menu->getButtons().begin(); it != menu->getButtons().end(); ++it) {
    if (it->second->wasClicked()) {
      game_state = GameState::PLAYING;
      createFirstPhase(); // Cria a primeira fase
      break;
    }
  }
}

/* ------------------------------------------- */
/*               CREATE FUNCTIONS              */
/* ------------------------------------------- */

MouseSubject &Game::getMouseSubject() {
  return mouseSubject;
}

void Game::setGameState(GameState state) {
  game_state = state;
}


void Game::create_menu() {
  menu = new MainMenu(this);
  menu->activateButtons();
}


void Game::updateCamera() {
  if (!currentPhase) {
    cerr << "Current phase is not set. Cannot update camera." << endl;
    return;
  }

  Vector2f phaseSize = currentPhase->getPhaseSize();
  // Find the average X position of both players
  float avgX = (player1->getPosition().x + player2->getPosition().x) / 2.0f;

  // Y positional fix
  float fixedY = 300.f;

  // Limita a câmera aos limites do mundo
  float cameraHalfWidth = pGM->getWindow()->getSize().x / 2.0f;
  avgX =
      max(cameraHalfWidth, min(avgX, phaseSize.x - cameraHalfWidth));

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
  currentPhase = new FirstPhase(Vector2f(6000.f, 600.f), player1, player2, "background.png");

  // Add players to collision manager
  pCM->addPlayer(player1);
  pCM->addPlayer(player2);
}

void Game::createSecondPhase() {
  if (currentPhase) {
    delete currentPhase;
  }
  currentPhase = new SecondPhase(Vector2f(6000.f, 600.f), player1, player2, "background2.png");

  // Add players to collision manager
  pCM->addPlayer(player1);
  pCM->addPlayer(player2);
}
