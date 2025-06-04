#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
#include "../Projectile.h"
#include <SFML/Graphics.hpp>
#include <list>
using namespace sf;
using namespace std;

class Player : public Character {
    private:
        /* ------ STATUS ------- */
        int player_num;
        int score;
        const float vel_max;
        bool faced_right;

        /* -------- GUN -------- */
        list<Projectile*> projectiles_list;
        float shoot_delay;

    public:
        Player(float x, float y, const float acel, int life = 5, float coef = 0.5, int s = 1, int p_num = 1, const float v_max = 50.f);
        ~Player();

        /* --- OWN FUNCTIONS --- */
        void execute();
        void move();
        void handlePlayer1Controls(float dt, float jumpForce);
        void handlePlayer2Controls(float dt, float jumpForce);
        void applyFriction(float dt);
        void collide();
        
        void loseHealth(int damage);

        /* --- GUN FUNCTIONS --- */
        void shoot();
        void addProjectile(Projectile* p);
        void reload();
        void shootProjectiles();
        
        /* ---- GETS & SETS ---- */
        int getHealth();

};

#endif
