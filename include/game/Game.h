#include "../entities/characters/Enemy.h"
#include "../entities/characters/Player.h"
#include "../entities/obstacles/Obstacle.h"
#include "../graphicalelements/MouseSubject.h"
#include "../lists/List.h"
#include "../managers/GraphicsManager.h"
#include <list>


class CollisionManager;
enum class GameState { MAIN_MENU, PLAYING, PAUSED, GAME_OVER };
class Menu;
class Button;
class Game {

private:
    GraphicsManager  *pGM;
    CollisionManager *pCM;
    List<Ente *> entes_list;
    List<Ente *>::iterator it;
    Player *player1;
    Player *player2;
    Menu *menu;
    void execute();
    void running();
    void main_menu();
    GameState game_state;
    MouseSubject mouseSubject;

public:
    Game();
    ~Game();
    void create_entes();
    void create_menu();

};
