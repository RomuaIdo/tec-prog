#include "../../include/lists/EntitiesList.h"

EntitiesList::EntitiesList() {
  entities.clear();
  it = entities.begin();
}

EntitiesList::~EntitiesList() { clear(); }

void EntitiesList::add(Entity *entity) { entities.push_back(entity); }

void EntitiesList::remove(Entity *entity) {
  for (it = entities.begin(); it != entities.end(); ++it) {
    if ((*it) == entity) {
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

void EntitiesList::removePlayerInEnemiesList(Player *p) {
  if (p) {
    for (it = entities.begin(); it != entities.end(); ++it) {
      if (*it) {
        if (dynamic_cast<Enemy *>(*it)) {
          Enemy *enemy = static_cast<Enemy *>(*it);
          enemy->removePlayer(p);
        }
      }
    }
  }
}

void EntitiesList::traverse() {
  for (it = entities.begin(); it != entities.end(); ++it) {
    if (*it) {
      (*it)->execute();
    }
  }
}
