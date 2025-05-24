#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../include/entidades/EntidadeQuadrado.h"
#include "../include/gerenciadores/Gerenciador_Grafico.h"

#define HEIGHT = 800
#define 
int 

int main() {
    RenderWindow window(VideoMode(800, 600), "SFML");
    window.setFramerateLimit(60);
    
    // Configura o Gerenciador Gráfico
    Gerenciador_Grafico* gg = Gerenciador_Grafico::getInstancia();
    gg->setJanela(&window);
    
    EntidadeQuadrado quadrado(100, 100, 50,1);
    EntidadeQuadrado quadrado2(100, 100, 40,2);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
               (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
            quadrado.handleEvent(event); // Trata eventos específicos
            quadrado2.handleEvent(event);
        }
        
        gg->limpar();
        quadrado.executar(); // Atualiza e desenha
        quadrado2.executar();
        gg->exibir();
    }
    
    return 0;
}
