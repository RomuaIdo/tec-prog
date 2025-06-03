#ifndef MENU_H
#include <map>
#include "../entities/Ente.h"
#include "../graphicalelements/Button.h"


class Game;
class Menu : public Ente{
private:
    Game* pGame; 
    Texture background;
    map<string, Button*> buttons;


public:
    Menu();
    Menu(Game* game);
    virtual ~Menu();
    void addButton(string name, Button* button);
    void setBackground(const string filePath);
    void deactivateButtons();
    void activateButtons();
    void execute() override;
    Drawable& getDrawable() override;
    void draw() override;
    map<string, Button*>& getButtons();
};

#endif
