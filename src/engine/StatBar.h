#include "DisplayObject.h"
#include "Game.h"
#include <string>

class StatBar : public DisplayObject {

public:
    explicit StatBar(std::string id);
    StatBar(std::string id, int red, int green, int blue);
    StatBar(std::string id, int red, int green, int blue, int w, int h);

	virtual ~StatBar();

	void scaleStat(double change);

	void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons) override;
	void draw(AffineTransform& at) override;

private:
    double StatPerc;
};
