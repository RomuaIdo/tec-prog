#ifndef ENTIDADE_QUADRADO_H
#define ENTIDADE_QUADRADO_H
#include "Entidade.h"
#include <SFML/Graphics.hpp>

class EntidadeQuadrado : public Entidade {
private:
    sf::RectangleShape shape;

public:
    EntidadeQuadrado(float x, float y, float size);
    void handleEvent(const sf::Event& event);
    
    void executar() override;
    void desenhar() override;
    void atualizar() override;
    void colidir(Entidade* outra) override;
};

#endif
