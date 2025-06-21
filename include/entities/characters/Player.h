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
        string name;        
        float jumpForce;

        /* -------- GUN -------- */
        list<Projectile*> projectiles_list;

    public:
        Player(float x, float y, const float acel, const string Name, int life = 5, int s = 1, int p_num = 1);
        ~Player();

        /* --- OWN FUNCTIONS --- */
        void execute();
        void move();
        void collide(Entity* e);
        void updateClocks();

        void increaseScore(int points = 10);
        void takeDamage(int damage = 1, int direction = 1);

        /* -------- SAVE -------- */
        json toJson() const;
        void fromJson(const json& j);
        std::string getType() const;

        /* --- INPUT HANDLING --- */
        void handlePlayer1Controls(float dt);
        void handlePlayer2Controls(float dt);

        /* --- GUN FUNCTIONS --- */
        void shoot();
        void addProjectile(Projectile* p);
        void shootProjectiles();
        
        /* ---- GETS & SETS ---- */
        int getHealth() const;
        int getScore() const;
        void setJumpForce(float jpForce = PLAYERJUMPFORCE);

};

#endif
