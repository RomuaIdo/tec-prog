#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../include/entidades/EntidadeQuadrado.h"
#include "../include/gerenciadores/Gerenciador_Grafico.h"


int main() {
    RenderWindow window(VideoMode(800, 600), "SFML");
    window.setFramerateLimit(60);
    
    // Configura o Gerenciador Gráfico
    Gerenciador_Grafico* gg = Gerenciador_Grafico::getInstancia();
    gg->setJanela(&window);
    
    EntidadeQuadrado quadrado(100, 100, 50);
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
               (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
            quadrado.handleEvent(event); // Trata eventos específicos
        }
        
        gg->limpar();
        quadrado.executar(); // Atualiza e desenha
        gg->exibir();
    }
    
    return 0;
}
