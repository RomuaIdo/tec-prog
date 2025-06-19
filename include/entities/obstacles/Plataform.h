#ifndef PLATAFORM_H
#define PLATAFORM_H
#include "Obstacle.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Plataform : public Obstacle{

    private:
        /* ------ STATUS ------- */

        bool isActive;

    public:
        Plataform();
        Plataform(float x, float y, bool harm = false);
        ~Plataform();
        
        static Texture cloud1;
        static Texture cloud1active;

        static Texture cloud2;
        static Texture cloud2active;

        /* ---- OWN FUNCTIONS ---- */
        void collide(Entity* other) override;
        void obstacleAction(Entity* e);
        void execute() override;

        /* ----- GETS & SETS ----- */
        bool getIsActive() const;
        void setIsActive(bool active);
};


#endif
