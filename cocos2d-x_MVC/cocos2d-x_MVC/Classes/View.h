#pragma once

#ifndef _VIEW_MVC_H_
#define _VIEW_MVC_H_

#include "cocos2d.h"
#include "Macro.h"

NS_MVC_BEGIN


// MVC中的View，负责创建界面，接口供Activity调用
class View
{
public:
    View();
    virtual ~View();

    virtual cocos2d::Node* onCreate() = 0;      // 创建一个界面

public:
    cocos2d::Node* viewRoot;                    // 界面的根节点，用于保存上面创建的界面
};

NS_MVC_END

#endif // _DEBUG