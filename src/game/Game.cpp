#include "../../include/game/Game.h"
#include "../../include/entities/Player.h"

Game::Game():
player1(nullptr), player2(nullptr), pGM(nullptr), entes_list(), it()
{
    entes_list.clear();
    create_entes();
    pGM = GraphicsManager::getInstance();
    player1 = new Player(50, 200, 100, 50.f, 10, 0.5, 4, 1, 60.f);
    player2 = new Player(50, 100, 100, 50.f, 10, 0.5, 4, 2, 60.f);
    for (auto& ent : entes_list) {
    Enemy* e = dynamic_cast<Enemy*>(ent);
    if (e) {
        e->addPlayer(player1);
        e->addPlayer(player2);
        std::cout << "Players added to enemy\n";
    }
}

    execute();
}

Game::~Game() {

    for( it = entes_list.begin(); it != entes_list.end(); it++){
        if(*it){
            delete (*it);
            (*it) = NULL;
        }
    }
    entes_list.clear();
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
        pGM->setClock();
        while (pWindow->pollEvent(event)) {
            if (event.type == Event::Closed || 
                (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
            player1->handleEvent(event); // Trata eventos específicos
            player2->handleEvent(event);
        }
        
        pGM->clean();
        for(it = entes_list.begin(); it != entes_list.end(); it++){
            if(*it)
                (*it)->execute();
            else 
                cout << "Não executado" << endl;
        }
        player1->execute(); // Atualiza e desenha
        player2->execute();
        
        pGM->show();
    }
}

void Game::create_entes(){
    for(int i = 0; i < 2; i++){
        Enemy* e = nullptr;
        e = new Enemy(30, (float) (i*150) , (float) ((i+1)*150), 30.f, 5, 0.5 , 2);
        if(e){
            // e->addPlayer(player2);
            entes_list.push_back(e);
        }else 
            cout << "Enemy not allocated." << endl;
    }

}

