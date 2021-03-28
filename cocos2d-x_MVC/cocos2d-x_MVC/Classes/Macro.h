#pragma once

#ifndef _MACRO_MVC_H_
#define _MACRO_MVC_H_

typedef std::string EventNameMVC;
typedef std::string ActivityID;
typedef std::string DataProxyID;

#define RegEventMVCListeners std::map<const cocos2d::Ref*, std::map<const EventNameMVC, cocos2d::EventListenerCustom*>>
#define RegDataProxies		 std::map<const DataProxyID, std::pair<const cocos2d::Ref*, const DataProxy*>>

#define FacadeInstance                       Facade::getInstance()
#define GetDataProxy(__T__, __proxyname__)   Facade::getInstance()->getDataProxy< __T__ >( __proxyname__ )
#define GetActivity(__T__, __activityname__) Facade::getInstance()->getActivity< __T__ >( __activityname__ )
#define DispatchEvent(__eventname__, data)   Facade::getInstance()->dispatchEvent( __eventname__, data )

#ifdef __cplusplus
    #define NS_MVC_BEGIN                     namespace mvc {
    #define NS_MVC_END                       }
    #define USING_NS_MVC                     using namespace mvc
    #define NS_MVC                           ::mvc
#else
    #define NS_MVC_BEGIN
    #define NS_MVC_END
    #define USING_NS_MVC
    #define NS_MVC
#endif

#endif // !_CONSTANTMVC_H_

