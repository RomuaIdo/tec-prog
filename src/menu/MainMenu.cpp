#include "../../include/menu/MainMenu.h"
#include "../../include/game/Game.h"
#include "../../include/graphicalelements/Button.h"
#include <iostream>


MainMenu::MainMenu(Game* game) : Menu(game), currentPhase(1) {
    setBackground("assets/textures/menu_background.png");
    createButtons();
    updatePhaseDisplay();
}

MainMenu::~MainMenu() {
}

void MainMenu::createButtons() {
    MouseSubject& mouseSubject = pGame->getMouseSubject();
    Button* newGameButton = new Button("assets/fonts/Minecraft.ttf", "New Game",
                                      "assets/textures/button.png",
                                      "assets/textures/button_hovered.png",
                                      &mouseSubject, 24, Vector2f(400.f, 250.f));
    newGameButton->activate();
    addButton("new_game", newGameButton);

    Button* loadGameButton = new Button("assets/fonts/Minecraft.ttf", "Load Game",
                                       "assets/textures/button.png",
                                       "assets/textures/button_hovered.png",
                                       &mouseSubject, 24, Vector2f(400.f, 320.f));
    loadGameButton->activate();
    addButton("load_game", loadGameButton);

    Button* leftButton = new Button("assets/fonts/Minecraft.ttf", "<",
                                   "assets/textures/button.png",
                                   "assets/textures/button_hovered.png",
                                   &mouseSubject, 24, Vector2f(350.f, 400.f));
    leftButton->activate();
    addButton("left_phase", leftButton);

    Button* rightButton = new Button("assets/fonts/Minecraft.ttf", ">",
                                    "assets/textures/button.png",
                                    "assets/textures/button_hovered.png",
                                    &mouseSubject, 24, Vector2f(450.f, 400.f));
    rightButton->activate();
    addButton("right_phase", rightButton);

    Button* leaderboardButton = new Button("assets/fonts/Minecraft.ttf", "LeaderBoard",
                                          "assets/textures/button.png",
                                          "assets/textures/button_hovered.png",
                                          &mouseSubject, 24, Vector2f(400.f, 480.f));
    leaderboardButton->activate();
    addButton("leaderboard", leaderboardButton);

    if (!font.loadFromFile("assets/fonts/Minecraft.ttf")) {
        cerr << "Failed to load font for phase text!" << endl;
    }
    phaseText.setFont(font);
    phaseText.setCharacterSize(24);
    phaseText.setFillColor(Color::White);
    phaseText.setPosition(400.f, 400.f);
}

void MainMenu::updatePhaseDisplay() {
    phaseText.setString("Phase " + to_string(currentPhase));
    
    FloatRect textBounds = phaseText.getLocalBounds();
    phaseText.setOrigin(textBounds.width/2, textBounds.height/2);
    phaseText.setPosition(400.f, 400.f);
}

void MainMenu::execute() {
    draw();

    map<string, Button*>::iterator it;
    for (it = buttons.begin(); it != buttons.end(); ++it) {
        it->second->execute();
        
        if (it->second->wasClicked()) {
            if (it->first == "new_game") {
                pGame->setGameState(GameState::PLAYING);
                pGame->createFirstPhase();
            }
            else if (it->first == "left_phase") {
                currentPhase = (currentPhase == 1) ? 2 : 1;
                updatePhaseDisplay();
            }
            else if (it->first == "right_phase") {
                currentPhase = (currentPhase == 1) ? 2 : 1;
                updatePhaseDisplay();
            }
            else if (it->first == "leaderboard") {
                cout << "Leaderboard button clicked" << endl;
            }
        }
    }
    
    pGM->draw(&phaseText);
}
