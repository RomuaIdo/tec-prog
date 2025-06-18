#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
#include <SFML/Graphics.hpp>
#include <list>
using namespace sf;
using namespace std;

class Projectile; // Forward declaration to avoid circular dependency

class Player : public Character {
    private:
        /* ------ CLOCKS ------- */
        float shootClock;

        /* ------ STATUS ------- */
        int player_num;
        int score;
        const float vel_max;
        
        /* -------- GUN -------- */
        list<Projectile*> projectiles_list;

    public:
        Player(float x, float y, const float acel, int life = 5, int s = 1, int p_num = 1, const float v_max = 50.f);
        ~Player();

        /* --- OWN FUNCTIONS --- */
        void execute();
        void move();
        void collide(Entity* e);
        void updateClocks();

        void takeDamage(int damage = 1);

        /* --- INPUT HANDLING --- */
        void handlePlayer1Controls(float dt, float jumpForce);
        void handlePlayer2Controls(float dt, float jumpForce);

        /* --- GUN FUNCTIONS --- */
        void shoot();
        void addProjectile(Projectile* p);
        void shootProjectiles();
        
        /* ---- GETS & SETS ---- */
        int getHealth();
        

};

#endif
