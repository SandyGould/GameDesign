#pragma once

#include "../../engine/Game.h"
#include "../../engine/WalkOnObject.h"
#include "../../engine/enemies/Archer.h"
#include "../../engine/enemies/Cannoneer.h"
#include "../../engine/enemies/KingdomArcher.h"
#include "../../engine/enemies/KingdomKing.h"
#include "../../engine/enemies/KingdomMage.h"
#include "../../engine/enemies/Knight.h"
#include "../../engine/enemies/Mage.h"
#include "../../engine/enemies/MasterArcher.h"
#include "../../engine/enemies/MonsterKing.h"
#include "../../engine/enemies/Ogre.h"
#include "../../engine/enemies/Orc.h"
#include "../../engine/enemies/Poisoner.h"
#include "../../engine/enemies/Roar.h"
#include "../../engine/enemies/RoarMonster.h"
#include "../../engine/enemies/RubberCannoneer.h"
#include "../../engine/enemies/SecondBoss.h"
#include "../../engine/projectiles/Arrow.h"
#include "../../engine/projectiles/CannonBall.h"
#include "../../engine/projectiles/IceAttack.h"
#include "../../engine/projectiles/MageAttack.h"
#include "../../engine/projectiles/PoisonBomb.h"
#include "../../engine/projectiles/RubberCannonBall.h"
#include "../../engine/things/Chest.h"
#include "../../engine/things/Coin.h"
#include "../../engine/things/Player.h"
#include "../../engine/things/Shield.h"

#include <memory>
#include <unordered_set>

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
