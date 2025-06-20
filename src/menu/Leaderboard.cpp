#include "../../include/menu/Leaderboard.h"
#include "../../include/game/Game.h"
#include "../../include/graphicalelements/Button.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>

Leaderboard::Leaderboard(Game *game) : Menu(game) {
    setBackground("assets/textures/menu_background.png");

    try {
        if (!font.loadFromFile("assets/fonts/Minecraft.ttf")) {
            throw runtime_error("Failed to load leaderboard font: assets/fonts/Minecraft.ttf");
        }
    }
    catch (const exception& e) {
        cerr << "EXCEÇÃO: " << e.what() << endl;
        if (!font.loadFromFile("assets/fonts/fallback_font.ttf")) {
            cerr << "Falha ao carregar fonte alternativa também!" << endl;
        }
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

    try {
        loadScores();
    }
    catch (const exception& e) {
        cerr << "EXCEÇÃO ao carregar scores: " << e.what() << endl;
    }
}

Leaderboard::~Leaderboard() {}

void Leaderboard::execute() {
    draw();
    backButton->execute();

    if (backButton->wasClicked()) {
        pGame->setGameState(GameState::MAIN_MENU);
    }

    try {
        drawScores();
    }
    catch (const exception& e) {
        cerr << "EXCEÇÃO ao desenhar scores: " << e.what() << endl;
        
        Text errorText("Erro ao carregar leaderboard", font, 24);
        errorText.setFillColor(Color::Red);
        errorText.setPosition(100, 100);
        pGM->draw(&errorText);
    }
}

void Leaderboard::loadFile(const string& filename, bool isSingle) {
    try {
        ifstream file(filename.c_str());
        if (!file.is_open()) {
            throw runtime_error("Não foi possível abrir o arquivo: " + filename);
        }

        if (file.peek() == ifstream::traits_type::eof()) {
            return; // Arquivo vazio
        }

        string line;
        int pos = 1;
        while (getline(file, line) && pos <= 10) {
            if (line.empty()) continue;

            istringstream iss(line);
            if (isSingle) {
                string name;
                int score;
                if (iss >> name >> score) {
                    scores.push_back(ScoreEntry(pos, name, "", score, true));
                    pos++;
                } else {
                    throw runtime_error("Formato inválido no arquivo: " + filename);
                }
            } else {
                string name1, name2;
                int score;
                if (iss >> name1 >> name2 >> score) {
                    scores.push_back(ScoreEntry(pos, name1, name2, score, false));
                    pos++;
                } else {
                    throw runtime_error("Formato inválido no arquivo: " + filename);
                }
            }
        }
        file.close();
    }
    catch (const ifstream::failure& e) {
        throw runtime_error("Erro de I/O: " + string(e.what()) + " - " + filename);
    }
    catch (const exception& e) {
        try {
            ofstream createFile(filename.c_str());
            if (!createFile) {
                throw runtime_error("Falha ao criar arquivo: " + filename);
            }
            createFile.close();
        }
        catch (const exception& createEx) {
            throw runtime_error("Falha ao criar arquivo: " + filename + " - " + createEx.what());
        }
    }
}

void Leaderboard::loadScores() {
    scores.clear();
    
    try {
        loadFile("leaderboards/leaderboard_single.txt", true);
    }
    catch (const exception& e) {
        cerr << "EXCEÇÃO (single): " << e.what() << endl;
    }
    
    try {
        loadFile("leaderboards/leaderboard_multi.txt", false);
    }
    catch (const exception& e) {
        cerr << "EXCEÇÃO (multi): " << e.what() << endl;
    }
}

void Leaderboard::drawScores() {
    if (scores.empty()) {
        throw runtime_error("Nenhum score disponível");
    }

    Vector2f viewSize = pGM->getWindow()->getView().getSize();
    float startY = 100.f;
    float singleX = viewSize.x * 0.3f;
    float multiX = viewSize.x * 0.7f;

    Text title("LEADERBOARD", font, 36);
    title.setFillColor(Color::White);
    title.setPosition(viewSize.x / 2 - title.getLocalBounds().width / 2, 30.f);
    pGM->draw(&title);

    Text singleHeader("SINGLE PLAYER", font, 28);
    singleHeader.setFillColor(Color::Yellow);
    singleHeader.setPosition(singleX - singleHeader.getLocalBounds().width / 2, startY);
    pGM->draw(&singleHeader);

    Text multiHeader("2 PLAYERS", font, 28);
    multiHeader.setFillColor(Color::Yellow);
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
        ostringstream oss;
        oss << it->position << ". " << it->player1 << " - " << it->score;
        
        Text entryText(oss.str(), font, 24);
        entryText.setFillColor(Color::White);
        entryText.setPosition(singleX - entryText.getLocalBounds().width / 2, currentYSingle);
        pGM->draw(&entryText);
        currentYSingle += 40.f;
    }

    float currentYMulti = startY + 50.f;
    for (vector<ScoreEntry>::iterator it = multiEntries.begin(); it != multiEntries.end(); ++it) {
        ostringstream oss;
        oss << it->position << ". " << it->player1 << " & " << it->player2 << " - " << it->score;
        
        Text entryText(oss.str(), font, 24);
        entryText.setFillColor(Color::White);
        entryText.setPosition(multiX - entryText.getLocalBounds().width / 2, currentYMulti);
        pGM->draw(&entryText);
        currentYMulti += 40.f;
    }
}
