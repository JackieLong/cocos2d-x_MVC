#pragma once

#ifndef _ACTIVITY_MVC_H_
#define _ACTIVITY_MVC_H_

#include "cocos2d.h"
#include "Macro.h"

NS_MVC_BEGIN

// 将游戏看成一个大任务，由很多的子任务（Activity）构成，这些子任务维护在一个栈中
// 一个UI界面及其（交互）功能可以看成一个任务，比如一个签到模块，有UI，有交互（签到功能、签到查询等）。
// 也可以只是一个界面（没有交互，没有数据请求）。
// 也可以是没有界面，只是在后台默默处理数据（数据请求、接收），比如与服务器的通讯连接模块。

// 从MVC上说：
// Activity（Controller）是Model（DataProxy）和View的协调者，为了让Model和View能够完全分离而存在。
// Activity直接操控DataProxy和View进行逻辑处理，而后两者的变化则通过消息通知Activity。
class Activity : public cocos2d::Ref
{

public:

    // Activity已经压栈，则代表已经激活
    bool active();

    // 事件通知，Activity之间可能需要事件通知。
    void dispatchEvent( const EventNameMVC &eventName, void* data = nullptr );

public:

    // Activity的生命周期，

    virtual void onCreate() = 0;    // 1、创建：如View
    virtual void onResume();        // 2、初始化：初始化View的数
    virtual void onPause();         // 3、Activity暂停回调
    virtual void onDestroy();       // 4、Activity销毁回调

    virtual const std::vector<std::pair<DataProxyID, const cocos2d::Ref*>> onDataProxy() = 0;
    virtual const std::vector<EventNameMVC> onEvent() = 0;
    virtual void handleEvent( const EventNameMVC &eventName, void* data = nullptr ) = 0;

public:
    Activity();
    virtual ~Activity();

private:
    bool _active;
};

// Activity的逻辑很可能会非常繁杂，HeavyTask的设计目的是用于分散Activity的逻辑。

class HeavyTask : public cocos2d::Ref
{
private:

};

NS_MVC_END

#endif // _DEBUG