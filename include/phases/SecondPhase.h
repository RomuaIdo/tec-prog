#ifndef SECOND_PHASE_H
#define SECOND_PHASE_H

#include "Phase.h"

class SecondPhase : public Phase {
public:
    SecondPhase(Vector2f size, Player* p1, Player* p2);
    ~SecondPhase();

    void execute() override;
    void createEnemies() override;
    void createObstacles() override;
    void createPlatforms() override;
    void createScenery() override;
};

#endif
