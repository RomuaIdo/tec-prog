#ifndef HONEY_H
#define HONEY_H
#include "Obstacle.h"
#include "../characters/Character.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Honey : public Obstacle{

    private:
        /* ------ STATUS ------- */
        float viscosity; // Honey viscosity, how much it slows down the player

    public:
        Honey(float x, float y, bool harm = false);
        ~Honey();

        /* ---- OWN FUNCTIONS ---- */
        void obstacleAction(Entity* e);
        void execute();
        void collide(Entity* e);

        /* ----- GETS & SETS ----- */
        void setViscosity(float v);
        float getViscosity() const;

};


#endif
