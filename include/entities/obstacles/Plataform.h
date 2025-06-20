#ifndef PLATAFORM_H
#define PLATAFORM_H
#include "Obstacle.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Plataform : public Obstacle{

    private:
        /* ------ STATUS ------- */
        int plataformType; // 0 for cloud1, 1 for cloud2
        bool isActive;

    public:
        Plataform();
        Plataform(float x, float y, bool harm = false);
        ~Plataform();
        /* ------ TEXTURES ------ */
        Texture cloud1;
        Texture cloud1active;

        Texture cloud2;
        Texture cloud2active;

        /* ---- OWN FUNCTIONS ---- */
        void collide(Entity* other) override;
        void obstacleAction(Entity* e);
        void execute() override;

        /* ----- GETS & SETS ----- */
        bool getIsActive() const;
        void setIsActive(bool active);
};


#endif
