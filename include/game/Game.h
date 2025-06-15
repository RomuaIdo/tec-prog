#include "../entities/characters/Enemy.h"
#include "../entities/characters/Player.h"
#include "../entities/obstacles/Obstacle.h"
#include "../graphicalelements/MouseSubject.h"
#include "../lists/List.h"
#include "../managers/GraphicsManager.h"
#include "../phases/FirstPhase.h"
#include "../phases/SecondPhase.h"
#include <list>

class CollisionManager;
enum class GameState { MAIN_MENU, PLAYING, PAUSED, GAME_OVER };
class Menu;
class Button;
class Game {

private:
  /* ------ VARIABLES ------- */
  GraphicsManager *pGM;
  CollisionManager *pCM;
  Player *player1;
  Player *player2;
  Menu *menu;
  MouseSubject mouseSubject;
  GameState game_state;
  Vector2f phase_size;
  Vector2f cameraCenter;
  FirstPhase* firstPhase;
  SecondPhase* secondPhase;   
  Phase* currentPhase;
  /* ---- OWN FUNCTIONS ----- */
  void execute();
  void running();
  void main_menu();
  void updateCamera();

public:
  Game();
  ~Game();
  /* ---- GETS & SETS ----- */
  MouseSubject& getMouseSubject();
  void setGameState(GameState state);
  /* ---- CREATE ----- */
  void create_menu();
  void createFirstPhase();
  void createSecondPhase();
};
