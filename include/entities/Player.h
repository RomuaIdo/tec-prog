#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Player : public Character {
private:

    int player_num;
    int score;
    const float vel_max;

public:
    Player(float x, float y, const float movSpeed, int life = 5, float coef = 0.5, int s = 1, int p_num = 1, const float v_max = 50.f);
    ~Player();
    void execute() ;
    void loseHealth(int damage);
    int getHealth();
    void move();
};
#endif
