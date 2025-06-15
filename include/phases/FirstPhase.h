#ifndef FIRSTPHASE_H
#define FIRSTPHASE_H
#include "Phase.h"

class FirstPhase : public Phase {
private:
    const int maxMediumEnemies = 5;

public:
    FirstPhase(Vector2f size, Player* p1, Player* p2);
    ~FirstPhase();

    void execute() override;
    void createEnemies() override;
    void createObstacles() override;
    void createPlatforms() override;
    void createScenery() override;

    void createMediumEnemies();
    void createMediumObstacles();
};

#endif
