#ifndef MENU_H
#include <vector>
#include "../entities/Ente.h"
#include "../graphicalelements/Button.h"


class Game;
class Menu : public Ente{
private:
    Game* pGame; 
    Texture background;
    vector<Button*> buttons;


public:
    Menu();
    Menu(Game* game);
    virtual ~Menu();
    void execute() override;
};

#endif
