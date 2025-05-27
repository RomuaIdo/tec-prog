#include "../../include/jogo/Jogo.h"


Jogo::Jogo() {
    gerenciadorGrafico = Gerenciador_Grafico::getInstancia();
    jogador1 = new Jogador(100, 100, 50, 1, gerenciadorGrafico);
    jogador2 = new Jogador(200, 200, 55, 2, gerenciadorGrafico);
    executar();
}

Jogo::~Jogo() {
    delete jogador1;
    delete jogador2;
}

void Jogo::executar() {
    RenderWindow window(VideoMode(800, 600), "Jogo de Teste");
    window.setFramerateLimit(60);
    gerenciadorGrafico->setJanela(&window);
    RenderWindow* janela = gerenciadorGrafico->getJanela();

    while (gerenciadorGrafico->janelaAberta()) {
        Event event;
        while (janela->pollEvent(event)) {
            if (event.type == Event::Closed || 
                (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                janela->close();
            }
            jogador1->handleEvent(event); // Trata eventos específicos
            jogador2->handleEvent(event);
        }
        
        gerenciadorGrafico->limpar();
        jogador1->executar(); // Atualiza e desenha
        jogador2->executar();
        jogador1->fixCollisionWithWindow(jogador1->getShape(), *janela);
        jogador2->fixCollisionWithWindow(jogador2->getShape(), *janela);
        
        gerenciadorGrafico->exibir();
    }
}
