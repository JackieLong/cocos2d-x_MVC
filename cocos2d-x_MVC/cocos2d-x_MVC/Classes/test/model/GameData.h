#pragma once

#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_

#include "../../MVC.h"

class GameData : public mvc::DataProxy
{
    // GameData只属于GameActivity，如果别处想获取数据，问GameActivity要。
    friend class GameActivity;

private:

    // 提供给GameActivity修改GameData的接口

    void changeDensity( const float & );    // 修改进攻强度
    void changeLife( const int & );         // 修改生命数
    void lossLife();                        // 生命数 - 1
    bool dead();                            // 生命数是否等于0

private:
    GameData();
    virtual ~GameData();
    virtual void onInit() override;

private:
    const static int INIT_LIFE_NUM = 3;     // 初始命数

private:
    bool  _pause;                           // 当前暂停状态
    int   _lifeNum;                         // 当前生命数
    float _attackDensity;                   // 当前进攻强度
    bool  _attacking;                       // 当前进攻状态，和暂停互不影响
};

#endif