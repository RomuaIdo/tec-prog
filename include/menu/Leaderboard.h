// Leaderboard.h
#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <vector>

class Leaderboard : public Menu {
public:
  class ScoreEntry {
  public:
    ScoreEntry(int pos, const std::string &p1, const std::string &p2, int sc,
               bool single)
        : position(pos), player1(p1), player2(p2), score(sc),
          isSinglePlayer(single) {}

    // Tornar todos os membros públicos
    int position;
    std::string player1;
    std::string player2;
    int score;
    bool isSinglePlayer;
  };

  Leaderboard(Game *game);
  virtual ~Leaderboard();

  void execute();
  void reloadScores();
  void loadScores();
  void drawScores();
  
private:
  void loadFile(const std::string &filename, bool isSingle); // Declaração corrigida

  bool scoresLoaded;
  sf::Font font;
  std::vector<ScoreEntry> scores;
  Button *backButton;
};

#endif
