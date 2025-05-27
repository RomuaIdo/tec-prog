#include "../managers/GraphicsManager.h"
#include "../entities/Player.h"


class Game {
private:
    GraphicsManager* pGM;
    Player* player1;
    Player* player2;

public:
  Game();
  ~Game();
  void execute();
};
