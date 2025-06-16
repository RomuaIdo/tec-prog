#ifndef SECOND_PHASE_H
#define SECOND_PHASE_H

#include "Phase.h"

class SecondPhase : public Phase {
private:
    const int maxSpikes = 10;
    const int maxCucas = 2;
public:
    SecondPhase(Vector2f size, Player* p1, Player* p2, const string &backgroundPath);
    ~SecondPhase();

    void execute() override;
    void createEnemies() override;
    void createObstacles() override;
    void createSpikes();
    void createCucas();
};

#endif
