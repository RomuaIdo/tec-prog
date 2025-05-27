#include "../managers/GraphicalManager.h"
#include "../entities/Player.h"


class Game {
private:
    GraphicalManager* GG;
    Player* player1;
    Player* player2;

public:
  Game();
  ~Game();
  void execute();
};
