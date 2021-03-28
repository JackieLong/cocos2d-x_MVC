
#include "Facade.h"
#include <mutex>

USING_NS_CC;
using namespace std;

NS_MVC_BEGIN

static mutex m_mutex;

Facade* Facade::_pInstance = nullptr;

Facade* Facade::getInstance()
{
    if( !_pInstance )
    {
        m_mutex.lock();
        if( !_pInstance )
        {
            _pInstance = new Facade;
        }
        m_mutex.unlock();
    }
    return _pInstance;
}

Facade::Facade()
    : _eventDispatcher( new( nothrow ) EventMVCDispatcher )
    , _activityMgr( new( nothrow ) ActivityMgr )
    , _dataProxyMgr( new( nothrow )DataProxyMgr )
{
}

Facade::~Facade()
{
}

Facade* Facade::start()
{
    _eventDispatcher->start();
    _dataProxyMgr->start();
    _activityMgr->start();

    return this;
}

Facade* Facade::end()
{
    //_eventDispatcher->end();
    //_dataProxyMgr->end();
    //_activityMgr->end();

    Director::getInstance()->end();

    return this;
}

bool Facade::regActivity( const ActivityID &activityID, Activity* activity )
{

    auto pRet = true;

    pRet = pRet && _activityMgr->regActivity( activityID, activity );

    for( auto itPair : activity->onDataProxy() )
    {
        pRet = pRet && regDataProxy( itPair.first, activity, dynamic_cast<const DataProxy*>( itPair.second ) );
    }

    return pRet;
}

void Facade::unRegActivity( const ActivityID &activityID )
{
    _activityMgr->unRegActivity( activityID );
}

bool Facade::regDataProxy( const DataProxyID &dataProxyID, const Ref* activity, const DataProxy* dataProxy )
{
    return _dataProxyMgr->regDataProxy( dataProxyID, activity, dataProxy );
}

void Facade::unRegDataProxy( const DataProxyID &dataProxylID )
{
    _dataProxyMgr->unRegDataProxy( dataProxylID );
}

void Facade::startActivity( const ActivityID &activityID, const ActivityStackAction &action )
{
    _activityMgr->startActivity( activityID, action );
}

void Facade::back()
{
    _activityMgr->back();
}

void Facade::dispatchEvent( const EventNameMVC &eventName, void* data /*= nullptr */ )
{
    _eventDispatcher->dispatchEvent( eventName, data );
}

EventMVCDispatcher* Facade::getEventDispatcher()
{
    return _eventDispatcher;
}

NS_MVC_END
