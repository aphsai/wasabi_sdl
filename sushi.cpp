#include <iostream>
#include "sushi.hpp"
#include "defs.hpp"
#include "game.hpp"

#include "projectile.hpp"
#include "sword.hpp"

#include "physics-component.hpp"
#include "graphics-component.hpp"
#include "jumping-component.hpp"
#include "health-component.hpp"
#include "input-component.hpp"
#include "collider-component.hpp"
#include "grab-component.hpp"

Sushi::Sushi(int x, int y) {
	n_xpos = xpos = x;
	n_ypos = ypos = y;
    
    jump_height = JUMP_HEIGHT;
    width = WIDTH;
    height = HEIGHT;
    x_offset = X_OFFSET;
    y_offset = Y_OFFSET;

    sword = nullptr;

    flip = SDL_FLIP_NONE;
	generateTag();
	init();
	addAnimations();
}

void Sushi::addAnimations() {
	gc->addAnimation(WALK, SDL_Rect { 0 * TILESHEET_X, 1 * TILESHEET_Y, width + x_offset, height }, 12, 2);
	gc->addAnimation(JUMP, SDL_Rect { 1  * TILESHEET_X, 0 * TILESHEET_Y, width + x_offset, height }, 2, 10);
    gc->addAnimation(IDLE, SDL_Rect { 0 * TILESHEET_X, 0 * TILESHEET_Y, width + x_offset, height }, 1, 10);
    gc->addAnimation(WALL_GRAB, SDL_Rect { 2 * TILESHEET_X, 0 * TILESHEET_Y, width + x_offset, height }, 1, 3);
}

void Sushi::init() {
	addComponent<InputComponent>(INPUT_COMPONENT);
	addComponent<GraphicsComponent>(GRAPHICS_COMPONENT, SDL_Rect { 0 * TILESHEET_SIZE, 0 * TILESHEET_SIZE, TILESHEET_SIZE, TILESHEET_SIZE });
	addComponent<PhysicsComponent>(PHYSICS_COMPONENT);
	addComponent<ColliderComponent>(COLLIDER_COMPONENT, PLAYER, x_offset, y_offset);
	addComponent<JumpingComponent>(JUMPING_COMPONENT, jump_height); addComponent<CameraComponent>(CAMERA_COMPONENT);
    addComponent<HealthComponent>(HEALTH_COMPONENT, 100, 30);
    addComponent<GrabComponent>(GRAB_COMPONENT);

	initComponents();

	pc = &getComponent<PhysicsComponent>(PHYSICS_COMPONENT);
	gc = &getComponent<GraphicsComponent>(GRAPHICS_COMPONENT);
	jc = &getComponent<JumpingComponent>(JUMPING_COMPONENT);
    cc = &getComponent<ColliderComponent>(COLLIDER_COMPONENT);
    hc = &getComponent<HealthComponent>(HEALTH_COMPONENT);
    ic = &getComponent<InputComponent>(INPUT_COMPONENT);
    ggc = &getComponent<GrabComponent>(GRAB_COMPONENT);
}

void Sushi::update() {
    int animation = 0;

	if (ic->moving_forward && !ic->attack) {
        flip = SDL_FLIP_NONE;
		pc->xvel = LATERAL_SPEED;
        animation = WALK;
	}
    else if (ic->moving_backward && !ic->attack)  {
        flip = SDL_FLIP_HORIZONTAL;
	    pc->xvel = -LATERAL_SPEED;
        animation = WALK; 
	}
	else {
	    pc->xvel = 0;
        animation = IDLE;
	}

    //if (ic->fire) {
    //    ic->fire = false;
    //    Game::manager->addEntity(new Projectile(xpos, ypos, tag, PROJECTILE_SPEED - 2 * PROJECTILE_SPEED * (flip == SDL_FLIP_HORIZONTAL)));
    //} 

    //if (gc->animationIndex == ATTACK && gc->animation_complete) {
    //    ic->attack = false;
    //    sword->mark_remove = true;
    //    sword = nullptr;
    //}

	if (ic->jumping && !ic->attack) {
        if (!jc->isJumping) {
		    jc->jump();
        }
	}

    if(jc->isJumping) {
        animation = JUMP;
    }

    if (hc->isHurt) {
        animation = HURT;
    }

//    if (ic->attack) {
//        if (sword == nullptr) {
//            Game::manager->addEntity(sword = new Sword(xpos + x_offset + width / 2, ypos + y_offset + 10, tag, 36, 20));
//        }
//       animation = ATTACK;
//    } 

    gc->setAnimation(animation, flip);
    updateComponents();
}

void Sushi::draw() {
	drawComponents();
}

Sushi::~Sushi() {
    for (Component* c : components) { delete c; }
	components.clear();
    delete sword;
}

