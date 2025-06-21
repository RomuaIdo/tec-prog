#include "../../include/menu/NewGameMenu.h"
#include "../../include/game/Game.h"
#include "../../include/graphicalelements/Button.h"
#include <iostream>
#include <sstream>

NewGameMenu::NewGameMenu(Game *game)
    : Menu(game), activeInputField(nullptr), currentPhase(1), players(1),
      currentInputIndex(0) {
  setBackground("assets/textures/menu_background.png");
  createButtons();
  updatePhaseDisplay();
  updatePlayersDisplay();
}

NewGameMenu::~NewGameMenu() {
  for (auto input : nameInputs) {
    pGame->getMouseSubject().removeObserver(input);
    pGame->getTextInputSubject().removeObserver(input);
    delete input;
  }
  nameInputs.clear();
}

void NewGameMenu::createButtons() {
  Vector2f viewSize = pGM->getWindow()->getView().getSize();
  Vector2f center(viewSize.x / 2, viewSize.y / 2);

  MouseSubject &mouseSubject = pGame->getMouseSubject();

  Button *playersLeftButton = new Button(
      "assets/fonts/Minecraft.ttf", "<", "assets/textures/button.png",
      "assets/textures/button_hovered.png", &mouseSubject, 24,
      Vector2f(center.x - 100.f, center.y - 300.f));
  playersLeftButton->activate();
  addButton("players_left", playersLeftButton);

  Button *playersRightButton = new Button(
      "assets/fonts/Minecraft.ttf", ">", "assets/textures/button.png",
      "assets/textures/button_hovered.png", &mouseSubject, 24,
      Vector2f(center.x + 100.f, center.y - 300.f));
  playersRightButton->activate();
  addButton("players_right", playersRightButton);

  Button *phaseLeftButton = new Button(
      "assets/fonts/Minecraft.ttf", "<", "assets/textures/button.png",
      "assets/textures/button_hovered.png", &mouseSubject, 24,
      Vector2f(center.x - 100.f, center.y - 50.f));
  phaseLeftButton->activate();
  addButton("phase_left", phaseLeftButton);

  Button *phaseRightButton = new Button(
      "assets/fonts/Minecraft.ttf", ">", "assets/textures/button.png",
      "assets/textures/button_hovered.png", &mouseSubject, 24,
      Vector2f(center.x + 100.f, center.y - 50.f));
  phaseRightButton->activate();
  addButton("phase_right", phaseRightButton);

  Button *startButton = new Button(
      "assets/fonts/Minecraft.ttf", "Start", "assets/textures/button.png",
      "assets/textures/button_hovered.png", &mouseSubject, 24,
      Vector2f(center.x, center.y + 100.f));
  startButton->getSprite().setScale(1.5f, 1.5f);
  startButton->activate();
  addButton("start", startButton);

  Button *backButton = new Button(
      "assets/fonts/Minecraft.ttf", "Back", "assets/textures/button.png",
      "assets/textures/button_hovered.png", &mouseSubject, 24,
      Vector2f(center.x, center.y + 200.f));
  backButton->activate();
  addButton("back", backButton);

  if (!font.loadFromFile("assets/fonts/Minecraft.ttf")) {
    std::cerr << "Failed to load font for phase text!" << std::endl;
  }
  playersText.setFont(font);
  playersText.setCharacterSize(24);
  playersText.setFillColor(Color::White);
  playersText.setPosition(center.x, center.y - 300.f);

  phaseText.setFont(font);
  phaseText.setCharacterSize(24);
  phaseText.setFillColor(Color::White);
  phaseText.setPosition(center.x, center.y - 50.f);

  createNameInputs();
}

void NewGameMenu::createNameInputs() {
  Vector2f viewSize = pGM->getWindow()->getView().getSize();
  Vector2f center(viewSize.x / 2, viewSize.y / 2);

  for (auto input : nameInputs) {
    pGame->getMouseSubject().removeObserver(input);
    pGame->getTextInputSubject().removeObserver(input);
    delete input;
  }
  nameInputs.clear();

  if (players == 1) {
    TextInputField *input = new TextInputField(
        font, "Player 1:", Vector2f(center.x - 50.f, center.y - 200.f));
    nameInputs.push_back(input);
    pGame->getMouseSubject().addObserver(input);     // Registrar mouse observer
    pGame->getTextInputSubject().addObserver(input); // Registrar text observer
  } else {
    TextInputField *input1 = new TextInputField(
        font, "Player 1:", Vector2f(center.x - 150.f, center.y - 200.f));
    TextInputField *input2 = new TextInputField(
        font, "Player 2:", Vector2f(center.x + 50.f, center.y - 200.f));
    nameInputs.push_back(input1);
    nameInputs.push_back(input2);
    pGame->getMouseSubject().addObserver(input1); // Registrar mouse observer
    pGame->getMouseSubject().addObserver(input2); // Registrar mouse observer
    pGame->getTextInputSubject().addObserver(input1); // Registrar text observer
    pGame->getTextInputSubject().addObserver(input2); // Registrar text observer
  }

  if (!nameInputs.empty()) {
    setActiveInputField(0);
  }
}

void NewGameMenu::updatePhaseDisplay() {
  Vector2f viewSize = pGM->getWindow()->getView().getSize();
  Vector2f center(viewSize.x / 2, viewSize.y / 2);

  std::ostringstream oss;
  oss << "Phase " << currentPhase;
  phaseText.setString(oss.str());

  FloatRect textBounds = phaseText.getLocalBounds();
  phaseText.setOrigin(textBounds.width / 2, textBounds.height / 2);
  phaseText.setPosition(center.x, center.y - 50.f);
}

void NewGameMenu::updatePlayersDisplay() {
  Vector2f viewSize = pGM->getWindow()->getView().getSize();
  Vector2f center(viewSize.x / 2, viewSize.y / 2);

  std::ostringstream oss;
  oss << "Players " << players;
  playersText.setString(oss.str());

  FloatRect textBounds = playersText.getLocalBounds();
  playersText.setOrigin(textBounds.width / 2, textBounds.height / 2);
  playersText.setPosition(center.x, center.y - 300.f);

  createNameInputs();
}

void NewGameMenu::setActiveInputField(int index) {
  if (index >= 0 && static_cast<size_t>(index) < nameInputs.size()) {
    if (activeInputField) {
      activeInputField->setActive(false);
    }
    activeInputField = nameInputs[index];
    activeInputField->setActive(true);
    currentInputIndex = index;
  }
}

void NewGameMenu::execute() {
  draw();

  map<std::string, Button *>::iterator it;
  for (it = buttons.begin(); it != buttons.end(); ++it) {
    Button *button = it->second;
    button->execute();

    if (button->wasClicked()) {
      if (it->first == "players_left" || it->first == "players_right") {
        players = (players == 1) ? 2 : 1;
        updatePlayersDisplay();
      } else if (it->first == "phase_left" || it->first == "phase_right") {
        currentPhase = (currentPhase == 1) ? 2 : 1;
        updatePhaseDisplay();
      } else if (it->first == "start") {
        vector<std::string> playerNames;
        vector<TextInputField *>::iterator inputIt;
        for (inputIt = nameInputs.begin(); inputIt != nameInputs.end();
             ++inputIt) {
          playerNames.push_back((*inputIt)->getInput());
        }

        pGame->setNumberPlayers(players);
        pGame->setPlayerNames(playerNames);
        pGame->setGameState(GameState::PLAYING);
        pGame->createPlayers(playerNames);
        pGame->createPhase(currentPhase);
      } else if (it->first == "back") {
        pGame->setGameState(GameState::MAIN_MENU);
      }
    }
  }

  pGM->draw(&phaseText);
  pGM->draw(&playersText);

  vector<TextInputField *>::iterator inputIt;
  for (inputIt = nameInputs.begin(); inputIt != nameInputs.end(); ++inputIt) {
    (*inputIt)->draw();
  }
}


void NewGameMenu::activateTextInputFields() {
  vector<TextInputField *>::iterator it; 
  for (it = nameInputs.begin(); it != nameInputs.end(); ++it) {
    pGame->getTextInputSubject().addObserver(*it);
  }
}

void NewGameMenu::deactivateTextInputFields() {
  vector<TextInputField *>::iterator it; 
  for (it = nameInputs.begin(); it != nameInputs.end(); ++it) {
    pGame->getTextInputSubject().removeObserver(*it);
  }
}

void NewGameMenu::activate(){
  activateButtons();
  activateTextInputFields();
}

void NewGameMenu::deactivate() {
  deactivateButtons();
  deactivateTextInputFields();
}
