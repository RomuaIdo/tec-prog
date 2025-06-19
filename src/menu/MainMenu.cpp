#include "../../include/menu/MainMenu.h"
#include "../../include/game/Game.h"
#include "../../include/graphicalelements/Button.h"
#include <iostream>


MainMenu::MainMenu(Game* game) : Menu(game), currentPhase(1), players(1) {
    setBackground("assets/textures/menu_background.png");
    createButtons();
    updatePhaseDisplay();
    updatePlayersDisplay();
}

MainMenu::~MainMenu() {
}

void MainMenu::createButtons() {
    Vector2f viewSize = pGM->getWindow()->getView().getSize();
    Vector2f center(viewSize.x / 2, viewSize.y / 2);

  MouseSubject& mouseSubject = pGame->getMouseSubject();
    Button* newGameButton = new Button("assets/fonts/Minecraft.ttf", "New Game",
                                      "assets/textures/button.png",
                                      "assets/textures/button_hovered.png",
                                      &mouseSubject, 24, Vector2f(center.x, center.y - 200.f));
    newGameButton->activate();
    addButton("new_game", newGameButton);

    Button* loadGameButton = new Button("assets/fonts/Minecraft.ttf", "Load Game",
                                       "assets/textures/button.png",
                                       "assets/textures/button_hovered.png",
                                       &mouseSubject, 24, Vector2f(center.x, center.y - 100.f));
    loadGameButton->activate();
    addButton("load_game", loadGameButton);

    Button* playersButton = new Button("assets/fonts/Minecraft.ttf", "+",
                                   "assets/textures/button.png",
                                   "assets/textures/button_hovered.png",
                                   &mouseSubject, 24, Vector2f(center.x + 60.f, center.y ));
    playersButton->activate();
    addButton("playersNumber", playersButton);

    Button* leftButton = new Button("assets/fonts/Minecraft.ttf", "<",
                                   "assets/textures/button.png",
                                   "assets/textures/button_hovered.png",
                                   &mouseSubject, 24, Vector2f(center.x - 100.f, center.y + 100.f));
    leftButton->activate();
    addButton("left_phase", leftButton);

    Button* rightButton = new Button("assets/fonts/Minecraft.ttf", ">",
                                    "assets/textures/button.png",
                                    "assets/textures/button_hovered.png",
                                    &mouseSubject, 24, Vector2f(center.x + 100.f, center.y + 100.f));
    rightButton->activate();
    addButton("right_phase", rightButton);

    Button* leaderboardButton = new Button("assets/fonts/Minecraft.ttf", "LeaderBoard",
                                          "assets/textures/button.png",
                                          "assets/textures/button_hovered.png",
                                          &mouseSubject, 24, Vector2f(center.x, center.y + 200.f));
    leaderboardButton->activate();
    addButton("leaderboard", leaderboardButton);

    if (!font.loadFromFile("assets/fonts/Minecraft.ttf")) {
        cerr << "Failed to load font for phase text!" << endl;
    }
    phaseText.setFont(font);
    phaseText.setCharacterSize(24);
    phaseText.setFillColor(Color::White);
    phaseText.setPosition(center.x, center.y + 100.f);

    playersText.setFont(font);
    playersText.setCharacterSize(24);
    playersText.setFillColor(Color::White);
    playersText.setPosition(center.x - 50.f, center.y);
}

void MainMenu::updatePhaseDisplay() {
    Vector2f viewSize = pGM->getWindow()->getView().getSize();
    Vector2f center(viewSize.x / 2, viewSize.y / 2);
    phaseText.setString("Phase " + to_string(currentPhase));
    
    FloatRect textBounds = phaseText.getLocalBounds();
    phaseText.setOrigin(textBounds.width/2, textBounds.height/2);
    phaseText.setPosition(center.x, center.y + 100.f);
}

void MainMenu::updatePlayersDisplay(){
    Vector2f viewSize = pGM->getWindow()->getView().getSize();
    Vector2f center(viewSize.x / 2, viewSize.y / 2);
    playersText.setString("Players " + to_string(players));

    FloatRect textBounds = playersText.getLocalBounds();
    playersText.setOrigin(textBounds.width/2, textBounds.height/2);
    playersText.setPosition(center.x - 50.f, center.y );
}

void MainMenu::execute() {
    draw();

    map<string, Button*>::iterator it;
    for (it = buttons.begin(); it != buttons.end(); ++it) {
        it->second->execute();
        
        if (it->second->wasClicked()) {
            if (it->first == "new_game") {
                pGame->setNumberPlayers(players);
                pGame->setGameState(GameState::PLAYING);
                pGame->createPlayers();
                pGame->createPhase(currentPhase);
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
                pGame->setGameState(GameState::LEADERBOARD);
            }
            else if(it->first == "playersNumber"){
                players = (players == 1) ? 2 : 1;
                updatePlayersDisplay();
            }
        }
    }
    
    pGM->draw(&phaseText);
    pGM->draw(&playersText);

}
