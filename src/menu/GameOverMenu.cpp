#include "../../include/menu/GameOverMenu.h"
#include "../../include/game/Game.h"
#include "../../include/graphicalelements/Button.h"

GameOverMenu::GameOverMenu(Game* game) : Menu(game) {
    setBackground("assets/textures/0_Background.png");

    if (!font.loadFromFile("assets/fonts/Minecraft.ttf")) {
        std::cerr << "Failed to load font for game over menu!" << std::endl;
    }

    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(72);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setStyle(Text::Bold);

    Vector2f viewSize = pGM->getWindow()->getView().getSize();
    Vector2f center(viewSize.x / 2, viewSize.y / 2);

    FloatRect textBounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textBounds.width / 2, textBounds.height / 2);
    gameOverText.setPosition(center.x, center.y - 200.f);

    MouseSubject &mouseSubject = pGame->getMouseSubject();
    Button* backButton = new Button(
        "assets/fonts/Minecraft.ttf", "Back to Main Menu", "assets/textures/button.png",
        "assets/textures/button_hovered.png", &mouseSubject, 24,
        Vector2f(center.x, center.y + 100.f)
    );
    addButton("back", backButton);
}

void GameOverMenu::execute() {
    draw();     pGM->draw(&gameOverText);
    buttons["back"]->execute();

    if (buttons["back"]->wasClicked()) {
        pGame->cleanupAfterGame();
        pGame->setGameState(GameState::MAIN_MENU);
    }
}
