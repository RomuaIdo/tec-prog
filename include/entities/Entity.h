#ifndef ENTITY_H
#define ENTITY_H
#include "Ente.h"
#include <SFML/Graphics.hpp>
using namespace sf;


/* =============================================================== */
/*                            DEFINES                              */
/* =============================================================== */

/* ------- CHARACTERS -------- */
#define FRICTION 15.f

/* MULA SEM CABECA */
#define ACELMULA 10.f
#define CHARGECOOLDOWN 7.f
#define MULACHANGEDIRECTION 3.f
#define MULAFAR 700.f

/* SACI */
#define ACELSACI 10.f
#define TELEPORTCOOLDOWN 8.f
#define JUMPCOOLDOWN 2.f
#define LASTPOSCOOLDOWN 1.f
#define SACIJUMPFORCE 15.f
#define SACIFAR 500.f

/* CUCA */
#define ACELCUCA 15.f
#define POTIONCOOLDOWN 1.5f
#define CUCAFAR 400.f

/* PLAYER */
#define ACELPLAYER 20.f
#define TAKEDAMAGECOOLDOWN 2.5f
#define SHOOTCOOLDOWN 0.5f
#define PLAYERJUMPFORCE 15.f
#define PLAYERMAXVEL 20.f

/* -------- OBSTACLES -------- */

#define VISCOSITYHONEY 0.5f

#define DELAYTHORNYBUSH 2.f



/*---------------------------------------------------------------*/

class Entity : public Ente {
    
    protected:
        /* ------ STATUS ------- */
        Vector2f position;
        Vector2f velocity;
        float clock;
        static Vector2f gravity;


    public:
        Entity();
        Entity(float x, float y);
        virtual ~Entity();
        
        /* ---- PURE VIRTUAL FUNCTIONS ---- */
        virtual void collide(Entity* other) = 0;
        virtual void execute() = 0;

        /* ---- OWN FUNCTIONS ---- */
        void draw();
        Drawable& getDrawable();
        void applyGravity();

        /* ----- GETS & SETS ----- */
        Vector2f getVelocity() const;
        void setVelocity(Vector2f vel);
        Vector2f getPosition() const;
        void setPosition(Vector2f pos);

};

#endif
