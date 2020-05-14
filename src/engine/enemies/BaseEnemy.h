#ifndef BASEENEMY_H
#define BASEENEMY_H

#include "../AnimatedSprite.h"
#include "../events/EventListener.h"
#include "../events/EventDispatcher.h"
#include "../things/Player.h"
#include "../Sprite.h"
#include "Projectile.h"
#include "../tweens/Tween.h"
#include "../tweens/TweenJuggler.h"

class BaseEnemy : public AnimatedSprite{

public:

    BaseEnemy(std::string id, std::string spritesheet, std::string xml, std::string animName, std::shared_ptr<Player> player);

    void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
    void draw(AffineTransform& at) override;
    bool onCollision(std::shared_ptr<DisplayObject> other) override;

    void changeHealth(int amount);

    //Knowing about the player is nice :)
    std::shared_ptr<Player> player;

    std::shared_ptr<Tween> damage;

    //Info about the Enemies' state
    int health = 100;
    int state = 0;
    double speed = 1;
private:
    int collisionWaitTime = 0;

};

#endif
