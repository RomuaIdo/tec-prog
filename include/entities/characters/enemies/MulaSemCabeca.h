#ifndef MULA_SEM_CABECA_H
#define MULA_SEM_CABECA_H
#include "../Enemy.h"

class MulaSemCabeca : public Enemy {

    private:
        /* ------ STATUS ------- */
        float chargeClock;
        bool isCharging;
        float chargingClock;

        /* ------ TEXTURES ------ */
        Texture chargeTexture;
        Texture runTexture;

    public:
        /* ---- CONSTRUCTORS ---- */
        MulaSemCabeca(float x, float y, const float acel = 5.f, int life = 5, int s = 1);
        ~MulaSemCabeca();

        /* ---- OWN FUNCTIONS ---- */
        void execute();
        void move();
        void charge();
        void updateClocks();
        void updateChargingClock();

        /* -------- SAVE -------- */
        json toJson() const;
        void fromJson(const json& j);
        std::string getType() const;

        /* ------- PLAYER -------- */
        void attack(Player *p);
};

#endif
