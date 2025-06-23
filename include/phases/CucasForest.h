#ifndef FIRSTPHASE_H
#define FIRSTPHASE_H
#include "Phase.h"

class CucasForest : public Phase {
    private:
        const int maxHoneys = 15;
        const int minHoneys = 5;
        const int maxCucas = 8;
        const int minCucas = 3;
    public:
        CucasForest();
        CucasForest(Vector2f size, float limiarX, Player* p1, Player* p2);
        ~CucasForest();

        void execute() override;
        void createEnemies() override;
        void createObstacles() override;

        void createCucas();
        void createHoney();

        std::string getType() const override {
            return "CucasForest";
        }
};

#endif
