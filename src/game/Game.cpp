#include "../../include/game/Game.h"
#include "../../include/entities/Player.h"

Game::Game():
pGM(nullptr), entes_list(), it(), player1(nullptr), player2(nullptr){
    entes_list.clear();
    pGM = GraphicsManager::getInstance();
    player1 = new Player(50, 200, 100, 50.f, 10, 1, 4, 1, 60.f);
    player2 = new Player(50, 100, 100, 50.f, 10, 1, 4, 2, 60.f);
    create_entes();
    
    // for (auto& ent : entes_list) {
    //     Enemy* e = dynamic_cast<Enemy*>(ent);
    //     if (e) {
    //         e->addPlayer(player1);
    //         e->addPlayer(player2);
    //         std::cout << "Players added to enemy\n";
    //     }
    // }

    execute();
}

Game::~Game() {

    list<Ente*>::iterator ite;
    for( ite = entes_list.begin(); ite != entes_list.end(); ite++){
        if(*ite){
            cout << "Deleting entity..." << endl;
            delete (*ite);
            (*ite) = nullptr;
        }
    }
    cout << "Deletado com sucesso" << endl;
    entes_list.clear();
    pGM = nullptr;
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
        e = new Enemy(30, (float) (i*150) , (float) ((i+1)*150),  60.f , 5, 0.f , 2);
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
        o = new Obstacle(false, 60, (i+2) * 100.f, 300.f);
        if(o){
            entes_list.push_back(o);
            cout << "Obstacle created" << endl;
        }else 
            cout << "Obstacle not allocated." << endl;
    }

}

