#ifndef PLAYER_H
#define PLAYER_H
#include "Entidade.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Player : public Sprite, Entidade {
private:
    const float movimentSpeed;
    const float grid_size;
    RectangleShape shape;
    Vector2f velocity;
    Gerenciador_Grafico* gg;
    int player_num;
    int health;
    const float vel_max;
    Vector2f gravity;
    Vector2f friction;
    float friction_coef;

public:
    Player(float x, float y, Gerenciador_Grafico* pGG, int p_num);
    ~Player();
    void handleEvent(const sf::Event& event);
    void executar() ;

    void move();
    void colide();
    sf::RectangleShape getShape();
};
#endif
