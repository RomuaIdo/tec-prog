#include "../../include/menu/Leaderboard.h"
#include "../../include/game/Game.h"
#include "../../include/graphicalelements/Button.h"
#include <filesystem>
namespace fs = std::filesystem;

Leaderboard::Leaderboard(Game *game) : Menu(game) {
  setBackground("assets/textures/menu_background.png");

  if (!font.loadFromFile("assets/fonts/Minecraft.ttf")) {
    cerr << "Failed to load leaderboard font!" << endl;
  }

  Vector2f viewSize = pGM->getWindow()->getView().getSize();
  Vector2f center(viewSize.x / 2, viewSize.y / 2);

  MouseSubject &mouseSubject = pGame->getMouseSubject();
  backButton = new Button("assets/fonts/Minecraft.ttf", "Back",
                          "assets/textures/button.png",
                          "assets/textures/button_hovered.png", &mouseSubject,
                          24, Vector2f(center.x, center.y + 100.f));
  backButton->activate();
  addButton("back", backButton);

  loadScores();
}

Leaderboard::~Leaderboard() {}

void Leaderboard::execute() {
  draw();
  backButton->execute();

  if (backButton->wasClicked()) {
    pGame->setGameState(GameState::MAIN_MENU);
  }

  drawScores();
}

void Leaderboard::loadScores() {
  scores.clear();

  auto loadFile = [&](const string &filename, bool isSingle) {
    if (!fs::exists(filename) || fs::file_size(filename) == 0) {
      try {
        ofstream temp(filename, ios::app);
        temp.close();
        cerr << "Created empty: " << filename << endl;
      } catch (const exception &e) {
        cerr << "Error creating file: " << e.what() << endl;
      }
      return;
    }

    try {
      ifstream file(filename);
      if (!file.is_open()) {
        cerr << "Failed to open: " << filename << endl;
        return;
      }

      string line;
      int pos = 1;
      while (getline(file, line) && pos <= 10) {
        if (line.empty())
          continue;

        istringstream iss(line);
        if (isSingle) {
          string name;
          int score;
          if (iss >> name >> score) {
            scores.push_back(ScoreEntry(pos, name, "", score, true));
            pos++;
          }
        } else {
          string name1, name2;
          int score;
          if (iss >> name1 >> name2 >> score) {
            scores.push_back(ScoreEntry(pos, name1, name2, score, false));
            pos++;
          }
        }
      }
    } catch (const exception &e) {
      cerr << "Error reading " << filename << ": " << e.what() << endl;
    }
  };

  loadFile("leaderboards/leaderboard_single.txt", true);
  loadFile("leaderboards/leaderboard_multi.txt", false);
}


void Leaderboard::drawScores() {
    Vector2f viewSize = pGM->getWindow()->getView().getSize();
    float startY = 100.f;
    float singleX = viewSize.x * 0.3f;
    float multiX = viewSize.x * 0.7f;

    Text title("LEADERBOARD", font, 36);
    title.setFillColor(::Color::White);
    title.setPosition(viewSize.x / 2 - title.getLocalBounds().width / 2, 30.f);
    pGM->draw(&title);

    Text singleHeader("SINGLE PLAYER", font, 28);
    singleHeader.setFillColor(Color::Yellow);
    singleHeader.setPosition(singleX - singleHeader.getLocalBounds().width / 2, startY);
    pGM->draw(&singleHeader);

    Text multiHeader("2 PLAYERS", font, 28);
    multiHeader.setFillColor(::Color::Yellow);
    multiHeader.setPosition(multiX - multiHeader.getLocalBounds().width / 2, startY);
    pGM->draw(&multiHeader);

    vector<ScoreEntry> singleEntries;
    vector<ScoreEntry> multiEntries;
    
    for (vector<ScoreEntry>::iterator it = scores.begin(); it != scores.end(); ++it) {
        if (it->isSinglePlayer) {
            singleEntries.push_back(*it);
        } else {
            multiEntries.push_back(*it);
        }
    }

    float currentYSingle = startY + 50.f;
    for (vector<ScoreEntry>::iterator it = singleEntries.begin(); it != singleEntries.end(); ++it) {
        Text entryText;
        entryText.setFont(font);
        entryText.setCharacterSize(24);
        entryText.setFillColor(Color::White);

        ostringstream oss;
        oss << it->position << ". " << it->player1 << " - " << it->score;
        entryText.setString(oss.str());
        entryText.setPosition(singleX - entryText.getLocalBounds().width / 2, currentYSingle);
        pGM->draw(&entryText);
        currentYSingle += 40.f;
    }

    float currentYMulti = startY + 50.f;
    for (vector<ScoreEntry>::iterator it = multiEntries.begin(); it != multiEntries.end(); ++it) {
        Text entryText;
        entryText.setFont(font);
        entryText.setCharacterSize(24);
        entryText.setFillColor(Color::White);

        ostringstream oss;
        oss << it->position << ". " << it->player1 << " & " << it->player2 << " - " << it->score;
        entryText.setString(oss.str());
        entryText.setPosition(multiX - entryText.getLocalBounds().width / 2, currentYMulti);
        pGM->draw(&entryText);
        currentYMulti += 40.f;
    }
}
