#pragma once
#include "ecs.hpp"
#include <SDL2/SDL.h>

class Collision;

class ColliderComponent : public Component {
	public:
		static Collision c;
		SDL_Rect collider;
		int tag = 0;
		int type;

        bool leftCollision = false;
        bool rightCollision = false;
        bool topCollision = false;
        bool bottomCollision = false;

		ColliderComponent(int);
		ColliderComponent(int, int w, int h);
		void init(Entity*);
		void update(Entity*);
		void hasCollision(Entity*, Entity*);
        void resetCollision();
};