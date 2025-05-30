#include "../managers/GraphicsManager.h"
#include "../entities/Player.h"
#include "../entities/Enemy.h"
#include "../entities/obstacles/Obstacle.h"
#include "../graphicalelements/MouseSubject.h"
#include <list>
#include "../lists/List.h"

enum class GameState {
    MAIN_MENU,
    PLAYING,
    GAME_OVER
};


class Game {
    private:
        GraphicsManager* pGM;
        List<Ente*> entes_list;
        List<Ente*>::iterator it;
        Player* player1;
        Player* player2;
        void execute();
        GameState game_state;
        MouseSubject mouseSubject;

    public:
        Game();
        ~Game();
        void create_entes();
};
