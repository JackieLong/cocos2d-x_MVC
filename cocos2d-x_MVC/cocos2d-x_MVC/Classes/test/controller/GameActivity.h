#pragma once

#ifndef _GAMEACTIVITY_H_
#define _GAMEACTIVITY_H_

#include "../../MVC.h"
#include "../view/GameView.h"
#include "../model/GameData.h"

class GameActivity : public mvc::Activity
{
public:
    void start();
    void restart();
    void pause();
    void stop();
    void updateView();

public:
    GameActivity();
    ~GameActivity();

    virtual void onCreate()  override;
    virtual void onResume()  override;
    virtual void onPause()   override;
    virtual void onDestroy() override;
    virtual const std::vector<std::pair<DataProxyID, const cocos2d::Ref*>> onDataProxy() override;
    virtual const std::vector<EventNameMVC> onEvent() override;
    virtual void handleEvent( const EventNameMVC &, void* data = nullptr ) override;

    void update( float dt );

private:
    void onBtnClickListener( cocos2d::Ref* );
    cocos2d::Node* genBug();

private:
    GameView                    _gameView;
    GameData*                   _gameData;
    std::vector<cocos2d::Node*> _bugs;
    cocos2d::Vec2               _holePos;
    double                      _dt;
};

#endif // !_GAMEACTIVITY_H_