#include "DisplayObject.h"
#include "Game.h"
#include <string>

class HealthBar : public DisplayObject {

public:
    HealthBar(std::string id);
    HealthBar(std::string id, int red, int green, int blue);
    HealthBar(std::string id, int red, int green, int blue, int w, int h);

	virtual ~HealthBar();

	void scaleHealth(double change);

	virtual void update(std::unordered_set<SDL_Scancode> pressedKeys, jState joystickState, std::unordered_set<Uint8> pressedButtons);
	virtual void draw(AffineTransform& at);
    virtual void draw(AffineTransform& at, SDL_Renderer* r, SDL_Rect* src = NULL);

private:
    double healthPerc;
};
