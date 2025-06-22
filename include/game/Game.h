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
#include <fstream>

enum class GameState { MAIN_MENU, NEW_GAME_MENU, PLAYING, PAUSED, GAME_OVER, LEADERBOARD };

/* Forward declarations */
class CollisionManager;
class Menu;
class Button;
class Leaderboard;
class MainMenu;
class NewGameMenu;
class PauseMenu;
class GameOverMenu;

class Game {

    private:
        /* ------ VARIABLES ------- */
        GraphicsManager *pGM;
        //   vector<Player *> players_vector;
        Player* player1;
        Player* player2;
        vector<string> player_names;
        Menu *currentMenu;
        MainMenu *mainMenu;
        PauseMenu *pauseMenu;
        NewGameMenu *newGameMenu;
        Leaderboard *leaderboard;
        GameOverMenu *gameOverMenu;
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

        /* ------ SAVE GAME ----- */
        json toJson() const;
        void fromJson(const json& j);
        void saveGame(const std::string& filename) const;
        void loadGame(const std::string& filename);

        /* ---- CREATE ----- */
        void createPhase(short int phaseNumber);
        void create_menus();
        void createPlayers(const vector<string> &playerNames);
        void setPlayerNames(const vector<string> &names);
        void saveScoretoLeaderboard();
        void cleanupAfterGame();
        void resetCamera();
};

