#ifndef ROOMS_H
#define ROOMS_H

#include "../engine/AnimatedSprite.h"
#include "../engine/Camera.h"
#include "../engine/CollisionSystem.h"
#include "../engine/Game.h"
#include "../engine/Scene.h"
#include "../engine/SceneManager.h"
#include "../engine/Sprite.h"
#include "../engine/StatBar.h"
#include "../engine/things/Coin.h"
#include "../engine/things/Player.h"
#include "../engine/things/SelectionMenuBase.h"
#include "../engine/things/SelectionMenuOption.h"
#include "../engine/things/TextBox.h"
#include "../engine/tweens/Tween.h"
#include "../engine/tweens/TweenJuggler.h"
#include "../engine/events/GameOverEvent.h"

class Rooms : public Game {

public:
	Rooms();

    void update(const unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const unordered_set<Uint8>& pressedButtons) override;
	void draw(AffineTransform& at) override;
    void handleEvent(Event * e) override;

private:
    bool esc_prepressed = false;
    bool sceneChange = false;
    bool sceneChange2 = false;

    std::shared_ptr<SceneManager> sceneManager;
    //bool prevScene = false;

	std::shared_ptr<Camera> camera;

	std::shared_ptr<Player> player;

    std::shared_ptr<SelectionMenuBase> selection_menu_base;
    std::shared_ptr<SelectionMenuOption> selection_quit_option;
    std::shared_ptr<SelectionMenuOption> selection_resume_option;


    std::shared_ptr<SelectionMenuBase> gameover_base;
    std::shared_ptr<SelectionMenuOption> gameover_quit_option;
    std::shared_ptr<SelectionMenuOption> gameover_resume_option;

    std::shared_ptr<Scene> scene;
    std::shared_ptr<Scene> scene2;
    std::shared_ptr<Scene> scene3;

    std::shared_ptr<TextBox> start_text_box;

    std::shared_ptr<StatBar> health;

    int room;

    std::unique_ptr<CollisionSystem> collisionSystem;

    std::shared_ptr<Tween> player_tween;
    std::shared_ptr<Tween> start_text_tween;
    std::shared_ptr<Tween> scene_transition;

    std::unordered_set<SDL_Scancode> prevKeys;
};

#endif
