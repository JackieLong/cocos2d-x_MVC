#pragma once

#ifndef _EVENTDISPATCHER_MVC_H_
#define _EVENTDISPATCHER_MVC_H_

#include "cocos2d.h"
#include "Macro.h"
#include "Activity.h"

NS_MVC_BEGIN

// 负责MVC框架的消息通讯，独立的一个EventDispatcher，和引擎内部的互不影响。
class EventMVCDispatcher : cocos2d::Ref
{
    // 成员全部私有，只能友元调用防止滥用
    friend class Facade;
    friend class ActivityMgr;

private:

    EventMVCDispatcher* start();
    EventMVCDispatcher* end();

    // 使Activity可以接收来自DataProxy和View的事件，即使onEvent和handleEvent生效。
    bool addListener( Activity* activity );
    void removeListener( const Activity* activity );
    void dispatchEvent( const EventNameMVC &, void* data = nullptr );

private:
    EventMVCDispatcher();
    virtual ~EventMVCDispatcher();

private:

    //{
    //    {
    //        activity1,  // activity1监听的事件
    //        {
    //            { eventNameMVC1, listener },    // 接收事件eventNameMVC1，触发回调listener
    //            { eventNameMVC2, listener },
    //        }
    //    }
    //    {
    //        activity2,  // activity2监听的事件
    //        {
    //            { eventNameMVC1, listener },
    //            { eventNameMVC2, listener },
    //        }
    //    }
    //}
    RegEventMVCListeners _listeners;

    cocos2d::EventDispatcher* _eventDispatcher;
};

NS_MVC_END


#endif // !_EVENTMGR_H_
