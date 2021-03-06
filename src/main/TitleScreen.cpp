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

    selection_resume_option = std::make_shared<SelectionMenuOption>(selection_menu_base.get(), SelectionMenuOption::START, "Start");
    selection_resume_option->position = {200, 200};
    selection_menu_base->addChild(selection_resume_option);

    selection_quit_option = std::make_shared<SelectionMenuOption>(selection_menu_base.get(), SelectionMenuOption::QUIT, "Quit");
    selection_quit_option->position = {200, 300};
    selection_menu_base->addChild(selection_quit_option);

    title_graphic = std::make_shared<DisplayObject>("title","./resources/Rebound/title-screen/Title.png");
    title_graphic->width = 200;
    title_graphic->height = 200;
    title_graphic->position = {200, 0};
    selection_menu_base->addChild(title_graphic);

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
