#ifndef JOGADOR_H
#define ENTIDADE_QUADRADO_H
#include "Entidade.h"
#include <SFML/Graphics.hpp>

class Jogador : public Entidade{
private:
    RectangleShape shape;
    int player_num;
    Gerenciador_Grafico* pGG;

public:
    Jogador(float x, float y, float size, int p_num, Gerenciador_Grafico* pgg);
    void handleEvent(const sf::Event& event);
    void executar() override;
    void desenhar() override;
    void atualizar() override;
    void movePlayer();
    void colidir();
    RectangleShape* getShape();
    Drawable& getDrawable() override;
    void fixCollisionWithWindow(Shape* sprite, const RenderWindow& window);
};

#endif
