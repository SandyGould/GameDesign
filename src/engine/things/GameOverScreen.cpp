#include "GameOverScreen.h"

#include <iostream>


GameOverScreen::GameOverScreen() : DisplayObject("GameOverScreen") {
    this->gameOver = std::make_shared<DisplayObject>("game_over_label", "./resources/Rebound/game-over-screen/game_over_text.png");
    // set size and position here
    this->gameOver->position = {50, 150};
    this->addChild(this->gameOver);

    this->inspiration = std::make_shared<TextBox>("inspiration!", "But don't give up hope!");
    // set size and position
    this->inspiration->position = {60, 300};
    this->addChild(this->inspiration);
	
    this->do_continue = std::make_shared<TextBox>("do_continue", "Press any key to continue");
    // set size and position 
    this->do_continue->position = {300, 300};
    this->addChild(this->do_continue);


}

GameOverScreen::~GameOverScreen() {
    // delete this->inspiration;
    // delete this->do_continue;
}

void GameOverScreen::update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) {
    DisplayObject::update(pressedKeys, joystickState, pressedButtons);
}

void GameOverScreen::draw(AffineTransform& at) {
    DisplayObject::draw(at);
}