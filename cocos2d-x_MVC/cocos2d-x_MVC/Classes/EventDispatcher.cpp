
#include "EventDispatcher.h"

using namespace std;
USING_NS_CC;

NS_MVC_BEGIN

EventMVCDispatcher::EventMVCDispatcher()
    : _eventDispatcher( new( nothrow )EventDispatcher )
{

}

EventMVCDispatcher::~EventMVCDispatcher()
{

}

EventMVCDispatcher* EventMVCDispatcher::start()
{
    _eventDispatcher->setEnabled( true );

    return this;
}
EventMVCDispatcher* EventMVCDispatcher::end()
{
    _eventDispatcher->setEnabled( false );

    for( auto it : _listeners )
    {
        removeListener( dynamic_cast<const Activity*>( it.first ) );
    }
    _listeners.clear();

    return this;
}

bool EventMVCDispatcher::addListener( Activity* activity )
{
    if( activity == nullptr || _eventDispatcher == nullptr ) { return false; }

    const std::vector<EventNameMVC> eventNames = activity->onEvent();

    for( const auto &eventName : eventNames )
    {
        if( _listeners.find( activity ) == _listeners.end() )
        {
            _listeners[activity] = {};
        }

        auto activityListenerMap = _listeners[activity];

        auto listener = _eventDispatcher->addCustomEventListener( eventName, [ = ]( EventCustom * eventCustom )
        {
            activity->handleEvent( eventCustom->getEventName(), eventCustom->getUserData() );
        } );

        activityListenerMap[eventName] = listener;
    }

    return true;
}

void EventMVCDispatcher::removeListener( const Activity* activity )
{
    if( activity == nullptr || _eventDispatcher == nullptr ) { return; }

    if( _listeners.find( activity ) != _listeners.end() )
    {
        auto activityListenerMap = _listeners[activity];

        for( auto value : activityListenerMap )
        {
            _eventDispatcher->removeEventListener( value.second );
        }
        activityListenerMap.clear();
    }
}

void EventMVCDispatcher::dispatchEvent( const EventNameMVC &eventName, void* data /*= nullptr */ )
{
    if( _eventDispatcher )
    {
        _eventDispatcher->dispatchCustomEvent( eventName, data );
    }
}

NS_MVC_END