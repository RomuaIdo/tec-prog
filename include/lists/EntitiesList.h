#include "../entities/Entity.h"
#include "List.h"
#include "../managers/CollisionManager.h"
#include "../entities/characters/Player.h"
#include "../entities/characters/Enemy.h"


class EntitiesList {
    private:
        List<Entity*> entities;
        List<Entity*>::Iterator it;

    public:
        EntitiesList();
        ~EntitiesList();

        void add(Entity* entity);
        void remove(Entity* entity);
        void clear();
        void traverse();
        void removePlayerInEnemiesList(Player* p);
        vector<json> toJson();
        void addPlayerToEnemiesList(Player* p1, Player* p2);
};
