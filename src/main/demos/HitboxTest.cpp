#include <iostream>

#include "HitboxTest.h"

using namespace std;

HitboxTest::HitboxTest() : Game(1200, 800) {
    instance = this;

    player = std::make_shared<Player>();
    // player->height = 80;
    // player->width = 110;
    this->container->addChild(player);

    // this->container->addChild(std::make_shared<Archer>(player));
    // this->container->addChild(std::make_shared<Arrow>(0));
    // this->container->addChild(std::make_shared<CannonBall>());
    // this->container->addChild(std::make_shared<Cannoneer>(player));
    // this->container->addChild(std::make_shared<IceAttack>());
    // this->container->addChild(std::make_shared<KingdomArcher>(player));
    // this->container->addChild(std::make_shared<KingdomKing>(player));
    // this->container->addChild(std::make_shared<KingdomMage>(player));
    // this->container->addChild(std::make_shared<Knight>(player));
    // this->container->addChild(std::make_shared<Mage>(player));
    // this->container->addChild(std::make_shared<MageAttack>());
    // this->container->addChild(std::make_shared<MasterArcher>(player));
    // this->container->addChild(std::make_shared<MonsterKing>(player));
    // this->container->addChild(std::make_shared<Ogre>(player));
    // this->container->addChild(std::make_shared<Orc>(player));
    // this->container->addChild(std::make_shared<PoisonBomb>());
    // this->container->addChild(std::make_shared<Poisoner>(player));
    // this->container->addChild(std::make_shared<Roar>());
    // this->container->addChild(std::make_shared<RoarMonster>(player));
    // this->container->addChild(std::make_shared<RubberCannonBall>(0));
    // this->container->addChild(std::make_shared<RubberCannoneer>(player));
    // this->container->addChild(std::make_shared<SecondBoss>(player));
    this->container->addChild(std::make_shared<WalkOnObject>("mud", "./resources/assets/Display_Objects/mud1.png"));
    this->container->addChild(std::make_shared<WalkOnObject>("mud", "./resources/assets/Display_Objects/mud2.png"));
    this->container->addChild(std::make_shared<WalkOnObject>("mud", "./resources/assets/Display_Objects/mud3.png"));
    this->container->addChild(std::make_shared<WalkOnObject>("mud", "./resources/assets/Display_Objects/mud4.png"));
    this->container->addChild(std::make_shared<WalkOnObject>("mud", "./resources/assets/Display_Objects/mud5.png"));
    this->container->addChild(std::make_shared<WalkOnObject>("mud", "./resources/assets/Display_Objects/mud6.png"));
    this->container->addChild(std::make_shared<WalkOnObject>("mud", "./resources/assets/Display_Objects/mud7.png"));
    this->container->addChild(std::make_shared<WalkOnObject>("mud", "./resources/assets/Display_Objects/mud8.png"));

    this->container->addChild(std::make_shared<Chest>());
    this->container->addChild(std::make_shared<Coin>());
    this->container->addChild(std::make_shared<Shield>());

    maxIndex = 11;
}

HitboxTest::~HitboxTest() {
    
}

void HitboxTest::update(const unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const unordered_set<Uint8>& pressedButtons) {
    if (init < 10){
        for (int i = 0; i < maxIndex; i++){
            this->container->getChild(i)->visible = false;
            this->container->getChild(i)->position = {600, 400};
        }
        this->container->getChild(index)->visible = true;
        ++init;
    }
    //If there isn't controller input, take keyboard input. Otherwise ignore keyboard input.
    int DEAD_ZONE = 8000;
    if (pressedButtons.empty() && abs(joystickState.xVal1) - DEAD_ZONE < 0 && abs(joystickState.yVal1) - DEAD_ZONE < 0 
                               && abs(joystickState.xVal2) - DEAD_ZONE < 0 && abs(joystickState.yVal2) - DEAD_ZONE < 0){
        // Here
        if (pressedKeys.find(SDL_SCANCODE_TAB) != pressedKeys.end() &&
            prevKeys.find(SDL_SCANCODE_TAB) == prevKeys.end()) {
            this->container->getChild(index)->visible = false;

            if (SDL_GetModState() & KMOD_SHIFT){
                if (index != 0){
                    --index;
                } else{
                    index = (maxIndex - 1);
                }
            } else{
                if (index != (maxIndex - 1)){
                    ++index;
                } else{
                    index = 0;
                }
            }

            this->container->getChild(index)->visible = true;
        }

        if (pressedKeys.find(SDL_SCANCODE_H) != pressedKeys.end() && SDL_GetModState() & KMOD_CTRL){
            if (SDL_GetModState() & KMOD_SHIFT){
                int r, l, t, b;
                cin >> r;
                cin >> l;
                cin >> t;
                cin >> b;
                this->container->getChild(index)->setHitbox(r, l, t, b);
            } else{
                double r, l, t, b;
                cin >> r;
                cin >> l;
                cin >> t;
                cin >> b;
                this->container->getChild(index)->setHitbox(r, l, t, b);
            }
        }
	} else{
		// Honestly this doesn't need to check for controller input but it does anyway
        // If there is controller input, do nothing!
	}

    this->prevKeys = pressedKeys;
    Game::update(pressedKeys, joystickState, pressedButtons);
}

void HitboxTest::draw(AffineTransform& at) {
    Game::draw(at);
}

void HitboxTest::draw_post() {
    this->container->getChild(index)->drawHitbox();
}
