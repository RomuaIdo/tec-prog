#ifndef HONEY_H
#define HONEY_H
#include "../characters/Enemy.h"
#include "../characters/Player.h"
#include "Obstacle.h"

class Honey : public Obstacle {

    private:
        /* ------ STATUS ------- */
        float viscosity; // Honey viscosity, how much it slows down the player

    public:
        Honey(float x, float y, bool harm = false);
        ~Honey();

        /* ---- OWN FUNCTIONS ---- */
        void obstacleAction(Entity* e);
        void execute();
        void collide(Entity *e);

        /* ----- GETS & SETS ----- */
        void setViscosity(float v);
        float getViscosity() const;
};

#endif
