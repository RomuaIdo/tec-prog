#include "../../include/menu/Leaderboard.h"
#include "../../include/game/Game.h"
#include "../../include/graphicalelements/Button.h"

Leaderboard::Leaderboard(Game* game) : Menu(game) {
    setBackground("assets/textures/menu_background.png");
    
    if (!font.loadFromFile("assets/fonts/Minecraft.ttf")) {
        cerr << "Failed to load leaderboard font!" << endl;
    }

    Vector2f viewSize = pGM->getWindow()->getView().getSize();
    Vector2f center(viewSize.x / 2, viewSize.y / 2);
    
    MouseSubject& mouseSubject = pGame->getMouseSubject();
    backButton = new Button("assets/fonts/Minecraft.ttf", "Back",
                           "assets/textures/button.png",
                           "assets/textures/button_hovered.png",
                           &mouseSubject, 24, Vector2f(center.x, viewSize.y - 100));
    backButton->activate();
    addButton("back", backButton);

    loadScores();
}

Leaderboard::~Leaderboard() {
}

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

    // Carregar singleplayer
    ifstream singleFile("leaderboard_single.txt");
    if (singleFile.is_open()) {
        string line;
        int pos = 1;
        while (getline(singleFile, line) && pos <= 10) {
            istringstream iss(line);
            string name;
            int score;
            if (iss >> name >> score) {
                scores.push_back(ScoreEntry(pos, name, "", score, true));
                pos++;
            }
        }
        singleFile.close();
    } else {
        cerr << "Could not open leaderboard_single.txt" << endl;
    }

    // Carregar multiplayer
    ifstream multiFile("leaderboard_multi.txt");
    if (multiFile.is_open()) {
        string line;
        int pos = 1;
        while (getline(multiFile, line) && pos <= 10) {
            istringstream iss(line);
            string name1, name2;
            int score;
            if (iss >> name1 >> name2 >> score) {
                scores.push_back(ScoreEntry(pos, name1, name2, score, false));
                pos++;
            }
        }
        multiFile.close();
    } else {
        cerr << "Could not open leaderboard_multi.txt" << endl;
    }
}

void Leaderboard::drawScores() {
    Vector2f viewSize = pGM->getWindow()->getView().getSize();
    float startY = 100.f;
    float singleX = viewSize.x * 0.3f;
    float multiX = viewSize.x * 0.7f;

    Text title("LEADERBOARD", font, 36);
    title.setFillColor(::Color::White); // Corrigido
    title.setPosition(viewSize.x / 2 - title.getLocalBounds().width / 2, 30.f);
    pGM->draw(&title);

    Text singleHeader("SINGLE PLAYER", font, 28);
    singleHeader.setFillColor(Color::Yellow); // Corrigido
    singleHeader.setPosition(singleX - singleHeader.getLocalBounds().width / 2, startY);
    pGM->draw(&singleHeader);

    Text multiHeader("2 PLAYERS", font, 28);
    multiHeader.setFillColor(::Color::Yellow); // Corrigido
    multiHeader.setPosition(multiX - multiHeader.getLocalBounds().width / 2, startY);
    pGM->draw(&multiHeader);

    float currentY = startY + 50.f;
    for (vector<ScoreEntry>::iterator it = scores.begin(); it != scores.end(); ++it) {
        Text entryText;
        entryText.setFont(font);
        entryText.setCharacterSize(24);
        entryText.setFillColor(Color::White);  

        ostringstream oss;
        if (it->isSinglePlayer) {
            oss << it->position << ". " << it->player1 << " - " << it->score;
            entryText.setString(oss.str());
            entryText.setPosition(singleX - entryText.getLocalBounds().width / 2, currentY);
        } else {
            oss << it->position << ". " << it->player1 << " & " << it->player2 << " - " << it->score;
            entryText.setString(oss.str());
            entryText.setPosition(multiX - entryText.getLocalBounds().width / 2, currentY);
        }
        
        pGM->draw(&entryText);
        currentY += 40.f;
    }
}
