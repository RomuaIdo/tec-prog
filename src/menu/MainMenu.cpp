#include "../../include/menu/MainMenu.h"
#include "../../include/game/Game.h"
#include "../../include/graphicalelements/Button.h"
#include <iostream>

MainMenu::MainMenu(Game *game) : Menu(game) {
  setBackground("assets/textures/MainMenu_Background.png");
  createButtons();
  if (!font.loadFromFile("assets/fonts/Minecraft.ttf")) {
    cerr << "Failed to load font for game title!" << endl;
  }
}

MainMenu::~MainMenu() {}

void MainMenu::createButtons() {
  Vector2f viewSize = pGM->getWindow()->getView().getSize();
  Vector2f center(viewSize.x / 2, viewSize.y / 2);

  MouseSubject &mouseSubject = pGame->getMouseSubject();
  Button *newGameButton = new Button(
      "assets/fonts/Minecraft.ttf", "New Game", "assets/textures/button.png",
      "assets/textures/button_hovered.png", &mouseSubject, 24,
      Vector2f(center.x, center.y - 200.f));
  addButton("new_game", newGameButton);

  Button *loadGameButton = new Button(
      "assets/fonts/Minecraft.ttf", "Load Game", "assets/textures/button.png",
      "assets/textures/button_hovered.png", &mouseSubject, 24,
      Vector2f(center.x, center.y - 100.f));
  addButton("load_game", loadGameButton);

  Button *leaderboardButton = new Button(
      "assets/fonts/Minecraft.ttf", "LeaderBoard", "assets/textures/button.png",
      "assets/textures/button_hovered.png", &mouseSubject, 24,
      Vector2f(center.x, center.y));
  addButton("leaderboard", leaderboardButton);

  setGameTitle("BRASILORE");
}

void MainMenu::execute() {
  draw();

  map<string, Button *>::iterator it;
  for (it = buttons.begin(); it != buttons.end(); ++it) {
    it->second->execute();

    if (it->second->wasClicked()) {
      if (it->first == "new_game") {
        pGame->setGameState(GameState::NEW_GAME_MENU);
      } else if (it->first == "leaderboard") {
        pGame->setGameState(GameState::LEADERBOARD);
      } else if (it->first == "load_game") {
        pGame->loadGame("saves/savegame.json");
      }
    }
  }
  pGM->draw(&GameTitle);
}

void MainMenu::setGameTitle(const string &title) {
  GameTitle.setString(title);
  GameTitle.setFont(font);
  GameTitle.setCharacterSize(96);
  GameTitle.setFillColor(Color::Yellow);

  Vector2f viewSize = pGM->getWindow()->getView().getSize();
  Vector2f center(viewSize.x / 2, viewSize.y / 2);

  FloatRect textBounds = GameTitle.getLocalBounds();
  GameTitle.setOrigin(textBounds.width / 2, textBounds.height / 2);
  GameTitle.setPosition(660, center.y - 600.f);
}
