//This is my parent Projectiles Class.
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../Sprite.h"
#include "../events/EventDispatcher.h"
#include "../events/Collision.h"
#include "../events/Event.h"

class Projectile : public Sprite{

    public:
    Projectile(std::string id, std::string filepath, int velocity);
    double velocity;
    void fire(double angle); //Every projectile will need to fire at some point
    bool firing;
    bool magic = false;
    bool reflected = false;
    int lifetime = 600;
    double deltaX;
    double deltaY;
    double storedDeltaX;
    double storedDeltaY;
    double distance(SDL_Point& p1, SDL_Point& p2);
    void reflect(double speedMult, double deltaX, double deltaY);

    double aim(std::shared_ptr<DisplayObject> targetSprite);
    void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
};

#endif
