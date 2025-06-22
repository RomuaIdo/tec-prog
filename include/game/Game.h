#ifndef GAME_H
#define GAME_H
#include "../entities/characters/Enemy.h"
#include "../entities/characters/Player.h"
#include "../entities/obstacles/Obstacle.h"
#include "../graphicalelements/MouseSubject.h"
#include "../graphicalelements/TextInputSubject.h"
#include "../lists/List.h"
#include "../managers/GraphicsManager.h"
#include "../phases/FirstPhase.h"
#include "../phases/SecondPhase.h"
#include <fstream>
#include <list>
#include <vector>

enum class GameState {
  MAIN_MENU,
  NEW_GAME_MENU,
  PLAYING,
  PAUSED,
  GAME_OVER,
  LEADERBOARD
};

/* Forward declarations */
class Menu;


class Game {

private:
  /* ------ VARIABLES ------- */
  GraphicsManager *pGM;
  Player *player1;
  Player *player2;
  vector<string> player_names;
  map<GameState, Menu *> menus;
  Menu *currentMenu;
  MouseSubject mouseSubject;
  TextInputSubject textInputSubject;
  GameState game_state;
  Phase *currentPhase;
  int seed;
  /* ---- OWN FUNCTIONS ----- */
  void execute();
  void running();
  void createFirstPhase();
  void createSecondPhase();

public:
  Game();
  ~Game();
  /* ---- GETS & SETS ----- */
  MouseSubject &getMouseSubject();
  TextInputSubject &getTextInputSubject();
  void setGameState(GameState state);
  GameState getGameState() const;
  /* ------ SAVE GAME ----- */
  json toJson() const;
  void fromJson(const json &j);
  void saveGame(const std::string &filename) const;
  void loadGame(const std::string &filename);

  /* ---- CREATE ----- */
  void createPhase(short int phaseNumber);
  void create_menus();
  void createPlayers(const vector<string> &playerNames);
  void setPlayerNames(const vector<string> &names);
  void saveScoretoLeaderboard();
  void cleanupAfterGame();
  void resetCamera();
  void updateCamera();
};

#endif
