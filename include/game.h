#ifndef GAME_H
#define GAME_H

#include "level.h"
#include "level_generator.h"
#include "player.h"
#include "camera.h"
#include "lighting.h"
#include "hud.h"

class Game
{
	public:
		Game();
		
		void update(float delta);
		void draw();

		void loadLevel(LevelGenerator& lg);
		void resetLevel();

	private:
		Camera camera;
		Lighting lighting;
		Player player;
		Hud hud;

		Level* level;

		int layer;
};

#endif
