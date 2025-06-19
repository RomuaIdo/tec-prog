#include "../entities/characters/Enemy.h"
#include "../entities/characters/Player.h"
#include "../entities/obstacles/Obstacle.h"
#include "../graphicalelements/MouseSubject.h"
#include "../lists/List.h"
#include "../managers/GraphicsManager.h"
#include "../phases/FirstPhase.h"
#include "../phases/SecondPhase.h"
#include <list>
#include <vector>

/* Forward declarations */
class CollisionManager;
enum class GameState { MAIN_MENU, PLAYING, PAUSED, GAME_OVER, LEADERBOARD };
class Menu;
class Button;
class Leaderboard;

class Game {

    private:
        /* ------ VARIABLES ------- */
        GraphicsManager *pGM;
        CollisionManager *pCM;
        int number_of_players;
        //   vector<Player *> players_vector;
        Player* player1;
        Player* player2;
        Menu *menu;
        Leaderboard *leaderboard;
        MouseSubject mouseSubject;
        GameState game_state;
        Vector2f phase_size;
        Vector2f cameraCenter;
        FirstPhase *firstPhase;
        SecondPhase *secondPhase;
        Phase *currentPhase;
        /* ---- OWN FUNCTIONS ----- */
        void execute();
        void running();
        void main_menu();
        void updateCamera();
        void createFirstPhase();
        void createSecondPhase();


    public:
        Game();
        ~Game();
        /* ---- GETS & SETS ----- */
        MouseSubject &getMouseSubject();
        void setGameState(GameState state);
        void setNumberPlayers(int n);
        /* ---- CREATE ----- */
        void createPhase(short int phaseNumber);
        void create_menus();
        void createPlayers();
};
