#ifndef NEWGAMEMENU_H
#define NEWGAMEMENU_H

#include "../graphicalelements/TextInputField.h"
#include "Menu.h"
#include <SFML/Graphics.hpp>

class NewGameMenu : public Menu {
public:
  NewGameMenu(Game *game);
  virtual ~NewGameMenu();

  void createButtons();
  void createNameInputs();
  void updatePhaseDisplay();
  void updatePlayersDisplay();
  void execute() override;

private:
  vector<TextInputField *> nameInputs;
  TextInputField *activeInputField;
  Font font;
  Text phaseText;
  Text playersText;
  int currentPhase;
  int players;
  int currentInputIndex;
  void setActiveInputField(int index);
  void activate() override;
  void deactivate() override;
  void activateTextInputFields();
  void deactivateTextInputFields();
};

#endif
