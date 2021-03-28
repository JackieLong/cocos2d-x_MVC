#pragma once

#ifndef _FACADE_MVC_H_
#define _FACADE_MVC_H_

#include "cocos2d.h"
#include "Macro.h"
#include "EventDispatcher.h"
#include "ActivityMgr.h"
#include "DataProxyMgr.h"

NS_MVC_BEGIN

// ****************************************************************
//
//  FacadeInstance->start();                                            // 第一次进入游戏，初始化
//  FacadeInstance->regActivity( "GameActivity", new GameActivity );    // 注册Activity
//  FacadeInstance->startActivity( "GameActivity" );                    // 启动GameActivity，Activity压栈
//  FacadeInstance->back();                                             // 返回上一个Activity，这里栈已经空了，所以会退出游戏
//
//  FacadeInstance->end();                                              // 立即退出游戏

//  FacadeInstance->unRegActivity("GameActivity");                      // 注销Activity
//  FacadeInstance->startActivity("GameActivity");                      // Activity不存在，不会有任何效果
//
//  FacadeInstance->dispatchEvent("MotherFucker");                      // 注册了MotherFucker监听的Activity会收到这个事件
//
// ****************************************************************

// Facade是MVC的总指挥，EventDispatcher、ActivityMgr、DataProxyMgr的总代理
// EventDispatcher、ActivityMgr、DataProxyMgr的成员全部私有，Facde是其友元
class Facade : public cocos2d::Ref
{
public:
    static Facade* getInstance();
    Facade* start();

private:
    Facade* end();      // 没必要的感觉

public:

    // 代理ActivityMgr

    // 获得已注册的Activity
    template<typename T>
    T getActivity( const ActivityID &activityID )
    {
        return dynamic_cast<T>( _activityMgr->getActivity( activityID ) );
    }

    // 注册（注销）Activity，只有注册了，Activity才可能被使用
    bool regActivity( const ActivityID &, Activity* );
    void unRegActivity( const ActivityID & );

    // 启动Activity，Activity压栈，当然也有可能Activity已经在栈中
    void startActivity( const ActivityID &, const ActivityStackAction &action = DEFAULT_ACTION );

    // 返回，Activity栈弹栈
    void back();

public:

    // 代理DataProxyMgr

    // 同上Activity理
    template<typename T>
    T getDataProxy( const DataProxyID &dataProxyID, const T fuck = nullptr )
    {
        return dynamic_cast<T>( _dataProxyMgr->getDataProxy( dataProxyID ) );
    }

private:

    // 代理DataProxyMgr，私有化的原因：DataProxy由Activity操控，因此DataProxy的注册也依附于Activity

    bool regDataProxy( const DataProxyID &, const cocos2d::Ref* activity, const DataProxy* );
    void unRegDataProxy( const DataProxyID & );

public:

    // 代理EventDispatcher

    // 派发事件接口，完成MVC之间的通讯
    void dispatchEvent( const EventNameMVC &, void* data = nullptr );
    EventMVCDispatcher* getEventDispatcher();

private:
    Facade();
    ~Facade();

private:
    static Facade*      _pInstance;
    EventMVCDispatcher* _eventDispatcher;
    ActivityMgr*        _activityMgr;
    DataProxyMgr*       _dataProxyMgr;
};

NS_MVC_END

#endif // _DEBUG