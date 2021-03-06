#include "EntityManager.h"
#include "j1Player.h"
#include "p2Log.h"
#include "j1Render.h"

//Constructor and destructor
EntityManager::EntityManager() {

}

EntityManager::~EntityManager() {



}
Entity::Entity() {
}

Entity::Entity(ENTITYTYPE _t, SDL_Texture * _tex, SDL_Rect  _rect, iPoint _pos)
{
	type = _t;
	tex = _tex;
	rect = _rect;
	pos.x = _pos.x;
	pos.y = _pos.y;
}


Entity:: ~Entity() {
}
Entity* EntityManager::CreateEntity(ENTITYTYPE type, SDL_Texture * _tex, SDL_Rect  _rect, iPoint _pos) {

	Entity* ret = nullptr;

	switch (type) {
	case enemy:
		ret = new FSM_Enemy(type,_tex,_rect,_pos);
		break;
	case bush:
		ret = new Bush(type,_tex,_rect,_pos);
		break;
	default:
		break;
	}

	if (ret != nullptr) {
		entities.push_back(ret);
	}
	else {
		LOG("ERROR CREATING ENTITY type: %d", type);
	}

	return ret;
}
bool EntityManager::Update(float dt) {

	for (int i = 0; i < entities.size(); i++) {
		entities[i]->Update(dt);
	}
	return true;
}


void EntityManager::DestroyEntities()
{
	for (uint i = 0; i < entities.size(); i++) {
		if (entities[i] != nullptr) {
			delete entities[i];
		}
	}
} 
void EntityManager::OnCollision(Collider* c1, Collider* c2)
{

}

void Entity::Update(float dt) {


}

bool Entity::Draw()
{
	bool ret = NULL;



	return ret;

} // will return NULL if there's an error

//BUSH
Bush::Bush(ENTITYTYPE _t, SDL_Texture* _tex, SDL_Rect _rect, iPoint _pos)
{
	type = _t;
	tex = _tex;
	rect = _rect;
	pos.x = _pos.x;
	pos.y = _pos.y;
	collider = App->collisions->AddCollider({ pos.x,pos.y,rect.w,rect.h }, COLLIDER_BUSH, App->entitymanager);
}
void Bush::Update(float dt) 
{
	
}
//!BUSH

FSM_Enemy::FSM_Enemy(ENTITYTYPE _t, SDL_Texture* _tex, SDL_Rect _rect, iPoint _pos)
{
	type = _t;
	tex = _tex;
	rect = _rect;
	pos.x = _pos.x;
	pos.y = _pos.y;
	collider = App->collisions->AddCollider({ pos.x,pos.y,rect.w,rect.h }, COLLIDER_ENEMY, App->entitymanager);
}
void FSM_Enemy::OnCollision(Collider* c1, Collider* c2)
{
	//Hint -> if (c2->type == COLLIDER_ENEMY && c1->type == COLLIDER_PLAYER)
						//do something

}

void FSM_Enemy::Update(float dt)
{
	//TODO 3
		//select the function that the enemy will do this frame and update the state
	collider->SetPos(pos.x, pos.y);
}

