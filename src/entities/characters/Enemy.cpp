#include "../../../include/entities/characters/Enemy.h"
#include "../../../include/entities/characters/Player.h"
#include <SFML/Window.hpp>


Enemy::Enemy()
    : Character(), players_list() {

  if (!texture.loadFromFile("assets/textures/EnemySprite.png")) {
    std::cerr << "Failed to load EnemySprite.png!" << std::endl;
  }
  texture.setSmooth(true);
  sprite.setTexture(texture);
  centerOrigin();
  size.x = sprite.getLocalBounds().width;
  size.y = sprite.getLocalBounds().height;
  sprite.setScale(size.x / sprite.getLocalBounds().width,
                  size.y / sprite.getLocalBounds().height);

  players_list.clear();
}

Enemy::Enemy(float x, float y, const float acel, int life, float coef, int s)
    : Character(x, y, acel, life, coef, s), players_list() {

  if (!texture.loadFromFile("assets/textures/EnemySprite.png")) {
    std::cerr << "Failed to load EnemySprite.png!" << std::endl;
  }
  texture.setSmooth(true);
  sprite.setTexture(texture);
  centerOrigin();
  size.x = sprite.getLocalBounds().width;
  size.y = sprite.getLocalBounds().height;
  sprite.setScale(size.x / sprite.getLocalBounds().width,
                  size.y / sprite.getLocalBounds().height);

  players_list.clear();
}

Enemy::~Enemy() { players_list.clear(); }


void Enemy::execute() {
  move();
  draw();
}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Enemy::collide(Entity* other) {
    if (Player* player = dynamic_cast<Player*>(other)) {
        attack(player);
    }
    else if (Projectile* proj = dynamic_cast<Projectile*>(other)) {
        //loseHealth(1);
    }
}


void Enemy::move(){
    float closer = sqrt(800 * 800 + 600 * 600);
    Vector2f closer_direction = Vector2f(0.f,0.f);
    list<Player *>::iterator it;

    for(it = players_list.begin(); it != players_list.end(); it++){
        if(*it){
            // Get direction to player
            Vector2f direction = ((*it)->getPosition() - position);
            float module = sqrt(direction.x*direction.x + direction.y*direction.y);

            // To improve
            if(module == 0) {
                attack((*it));
                continue;
            }    

            if(module < closer ){
                closer = module;
                closer_direction = direction;
                // Normalize vector
                closer_direction /= closer;

                closer_direction *= aceleration;
            } 
        }
    }

    if(closer_direction.y < 0 && !isInAir()){
        closer_direction.y = -10.f;
    }else closer_direction.y = 0.f;
    

    velocity.x += closer_direction.x * pGM->getdt();
    velocity.y += closer_direction.y;
    
    moveCharacter();
}



/* ------------------------------------------- */
/*              PLAYER FUNCTIONS               */
/* ------------------------------------------- */

void Enemy::removePlayer(Player *p){
    list<Player *>::iterator it;
    for(it = players_list.begin(); it != players_list.end(); it++){
        if(*it == p){
            players_list.erase(it);
            return;
        }
  }
}

void Enemy::addPlayer(Player *p){
    players_list.push_back(p);
}

void Enemy::attack(Player *p){
    // If player has health and after 2 seconds, then he can attack 
    if(p->getHealth() > 0 && pGM->getClockTime() >= 2.f){
        p->loseHealth(strength);
        cout << "Player got hurt!" << endl;
        cout << "He now has:" << p->getHealth() << endl;
        pGM->resetClock();
    }

}
