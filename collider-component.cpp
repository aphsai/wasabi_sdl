#include <iostream>
#include "collider-component.hpp"
#include "collision.hpp"
#include "game.hpp"
#include "defs.hpp"

//Collision ColliderComponent::c;

ColliderComponent::ColliderComponent(int t, int x_off, int y_off) {
    type = t;
    x_offset = x_off;
    y_offset = y_off;
}

ColliderComponent::ColliderComponent(int t) {
    type = t;
}

void ColliderComponent::draw(Entity* entity) {
    SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
    SDL_Rect ent = {Game::camera->xpos + entity->xpos, Game::camera->ypos + entity->ypos, entity->width, entity->height };
    SDL_RenderDrawRect(Game::renderer, &ent);
}

void ColliderComponent::init(Entity* entity) {
    collider.x = entity->xpos + x_offset;
    collider.y = entity->ypos + y_offset;
    collider.w = entity->width - x_offset;
    collider.h = entity->height - y_offset;
}

void ColliderComponent::update(Entity *entity) {
    leftCollision = rightCollision = topCollision = bottomCollision = false;
    collider.x = entity->xpos + x_offset;
    collider.y = entity->ypos + y_offset;
    collider.w = entity->width - x_offset;
    collider.h = entity->height - y_offset;
}
