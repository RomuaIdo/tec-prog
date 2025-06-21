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
        Honey();
        Honey(float x, float y, bool harm = false);
        ~Honey();

        /* ---- OWN FUNCTIONS ---- */
        void obstacleAction(Entity* e);
        void execute();
        void collide(Entity *e);

        /* -------- SAVE -------- */
        json toJson() const;
        void fromJson(const json& j);
        std::string getType() const;

        /* ----- GETS & SETS ----- */
        void setViscosity(float v);
        float getViscosity() const;
};

#endif
