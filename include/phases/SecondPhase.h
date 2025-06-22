#ifndef SECOND_PHASE_H
#define SECOND_PHASE_H

#include "Phase.h"

class SecondPhase : public Phase {
    private:
        const int maxSpikes = 15;
        const int minSpikes = 5;
        const int maxMulas = 6;
        const int minMulas = 3;
    public:
        SecondPhase();
        SecondPhase(Vector2f size, float limiarX, Player* p1, Player* p2);
        ~SecondPhase();

        void execute() override;
        void createEnemies() override;
        void createObstacles() override;

        void createSpikes();
        void createMulas();

        std::string getType() const override {
            return "SecondPhase";
        }
};

#endif
