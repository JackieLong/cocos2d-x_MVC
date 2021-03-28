#pragma once

#ifndef _GAMEVIEW_H_
#define _GAMEVIEW_H_

#include "../../MVC.h"

enum TAG_GAMEVIEW
{
    LAND = 1,
    HOLE,
    BTN_START,
    BTN_RESTART,
    BTN_STOP,
    BTN_INCRI,
    BTN_DECRI,
    BTN_PAUSE,
    TXT_DENSITY,
    TXT_LIFE,

    TAG_MAX
};

class GameView : public mvc::View
{
    // GameView只属于GameActivity
    friend class GameActivity;

private:
    GameView();
    virtual ~GameView();
    virtual cocos2d::Node* onCreate() override;
};

#endif