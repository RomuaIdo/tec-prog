#ifndef ENTIDADE_QUADRADO_H
#define ENTIDADE_QUADRADO_H
#include "Entidade.h"
#include <SFML/Graphics.hpp>

class EntidadeQuadrado : public Entidade, public Sprite {
private:
    sf::RectangleShape shape;
    int player_num;

public:
    EntidadeQuadrado(float x, float y, float size, int p_num);
    void handleEvent(const sf::Event& event);
    void executar() override;
    void desenhar() override;
    void atualizar() override;
    void movePlayer();
    void colidir();
    sf::RectangleShape* getShape();
    void fixCollisionWithWindow(sf::Shape* sprite, const sf::RenderWindow& window);
};

#endif
