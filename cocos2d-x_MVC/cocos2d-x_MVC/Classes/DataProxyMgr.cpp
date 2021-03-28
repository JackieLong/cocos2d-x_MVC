#include "DataProxyMgr.h"

USING_NS_CC;

NS_MVC_BEGIN

DataProxyMgr::DataProxyMgr()
{

}

DataProxyMgr::~DataProxyMgr()
{

}

DataProxyMgr* DataProxyMgr::start()
{
    return this;
}

DataProxyMgr* DataProxyMgr::end()
{
    for( auto it : _regDataProxies )
    {
        unRegDataProxy( it.first );
    }

    return this;
}

DataProxy* DataProxyMgr::getDataProxy( const DataProxyID &dataProxyID )
{
    auto it = _regDataProxies.find( dataProxyID );
    if( it != _regDataProxies.end() )
    {
        return const_cast<DataProxy*>( it->second.second );
    }
    return nullptr;
}

bool DataProxyMgr::regDataProxy( const DataProxyID &dataProxyID, const Ref* activity, const DataProxy* dataProxy )
{
    if( dataProxyID == "" || dataProxy == nullptr || activity == nullptr )
    {
        return false;
    }

    CCASSERT( _regDataProxies.find( dataProxyID ) == _regDataProxies.end(), "dataProxy already exist" );

    _regDataProxies.insert( { dataProxyID, { activity, dataProxy } } );

    const_cast< DataProxy* >( dataProxy )->retain();
    const_cast< Ref* >( activity )->retain();

    return true;
}

void DataProxyMgr::unRegDataProxy( const DataProxyID &dataProxyID )
{
    if( _regDataProxies.find( dataProxyID ) != _regDataProxies.end() )
    {
        auto itPair = _regDataProxies.at( dataProxyID );

        const_cast< Ref* >( itPair.first )->release();
        const_cast< DataProxy* >( itPair.second )->release();

        _regDataProxies.erase( dataProxyID );
    }
}

NS_MVC_END