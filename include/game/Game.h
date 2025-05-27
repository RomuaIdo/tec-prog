#include "../managers/Graphical_Manager.h"
#include "../entities/Player.h"


class Game {
private:
    Graphical_Manager* GG;
    Player* player1;
    Player* player2;

public:
  Game();
  ~Game();
  void execute();
};
