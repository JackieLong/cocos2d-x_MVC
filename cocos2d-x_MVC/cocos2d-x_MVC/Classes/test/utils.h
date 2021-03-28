#pragma once

#ifndef _TEST_UTILS_H_
#define _TEST_UTILS_H_

#include "cocos2d.h"

#define visibleSize     (Director::getInstance()->getVisibleSize())
#define visibleSize2    (Director::getInstance()->getVisibleSize()*0.5)
#define visibleWidth    (Director::getInstance()->getVisibleSize().width)
#define visibleWidth2   (Director::getInstance()->getVisibleSize().width*0.5)
#define visibleHeight   (Director::getInstance()->getVisibleSize().height)
#define visibleHeight2  (Director::getInstance()->getVisibleSize().height*0.5)
#define visibleOrigin   (Director::getInstance()->getVisibleOrigin())
#define visibleOriginX  (Director::getInstance()->getVisibleOrigin().x)
#define visibleOriginY  (Director::getInstance()->getVisibleOrigin().y)
#define visibleSizePos  (Vec2(visibleWidth,visibleHeight))
#define visibleSizePos2 (Vec2(visibleWidth2,visibleHeight2))

#define PI 3.1415926

#endif



