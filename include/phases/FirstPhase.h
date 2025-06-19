#ifndef FIRSTPHASE_H
#define FIRSTPHASE_H
#include "Phase.h"

class FirstPhase : public Phase {
    private:
        const int maxHoneys = 10;
        const int maxCucas = 5;
    public:
        FirstPhase(Vector2f size, float limiarX, Player* p1, Player* p2);
        ~FirstPhase();

        void execute() override;
        void createEnemies() override;
        void createObstacles() override;

        void createCucas();
        void createHoney();
};

#endif
