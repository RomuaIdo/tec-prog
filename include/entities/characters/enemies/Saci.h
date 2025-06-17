#ifndef SACI_H
#define SACI_H
#include "../Enemy.h"
#include <list>

class Saci : public Enemy {

    private:
        /* ---- TELEPORT ---- */
        bool far;
        float lastPositionTime;
        float teleportTime;
        Vector2f lastPosition;
        float minDistance;
        bool tooClose;

    public:
        Saci(float x, float y, const float acel = 5.f, int life = 5, float coef = 0.5, int s = 1);
        ~Saci();

        /* ---- OWN FUNCTIONS ---- */
        void execute();
        void move();
        void collide(Entity *e);
        void teleport(Vector2f pos);
        Vector2f getPlayerLastPosition();

        /* ------- PLAYER -------- */

        void attack(Player *p);
};

#endif
