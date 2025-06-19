#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <sstream>

class Leaderboard : public Menu {
public:
    Leaderboard(Game* game);
    virtual ~Leaderboard();

    void execute();
    void loadScores();
    void drawScores();
    
private:
    class ScoreEntry {
    public:
        int position;
        std::string player1;
        std::string player2;
        int score;
        bool isSinglePlayer;
        
        ScoreEntry(int pos, const std::string& p1, const std::string& p2, int sc, bool single)
            : position(pos), player1(p1), player2(p2), score(sc), isSinglePlayer(single) {}
    };

    sf::Font font;
    std::vector<ScoreEntry> scores;
    Button* backButton;
};

#endif
