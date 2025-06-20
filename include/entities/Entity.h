#ifndef ENTITY_H
#define ENTITY_H
#include "Ente.h"
#include <SFML/Graphics.hpp>
using namespace sf;


/* =============================================================== */
/*                            DEFINES                              */
/* =============================================================== */

/* ------- CHARACTERS -------- */
#define FRICTION 25.f

/* MULA SEM CABECA (Hard Enemy) */
#define MULAACEL 5.f
#define MULAHEALTH 20
#define MULASTRENGTH 4
#define CHARGECOOLDOWN 7.f
#define MULACHANGEDIRECTION 3.f
#define MULAFAR 800.f
#define CHARGEPREPARATIONCOOLDOWN 2.f
#define MULAEVILNESS 10

/* CUCA (Medium Enemy) */
#define CUCAACEL 6.f
#define CUCAHEALTH 5
#define CUCASTRENGTH 2
#define CUCAFAR 400.f
#define POTIONDAMAGE 1
#define POTIONCOOLDOWN 1.5f
#define POTIONACEL 10.f
#define CUCAEVILNESS 7

/* SACI (Easy Enemy) */
#define SACIACEL 5.f
#define SACIHEALTH 5
#define SACISTRENGTH 2
#define TELEPORTCOOLDOWN 8.f
#define JUMPCOOLDOWN 2.5f
#define LASTPOSCOOLDOWN 1.f
#define SACIJUMPFORCE 15.f
#define SACIFAR 700.f
#define SACIEVILNESS 3

/* PLAYER */
#define PLAYERACEL 50.f
#define PLAYERHEALTH 20
#define PLAYERSTRENGTH 4
#define TAKEDAMAGECOOLDOWN 2.5f
#define SHOOTCOOLDOWN 0.5f
#define PLAYERJUMPFORCE 15.f
#define PLAYERMAXVEL 15.f
#define ROCKDAMAGE 1
#define ROCKACEL 15.f
#define SCOREMULTIPLIER 10

/* -------- OBSTACLES -------- */

/* HONEY */
#define HONEYVISCOSITY 0.5f

/* THORNY BUSH */
#define THORNYBUSHCOOLDOWN 2.f
#define THORNYBUSHSPIKES 2

/* PLATFORM */
#define PLATAFORMMAXPOSITION 100.f
#define PLATAFORMOVE 2.f

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
