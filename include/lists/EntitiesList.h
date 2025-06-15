#include "../entities/Entity.h"
#include "List.h"

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
};
