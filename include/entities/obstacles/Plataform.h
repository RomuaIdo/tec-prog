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
        int plataformType; // 0 for cloud1, 1 for cloud2
        float regenClock;

        Vector2f originalPosition;

        
        void setState();
        void move();

    public:
        Plataform();
        Plataform(float x, float y, bool harm = false, int n = 0);
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

        /* -------- SAVE -------- */
        json toJson() const;
        void fromJson(const json& j);
        std::string getType() const;

        /* ----- GETS & SETS ----- */
        bool getIsActive() const;
        void setIsActive(bool active);
};


#endif
