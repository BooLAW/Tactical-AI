#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "j1Module.h"
#include "Animation.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Map.h"

#define MAX_SPRITE_FRAMES 30

#define PL_OFFSET 12
#define PL_OFFSET_X 33
#define PL_OFFSET_Y 35


#define PL_WALK_FPS 0.8f

#define link_width 99
#define link_height 107
#define link_y 110
#define link_x 102
class Collider;
enum Direction {
	FirstDir = 0,
	Up,
	Left,
	Right,
	Down,
	LastDir
};

class j1Player : public j1Module {
public:
	enum Sprites {
		__FIRST = 0,
		Idle,
		Idle_Shield,
		Walk,		
		Walk_Shield,
		S_Charge_Idle,
		S_Charge_Walk,
		Pickup,
		Pull,
		Push,
		Slash,
		Unknown,
		__LAST
	};
	

private:
	Point<float> pos;
	Point<float> last_pos;
	Point<float> pl_speed;

	SDL_Texture* Link_Movement = nullptr;

	// All player sprites / animations
	Animation animations[Sprites::__LAST][Direction::LastDir];
	SDL_Rect sprites[Sprites::__LAST][Direction::LastDir][MAX_SPRITE_FRAMES];

	unsigned int curr_dir;

public:
	j1Player();
	virtual ~j1Player();

private:
	bool Awake();
	bool Start();
	bool Update(float dt);
	bool PostUpdate(float dt);
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

public:
	bool SetPosTile(int x, int y);
	Point<float> GetPos();

	bool action = false; // Actions: Throw, Pull, Slash,...
	int action_blit;
	bool dir_override = false; // Overrides directions expressed if there is an action that keeps movement but changes view direction being done at the time
	bool anim_override = false;
	bool shield = true;
	Collider* area;
	Collider* link_coll;
	

};

#endif // !__PLAYER_H__
