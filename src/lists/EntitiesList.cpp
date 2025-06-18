#include "../../include/lists/EntitiesList.h"


EntitiesList::EntitiesList() {
    entities.clear();
    it = entities.begin();
}

EntitiesList::~EntitiesList() {
    clear();
}

void EntitiesList::add(Entity* entity) {
     entities.push_back(entity);
}

void EntitiesList::remove(Entity* entity) {
    for (it = entities.begin(); it != entities.end(); ++it) {
        if (*it == entity) {
        entities.erase(it);
        return;
        }
    }
}

void EntitiesList::clear() {
    for (it = entities.begin(); it != entities.end(); ++it) {
        delete *it;
    }
    entities.clear();
}

void EntitiesList::traverse() {
    for (it = entities.begin(); it != entities.end(); ++it) {
        if (*it) {
            (*it)->execute();
            Character* character = dynamic_cast<Character*>(*it);
            if(character){
                if(character->getHealth() <= 0) {
                    if(dynamic_cast<Player*>(character))
                        pCM->removePlayer(static_cast<Player*>(character));
                        
                    else if(dynamic_cast<Enemy*>(character))
                        pCM->removeEnemy(static_cast<Enemy*>(character));
                }
            }
        }
    }
}
