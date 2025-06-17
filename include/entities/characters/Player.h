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
        /* ------ STATUS ------- */
        int player_num;
        int score;
        const float vel_max;
        float damageClock;
        float damageCooldown;
        
        /* -------- GUN -------- */
        list<Projectile*> projectiles_list;
        float shoot_delay;

    public:
        Player(float x, float y, const float acel, int life = 5, float coef = 0.5, int s = 1, int p_num = 1, const float v_max = 50.f);
        ~Player();

        /* --- OWN FUNCTIONS --- */
        void execute();
        void move();
        void collide(Entity* e);
        void handlePlayer1Controls(float dt, float jumpForce);
        void handlePlayer2Controls(float dt, float jumpForce);
        void applyFriction(float dt);

        /* --- GUN FUNCTIONS --- */
        void shoot();
        void addProjectile(Projectile* p);
        void reload();
        void shootProjectiles();
        
        /* ---- GETS & SETS ---- */
        int getHealth();
        float getDamageClock();
        void increaseDamageClock();
        void resetDamageClock();
        float getDamageCooldown();
        void setDamageCooldown(float cooldown);

};

#endif
