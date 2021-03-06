 #ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "EntityManager.h"
#include <vector>

struct SDL_Texture;
//UI forward declarations
class Image;
class Label;
class Text_Box;
class Button;
class Window;
class Selector;
class Windowed_Image;
class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

private:

	SDL_Texture* debug_tex;
	std::vector<Entity*> Bushes;
	SDL_Rect Bush_Rect;
	Entity* House;
	SDL_Rect House_Rect;
	Entity* enemy1;

	Window* window;
	Label* win_title;
};

#endif // __j1SCENE_H__