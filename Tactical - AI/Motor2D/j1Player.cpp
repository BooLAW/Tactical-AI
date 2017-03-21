#include "j1Player.h"
#include "j1Input.h"
#include "j1Collision.h"

j1Player::j1Player()
{
}

j1Player::~j1Player()
{
}

bool j1Player::Awake()
{
	bool ret = true;
	LOG("Player Awake Start");

	return ret;
}

bool j1Player::Start()
{
	bool ret = true;
	LOG("Player Start");

	// Setting Up all SDL_Rects x is every 102p, y is every 110p
	link_coll = App->collisions->AddCollider(LINK_RECT, COLLIDER_PLAYER, this); 
	//TODO 
		//add area collider
	//Idle
	{
		sprites[Idle][Up][0] = {link_x*3, link_y*2, link_width, link_height };
		sprites[Idle][Down][0] = {link_x*3, link_y, link_width, link_height };
		sprites[Idle][Left][0] = {link_x*3, link_y*4, link_width, link_height };
		sprites[Idle][Right][0] = { link_x*3, link_y*3, link_width, link_height };

	}

	//Idle Shield
	{
		sprites[Idle_Shield][Up][0] = { link_x * 3, link_y * 6, link_width, link_height };
		sprites[Idle_Shield][Down][0] = { link_x * 3, link_y * 5, link_width, link_height };
		sprites[Idle_Shield][Left][0] = { link_x * 3, link_y * 8, link_width, link_height };
		sprites[Idle_Shield][Right][0] = { link_x * 3, link_y * 7, link_width, link_height };
	}

	//Walk
	{
		sprites[Walk][Up][0] = { 0, link_y*2, link_width, link_height};
		sprites[Walk][Up][1] = { link_x, link_y*2, link_width, link_height };
		sprites[Walk][Up][2] = { link_x*2 , link_y*2, link_width, link_height };
		sprites[Walk][Up][3] = { link_x*3, link_y*2, link_width, link_height };
		sprites[Walk][Up][4] = { link_x*4, link_y*2, link_width, link_height };
		sprites[Walk][Up][5] = { link_x*5, link_y*2, link_width, link_height };
		sprites[Walk][Up][6] = { link_x*6, link_y*2, link_width, link_height };

		sprites[Walk][Down][0] = { 0 ,  link_y, link_width, link_height };
		sprites[Walk][Down][1] = { link_x, link_y, link_width, link_height };
		sprites[Walk][Down][2] = { link_x*2, link_y, link_width, link_height };
		sprites[Walk][Down][3] = { link_x*3, link_y, link_width, link_height };
		sprites[Walk][Down][4] = { link_x*4, link_y, link_width, link_height };
		sprites[Walk][Down][5] = { link_x*5, link_y, link_width, link_height };
		sprites[Walk][Down][6] = { link_x*6, link_y, link_width, link_height };

		sprites[Walk][Right][0] = { 0  ,link_y*3,link_width,link_height };
		sprites[Walk][Right][1] = { link_x,link_y*3,link_width,link_height };
		sprites[Walk][Right][2] = { link_x*2,link_y*3,link_width,link_height };
		sprites[Walk][Right][3] = { link_x*3,link_y*3,link_width,link_height };
		sprites[Walk][Right][4] = { link_x*4,link_y*3,link_width,link_height };
		sprites[Walk][Right][5] = { link_x*5,link_y*3,link_width,link_height };
		sprites[Walk][Right][6] = { link_x*6,link_y*3,link_width,link_height };

		sprites[Walk][Left][0] = { 0  ,link_y*4,link_width,link_height };
		sprites[Walk][Left][1] = { link_x,link_y*4,link_width,link_height };
		sprites[Walk][Left][2] = { link_x*2,link_y*4,link_width,link_height };
		sprites[Walk][Left][3] = { link_x*3,link_y*4,link_width,link_height };
		sprites[Walk][Left][4] = { link_x*4,link_y*4,link_width,link_height };
		sprites[Walk][Left][5] = { link_x*5,link_y*4,link_width,link_height };
		sprites[Walk][Left][6] = { link_x*6,link_y*4,link_width,link_height };
	}

	//Walk with blue Shield
	{
	
		sprites[Walk_Shield][Up][0] = { 0, link_y * 6, link_width, link_height };
		sprites[Walk_Shield][Up][1] = { link_x, link_y * 6, link_width, link_height };
		sprites[Walk_Shield][Up][2] = { link_x * 2 , link_y * 6, link_width, link_height };
		sprites[Walk_Shield][Up][3] = { link_x * 3, link_y * 6, link_width, link_height };
		sprites[Walk_Shield][Up][4] = { link_x * 4, link_y * 6, link_width, link_height };
		sprites[Walk_Shield][Up][5] = { link_x * 5, link_y * 6, link_width, link_height };
		sprites[Walk_Shield][Up][6] = { link_x * 6, link_y * 6, link_width, link_height };

		sprites[Walk_Shield][Down][0] = { 0 ,  link_y*5, link_width, link_height };
		sprites[Walk_Shield][Down][1] = { link_x, link_y*5, link_width, link_height };
		sprites[Walk_Shield][Down][2] = { link_x * 2, link_y*5, link_width, link_height };
		sprites[Walk_Shield][Down][3] = { link_x * 3, link_y*5, link_width, link_height };
		sprites[Walk_Shield][Down][4] = { link_x * 4, link_y*5, link_width, link_height };
		sprites[Walk_Shield][Down][5] = { link_x * 5, link_y*5, link_width, link_height };
		sprites[Walk_Shield][Down][6] = { link_x * 6, link_y*5, link_width, link_height };

		sprites[Walk_Shield][Right][0] = { 0  ,link_y * 7,link_width,link_height };
		sprites[Walk_Shield][Right][1] = { link_x,link_y * 7,link_width,link_height };
		sprites[Walk_Shield][Right][2] = { link_x * 2,link_y * 7,link_width,link_height };
		sprites[Walk_Shield][Right][3] = { link_x * 3,link_y * 7,link_width,link_height };
		sprites[Walk_Shield][Right][4] = { link_x * 4,link_y * 7,link_width,link_height };
		sprites[Walk_Shield][Right][5] = { link_x * 5,link_y * 7,link_width,link_height };
		sprites[Walk_Shield][Right][6] = { link_x * 6,link_y * 7,link_width,link_height };

		sprites[Walk_Shield][Left][0] = { 0  ,link_y * 8,link_width,link_height };
		sprites[Walk_Shield][Left][1] = { link_x,link_y * 8,link_width,link_height };
		sprites[Walk_Shield][Left][2] = { link_x * 2,link_y * 8,link_width,link_height };
		sprites[Walk_Shield][Left][3] = { link_x * 3,link_y * 8,link_width,link_height };
		sprites[Walk_Shield][Left][4] = { link_x * 4,link_y * 8,link_width,link_height };
		sprites[Walk_Shield][Left][5] = { link_x * 5,link_y * 8,link_width,link_height };
		sprites[Walk_Shield][Left][6] = { link_x * 6,link_y * 8,link_width,link_height };
	
	}
	//Pick-up Object
	//y coordinate for object depends on animatio



	// Load Textures

	Link_Movement = App->tex->Load("Sprites/Link_Movement.png");

	// !_Textures

	// Animations Settup

	// Idle
	{
		animations[Idle][Up].PushBack(sprites[Idle][Up][0]);
		animations[Idle][Down].PushBack(sprites[Idle][Down][0]);
		animations[Idle][Left].PushBack(sprites[Idle][Left][0]);
		animations[Idle][Right].PushBack(sprites[Idle][Right][0]);
	}

	//Idle Shield
	{
		animations[Idle_Shield][Up].PushBack(sprites[Idle_Shield][Up][0]);
		animations[Idle_Shield][Down].PushBack(sprites[Idle_Shield][Down][0]);
		animations[Idle_Shield][Left].PushBack(sprites[Idle_Shield][Left][0]);
		animations[Idle_Shield][Right].PushBack(sprites[Idle_Shield][Right][0]);
	}

	// Walking
	{

		// Walking UP 
		{
			animations[Walk][Up].PushBack(sprites[Walk][Up][0]);
			animations[Walk][Up].PushBack(sprites[Walk][Up][1]);
			animations[Walk][Up].PushBack(sprites[Walk][Up][2]);
			animations[Walk][Up].PushBack(sprites[Walk][Up][3]);
			animations[Walk][Up].PushBack(sprites[Walk][Up][4]);
			animations[Walk][Up].PushBack(sprites[Walk][Up][5]);
			animations[Walk][Up].PushBack(sprites[Walk][Up][6]);
			animations[Walk][Up].speed = PL_WALK_FPS;
		}

		// Walking DOWN
		{
			animations[Walk][Down].PushBack(sprites[Walk][Down][0]);
			animations[Walk][Down].PushBack(sprites[Walk][Down][1]);
			animations[Walk][Down].PushBack(sprites[Walk][Down][2]);
			animations[Walk][Down].PushBack(sprites[Walk][Down][3]);
			animations[Walk][Down].PushBack(sprites[Walk][Down][4]);
			animations[Walk][Down].PushBack(sprites[Walk][Down][5]);
			animations[Walk][Down].PushBack(sprites[Walk][Down][6]);
			animations[Walk][Down].speed = PL_WALK_FPS;
		}

		// Walking LEFT
		{
			animations[Walk][Left].PushBack(sprites[Walk][Left][0]);
			animations[Walk][Left].PushBack(sprites[Walk][Left][1]);
			animations[Walk][Left].PushBack(sprites[Walk][Left][2]);
			animations[Walk][Left].PushBack(sprites[Walk][Left][3]);
			animations[Walk][Left].PushBack(sprites[Walk][Left][4]);
			animations[Walk][Left].PushBack(sprites[Walk][Left][5]);
			animations[Walk][Left].PushBack(sprites[Walk][Left][6]);
			animations[Walk][Left].speed = PL_WALK_FPS;
		}

		// Walking RIGHT
		{
			animations[Walk][Right].PushBack(sprites[Walk][Right][0]);
			animations[Walk][Right].PushBack(sprites[Walk][Right][1]);
			animations[Walk][Right].PushBack(sprites[Walk][Right][2]);
			animations[Walk][Right].PushBack(sprites[Walk][Right][3]);
			animations[Walk][Right].PushBack(sprites[Walk][Right][4]);
			animations[Walk][Right].PushBack(sprites[Walk][Right][5]);
			animations[Walk][Right].PushBack(sprites[Walk][Right][6]);
			animations[Walk][Right].speed = PL_WALK_FPS;
		}

		// Walking Shield UP 
		{
			animations[Walk_Shield][Up].PushBack(sprites[Walk_Shield][Up][0]);
			animations[Walk_Shield][Up].PushBack(sprites[Walk_Shield][Up][1]);
			animations[Walk_Shield][Up].PushBack(sprites[Walk_Shield][Up][2]);
			animations[Walk_Shield][Up].PushBack(sprites[Walk_Shield][Up][3]);
			animations[Walk_Shield][Up].PushBack(sprites[Walk_Shield][Up][4]);
			animations[Walk_Shield][Up].PushBack(sprites[Walk_Shield][Up][5]);
			animations[Walk_Shield][Up].PushBack(sprites[Walk_Shield][Up][6]);
			animations[Walk_Shield][Up].speed = PL_WALK_FPS;
		}

		// Walking Shield DOWN
		{
			animations[Walk_Shield][Down].PushBack(sprites[Walk_Shield][Down][0]);
			animations[Walk_Shield][Down].PushBack(sprites[Walk_Shield][Down][1]);
			animations[Walk_Shield][Down].PushBack(sprites[Walk_Shield][Down][2]);
			animations[Walk_Shield][Down].PushBack(sprites[Walk_Shield][Down][3]);
			animations[Walk_Shield][Down].PushBack(sprites[Walk_Shield][Down][4]);
			animations[Walk_Shield][Down].PushBack(sprites[Walk_Shield][Down][5]);
			animations[Walk_Shield][Down].PushBack(sprites[Walk_Shield][Down][6]);
			animations[Walk_Shield][Down].speed = PL_WALK_FPS;
		}

		// Walking Shield LEFT
		{
			animations[Walk_Shield][Left].PushBack(sprites[Walk_Shield][Left][0]);
			animations[Walk_Shield][Left].PushBack(sprites[Walk_Shield][Left][1]);
			animations[Walk_Shield][Left].PushBack(sprites[Walk_Shield][Left][2]);
			animations[Walk_Shield][Left].PushBack(sprites[Walk_Shield][Left][3]);
			animations[Walk_Shield][Left].PushBack(sprites[Walk_Shield][Left][4]);
			animations[Walk_Shield][Left].PushBack(sprites[Walk_Shield][Left][5]);
			animations[Walk_Shield][Left].PushBack(sprites[Walk_Shield][Left][6]);
			animations[Walk_Shield][Left].speed = PL_WALK_FPS;
		}

		// Walking Shield RIGHT
		{
			animations[Walk_Shield][Right].PushBack(sprites[Walk_Shield][Right][0]);
			animations[Walk_Shield][Right].PushBack(sprites[Walk_Shield][Right][1]);
			animations[Walk_Shield][Right].PushBack(sprites[Walk_Shield][Right][2]);
			animations[Walk_Shield][Right].PushBack(sprites[Walk_Shield][Right][3]);
			animations[Walk_Shield][Right].PushBack(sprites[Walk_Shield][Right][4]);
			animations[Walk_Shield][Right].PushBack(sprites[Walk_Shield][Right][5]);
			animations[Walk_Shield][Right].PushBack(sprites[Walk_Shield][Right][6]);
			animations[Walk_Shield][Right].speed = PL_WALK_FPS;
		}

	}


	animations[Walk][Down].PushBack(sprites[Idle][Down][0]);
	animations[Walk][Left].PushBack(sprites[Idle][Left][0]);
	animations[Walk][Right].PushBack(sprites[Idle][Right][0]);

	// animations speed settup
	//This was bad because not all animations are played back in the same speed, every animation requires a speed setup
	
		for (int n_dir = Direction::FirstDir; n_dir < Direction::LastDir; n_dir++) {
			animations[Pickup][n_dir].speed = 0.18f;
		}
		for (int n_dir = Direction::FirstDir; n_dir < Direction::LastDir; n_dir++) {
			animations[Slash][n_dir].speed = 0.4f;
		}
	


	// !_Animations

	// Variable Settup

	pos.x = 300;
	pos.y = 350;

	pl_speed.x = 2.5;
	pl_speed.y = 2.5;

	curr_dir = Down;

	// !_Variables

	return ret;
}

bool j1Player::Update(float dt)
{
	bool ret = true;

	// Logic
	if (action == false) 
	{
		//Movement
		{
			if (App->input->GetKey(SDL_SCANCODE_W) && App->input->GetKey(SDL_SCANCODE_A)) {
				pos.y -= pl_speed.y * sqrt(2) / 2;
				pos.x -= pl_speed.x * sqrt(2) / 2;
				if (anim_override == false)
					action_blit = Walk;
			}
			else if (App->input->GetKey(SDL_SCANCODE_A) && App->input->GetKey(SDL_SCANCODE_S)) {
				pos.y += pl_speed.y * sqrt(2) / 2;
				pos.x -= pl_speed.x * sqrt(2) / 2;
				if (anim_override == false)
					action_blit = Walk;
			}
			else if (App->input->GetKey(SDL_SCANCODE_S) && App->input->GetKey(SDL_SCANCODE_D)) {
				pos.y += pl_speed.y * sqrt(2) / 2;
				pos.x += pl_speed.x * sqrt(2) / 2;
				if (anim_override == false)
					action_blit = Walk;
			}
			else if (App->input->GetKey(SDL_SCANCODE_D) && App->input->GetKey(SDL_SCANCODE_W)) {
				pos.y -= pl_speed.y * sqrt(2) / 2;
				pos.x += pl_speed.x * sqrt(2) / 2;
				if (anim_override == false)
					action_blit = Walk;
			}
			else if (App->input->GetKey(SDL_SCANCODE_W)) {
				pos.y -= pl_speed.y;
				if (anim_override == false)
					action_blit = Walk;
				if (dir_override == false)
					curr_dir = Up;

			}
			else if (App->input->GetKey(SDL_SCANCODE_A)) {
				pos.x -= pl_speed.x;
				if (anim_override == false)
				 action_blit = Walk;
				if (dir_override == false)
					curr_dir = Left;
			}
			else if (App->input->GetKey(SDL_SCANCODE_S)) {
				pos.y += pl_speed.y;
				if (anim_override == false)
					action_blit = Walk;
				if (dir_override == false)
					curr_dir = Down;
			}
			else if (App->input->GetKey(SDL_SCANCODE_D)) {
				pos.x += pl_speed.x;
				if(anim_override == false)
					action_blit = Walk;
				if (dir_override == false)
					curr_dir = Right;
			}
			else {
				if (anim_override == false)
					action_blit = Idle;
			}

			last_pos = pos;
			// Direction/Atk
			// This inherently bad, you are ignoring 6 more buttons (X Y L R SELECT START)
			//It would work for gamepad, but not for keyboard
			//Objects will go here too, then they might trigger action or nah

			
			}
		}
			//Idle
	{	
		//if(App->input->GetKey(SDL_SCANCODE))action_blit = Idle;
	}

			// !_Logic

			// Graphics
		if (action == false){
			//Movement or any action that does not stop movement

			if (shield == true && (action_blit == Idle || action_blit == Walk)) //add cases for actions that can be done with or without shield
				action_blit++;
			
			App->render->Blit(Link_Movement, pos.x - PL_OFFSET_X, pos.y - PL_OFFSET_Y, &animations[action_blit][curr_dir].GetCurrentFrame());
			//!_Movement ""

			if (anim_override == true && animations[action_blit][curr_dir].Finished()) {
				anim_override = false;
				dir_override = false;
				animations[action_blit][curr_dir].Reset();
				action_blit = Idle;
				pl_speed.x = pl_speed.x * 3;
				pl_speed.y = pl_speed.y * 3;
			}
		}
	

	//Actions
		else if (action == true) {

			if (animations[action_blit][curr_dir].Finished() && App->input->GetKey(SDL_SCANCODE_SPACE) != KEY_REPEAT) {
				action = false;
				animations[action_blit][curr_dir].Reset();
				App->render->Blit(Link_Movement, pos.x - PL_OFFSET_X, pos.y - PL_OFFSET_Y, &animations[Idle][curr_dir].GetCurrentFrame());
			}
			else {
				App->render->Blit(Link_Movement, pos.x - PL_OFFSET_X, pos.y - PL_OFFSET_Y, &animations[action_blit][curr_dir].GetCurrentFrame());

				if (animations[action_blit][curr_dir].Finished() && App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
					animations[action_blit][curr_dir].Reset();
			}

		}
	//!_Actions																													
	
	//!_Graphics

	// MODIFY COLLISION -------------------------------------------------
	//TODO 
	//Set the position of the area collider
		link_coll->SetPos(pos.x , pos.y );
	return ret;
}

bool j1Player::PostUpdate(float dt)
{
	bool ret = true;


	return ret;
}

bool j1Player::CleanUp()
{
	bool ret = true;
	LOG("Player CleanUp Start");

	// Unloading All Textures
	App->tex->UnLoad(Link_Movement);


	return ret;
}

bool j1Player::SetPosTile(int x, int y)
{
	bool ret = true;

	pos.x = App->map->MapToWorld(x, y).x;
	pos.y = App->map->MapToWorld(x, y).y;

	return ret;
}

Point<float> j1Player::GetPos()
{
	return pos;
}

void j1Player::OnCollision(Collider* c1, Collider* c2)
{
	if (link_coll == c1  && (c2->type == COLLIDER_WALL || c2->type == COLLIDER_BUSH || c2->type == COLLIDER_ENEMY) && link_coll != nullptr)
	{
		
		if (pos.y + PLAYER_COLL_Y_OFFSET >= c2->rect.y + c2->rect.h)
		{
			pos.y = c2->rect.y + c2->rect.h;
		}

		else if (pos.y + c1->rect.h - PLAYER_COLL_Y_OFFSET <= c2->rect.y)
		{
			pos.y = c2->rect.y - c1->rect.h;
		}
		else if (c1->rect.x + c1->rect.w >= c2->rect.x && c1->rect.x <= c2->rect.x)
		{
			pos.x = c2->rect.x - c1->rect.w ;
		}
		else if (pos.x  <= c2->rect.x + c2->rect.w)
		{
			//polish this one 
			pos.x = c2->rect.x + c2->rect.w ;
		}
	}
	// dying collision

	/*if (self == c1 && self != nullptr && self->type == COLLIDER_PLAYER && (c2->type == COLLIDER_ENEMY_SHOT || c2->type == COLLIDER_ENEMY || c2->type == COLLIDER_TRUCK || c2->type == COLLIDER_RED_SOLDIER) && !destroyed)
	{
		App->explosion->AddExplosion(App->explosion->Player, position.x - 30, position.y - 30, { 0, 0 }, { 0, 0, 105, 115 }, COLLIDER_EXPLOSION);
		destroyed = true;
		Disable();
	}*/
}