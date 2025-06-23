#ifndef FASE_H
#define FASE_H

#include "../lists/EntitiesList.h"
#include "../managers/CollisionManager.h"
#include "../../include/entities/characters/enemies/Saci.h"
#include "../../include/entities/characters/enemies/MulaSemCabeca.h"
#include "../../include/entities/characters/enemies/Cuca.h"
#include "../../include/entities/obstacles/Cloud.h"
#include "../../include/entities/obstacles/Honey.h"
#include "../../include/entities/obstacles/ThornyBush.h"
#include "../../include/graphicalelements/BackgroundElement.h"

class BackgroundElement;

class Phase : public Ente {
    protected:

        EntitiesList entities_list;
        vector<ge::BackgroundElement *> tiles;
        vector<ge::BackgroundElement *> BackgroundLayers;
        CollisionManager *pCM;
        Vector2f phaseSize;
        Player *player1;
        Player *player2;
        float passingX;
        bool passedPhase;
        const int maxPlatforms = 20;
        const int minPlatforms = 5;
        const int maxSaci = 7;
        const int minSaci = 3;
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
        void setPlayers(Player *p1, Player *p2);
        /* -------- SAVE -------- */
        virtual json toJson() ;
        virtual void fromJson(const json& j);
        virtual string getType() const = 0;
};

#endif
