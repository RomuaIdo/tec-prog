#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../include/entidades/EntidadeQuadrado.h"
#include "../include/gerenciadores/Gerenciador_Grafico.h"

unsigned int const HEIGHT = 600;
unsigned int const WIDTH  = 800;


int main() {
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "SFML");
    window.setFramerateLimit(60);
    
    // Configura o Gerenciador Gráfico
    Gerenciador_Grafico* gg = Gerenciador_Grafico::getInstancia();
    gg->setJanela(&window);
    

    EntidadeQuadrado* quadrado;
    EntidadeQuadrado* quadrado2;
    quadrado  = new EntidadeQuadrado(100,100, 50, 1);
    quadrado2 = new EntidadeQuadrado(200,200, 55, 2);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
               (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
            quadrado->handleEvent(event); // Trata eventos específicos
            quadrado2->handleEvent(event);
        }
        
        gg->limpar();
        quadrado->executar(); // Atualiza e desenha
        quadrado2->executar();
        quadrado->fixCollisionWithWindow(quadrado->getShape() , window);
        quadrado2->fixCollisionWithWindow(quadrado2->getShape() , window);

        gg->exibir();
    }
    
    return 0;
}
