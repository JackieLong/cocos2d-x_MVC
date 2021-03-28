#pragma once

#ifndef _DATAPROXYMGR_MVC_H_
#define _DATAPROXYMGR_MVC_H_

#include "cocos2d.h"
#include "DataProxy.h"

NS_MVC_BEGIN

// 管理已注册的DataProxy（Model）
class DataProxyMgr : public cocos2d::Ref
{
    // 所有成员私有，只有Facade可以访问，防止滥用。
    friend class Facade;

private:
    DataProxyMgr* start();
    DataProxyMgr* end();

    DataProxy* getDataProxy( const DataProxyID & );

    // 注册注销DataProxy
    // DataProxy由Activity操控，因此DataProxy的注册也依附于Activity
    bool regDataProxy( const DataProxyID &, const cocos2d::Ref* activity, const DataProxy* );
    void unRegDataProxy( const DataProxyID & );

private:
    DataProxyMgr();
    virtual ~DataProxyMgr();

private:

    //{
    //  {
    //      DataProxyID,
    //      { Activity, DataProxy }
    //  }
    //}
    // 注意维护了容器内Ref元素的引用计数
    RegDataProxies _regDataProxies;
};

NS_MVC_END


#endif


