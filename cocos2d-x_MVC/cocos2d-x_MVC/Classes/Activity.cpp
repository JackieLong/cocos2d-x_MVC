#include "Activity.h"
#include "Macro.h"
#include "Facade.h"

NS_MVC_BEGIN

Activity::Activity()
    : _active( false )
{

}

Activity::~Activity()
{

}

void Activity::dispatchEvent( const EventNameMVC &eventName, void* data /*= nullptr */ )
{
    FacadeInstance->dispatchEvent( eventName, data );
}

bool Activity::active()
{
    return _active;
}

void Activity::onCreate()
{
    _active = true;
}

void Activity::onResume()
{
}

void Activity::onPause()
{

}

void Activity::onDestroy()
{
    _active = false;
}

NS_MVC_END