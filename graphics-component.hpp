#pragma once
#include <SDL2/SDL.h>
#include "ecs.hpp"
#include "texture-manager.hpp"

class GraphicsComponent : public Component {
	public: 
		SDL_Rect src;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		GraphicsComponent(SDL_Rect r) {
			src = r;
		}

		void draw(Entity* entity) {
			TextureManager::draw(src, SDL_Rect {entity->xpos, entity->ypos, src.w * SCALING, src.h * SCALING}, flip);
		}
};
