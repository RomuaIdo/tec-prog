<<<<<<< HEAD
#include "../managers/GraphicsManager.h"
#include "../managers/CollisionManager.h"
#include "../entities/characters/Player.h"
#include "../entities/characters/Enemy.h"
#include "../entities/obstacles/Obstacle.h"
=======
#include "../entities/Enemy.h"
#include "../entities/Player.h"
#include "../entities/obstacles/Obstacle.h"
#include "../graphicalelements/MouseSubject.h"
#include "../lists/List.h"
#include "../managers/GraphicsManager.h"
>>>>>>> ad317a32e35cc3f6ff773c379935c4e283a8948c
#include <list>

enum class GameState { MAIN_MENU, PLAYING, PAUSED, GAME_OVER };
class Menu;
class Button;
class Game {
<<<<<<< HEAD
    private:
        CollisionManager* pCM;
        GraphicsManager*  pGM;
        list<Ente*> entes_list;
        list<Ente*>::iterator it;
        Player* player1;
        Player* player2;
        void execute();
=======
private:
  GraphicsManager *pGM;
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
>>>>>>> ad317a32e35cc3f6ff773c379935c4e283a8948c

public:
  Game();
  ~Game();
  void create_entes();
  void create_menu();
};
