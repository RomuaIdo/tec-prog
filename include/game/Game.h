#include "../entities/characters/Enemy.h"
#include "../entities/characters/Player.h"
#include "../entities/obstacles/Obstacle.h"
#include "../graphicalelements/MouseSubject.h"
#include "../graphicalelements/TextInputSubject.h"
#include "../lists/List.h"
#include "../managers/GraphicsManager.h"
#include "../phases/FirstPhase.h"
#include "../phases/SecondPhase.h"
#include <list>
#include <vector>

enum class GameState { MAIN_MENU, NEW_GAME_MENU, PLAYING, PAUSED, GAME_OVER, LEADERBOARD };

/* Forward declarations */
class CollisionManager;
class Menu;
class Button;
class Leaderboard;
class MainMenu;
class NewGameMenu;

class Game {

    private:
        /* ------ VARIABLES ------- */
        GraphicsManager *pGM;
        CollisionManager *pCM;
        int number_of_players;
        //   vector<Player *> players_vector;
        Player* player1;
        Player* player2;
        vector<string> player_names;
        Menu *currentMenu;
        MainMenu *mainMenu;
        NewGameMenu *newGameMenu;
        Leaderboard *leaderboard;
        MouseSubject mouseSubject;
        TextInputSubject textInputSubject;
        GameState game_state;
        Vector2f phase_size;
        Vector2f cameraCenter;
        FirstPhase *firstPhase;
        SecondPhase *secondPhase;
        Phase *currentPhase;
        /* ---- OWN FUNCTIONS ----- */
        void execute();
        void running();
        void updateCamera();
        void createFirstPhase();
        void createSecondPhase();


    public:
        Game();
        ~Game();
        /* ---- GETS & SETS ----- */
        MouseSubject &getMouseSubject();
        TextInputSubject &getTextInputSubject();
        void setGameState(GameState state);
        void setNumberPlayers(int n);
        /* ---- CREATE ----- */
        void createPhase(short int phaseNumber);
        void create_menus();
        void createPlayers(const vector<string> &playerNames);
        void setPlayerNames(const vector<string> &names);
        void saveScoretoLeaderboard();
        void cleanupAfterGame();
        void resetCamera();
};
