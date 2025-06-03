#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
#include "../Projectile.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Player : public Character {
private:
    list<Projectile*> projectiles_list;
    int player_num;
    int score;
    const float vel_max;
    float shoot_delay;

public:
    Player(float x, float y, const float acel, int life = 5, float coef = 0.5, int s = 1, int p_num = 1, const float v_max = 50.f);
    ~Player();
    void execute() ;
    void loseHealth(int damage);
    int getHealth();
    void move();
    void collide();
    void shoot();
    void addProjectile(Projectile* p);
    void reload();

};

#endif
