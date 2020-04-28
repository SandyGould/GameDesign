#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include "../DisplayObject.h"
#include "../events/EventListener.h"
#include "TextBox.h"

#include <string>

class GameOverScreen : public DisplayObject {

public:

	explicit GameOverScreen();
    ~GameOverScreen();

	virtual void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
	virtual void draw(AffineTransform& at) override;

private:
    std::shared_ptr<DisplayObject> gameOver;
    std::shared_ptr<DisplayObject> background;
    std::shared_ptr<TextBox> inspiration;
    std::shared_ptr<TextBox> do_continue;
};

#endif