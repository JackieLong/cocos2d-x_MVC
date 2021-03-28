#pragma once

#ifndef _DATAPROXY_MVC_H_
#define _DATAPROXY_MVC_H_

#include "cocos2d.h"
#include "Macro.h"

NS_MVC_BEGIN

// MVC中的MODEL，注册后由DataProxyMgr管理
class DataProxy : public cocos2d::Ref
{

public:
    virtual void onInit()  = 0;     // 数据初始化

public:
    static void dispatchEvent( const EventNameMVC &, void* data = nullptr );

};

NS_MVC_END

#endif // _DEBUG