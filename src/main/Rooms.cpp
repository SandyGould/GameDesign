#include "Rooms.h"

#include "../engine/events/GameOverEvent.h"
#include "../engine/events/PlayerDeathEvent.h"
#include "../engine/events/RestartEvent.h"
#include "../engine/events/TweenEvent.h"

#include <cmath>
#include <iostream>

using namespace std;

Rooms::Rooms() : Game(600, 500) {
    instance = this;

    // create collision system
    this->collisionSystem = std::make_unique<CollisionSystem>();
    // set collisions between player and all environmental objects
    this->collisionSystem->watchForCollisions("player", "Switch");
    this->collisionSystem->watchForCollisions("player", "WalkOnObject");
    this->collisionSystem->watchForCollisions("player", "EnvironmentObject");
    this->collisionSystem->watchForCollisions("player", "arrow");
    this->collisionSystem->watchForCollisions("player", "knight");
    this->collisionSystem->watchForCollisions("player", "orc");
    this->collisionSystem->watchForCollisions("player", "ogre");
    this->collisionSystem->watchForCollisions("player", "mage_attack");
    this->collisionSystem->watchForCollisions("player", "cannonball");
    this->collisionSystem->watchForCollisions("shield", "arrow");
    this->collisionSystem->watchForCollisions("shield", "mage_attack");
    this->collisionSystem->watchForCollisions("shield", "enemy");
    this->collisionSystem->watchForCollisions("shield", "orc");
    this->collisionSystem->watchForCollisions("shield", "knight");
    this->collisionSystem->watchForCollisions("shield", "ogre");
    this->collisionSystem->watchForCollisions("enemy", "EnvironmentObject");
    this->collisionSystem->watchForCollisions("enemy", "WalkOnObject");
    this->collisionSystem->watchForCollisions("enemy", "arrow");
    this->collisionSystem->watchForCollisions("enemy", "mage_attack");
    this->collisionSystem->watchForCollisions("enemy", "cannonball");
    this->collisionSystem->watchForCollisions("orc", "EnvironmentObject");
    this->collisionSystem->watchForCollisions("orc", "WalkOnObject");
    this->collisionSystem->watchForCollisions("orc", "arrow");
    this->collisionSystem->watchForCollisions("orc", "mage_attack");
    this->collisionSystem->watchForCollisions("orc", "cannonball");
    this->collisionSystem->watchForCollisions("knight", "EnvironmentObject");
    this->collisionSystem->watchForCollisions("knight", "WalkOnObject");
    this->collisionSystem->watchForCollisions("knight", "arrow");
    this->collisionSystem->watchForCollisions("knight", "mage_attack");
    this->collisionSystem->watchForCollisions("knight", "cannonball");
    this->collisionSystem->watchForCollisions("ogre", "EnvironmentObject");
    this->collisionSystem->watchForCollisions("ogre", "WalkOnObject");
    this->collisionSystem->watchForCollisions("ogre", "arrow");
    this->collisionSystem->watchForCollisions("ogre", "mage_attack");
    this->collisionSystem->watchForCollisions("ogre", "cannonball");

    camera = std::make_shared<Camera>(this->windowWidth, this->windowHeight);
    container->addChild(camera);

    // load and prep player
    player = std::make_shared<Player>();

    // start text box
    start_text_box = std::make_shared<TextBox>("start_text", "Welcome to Rebound!\n\nPress any key to continue");
    start_text_box->addTextPanel("To move, press up, down, left, or right\n\nPress any key to continue");
    start_text_box->position = {300, 300};
    start_text_box->alpha = 0;
    container->addChild(start_text_box);

    // menu
    selection_menu_base = std::make_shared<SelectionMenuBase>();
    selection_menu_base->width = 600;
    selection_menu_base->height = 500;

    selection_resume_option = std::make_shared<SelectionMenuOption>(selection_menu_base.get(), SelectionMenuOption::RESUME, "Resume");
    selection_resume_option->position = {200, 220};
    selection_menu_base->addChild(selection_resume_option);

    selection_quit_option = std::make_shared<SelectionMenuOption>(selection_menu_base.get(), SelectionMenuOption::QUIT, "Quit");
    selection_quit_option->position = {200, 320};
    selection_menu_base->addChild(selection_quit_option);

    pause_graphic = std::make_shared<DisplayObject>("pausegraphic", "./resources/Rebound/pause-screen/pause.png");
    pause_graphic->width = 500;
    pause_graphic->height = 250;
    pause_graphic->position = {50, -10};
    selection_menu_base->addChild(pause_graphic);



    //Game Over menu
    gameover_base = std::make_shared<SelectionMenuBase>("game_over");
    gameover_base->width = 600;
    gameover_base->height = 500;

    gameover_resume_option = std::make_shared<SelectionMenuOption>(gameover_base.get(), SelectionMenuOption::CONTINUE, "Continue");
    gameover_resume_option->position = {200, 200};
    gameover_base->addChild(gameover_resume_option);

    gameover_quit_option = std::make_shared<SelectionMenuOption>(gameover_base.get(), SelectionMenuOption::QUIT, "Quit");
    gameover_quit_option->position = {200, 300};
    gameover_base->addChild(gameover_quit_option);

    gameover_graphic = std::make_shared<DisplayObject>("gameovergraphic", "./resources/Rebound/game-over-screen/game_over_text.png");
    gameover_graphic->width = 200;
    gameover_graphic->height = 200;
    gameover_graphic->position = {200, 0};
    gameover_base->addChild(gameover_graphic);

    // health bar
    health = std::make_shared<StatBar>("Health", "./resources/Rebound/greenbar (3).png", &player->health, 100, 255, 0, 0);
    container->addChild(health);

    // stamina bar
    stamina = std::make_shared<StatBar>("Stamina", "./resources/Rebound/greenbar (3).png", &player->stamina, 1000, 0, 0, 255);
    container->addChild(stamina);

    // tween stuff
    auto player_spawn_tween = std::make_shared<Tween>("player_spawn_tween", player);

    player_spawn_tween->animate(TweenableParam::SCALE_X, 5.0, 1.0, 0, 100);
    player_spawn_tween->animate(TweenableParam::SCALE_Y, 5.0, 1.0, 0, 100);
    player_spawn_tween->animate(TweenableParam::ALPHA, 0, 255, 0, 100);

    TweenJuggler::getInstance().add(player_spawn_tween);
    EventDispatcher::getInstance().addEventListener(this->start_text_box.get(), TweenEvent::TWEEN_COMPLETE_EVENT);

    EventDispatcher::getInstance().addEventListener(this, PlayerDeathEvent::PLAYER_DEATH_EVENT);
    EventDispatcher::getInstance().addEventListener(this, GameOverEvent::GAME_OVER_EVENT);
    EventDispatcher::getInstance().addEventListener(this, RestartEvent::RESTART_EVENT);

    this->sceneManager = std::make_unique<SceneManager>(camera, player);
    // load first scene
    this->sceneManager->loadFirstScene();
}

void Rooms::update(const unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const unordered_set<Uint8>& pressedButtons) {
    // menu controls
    if (pressedKeys.find(SDL_SCANCODE_ESCAPE) != pressedKeys.end() &&
        prevKeys.find(SDL_SCANCODE_ESCAPE) == prevKeys.end()) {
        if (selection_menu_base->active) {
            Game::instance->paused = false;
            container->removeImmediateChild(selection_menu_base);
        } else {
            Game::instance->paused = true;
            container->addChild(selection_menu_base);
        }
    }

    if (pressedKeys.find(SDL_SCANCODE_BACKSLASH) != pressedKeys.end() &&
        prevKeys.find(SDL_SCANCODE_BACKSLASH) == prevKeys.end()) {
        Game::instance->container->printDisplayTree();
    }

    prevKeys = pressedKeys;

    // update scene if criteria for changing scene are met
    this->sceneManager->updateScene();

    Game::update(pressedKeys, joystickState, pressedButtons);
    this->collisionSystem->update();
    camera->follow(player->position.x, player->position.y);
}

void Rooms::draw(AffineTransform& at) {
    Game::draw(at);
}

void Rooms::handleEvent(Event* e) {
    if (e->getType() == PlayerDeathEvent::PLAYER_DEATH_EVENT) {
        EventDispatcher::getInstance().removeEventListener(this, PlayerDeathEvent::PLAYER_DEATH_EVENT);

        auto player_death_tween = std::make_shared<Tween>("player_death_tween", player);

        player_death_tween->animate(TweenableParam::SCALE_X, 1.0, 0.0, 0, 100);
        player_death_tween->animate(TweenableParam::SCALE_Y, 1.0, 0.0, 0, 100);
        player_death_tween->animate(TweenableParam::ROTATION, 0.0, 4 * PI, 0, 100);
        player_death_tween->animate(TweenableParam::ALPHA, 255, 0, 0, 100);

        TweenJuggler::getInstance().remove("damage_player");
        TweenJuggler::getInstance().add(player_death_tween);

        this->sceneManager->unloadScene();

        EventDispatcher::getInstance().addEventListener(this, TweenEvent::TWEEN_COMPLETE_EVENT);
    } else if (e->getType() == TweenEvent::TWEEN_COMPLETE_EVENT) {
        auto* event = dynamic_cast<TweenEvent*>(e);
        if (event->getTween()->getID() == "player_death_tween") {
            EventDispatcher::getInstance().removeEventListener(this, TweenEvent::TWEEN_COMPLETE_EVENT);

            player->removeThis();
            health->removeThis();

            auto* gameOverEvent = new GameOverEvent();
            EventDispatcher::getInstance().dispatchEvent(gameOverEvent);
            delete gameOverEvent;
        }
    } else if(e->getType() == GameOverEvent::GAME_OVER_EVENT) {
        container->addChild(gameover_base);
    } else if(e->getType() == RestartEvent::RESTART_EVENT) {
        container->removeImmediateChild(gameover_base);
        container->addChild(health);

        auto player_spawn_tween = std::make_shared<Tween>("player_spawn_tween", player);

        player_spawn_tween->animate(TweenableParam::SCALE_X, 5.0, 1.0, 0, 100);
        player_spawn_tween->animate(TweenableParam::SCALE_Y, 5.0, 1.0, 0, 100);
        player_spawn_tween->animate(TweenableParam::ALPHA, 0, 255, 0, 100);

        TweenJuggler::getInstance().add(player_spawn_tween);

        EventDispatcher::getInstance().addEventListener(this, PlayerDeathEvent::PLAYER_DEATH_EVENT);
    }
}
