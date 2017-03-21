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
	if (c2->type == COLLIDER_ENEMY && c1->type == COLLIDER_PLAYER)
		player_near = true;
		hp -= 1;

}
state FSM_Enemy::SetState()
{
	if (hp < 2)
	{
		current_state = Aid;
	}
	else if (player_near)
	{
		current_state = Attack;
	}
	else
		current_state = Wander;

	return current_state;
}
void FSM_Enemy::Update(float dt)
{
	if (current_state != _NULL)
		SelectFunction();
	SetState();
	collider->SetPos(pos.x, pos.y);
}
void FSM_Enemy::WanderEnemy()
{
	LOG("Enemy Wandering");
	if (in_aid == true)
	{
		pos = ORIGINAL_TILE;
		in_aid = false;
	}
	if (attack_coll != nullptr)
		App->collisions->EraseCollider(attack_coll);
	

	switch (move_state)
	{
	case 0:
		pos.x += 1;
		break;
	case 1:
		pos.y -= 1;
		break;
	case 2: 
		pos.x -= 1;
		break;
	case 3:
		pos.y += 1;
		break;
	}
	if (move_state >= 3 && counter>10)
		move_state = 0;
	else if (counter > 10 && move_state <= 3)
	{
		move_state++;
		counter = 0;
	}
	else
		counter++;
	
}
void FSM_Enemy::AttackEnemy()
{
	LOG("Enemy Attacking");
	attack_coll = App->collisions->AddCollider({ pos.x,pos.y,rect.w + 20,rect.h + 20 }, COLLIDER_ENEMY_ATTACK, App->entitymanager);
}
void FSM_Enemy::AidEnemy()
{
	LOG("Enemy looking for Aid");
	if (attack_coll != nullptr)
		App->collisions->EraseCollider(attack_coll);
	in_aid = true;
	pos = AID_POS;
	hp = 6;
}
void FSM_Enemy::SelectFunction()
{
	switch (current_state)
	{
	case 0:
		WanderEnemy();
		break;
	case 1:
		AttackEnemy();
		break;
	case 2:
		//we won't evade
		break;
	case 3:
		AidEnemy();
		break;
	default:
		break;
	}
}
