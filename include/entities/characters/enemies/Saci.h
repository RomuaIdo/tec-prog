#ifndef SACI_H
#define SACI_H
#include "../Enemy.h"

class Saci : public Enemy {

    private:
        /* ----- CLOCKS ----- */
        float jumpClock;
        float lastPositionClock;
        float teleportClock;

        /* ----- STATUS ----- */
        Vector2f lastPosition;

    public:

        /* ---- CONSTRUCTORS ---- */
        Saci(float x, float y, const float acel = 5.f, int life = 5, int s = 1);
        ~Saci();

        /* ---- OWN FUNCTIONS ---- */
        void execute();
        void move();
        void updateClocks();

        /* ------- TELEPORT -------- */
        void teleport(Vector2f pos);
        Vector2f getPlayerLastPosition();

        /* ------- PLAYER -------- */
        void attack(Player *p);
};

#endif
