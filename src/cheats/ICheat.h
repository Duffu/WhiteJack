#pragma once
#include "managers/UIManager.h"
#include "game/Card.h"
#include "game/Deck.h"
#include "game/Hand.h"
#include "game/Player.h"

enum class CheatState
{
    RUNNING,
    SUCCESS,
    REWARD,
    FAIL
};
enum class ArrowState
{
    MOVING_DOWN,
    MOVING_UP,
};
enum class PoppedCardState
{
    SHOW,
    Hide
};
class ICheat
{
public:
    virtual ~ICheat() {}

    virtual void Start() = 0;
    virtual void Update(float dt) = 0;
    virtual void Draw(UIManager &uiManager) = 0;
    virtual CheatState GetState() const = 0;
};