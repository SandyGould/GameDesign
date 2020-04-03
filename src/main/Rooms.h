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
#include "../engine/QuestManager.h"
#include "../engine/events/PickedUpEvent.h"
// #include "../engine/Sound.h"
#include "../tweens/Tween.h"
#include "../tweens/TweenJuggler.h"


class Rooms : public Game {

public:
	Rooms();
	virtual ~Rooms();

    void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;
	void draw(AffineTransform& at) override;

private:
    bool esc_prepressed = false;

	Camera* camera;

	AnimatedSprite* player;

    SelectionMenuBase* selection_menu_base;
    SelectionMenuOption * selection_quit_option;
    SelectionMenuOption * selection_resume_option;
    
    Scene* scene;

    TextBox* start_text_box;

    Tween* player_tween;
    Tween* start_text_tween;
};

#endif