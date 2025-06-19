#include "../../include/game/Game.h"
#include "../../include/graphicalelements/Button.h"
#include "../../include/managers/CollisionManager.h"
#include "../../include/menu/Leaderboard.h"
#include "../../include/menu/MainMenu.h"
#include <algorithm>

Game::Game()
    : pGM(nullptr), pCM(nullptr), number_of_players(1), player1(nullptr), player2(nullptr),
      menu(nullptr), leaderboard(nullptr), mouseSubject(),
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
  srand(time(nullptr));
  execute();
}

Game::~Game() {
  delete player1;
  player1 = nullptr;
  if(player2){
      delete player2;
      player2 = nullptr;
  }
  delete menu;
  menu = nullptr;

  if (firstPhase) {
    delete firstPhase;
    firstPhase = nullptr;
  }
  if (secondPhase) {
    delete secondPhase;
    secondPhase = nullptr;
  }
  currentPhase = nullptr;
}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

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
      main_menu();
      break;
    case GameState::PLAYING:
      running();
      break;
    case GameState::LEADERBOARD:
      leaderboard->execute();
      break;
    }

    pGM->show();
  }
}

void Game::running() {
    if (currentPhase) {
        currentPhase->execute();

        // Verifica se ambos os jogadores saíram pela direita
        if (currentPhase->passed()) {
        if (dynamic_cast<FirstPhase *>(currentPhase)) {
            createSecondPhase();
        } else if (dynamic_cast<SecondPhase *>(currentPhase)) {
            // Lógica para final do jogo ou próxima fase
            setGameState(GameState::MAIN_MENU);
        }
        }
    }
    updateCamera();
    player1->execute();
    if(player2){
        player2->execute();
    }
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

MouseSubject &Game::getMouseSubject() { return mouseSubject; }

void Game::setGameState(GameState state) { game_state = state; }

void Game::setNumberPlayers(int n) { number_of_players = n; }

void Game::create_menus() {
  menu = new MainMenu(this);
  menu->activateButtons();
  leaderboard = new Leaderboard(this);
}

void Game::updateCamera() {
  if (!currentPhase) {
    cerr << "Current phase is not set. Cannot update camera." << endl;
    return;
  }

  Vector2f phaseSize = currentPhase->getPhaseSize();
    float avgX = player1->getPosition().x;
    
     // Find the average X position of both players
    if(player2){
        avgX = (player1->getPosition().x + player2->getPosition().x) / 2.0f;
    }


    // Y positional fix
    float fixedY = 300.f;

    // Limita a câmera aos limites do mundo
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

    cout <<" ta tendando criar " << number_of_players << player1->getHealth()<<endl;
    player1->setPosition(Vector2f(200.f, 100.f));
    player1->setVelocity(Vector2f(0.f, 0.f));
    // Add players to collision manager
    pCM->addPlayer(player1);
    if(player2){
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
    // Add players to collision manager
    pCM->addPlayer(player1);
    if(player2){
        player2->setPosition(Vector2f(100.f, 100.f));
        player2->setVelocity(Vector2f(0.f, 0.f));
        pCM->addPlayer(player2);
    }
}

void Game::createPlayers(){
    if(!player1 && !player2){

        player1 = new Player(200, 100, PLAYERACEL, PLAYERHEALTH, PLAYERSTRENGTH, 1);
        std::cout << "Created player1: " << player1 << std::endl;
        
        if(number_of_players == 2){
            player2 = new Player(100, 100, PLAYERACEL, PLAYERHEALTH, PLAYERSTRENGTH, 2);
            std::cout << "Created player2: " << player2 << std::endl;
        }
    }
}
