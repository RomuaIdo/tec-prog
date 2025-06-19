#include "../../include/menu/NewGameMenu.h"
#include "../../include/game/Game.h"
#include "../../include/graphicalelements/Button.h"
#include <iostream>

NewGameMenu::NewGameMenu(Game* game) : Menu(game), currentPhase(1), players(1) {
    setBackground("assets/textures/menu_background.png");
    createButtons();
    updatePhaseDisplay();
    updatePlayersDisplay();
}

NewGameMenu::~NewGameMenu() {
}

void NewGameMenu::createButtons() {
    Vector2f viewSize = pGM->getWindow()->getView().getSize();
    Vector2f center(viewSize.x / 2, viewSize.y / 2);

    MouseSubject& mouseSubject = pGame->getMouseSubject();
    
    // Botões para jogadores
    Button* playersLeftButton = new Button("assets/fonts/Minecraft.ttf", "<",
                                       "assets/textures/button.png",
                                       "assets/textures/button_hovered.png",
                                       &mouseSubject, 24, Vector2f(center.x - 100.f, center.y - 100.f));
    playersLeftButton->activate();
    addButton("players_left", playersLeftButton);

    Button* playersRightButton = new Button("assets/fonts/Minecraft.ttf", ">",
                                        "assets/textures/button.png",
                                        "assets/textures/button_hovered.png",
                                        &mouseSubject, 24, Vector2f(center.x + 100.f, center.y - 100.f));
    playersRightButton->activate();
    addButton("players_right", playersRightButton);

    Button* phaseLeftButton = new Button("assets/fonts/Minecraft.ttf", "<",
                                     "assets/textures/button.png",
                                     "assets/textures/button_hovered.png",
                                     &mouseSubject, 24, Vector2f(center.x - 100.f, center.y));
    phaseLeftButton->activate();
    addButton("phase_left", phaseLeftButton);

    Button* phaseRightButton = new Button("assets/fonts/Minecraft.ttf", ">",
                                      "assets/textures/button.png",
                                      "assets/textures/button_hovered.png",
                                      &mouseSubject, 24, Vector2f(center.x + 100.f, center.y));
    phaseRightButton->activate();
    addButton("phase_right", phaseRightButton);

    Button* startButton = new Button("assets/fonts/Minecraft.ttf", "Start",
                                  "assets/textures/button.png",
                                  "assets/textures/button_hovered.png",
                                  &mouseSubject, 24, Vector2f(center.x, center.y + 100.f));
    startButton->activate();
    addButton("start", startButton);

    Button* backButton = new Button("assets/fonts/Minecraft.ttf", "Back",
                                 "assets/textures/button.png",
                                 "assets/textures/button_hovered.png",
                                 &mouseSubject, 24, Vector2f(center.x, center.y + 200.f));
    backButton->activate();
    addButton("back", backButton);

    if (!font.loadFromFile("assets/fonts/Minecraft.ttf")) {
        cerr << "Failed to load font for phase text!" << endl;
    }
    playersText.setFont(font);
    playersText.setCharacterSize(24);
    playersText.setFillColor(Color::White);
    playersText.setPosition(center.x, center.y - 100.f);

    phaseText.setFont(font);
    phaseText.setCharacterSize(24);
    phaseText.setFillColor(Color::White);
    phaseText.setPosition(center.x, center.y);
}

void NewGameMenu::updatePhaseDisplay() {
    Vector2f viewSize = pGM->getWindow()->getView().getSize();
    Vector2f center(viewSize.x / 2, viewSize.y / 2);
    phaseText.setString("Phase " + to_string(currentPhase));
    
    FloatRect textBounds = phaseText.getLocalBounds();
    phaseText.setOrigin(textBounds.width/2, textBounds.height/2);
    phaseText.setPosition(center.x, center.y);
}

void NewGameMenu::updatePlayersDisplay(){
    Vector2f viewSize = pGM->getWindow()->getView().getSize();
    Vector2f center(viewSize.x / 2, viewSize.y / 2);
    playersText.setString("Players " + to_string(players));

    FloatRect textBounds = playersText.getLocalBounds();
    playersText.setOrigin(textBounds.width/2, textBounds.height/2);
    playersText.setPosition(center.x, center.y - 100.f);
}

void NewGameMenu::execute() {
    draw();

    map<string, Button*>::iterator it;
    for (it = buttons.begin(); it != buttons.end(); ++it) {
        it->second->execute();
        
        if (it->second->wasClicked()) {
            if (it->first == "players_left" || it->first == "players_right") {
                players = (players == 1) ? 2 : 1;
                updatePlayersDisplay();
            }
            else if (it->first == "phase_left" || it->first == "phase_right") {
                currentPhase = (currentPhase == 1) ? 2 : 1;
                updatePhaseDisplay();
            }
            else if (it->first == "start") {
                pGame->setNumberPlayers(players);
                pGame->setGameState(GameState::PLAYING);
                pGame->createPlayers();
                pGame->createPhase(currentPhase);
            }
            else if (it->first == "back") {
                pGame->setGameState(GameState::MAIN_MENU);
            }
        }
    }
    
    pGM->draw(&phaseText);
    pGM->draw(&playersText);
}
