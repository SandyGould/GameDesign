#ifndef ROOMS_H
#define ROOMS_H

#include "../engine/Game.h"
#include "../engine/Sprite.h"
#include "../engine/AnimatedSprite.h"
#include "../engine/Scene.h"
#include "../engine/Camera.h"
// #include "../engine/TextObject.h"
#include "../engine/things/Coin.h"
#include "../engine/things/Player.h"
#include "../engine/things/TextBox.h"
#include "../engine/things/SelectionMenuBase.h"
#include "../engine/things/SelectionMenuOption.h"
// #include "../engine/QuestManager.h"
// #include "../engine/events/PickedUpEvent.h"
// #include "../engine/Sound.h"
#include "../engine/tweens/Tween.h"
#include "../engine/tweens/TweenJuggler.h"
#include "../engine/StatBar.h"
#include "../engine/CollisionSystem.h"


class Rooms : public Game {

public:
	Rooms();
	virtual ~Rooms();

    void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;
	void draw(AffineTransform& at) override;

private:
    bool esc_prepressed = false;

	Camera* camera;

	Player* player;

    SelectionMenuBase* selection_menu_base;
    SelectionMenuOption * selection_quit_option;
    SelectionMenuOption * selection_resume_option;

    Scene* scene;
    Scene* scene2;

    TextBox* start_text_box;

    StatBar* health;

    int room;

    CollisionSystem* collisionSystem;

    Tween* player_tween;
    Tween* start_text_tween;
    Tween* scene_transition;
};

#endif
