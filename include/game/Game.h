#include "../entities/characters/Enemy.h"
#include "../entities/characters/Player.h"
#include "../entities/obstacles/Obstacle.h"
#include "../graphicalelements/MouseSubject.h"
#include "../lists/List.h"
#include "../managers/GraphicsManager.h"
#include <list>

enum class GameState { MAIN_MENU, PLAYING, PAUSED, GAME_OVER };
class Menu;
class Button;
class Game {

    private:
        
        /* ------ VARIABLES ------- */
        GraphicsManager  *pGM;
        CollisionManager *pCM;
        List<Ente *> entes_list;
        List<Ente *>::iterator it;
        Player *player1;
        Player *player2;
        Menu *menu;
        MouseSubject mouseSubject;
        GameState game_state;
        
        /* ---- OWN FUNCTIONS ----- */
        void execute();
        void running();
        void main_menu();

    public:
        Game();
        ~Game();

        /* ---- CREATE ----- */
        void create_entes();
        void create_menu();

};
