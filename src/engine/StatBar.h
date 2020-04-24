#ifndef STATBAR_H
#define STATBAR_H

#include "DisplayObject.h"
#include "things/Player.h"
#include "Game.h"
#include <string>

class StatBar : public DisplayObject {

public:
    explicit StatBar(std::string id, std::shared_ptr<Player> player);
    StatBar(std::string id, int red, int green, int blue, std::shared_ptr<Player> player);
    StatBar(std::string id, int red, int green, int blue, std::shared_ptr<Player> player, int w, int h);

	~StatBar() override;

	void scaleStat(double change);

    void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
    void updateHealth();
	void draw(AffineTransform& at) override;

private:
    double StatPerc;
    std::shared_ptr<Player> player;
};
#endif
