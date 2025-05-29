#include "../managers/GraphicsManager.h"
#include "../entities/Player.h"
#include "../entities/Enemy.h"
#include "../entities/obstacles/Obstacle.h"
#include <list>
#include "../lists/List.h"

class Game {
    private:
        GraphicsManager* pGM;
        List<Ente*> entes_list;
        List<Ente*>::iterator it;
        Player* player1;
        Player* player2;
        void execute();

    public:
        Game();
        ~Game();
        void create_entes();
};
