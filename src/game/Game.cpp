#include "../../include/game/Game.h"
#include "../../include/graphicalelements/Button.h"
#include "../../include/managers/CollisionManager.h"
#include "../../include/menu/Menu.h"

Game::Game()
    : pGM(nullptr), pCM(nullptr), entes_list(), it(), player1(nullptr),
      player2(nullptr), mouseSubject() {
  entes_list.clear();
  pCM = CollisionManager::getInstance();
  pGM = GraphicsManager::getInstance();
  Ente::setGraphicsManager(pGM);
  player1 = new Player(200, 100, 50.f, 10, 1, 4, 1, 60.f);
  player2 = new Player(100, 100, 50.f, 10, 1, 4, 2, 60.f);
  create_entes();
  create_menu();

  game_state = GameState::MAIN_MENU;
  execute();
}

Game::~Game() {
  delete player1;
  player1 = nullptr;
  delete player2;
  player2 = nullptr;
  delete menu;
  menu = nullptr;

  List<Ente *>::iterator ite;
  for (ite = entes_list.begin(); ite != entes_list.end(); ite++) {
    if (*ite) {
      cout << "Deleting ente..." << endl;
      delete (*ite);
      (*ite) = nullptr;
    }
  }
  cout << "Successfully Deleted!" << endl;
  entes_list.clear();
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
  for (it = entes_list.begin(); it != entes_list.end(); it++) {
    if (*it) {
      (*it)->execute();
    } else
      cout << "Not executed." << endl;
  }
  player1->execute();
  player2->execute();
  pCM->execute();
}

void Game::main_menu() {

  menu->execute();
  map<string, Button *>::iterator it;
  for (it = menu->getButtons().begin(); it != menu->getButtons().end(); ++it) {
    if (it->second->wasClicked()) {
      game_state = GameState::PLAYING;
      cout << "Button pressed: " << it->first << endl;
      break;
    }
  }
}

/* ------------------------------------------- */
/*               CREATE FUNCTIONS              */
/* ------------------------------------------- */

void Game::create_menu() {
  menu = new Menu(this);
  if (menu) {
    menu->setBackground("assets/textures/menu_background.png");
    Button *playButton = new Button("assets/fonts/Minecraft.ttf", "Play",
                                    "assets/textures/button.png",
                                    "assets/textures/button_hovered.png",
                                    &mouseSubject, 20, Vector2f(300.f, 400.f));
    playButton->activate();
    menu->addButton("play", playButton);
    menu->activateButtons();
  } else {
    cerr << "Menu not allocated." << endl;
  }
}

void Game::create_entes() {
  for (int i = 0; i < 1; i++) {
    Enemy *e = nullptr;
    e = new Enemy((float)(i * 150), (float)((i + 1) * 150), 15.f, 5, 1.f, 2);
    if (e) {
      e->addPlayer(player1);
      e->addPlayer(player2);
      pCM->addEnemy(e);
      entes_list.push_back(e);
      cout << "Players added to enemy" << endl;
    } else
      cout << "Enemy not allocated." << endl;
  }
  for (int i = 0; i < 2; i++) {
    Obstacle *o = nullptr;
    o = new Obstacle(false, (i + 2) * 100.f, 570.f);
    if (o) {
      pCM->addObstacle(o);
      entes_list.push_back(o);
      cout << "Obstacle created" << endl;
    } else
      cout << "Obstacle not allocated." << endl;
  }
  pCM->addPlayer(player1);
  pCM->addPlayer(player2);
}
