#include "DataProxy.h"
#include "Facade.h"

NS_MVC_BEGIN

void DataProxy::dispatchEvent( const EventNameMVC &eventName, void* data /*= nullptr */ )
{
    DispatchEvent( eventName, data );
}

NS_MVC_END
