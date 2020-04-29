#pragma once

#include <unordered_set>
#include <memory>

#include "../../engine/Game.h"

#include "../../engine/enemies/Archer.h"
#include "../../engine/enemies/Arrow.h"
#include "../../engine/enemies/CannonBall.h"
#include "../../engine/enemies/Cannoneer.h"
#include "../../engine/enemies/IceAttack.h"
#include "../../engine/enemies/KingdomArcher.h"
#include "../../engine/enemies/KingdomKing.h"
#include "../../engine/enemies/KingdomMage.h"
#include "../../engine/enemies/Knight.h"
#include "../../engine/enemies/Mage.h"
#include "../../engine/enemies/MageAttack.h"
#include "../../engine/enemies/MasterArcher.h"
#include "../../engine/enemies/MonsterKing.h"
#include "../../engine/enemies/Ogre.h"
#include "../../engine/enemies/Orc.h"
#include "../../engine/enemies/PoisonBomb.h"
#include "../../engine/enemies/Poisoner.h"
#include "../../engine/enemies/Roar.h"
#include "../../engine/enemies/RoarMonster.h"
#include "../../engine/enemies/RubberCannonBall.h"
#include "../../engine/enemies/RubberCannoneer.h"
#include "../../engine/enemies/SecondBoss.h"

#include "../../engine/things/Chest.h"
#include "../../engine/things/Coin.h"
#include "../../engine/things/Player.h"
#include "../../engine/things/Shield.h"

class HitboxTest : public Game {

public:
    HitboxTest();
    ~HitboxTest() override;

private:
    void update(const std::unordered_set<SDL_Scancode>& pressedKeys, const jState& joystickState, const std::unordered_set<Uint8>& pressedButtons) override;
    void draw(AffineTransform &at) override;
    void draw_post() override;

    std::shared_ptr<Player> player;

    int init = 0;
    int index = 0;
    int maxIndex = 0;
    std::unordered_set<SDL_Scancode> prevKeys;
};
