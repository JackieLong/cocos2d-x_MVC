#pragma once

#ifndef _ACTIVITYMGR_MVC_H_
#define _ACTIVITYMGR_MVC_H_

#include "cocos2d.h"
#include "Macro.h"
#include "Activity.h"

NS_MVC_BEGIN


// ********************************************************************************
// TODO：Activity栈的维护逻辑需要结合项目进行完善。这里的逻辑并不完整。
// ********************************************************************************

// Activity压栈、弹栈时的操作
enum ActivityStackAction
{
    I_DONT_KNOW = 0,

    DEFAULT_ACTION = I_DONT_KNOW
};

// 管理Activity栈，栈顶Activity为当前Activity
class ActivityMgr : public cocos2d::Ref
{
    // 所有成员私有，只有Facade可以访问，防止滥用。
    friend class Facade;

private:
    ActivityMgr* start();
    ActivityMgr* end();

    // 注册（注销）Activity，只有注册了，Activity才可能被使用
    Activity* getActivity( const ActivityID & );
    bool regActivity( const ActivityID &activityID, Activity* activity );
    void unRegActivity( const ActivityID &activityID );

    // 启动Activity，Activity压栈，当然也有可能Activity已经在栈中
    void startActivity( const ActivityID &, const ActivityStackAction &action = DEFAULT_ACTION );

    // 返回，Activity栈弹栈
    void back();

private:
    ActivityMgr();
    virtual ~ActivityMgr();

private:
    cocos2d::Vector<Activity*>          _activeActivityStack;
    cocos2d::Map<ActivityID, Activity*> _regActivities;
};

NS_MVC_END

#endif
