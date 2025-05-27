#include "../../include/game/Game.h"
#include "../../include/entities/Player.h"

Game::Game() {
    pGM = GraphicsManager::getInstance();
    player1 = new Player(100, 100, pGM, 1);
    player2 = new Player(200, 200, pGM, 2);
    execute();
}

Game::~Game() {
    delete player1;
    delete player2;
}

void Game::execute() {
    RenderWindow window(VideoMode(800, 600), "Good Game");
    window.setFramerateLimit(60);
    pGM->setWindow(&window);
    RenderWindow* pWindow = pGM->getWindow();

    while (pGM->openWindow()) {
        Event event;
        while (pWindow->pollEvent(event)) {
            if (event.type == Event::Closed || 
                (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
            player1->handleEvent(event); // Trata eventos específicos
            player2->handleEvent(event);
        }
        
        pGM->clean();

        player1->execute(); // Atualiza e desenha
        player2->execute();
        
        pGM->show();
    }
}
