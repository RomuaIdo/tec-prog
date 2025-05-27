#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Player : public Sprite, Entity {
private:
    const float movimentSpeed;
    const float grid_size;
    RectangleShape shape;
    Vector2f velocity;
    GraphicalManager* gg;
    int player_num;
    int health;
    const float vel_max;
    Vector2f gravity;
    Vector2f friction;
    float friction_coef;

public:
    Player(float x, float y, GraphicalManager* pGG, int p_num);
    ~Player();
    void handleEvent(const sf::Event& event);
    void execute() ;

    void move();
    void colide();
    sf::RectangleShape getShape();
};
#endif
