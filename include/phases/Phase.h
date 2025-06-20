#ifndef FASE_H
#define FASE_H

#include "../entities/Ente.h"
#include "../entities/Entity.h"
#include "../lists/EntitiesList.h"
#include "../managers/CollisionManager.h"

class BackgroundElement;

class Phase : public Ente {
    protected:
        EntitiesList entities_list;
        vector<BackgroundElement *> tiles;
        vector<BackgroundElement *> BackgroundLayers;
        CollisionManager *pCM;
        Vector2f phaseSize;
        Player *player1;
        Player *player2;
        float passingX;
        bool passedPhase;
        const int maxPlatforms = 20;
        const int maxSaci = 4;
        Phase(Vector2f size, float limiarX, Player *p1, Player *p2);
        virtual void createEnemies() = 0;
        virtual void createObstacles() = 0;
        void createSaci();
        void createPlatforms();
        void createScenery();
        void checkPhaseCompletion();

    public:
        virtual ~Phase();
        Vector2f getPhaseSize() const;
        bool passed() const;
        virtual void execute() = 0;
};

#endif
