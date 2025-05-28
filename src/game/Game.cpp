#include "../../include/game/Game.h"
#include "../../include/entities/Player.h"

Game::Game():
player1(nullptr), player2(nullptr), pGM(nullptr), entes_list(), it()
{
    entes_list.clear();
    pGM = GraphicsManager::getInstance();
    player1 = new Player(200, 100, 50.f, 10, 1, 4, 1, 60.f);
    player2 = new Player(100, 100, 50.f, 10, 1, 4, 2, 60.f);
    create_entes();
    

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
    delete pGM;
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
        pGM->operator++();
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
            if(*it){
                (*it)->execute();
            }
            else 
                cout << "Not executed." << endl;
        }
        player1->execute(); // Atualiza e desenha
        player2->execute();
        
        pGM->show();
    }
}

void Game::create_entes(){
    for(int i = 0; i < 2; i++){
        Enemy* e = nullptr;
        e = new Enemy((float) (i*150) , (float) ((i+1)*150),  60.f , 5, 0.f , 2);
        if(e){
            e->addPlayer(player1);
            e->addPlayer(player2);
            entes_list.push_back(e);
            cout << "Players added to enemy" << endl;
        }else 
            cout << "Enemy not allocated." << endl;
    }
    for(int i = 0; i < 2; i++){
        Obstacle* o = nullptr;
        o = new Obstacle(false, (i+2) * 100.f, 520.f);
        if(o){
            entes_list.push_back(o);
            cout << "Obstacle created" << endl;
        }else 
            cout << "Obstacle not allocated." << endl;
    }

}

