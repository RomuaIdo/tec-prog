#include "../../include/menu/PauseMenu.h"
#include "../../include/game/Game.h"
#include "../../include/graphicalelements/Button.h"

PauseMenu::PauseMenu(Game *game) : Menu(game) {
  setBackground("assets/textures/menu_background.png");

  Vector2f viewSize = pGM->getWindow()->getView().getSize();
  Vector2f center(viewSize.x / 2, viewSize.y / 2);

  if (!font.loadFromFile("assets/fonts/Minecraft.ttf")) {
    std::cerr << "Failed to load font for pause menu!" << std::endl;
  }

  pauseText.setFont(font);
  pauseText.setString("PAUSE");
  pauseText.setCharacterSize(72);
  pauseText.setFillColor(Color::White);
  pauseText.setStyle(Text::Bold);

  sf::FloatRect textBounds = pauseText.getLocalBounds();
  pauseText.setOrigin(textBounds.width / 2, textBounds.height / 2);
  pauseText.setPosition(center.x, center.y - 200);

  MouseSubject &mouseSubject = pGame->getMouseSubject();

  Button *resumeButton = new Button(
      "assets/fonts/Minecraft.ttf", "Resume", "assets/textures/button.png",
      "assets/textures/button_hovered.png", &mouseSubject, 24,
      Vector2f(center.x, center.y - 100.f));
  addButton("resume", resumeButton);

  Button *mainMenuButton = new Button(
      "assets/fonts/Minecraft.ttf", "Main Menu", "assets/textures/button.png",
      "assets/textures/button_hovered.png", &mouseSubject, 24,
      Vector2f(center.x, center.y));
  addButton("main_menu", mainMenuButton);

  activateButtons();
}

void PauseMenu::execute() {
  draw();
  pGM->draw(&pauseText);

  for (auto &[name, button] : buttons) {
    button->execute();

    if (button->wasClicked()) {
      if (name == "resume") {
        pGame->setGameState(GameState::PLAYING);
      } else if (name == "main_menu") {
        pGame->cleanupAfterGame();
        pGame->setGameState(GameState::MAIN_MENU);
      }
    }
  }
}
