#include "../managers/GraphicsManager.h"
#include "../managers/CollisionManager.h"
#include "../entities/characters/Player.h"
#include "../entities/characters/Enemy.h"
#include "../entities/obstacles/Obstacle.h"
#include <list>

class Game {
    private:
        CollisionManager* pCM;
        GraphicsManager*  pGM;
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
