#ifndef MENU_H
#include <map>
#include "../entities/Ente.h"
#include "../graphicalelements/Button.h"


class Game;
class Menu : public Ente{
    
    private:
        /* ----- VARIABLES ----- */
        Game* pGame; 
        map<string, Button*> buttons;
        
        /* ------ STATUS ------- */
        Texture background;

    public:
        Menu();
        Menu(Game* game);
        virtual ~Menu();

        /* ---- OWN FUNCTIONS ---- */
        void execute() override;
        Drawable& getDrawable() override;
        void draw() override;

        /* ------ BUTTON ------- */
        void addButton(string name, Button* button);
        void deactivateButtons();
        void activateButtons();
        
        /* ----- GETS & SETS ----- */
        void setBackground(const string filePath);
        map<string, Button*>& getButtons();
};

#endif
