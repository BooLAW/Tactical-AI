#include "PlayerManager.h"
#include "j1Viewports.h"
#include "j1Scene.h"
#include "j1Input.h"
#include "p2Log.h"

PlayerManager::PlayerManager()
{
}

PlayerManager::~PlayerManager()
{
}

bool PlayerManager::Awake(pugi::xml_node &)
{
	return true;
}

bool PlayerManager::Start()
{
	return true;
}

bool PlayerManager::PreUpdate()
{
	return true;
}

bool PlayerManager::Update(float dt)
{
	if (players.empty())
		return true;

	for (int i = 0; i < players.size(); i++)
	{
		// Input
	//Move
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			players.at(i)->move = move_left;
		}
		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			players.at(i)->move = move_right;
		}
		else if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			players.at(i)->move = move_up;
		}
		else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			players.at(i)->move = move_down;
		}
		else
		{
			players.at(i)->move = stop;
		}
		// --------------------

		// Right Joystick -----
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT )
		{
			if (players.at(i)->move != stop)
				players.at(i)->state = run_left;
			else
				players.at(i)->state = idle_left;
		}
		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			if (players.at(i)->move != stop)
				players.at(i)->state = run_right;
			else
				players.at(i)->state = idle_right;
		}
		else if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			if (players.at(i)->move != stop)
				players.at(i)->state = run_up;
			else
				players.at(i)->state = idle_up;
		}
		else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT )
		{
			if (players.at(i)->move != stop)
				players.at(i)->state = run_down;
			else
				players.at(i)->state = idle_down;
		}
		// --------------------

		// Run to idle when not moving
		else if (players.at(i)->state == run_left)
		{
			players.at(i)->state = idle_left;
		}
		else if (players.at(i)->state == run_right)
		{
			players.at(i)->state = idle_right;
		}
		else if (players.at(i)->state == run_up)
		{
			players.at(i)->state = idle_up;
		}
		else if (players.at(i)->state == run_down)
		{
			players.at(i)->state = idle_down;
		}

		// Idle to run when moving
		if (players.at(i)->move != stop)
		{
			if (players.at(i)->state == idle_left)
				players.at(i)->state = run_left;

			else if (players.at(i)->state == idle_right)
				players.at(i)->state = run_right;

			else if (players.at(i)->state == idle_up)
				players.at(i)->state = run_up;

			else if (players.at(i)->state == idle_down)
				players.at(i)->state = run_down;
		}

		// Abilities
		if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
		{
			if(players.at(i)->state == idle_down || players.at(i)->state == run_down)
				players.at(i)->state = basic_atack_down;
			else if (players.at(i)->state == idle_up || players.at(i)->state == run_up)
				players.at(i)->state = basic_atack_up;
			else if (players.at(i)->state == idle_left || players.at(i)->state == run_left)
				players.at(i)->state = basic_atack_left;
			else if (players.at(i)->state == idle_right || players.at(i)->state == run_right)
				players.at(i)->state = basic_atack_right;
		}

		
		// State machines

		// Animations
		switch (players.at(i)->state)
		{
		case run_up:
			players.at(i)->entity->RunUp();
			break;
		case run_left:
			players.at(i)->entity->RunLeft();
			break;
		case run_down:
			players.at(i)->entity->RunDown();
			break;
		case run_right:
			players.at(i)->entity->RunRight();
			break;
		case walk_up:
			break;
		case walk_left:
			break;
		case walk_down:
			break;
		case walk_right:
			break;
		case idle_up:
			players.at(i)->entity->IdleUp();
			break;
		case idle_left:
			players.at(i)->entity->IdleLeft();
			break;
		case idle_down:
			players.at(i)->entity->IdleDown();
			break;
		case idle_right:
			players.at(i)->entity->IdleRight();
			break;
		case basic_atack_up:
			players.at(i)->entity->BasicAttackUp();
			players.at(i)->state = idle_up;
			break;
		case basic_atack_left:
			players.at(i)->entity->BasicAttackLeft();
			players.at(i)->state = idle_left;
			break;
		case basic_atack_down:
			players.at(i)->entity->BasicAttackDown();
			players.at(i)->state = idle_down;
			break;
		case basic_atack_right:
			players.at(i)->entity->BasicAttackRight();
			players.at(i)->state = idle_right;
			break;
		case states_null:
			break;
		default:
			break;
		}

		// Movement
		float speed = (players.at(i)->entity->stats.speed * dt);

		switch (players.at(i)->move)
		{
		case move_up:
			players.at(i)->entity->MoveUp(speed);
			break;
		case move_down:
			players.at(i)->entity->MoveDown(speed);
			break;
		case move_left:
			players.at(i)->entity->MoveLeft(speed);
			break;
		case move_right:
			players.at(i)->entity->MoveRight(speed);
			break;
		case move_upleft:
			players.at(i)->entity->MoveUpLeft(speed);
			break;
		case move_upright:
			players.at(i)->entity->MoveUpRight(speed);
			break;
		case move_downleft:
			players.at(i)->entity->MoveDownLeft(speed);
			break;
		case move_downright:
			players.at(i)->entity->MoveDownRight(speed);
			break;
		case stop:
			break;
		}
	}
	return true;
}

bool PlayerManager::PostUpdate()
{
	return true;
}

bool PlayerManager::CleanUp()
{
	bool ret = true;

	ClearPlayers();

	return ret;
}

Player* PlayerManager::AddPlayer(entity_name name, int index, iPoint pos, int team, int show_life_bar)
{
	Player* ret = nullptr;
	if (players.size() < 3)
	{
		Player* p = new Player(App->entity->CreateEntity(name, pos), index - 1);
		p->entity->SetCamera(p->index + 1);
		p->entity->SetTeam(team);
		p->entity->show_life_bar = show_life_bar;
		p->entity->is_player = true;
		players.push_back(p);
		ret = p;
	}
	return ret;
}

void PlayerManager::ChangePlayer(entity_name name, int index)
{
	iPoint pos;
	for(vector<Player*>::iterator it = players.begin(); it != players.end(); it++)
	{
		if ((*it)->index == index - 1)
		{
			pos = (*it)->entity->GetPos();
			App->entity->DeleteEntity((*it)->entity);
			players.erase(it);
			RELEASE(*it);
			break;
		}
	}

	Player* p = new Player(App->entity->CreateEntity(name, pos), index - 1);
	p->entity->SetCamera(p->index + 1);
	players.push_back(p);
}

void PlayerManager::DeletePlayer(int index)
{
	for (vector<Player*>::iterator it = players.begin(); it != players.end(); it++)
	{
		if ((*it)->index == index - 1)
		{
			players.erase(it);
			App->entity->DeleteEntity((*it)->entity);
			RELEASE(*it);
			break;
		}
	}
}

void PlayerManager::ClearPlayers()
{
	for (int i = 0; i < players.size(); i++)
	{
		RELEASE(players.at(i));
	}
	players.clear();
}

std::vector<Entity*> PlayerManager::GetTeamPlayers(int team)
{
	std::vector<Entity*> ret;

	for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); it++)
	{
		if ((*it)->entity->GetTeam() == team)
		{
			ret.push_back((*it)->entity);
		}
	}

	return ret;
}

std::vector<int> PlayerManager::GetTeamViewports(int team)
{
	std::vector<int> ret;

	for (std::vector<Player*>::iterator it = players.begin(); it != players.end(); it++)
	{
		if ((*it)->entity->GetTeam() == team)
		{
			ret.push_back((*it)->index+1);
		}
	}

	return ret;
}

int PlayerManager::GetEntityViewportIfIsPlayer(Entity * entity)
{
	for (int i = 0; i < players.size(); i++)
	{
		if (players.at(i)->entity == entity)
		{
			return players.at(i)->index + 1;
		}
	}
}

