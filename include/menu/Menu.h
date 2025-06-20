#ifndef MENU_H
#define MENU_H
#include "../entities/Ente.h"
#include "../graphicalelements/Button.h"
#include <map>

class Game;
class Menu : public Ente {

protected:
  /* ----- VARIABLES ----- */
  Game *pGame;
  map<string, Button *> buttons;

  /* ------ STATUS ------- */
  Texture background;

public:
  Menu();
  Menu(Game *game);
  virtual ~Menu();

  /* ---- OWN FUNCTIONS ---- */
  virtual void execute();   
  virtual Drawable &getDrawable();
  virtual void draw();

  /* ------ BUTTON ------- */
  void addButton(string name, Button *button);
  void deactivateButtons();
  void activateButtons();

  /* ----- GETS & SETS ----- */
  void setBackground(const string filePath);
  map<string, Button *> &getButtons();
};

#endif
