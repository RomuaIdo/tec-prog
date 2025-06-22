#ifndef FIRSTPHASE_H
#define FIRSTPHASE_H
#include "Phase.h"

class FirstPhase : public Phase {
    private:
        const int maxHoneys = 15;
        const int minHoneys = 5;
        const int maxCucas = 8;
        const int minCucas = 3;
    public:
        FirstPhase();
        FirstPhase(Vector2f size, float limiarX, Player* p1, Player* p2);
        ~FirstPhase();

        void execute() override;
        void createEnemies() override;
        void createObstacles() override;

        void createCucas();
        void createHoney();

        std::string getType() const override {
            return "FirstPhase";
        }
};

#endif
