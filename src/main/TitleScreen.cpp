#include "TitleScreen.h"

#include "../engine/events/GameStartEvent.h"
#include "../engine/events/MouseDownEvent.h"

#include <iostream>

using namespace std;

TitleScreen::TitleScreen() : Game(600, 500) {
    instance = this;

    EventDispatcher::getInstance().addEventListener(this, GameStartEvent::GAME_START_EVENT);
    selection_menu_base = std::make_shared<SelectionMenuBase>();
    selection_menu_base->width = 600;
    selection_menu_base->height = 500;
    container->addChild(selection_menu_base);

    selection_resume_option = std::make_shared<SelectionMenuOption>(SelectionMenuOption::START, "Start");
    selection_resume_option->width = 200;
    selection_resume_option->height = 50;
    selection_resume_option->position = {200, 200};
    selection_resume_option->updateAlpha();
    selection_menu_base->addChild(selection_resume_option);

    selection_quit_option = std::make_shared<SelectionMenuOption>(SelectionMenuOption::QUIT, "Quit");
    selection_quit_option->width = 200;
    selection_quit_option->height = 50;
    selection_quit_option->position = {200, 300};
    selection_quit_option->updateAlpha();
    selection_menu_base->addChild(selection_quit_option);

    EventDispatcher::getInstance().addEventListener(this->selection_resume_option.get(), MouseDownEvent::MOUSE_DOWN_EVENT);
    EventDispatcher::getInstance().addEventListener(this->selection_quit_option.get(), MouseDownEvent::MOUSE_DOWN_EVENT);
}

void TitleScreen::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) {
    Game::update(pressedKeys, joystickState, pressedButtons);
}

void TitleScreen::draw(AffineTransform& at) {
    Game::draw(at);
}

void TitleScreen::handleEvent(Event* e) {
    if (e->getType() == GameStartEvent::GAME_START_EVENT) {
        this->quit = true;
    }
}