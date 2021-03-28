#include "ActivityMgr.h"
#include "Macro.h"
#include "Facade.h"

USING_NS_CC;

NS_MVC_BEGIN

ActivityMgr::ActivityMgr()
{

}

ActivityMgr::~ActivityMgr()
{

}

ActivityMgr* ActivityMgr::start()
{

    return this;
}

ActivityMgr* ActivityMgr::end()
{
    // TODO
    // 这里end的逻辑比较复杂，需要结合项目不断完善。

    while( !_activeActivityStack.empty() )
    {
        back();
    }

    return this;
}

Activity* ActivityMgr::getActivity( const ActivityID &activityID )
{
    auto it = _regActivities.find( activityID );
    if( it != _regActivities.end() )
    {
        return it->second;
    }
    return nullptr;
}

bool ActivityMgr::regActivity( const ActivityID &activityID, Activity* activity )
{
    if( activityID == "" || activity == nullptr )
    {
        return false;
    }

    _regActivities.insert( activityID, activity );

    auto eventDispatcher = FacadeInstance->getEventDispatcher();

    if( eventDispatcher )
    {
        eventDispatcher->addListener( activity );
    }

    return true;
}

void ActivityMgr::unRegActivity( const ActivityID &activityID )
{
    if( activityID != "" )
    {
        auto targetActivity = _regActivities.find( activityID );
        if( targetActivity != _regActivities.end() )
        {
            auto eventDispatcher = FacadeInstance->getEventDispatcher();

            if( !eventDispatcher )
            {
                eventDispatcher->removeListener( targetActivity->second );
            }

            _regActivities.erase( activityID );
        }
    }
}

void ActivityMgr::startActivity( const ActivityID &activityID, const ActivityStackAction &action /*= DEFAULT_ACTION */ )
{
    auto it = _regActivities.find( activityID );
    if( it != _regActivities.end() )
    {
        auto targetActivity = it->second;
        if( !targetActivity->active() )
        {
            if( _activeActivityStack.empty() )
            {
                targetActivity->onCreate();
                targetActivity->onResume();
                _activeActivityStack.pushBack( targetActivity );
            }
            else
            {
                targetActivity->onCreate();
                targetActivity->onResume();
                _activeActivityStack.back()->onPause();

                _activeActivityStack.pushBack( targetActivity );
            }
        }
    }
}

void ActivityMgr::back()
{
    if( _activeActivityStack.size() <= 1 )
    {
        Director::getInstance()->end();
    }
    else
    {
        auto topActivity = _activeActivityStack.back();
        auto underTopActivity = _activeActivityStack.at( _activeActivityStack.size() - 2 );

        topActivity->onPause();
        topActivity->onDestroy();
        underTopActivity->onResume();
    }
}

NS_MVC_END

