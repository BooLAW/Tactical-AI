#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_
#include "j1Module.h"
#include <deque>
#include "j1Timer.h"
#include "Point.h"
#include "j1Collision.h"

class j1Player;
struct SDL_Texture;
struct SDL_Rect;
enum ENTITYTYPE { player,bush,enemy,null };
class Entity;
class FSM;
class EntityManager :public j1Module {
public:
	EntityManager();
	~EntityManager();
	bool Update(float dt);
	Entity* CreateEntity(ENTITYTYPE type, SDL_Texture* _tex, SDL_Rect _rect, iPoint _pos);
	void DestroyEntities();
	void OnCollision(Collider* c1, Collider* c2);
private:
	std::deque<Entity*> entities;
	j1Timer time;
};


class Entity {
public:
	Entity();
	Entity(ENTITYTYPE _t, SDL_Texture* _tex, SDL_Rect _rect,iPoint _pos);
	virtual ~Entity();
	virtual void Update(float dt);
	virtual bool Draw();
public:
	struct {
		int x;
		int y;
	} pos;
	SDL_Texture* tex;
	SDL_Rect rect;
	ENTITYTYPE type;
};
//TODO 1
	//make an enum with the states wander - attack - aid - null

class FSM_Enemy : public  Entity {
public:
	FSM_Enemy();
	FSM_Enemy(ENTITYTYPE type,SDL_Texture * _tex,SDL_Rect _rect,iPoint _pos);
	void Update(float dt);
	void OnCollision(Collider* c1, Collider* c2);
	
//TODO 2
	//Make Functions for each state, another to select this functions and another one to change the states of 
	//at
public:
	//TODO 1
		//stablish a state property 
	bool x_wander = true;
	bool is_coll;
	bool in_aid;
	bool player_near = false;
	uint hp = 6;
	int move_state = 0;
	uint counter = 0;
	Collider* collider = nullptr;
	Collider* attack_coll = nullptr;
	Collider* affecting_area = nullptr; 
};

class Bush : public  Entity {
public:
	Bush();
	Bush(ENTITYTYPE _t, SDL_Texture* _tex, SDL_Rect _rect, iPoint _pos);
	void Update(float dt);
	void OnCollision(Collider* c1, Collider* c2);
public:
	bool slashed = false;
	bool is_coll;
	Collider* collider = nullptr;

};

#endif
