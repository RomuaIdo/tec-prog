#include "../managers/GraphicsManager.h"
#include "../entities/Player.h"
#include "../entities/Enemy.h"
#include "../obstacles/Obstacle.h"
#include <list>

class Game {
    private:
        GraphicsManager* pGM;
        list<Ente*> entes_list;
        list<Ente*>::iterator it;
        Player* player1;
        Player* player2;
        void execute();

    public:
        Game();
        ~Game();
        void create_entes();
};
